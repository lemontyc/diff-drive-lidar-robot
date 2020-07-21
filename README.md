 Simple ifferential-drive autonomous lidar  platform.

> This includes the necessary nodes for a simple 2 wheel autonomous robot.

This repository develops a ROS Package designed to implement autonomous navigation using a differential drive robot with ros_nav2d and urg_node (LaserScan).

## Requirements

* 2 wheel robot with an Arduino
* 2 motors with encoders
* Hokuyo URG-04LX-UG01 Lidar Scanner
* A laptop or Raspberry Pi with ROS Kinetic installed

## Running

1. Change permissions for the serial (Arduino) and urg (LiDAR) nodes:
```bash
# Lidar
sudo chmod 777 /dev/ttyACM0 
# Arduino
sudo chmod 777 /dev/ttyACM1
```
2. Load **Encoders_speed.ino** on an arduno-compatible microcontroller.

3. Source setup.bash and run launch files:
Run launch files:
```bash
roslaunch odom_speed hokuyo.launch
roslaunch odom_speed launch_motors_pid.launch
roslaunch odom_speed nav2d.launch
```

And that's it! Everything is now on these launch files :) and yeah ... the /cmd topic now is subscribed to a joy node (PS4 controller)



# Meta
Fabián G. [GitHub](https://github.com/fgomezgo)
Luis M.  [GitHub](https://github.com/lemontyc)
Naomi T.


This package was developed for the **TE3045-Robotics Project** course at **Instituto Tecnológico de Monterrey campus Querétaro**.

