#include <Encoder.h>
#include <ros.h>
#include <std_msgs/Float32MultiArray.h>
#include <geometry_msgs/Twist.h>
#include "DualMC33926MotorShield.h"

DualMC33926MotorShield md;

Encoder myEnc1(31, 32);
Encoder myEnc2(33, 34);

ros::NodeHandle  nh;
const float pi = 3.141516;
float r = 0.075, refsign=0.0, ref = 0.0;
float angle = 0;

std_msgs::Float32MultiArray flt_msg;
ros::Publisher motor_speed("motor_speed", &flt_msg);

void messageCb( const geometry_msgs::Twist& toggle_msg){
  refsign = toggle_msg.linear.x;
  ref=abs(toggle_msg.linear.x);
  angle = toggle_msg.angular.z;
}

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );

long oldPosition1  = -999, oldPosition2  = -999;
float rads1 = 0.0, rads2 = 0.0;

unsigned long t1,t2;

float ki = 1000.8, ki2 = 1000.8;
float kp = 605.5, kp2 = 605.5;

float T=0.1;
float a,b,c;
float a2,b2,c2;
float eant = 0,uant = 0, eact=0, uact=0;
float eant2 = 0,uant2 = 0, eact2=0, uact2=0;
float factor = 100000;


float y_k, u_k = 0;
float y_k2, u_k2 =0;
long newPosition1, newPosition2;
float data[2];


void setup() {
  //Serial.begin(115200);
  md.init();
  md.setM1Speed(0);
  md.setM2Speed(0);
  nh.initNode();
  nh.advertise(motor_speed);
  nh.subscribe(sub);

  
  a = 1*factor;
  b = (kp+(ki*T)/2.)*factor;
  c = (ki*T/2.-kp)*factor;

  a2 = 1*factor;
  b2 = (kp2+(ki2*T)/2.)*factor;
  c2 = (ki2*T/2.-kp2)*factor;
}

void loop() {

  t1 = millis();
  nh.spinOnce();
  newPosition1 = myEnc1.read();
  if (newPosition1 != oldPosition1) {
    rads1 = abs(oldPosition1-newPosition1)*(pi/100.0);
    rads1 = rads1*r;
    oldPosition1 = newPosition1;
  }else{
    rads1=0;
  }
  newPosition2 = myEnc2.read();
  if (newPosition2 != oldPosition2) {
    rads2 = abs(oldPosition2-newPosition2)*(pi/100.0);
    rads2 = rads2*r;
    oldPosition2 = newPosition2;
  }else{
    rads2=0;
  }

  y_k = rads1;
  if( angle != 0 && ref != 0){
    ref = angle * .16;
  }
  eact = ref-y_k;
  uact = (a*uant+b*eact+c*eant)/factor;
  uact = min(uact,400.);
  uact = max(uact,0.);
  
  nh.spinOnce();
  y_k2 = rads2;
  if( angle != 0 && ref != 0){
    ref = angle * -.16;
  }
  eact2 = ref-y_k2;
  uact2 = (a*uant2+b*eact2+c*eant2)/factor;
  uact2 = min(uact2,400.);
  uact2 = max(uact2,0.);
  
  //float w = (uact-uact2)/0.33;
  if(ref == 0 && angle >=0){
    ref = angle * -.16;
    ref = (ref * 400.0)/(0.52*0.32);
    md.setM1Speed(-ref);
    md.setM2Speed(ref);
  }else if(ref == 0 && angle <0){
    ref = angle * .16;
    ref = (ref * 400.0)/(0.52*0.32);
    md.setM1Speed(ref);
    md.setM2Speed(-ref);
    
  }else if(refsign > 0 ){
    md.setM1Speed(uact);
    md.setM2Speed(uact2);
  }else {
    md.setM1Speed(-uact);
    md.setM2Speed(-uact2);
  }
  
   
  

  data[0] = rads1;
  data[1] = rads2;
  flt_msg.data = data;
  flt_msg.data_length = 2;
  motor_speed.publish( &flt_msg );
  uant = uact;
  eant = eact;

  uant2 = uact2;
  eant2 = eact2;

  t2 = millis();
  nh.spinOnce();
  delay(100-(t2-t1));
}

