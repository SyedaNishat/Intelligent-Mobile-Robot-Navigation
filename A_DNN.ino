#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------------- SENSOR PINS ----------------
#define FRONT_TRIG   13
#define FRONT_ECHO   A3

#define RIGHT_TRIG   A2
#define RIGHT_ECHO   A1

#define LEFT_TRIG    A0
#define LEFT_ECHO    9

// ---------------- MOTOR PINS ----------------
#define ML_PWM   6
#define ML_IN1   7
#define ML_IN2   8

#define MR_PWM   11
#define MR_IN1   12
#define MR_IN2   10

// ---------------- VARIABLES ----------------
long duration;
int frontDist, rightDist, leftDist;

String action = "STOP";
char lastCmd = '-';
char currentModeChar = 'A';  // 'A' = A*, 'D' = DNN

unsigned long lastSendTime = 0;
unsigned long lastCommandTime = 0;

// 🔥 MODE DETECTION (NEW)
int stopCount = 0;
int commandCount = 0;
bool isDNNMode = false;

String currentMode = "ASTAR";

// ---------------- SENSOR FUNCTION ----------------
int readDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 30000);
  int dist = duration * 0.034 / 2;

  if (dist == 0) dist = 200;
  return dist;
}

// ---------------- MOTOR CONTROL ----------------

void moveForward()
{
  action = "FORWARD";

  int speed = 70;

  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);

  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);

  analogWrite(ML_PWM, speed);
  analogWrite(MR_PWM, speed);

  delay(500);
  stopRobot();
}

void moveBackward()
{
  action = "BACKWARD";

  int speed = 70;

  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);

  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);

  analogWrite(ML_PWM, speed);
  analogWrite(MR_PWM, speed);
}

// 🔥 90° TURNS (A*)
void turnLeft90()
{
  action = "LEFT_90";

  int speed = 80;

  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);

  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);

  analogWrite(ML_PWM, speed);
  analogWrite(MR_PWM, speed);

  delay(420);
  stopRobot();
}

void turnRight90()
{
  action = "RIGHT_90";

  int speed = 80;

  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);

  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);

  analogWrite(ML_PWM, speed);
  analogWrite(MR_PWM, speed);

  delay(420);
  stopRobot();
}

// 🔥 30° TURNS (DNN)
void turnLeft30()
{
  action = "LEFT_30";

  int speed = 80;

  digitalWrite(ML_IN1, LOW);
  digitalWrite(ML_IN2, HIGH);

  digitalWrite(MR_IN1, HIGH);
  digitalWrite(MR_IN2, LOW);

  analogWrite(ML_PWM, speed);
  analogWrite(MR_PWM, speed);

  delay(140);
  stopRobot();
}

void turnRight30()
{
  action = "RIGHT_30";

  int speed = 80;

  digitalWrite(ML_IN1, HIGH);
  digitalWrite(ML_IN2, LOW);

  digitalWrite(MR_IN1, LOW);
  digitalWrite(MR_IN2, HIGH);

  analogWrite(ML_PWM, speed);
  analogWrite(MR_PWM, speed);

  delay(140);
  stopRobot();
}

void stopRobot()
{
  analogWrite(ML_PWM, 0);
  analogWrite(MR_PWM, 0);
}

// ---------------- OLED DISPLAY ----------------

void showOLED()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("F:");
  display.println(frontDist);

  display.setCursor(0, 12);
  display.print("R:");
  display.println(rightDist);

  display.setCursor(0, 24);
  display.print("L:");
  display.println(leftDist);

  display.setCursor(0, 36);
  display.print("Act:");
  display.println(action);

  display.setCursor(0, 48);
  display.print("RX:");
  display.print(lastCmd);

  display.setCursor(64, 0);
  display.print("M:");
  display.print(currentMode);

  display.display();
}

// ---------------- SETUP ----------------

void setup()
{
  Serial.begin(9600);

  pinMode(FRONT_TRIG, OUTPUT);
  pinMode(FRONT_ECHO, INPUT);

  pinMode(RIGHT_TRIG, OUTPUT);
  pinMode(RIGHT_ECHO, INPUT);

  pinMode(LEFT_TRIG, OUTPUT);
  pinMode(LEFT_ECHO, INPUT);

  pinMode(ML_PWM, OUTPUT);
  pinMode(ML_IN1, OUTPUT);
  pinMode(ML_IN2, OUTPUT);

  pinMode(MR_PWM, OUTPUT);
  pinMode(MR_IN1, OUTPUT);
  pinMode(MR_IN2, OUTPUT);

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setCursor(20, 25);
  display.println("Robot Ready");
  display.display();

  delay(1500);
}

// ---------------- LOOP ----------------

void loop()
{
  if (Serial.available())
  {
    char cmd = Serial.read();

    if (cmd != '\n' && cmd != '\r' && cmd != '#')
    {
      // MODE SWITCH COMMAND
      if (cmd == 'A') {
        currentModeChar = 'A';
        currentMode = "ASTAR"; 
      }

      if (cmd == 'D') {
        currentModeChar = 'D';
        currentMode = "DNN";
      }

      lastCmd = cmd;

      // DISPLAY LOGIC
      if (cmd == 'F') action = "FORWARD";
      else if (cmd == 'B') action = "BACKWARD";
      else if (cmd == 'L') action = (currentModeChar == 'D') ? "LEFT_30" : "LEFT_90";
      else if (cmd == 'R') action = (currentModeChar == 'D') ? "RIGHT_30" : "RIGHT_90";
      else if (cmd == 'S') action = "STOP";
    }
  }

  // EXECUTION
  if (lastCmd == 'F') {
    moveForward();
    lastCmd = 'S';
  }
  else if (lastCmd == 'B') {
    moveBackward();
  }
  else if (lastCmd == 'L') {
    if (currentModeChar == 'D') turnLeft30();
    else turnLeft90();
    lastCmd = 'S';
  }
  else if (lastCmd == 'R') {
    if (currentModeChar == 'D') turnRight30();
    else turnRight90();
    lastCmd = 'S';
  }
  else if (lastCmd == 'S') {
    stopRobot();
  }

  frontDist = readDistance(FRONT_TRIG, FRONT_ECHO);
  delay(20);

  rightDist = readDistance(RIGHT_TRIG, RIGHT_ECHO);
  delay(20);

  leftDist = readDistance(LEFT_TRIG, LEFT_ECHO);
  delay(20);

  showOLED();

  if (millis() - lastSendTime > 200)
  {
    Serial.print("F:");
    Serial.print(frontDist);
    Serial.print(",L:");
    Serial.print(leftDist);
    Serial.print(",R:");
    Serial.print(rightDist);
    Serial.print("#");

    lastSendTime = millis();
  }
}
