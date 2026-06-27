# Intelligent Mobile Robot Navigation System Using Deep Neural Networks and A* Path Planning

## Project Overview

This project presents a lightweight hybrid autonomous indoor navigation framework for low-cost mobile robotic platforms operating under limited sensing and computational resources. The proposed system combines A*-based global path planning with Deep Neural Network (DNN)-based obstacle avoidance to achieve safe, adaptive, and real-time indoor navigation.

The framework is implemented using a Car-3 differential-drive robotic platform integrated with ultrasonic sensors, Arduino-based embedded control, Bluetooth communication, and Android-supported edge-AI processing. 

**Key Features**
- Hybrid navigation using A* + DNN
- Real-time obstacle avoidance
- Android edge-AI processing
- Bluetooth-based robot communication
- Lightweight embedded implementation
- Grid-based indoor path planning
- Dynamic obstacle handling
- Low-cost autonomous navigation framework

**System Architecture**

The navigation framework consists of two major processing layers:

**1. Android Edge-AI Layer**

Responsible for:

- Voice/input command processing
- Grid-map generation
- A* path planning
- DNN-based obstacle classification
- Navigation decision making
  
**2. Embedded Robot Layer**

Responsible for:

- Motor control
- Sensor acquisition
- Bluetooth communication
- Motion execution
- Real-time telemetry feedback

**Hardware Components**
| Component | Description |
|---|---|
| Arduino Nano | Main embedded controller |
| HC-SR04 Sensors | Obstacle distance measurement |
| HC-05 Module | Bluetooth communication |
| Differential Drive Motors | Robot locomotion |
| Motor Driver | Motor actuation control |
| Android Smartphone | Edge-AI processing platform |
| Car-3 Chassis | Mobile robot base |

**Software Tools and Technologies**
- Arduino IDE
- Android Studio
- TensorFlow Lite
- Python
- C/C++
- Java/Kotlin
- A* Path Planning Algorithm
- Deep Neural Networks (DNN)

**Navigation Methodology**
1. User selects destination through Android application.
2. Indoor environment is represented as a grid map.
3. A* algorithm computes the optimal global path.
4. Navigation commands are transmitted to the robot.
5. Ultrasonic sensors continuously monitor obstacles.
6. DNN model predicts safe movement actions.
7. Hybrid controller dynamically adjusts robot motion.
8. Robot reaches destination while avoiding obstacles.

**DNN Motion Classes**
The deployed DNN model classifies robot motion into:
- Forward
- Left
- Right
- Backward
- Stop

**Experimental Evaluation**
The system was evaluated in a structured indoor environment under:
- Static obstacle scenarios
- Dynamic obstacle scenarios
- Multiple start-goal combinations

Performance comparison was conducted across:
- A* Navigation
- DNN Navigation
- Hybrid Navigation

**Applications**
- Indoor service robots
- Smart warehouse navigation
- Educational robotics
- Autonomous mobile platforms
- Research in lightweight robotic intelligence

**Future Improvements**
- SLAM integration
- Camera-based perception
- Multi-robot coordination
- Cloud-assisted navigation
- Reinforcement learning-based control

**Research Contribution**

This work demonstrates that reliable indoor autonomous navigation can be achieved using:

- Low-cost sensors
- Lightweight embedded hardware
- Edge-AI processing
- Hybrid navigation intelligence

without requiring expensive sensing or high-performance computing platforms.

**Authors**

Syeda Nishat
Department of Artificial Intelligence and Machine Learning
