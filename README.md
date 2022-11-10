# handy_motor_control

## Overview
The handy_motor_control repo is part of a multi-repository project to create a life-size, working, Mr. Handy Robot from the Fallout Game series. 
The goal of this project is to have three indivdual 3DOF arms mounted to a central slew drive. Each arm will be capable of both Forward and Inverse Kinematics, will have predetermined locations, and each will be equiped with a different end-effector. 

The Mr. Handy will be able to:
- Choose an arm based on the action/ end-effector needed
- Move to the desired locations or predetermined locations
- Respond using audio files from the game files 

## Hardware Setup
This setup uses:
- Main Compute Module: Small Desktop Computer
  - Ιntel Celeron J4125 Quad Core Processor
  - 8GB RAM
  - 128GB SSD 
- Motor Controller: 
  - Arduino UNO 
  - PCA9685 16 Channel, 12 Bit PWM Servo Driver Board
- Motors: 
  - MG995 Servo Motor (20KG)
  
## This Repo
This repository contains the control logic for servo motors used with Arduino and PCA9685 servo control board.
The joint angles are recieved via serial communication from one of the ROS nodes within the supporting ROS package: [ROS_handy_joint_angles](https://github.com/curtisburke-eng/ROS_handy_joint_angles.git).
The conversion from angle to PWM is handled using the library files from the PCA9685 board. 
