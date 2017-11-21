#!/usr/bin/env python
# license removed for brevity
import rospy
from sensor_msgs.msg import LaserScan

def callback(data): 
	global message
	message = data;
	message.intensities = [1.0, 1.0];


def scan():
	global message                              
	rospy.init_node('scan_node', anonymous=True) 
	message = LaserScan()                             
	
	rospy.Subscriber("/scan",  LaserScan, callback)
	
	pub  = rospy.Publisher('/base_scan', LaserScan, queue_size=10)
	rate = rospy.Rate(10) 
	
	while not rospy.is_shutdown():
		pub.publish(message)
		rate.sleep()

if __name__ == '__main__':
	try:
		scan()
	except rospy.ROSInterruptException:
		pass
