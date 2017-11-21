#!/usr/bin/env python
# license removed for brevity
import rospy
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Float32

def callback(data): 
	global message
	intesity
	message = data;


def inten():
	global message                              
	rospy.init_node('intensity_node', anonymous=True) 
	message = LaserScan()                             
	
	rospy.Subscriber("/base_scan",  LaserScan, callback)
	
	pub  = rospy.Publisher('/scan', LaserScan, queue_size=10)
	rate = rospy.Rate(10) 
	
	while not rospy.is_shutdown():
		pub.publish(message)
		rate.sleep()

if __name__ == '__main__':
	try:
		inten()
	except rospy.ROSInterruptException:
		pass
