#include <Encoder.h>
#include <ros.h>
#include <std_msgs/Float64.h>
#include "DualMC33926MotorShield.h"


DualMC33926MotorShield md;

Encoder myEnc1(31, 32);
Encoder myEnc2(33, 34);

const float pi = 3.14159;
float r = 0.075;

ros::NodeHandle  nh;

// Real speed variables
std_msgs::Float64 motor_left_speed;
std_msgs::Float64 motor_right_speed;

// Set speed variables
std_msgs::Float64 motor_left_speed_set;
std_msgs::Float64 motor_right_speed_set;

// Callbacks for motor speed

void set_left_speed( const std_msgs::Float64& motor_left_speed_set){
  // Left motor
  md.setM2Speed(map(motor_left_speed_set.data, -1, 1, -400,400));
}

void set_right_speed( const std_msgs::Float64& motor_right_speed_set){
  // Right motor
  md.setM1Speed(map(motor_right_speed_set.data, -1, 1, -400,400));
}


// Real velocity publishers
ros::Publisher motor_left("/left_motor/state", &motor_left_speed);
ros::Publisher motor_right("/right_motor/state", &motor_right_speed);

// Velocity subscribers
ros::Subscriber<std_msgs::Float64> motor_left_controller("/left_motor/control_effort", &set_left_speed );
ros::Subscriber<std_msgs::Float64> motor_right_controller("/right_motor/control_effort", &set_right_speed);

long oldPosition1  = -999, oldPosition2  = -999;
float rads1 = 0.0, rads2 = 0.0;
long newPosition1, newPosition2;


void setup()
{
  md.init();
  // Right motor
  md.setM1Speed(0);
  // Left motor
  md.setM2Speed(0);
  nh.initNode();
  nh.advertise(motor_left);
  nh.advertise(motor_right);
  nh.subscribe(motor_left_controller);
  nh.subscribe(motor_right_controller);
}

void loop()
{
  // Right motor speed
  newPosition1 = myEnc1.read();
  if (newPosition1 != oldPosition1) {
    rads1 = abs(oldPosition1-newPosition1)*(pi/100.0);
    rads1 = rads1*r;
    oldPosition1 = newPosition1;
  }else{
    rads1=0;
  }
  motor_right_speed.data = rads1;
  
  // LEft motor speed
  newPosition2 = myEnc2.read();
  if (newPosition2 != oldPosition2) {
    rads2 = abs(oldPosition2-newPosition2)*(pi/100.0);
    rads2 = rads2*r;
    oldPosition2 = newPosition2;
  }else{
    rads2=0;
  }
  motor_left_speed.data = rads2;
  
  
  motor_left.publish(&motor_left_speed);
  motor_right.publish(&motor_right_speed);
  
  /*
  str_msg.data = hello;
  chatter.publish( &str_msg );

  */
  nh.spinOnce();
  delay(100);
}
