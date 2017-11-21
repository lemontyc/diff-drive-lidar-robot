# Robotics Project: Odom Speed ROS Package
This repository develops a ROS Package designed to implement autonomous navigation using a differential drive robot with ros_nav2d and urg_node (LaserScan)

This package is being developed for the Robotics Project class at Instituto Tecnologico de Monterrey campus Queretaro.

To make it work:

Change permissions for the serial and urg nodes

## Urg
##### sudo chmod 777 /dev/ttyACM0 

## Teensy
##### sudo chmod 777 /dev/ttyACM1

Run these launch files:

##### roslaunch odom_speed hokuyo.launch
##### roslaunch odom_speed launch_motors_pid.launch
##### roslaunch odom_speed nav2d.launch

And that's it ! Everything is now on these launch files :) and yeah ... the /cmd topic now is subscribed to a joy node (PS4 controller)

