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

System Architecture

The navigation framework consists of two major processing layers:

1. Android Edge-AI Layer

Responsible for:

Voice/input command processing
Grid-map generation
A* path planning
DNN-based obstacle classification
Navigation decision making
2. Embedded Robot Layer

Responsible for:

Motor control
Sensor acquisition
Bluetooth communication
Motion execution
Real-time telemetry feedback
