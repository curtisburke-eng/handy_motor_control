// Include Libraries
#include <Arduino.h>
#include <ros.h>
#include <std_msgs/UInt16.h>
#include "PCA9685.h"

// Delare and Define Variables
#define J1_SERVO_CHANNEL 7
#define J2_SERVO_CHANNEL 8
PCA9685 pwmController(Wire);
PCA9685_ServoEval pwmServo1;
PCA9685_ServoEval pwmServo2;

// Declare ROS backend variable
ros::NodeHandle node_handle;

// Create a fuction that happens each time an event is triggered (ie a message is recieved on the topic)
void joint1_cb(const std_msgs::UInt16& angle)
{
  // Print for debug
  //Serial.print("Angle from msg: ");
  //Serial.println(angle.data);
  
  // Write the message (angle) to the servo using pwm value
  pwmController.setChannelPWM(J1_SERVO_CHANNEL, pwmServo1.pwmForAngle(angle.data));
  
  // Print for debug
  //Serial.print("PWM Value from given angle: ");
  //Serial.println(pwmController.getChannelPWM(J1_SERVO_CHANNEL)); 
}

void joint2_cb(const std_msgs::UInt16& angle)
{
  // Print for debug
  //Serial.print("Angle from msg: ");
  //Serial.println(angle.data);
  
  // Write the message (angle) to the servo using pwm value
  pwmController.setChannelPWM(J2_SERVO_CHANNEL, pwmServo2.pwmForAngle(angle.data));
  
  // Print for debug
  //Serial.print("PWM Value from given angle: ");
  //Serial.println(pwmController.getChannelPWM(J2_SERVO_CHANNEL)); 
}

// Set up ROS Subsriber on the topic of joint1_angle_topic
ros::Subscriber<std_msgs::UInt16> J1_sub("joint1_angle_topic", &joint1_cb);

// Set up ROS Subsriber on the topic of joint2_angle_topic
ros::Subscriber<std_msgs::UInt16> J2_sub("joint2_angle_topic", &joint2_cb);

// Run the set up parameters once
void setup()
{
  //Serial.begin(9600);                 // Begin Serial and Wire interfaces
  Wire.begin();

  pwmController.resetDevices();       // Resets all PCA9685 devices on i2c line
  pwmController.init();               // Initializes module using default totem-pole driver mode, and default disabled phase balancer
  pwmController.setPWMFreqServo();    // 50Hz provides standard 20ms servo phase length
  
  
  node_handle.initNode();               // Initialize the conversation with the ROS backend
  node_handle.subscribe(J1_sub);        // Tell ROS backend that this sub is subscribing to the topic for J1
  node_handle.subscribe(J2_sub);        // Tell ROS backend that this sub is subscribing to the topic for J2

}

void loop()
{
  node_handle.spinOnce();             // SpinOnce instead of Spin because it is in our own loop function
  delay(1);
}