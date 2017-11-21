#!/usr/bin/env python
# license removed for brevity
import rospy
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist

def callback(data): 
	global message
	
	message.linear.x = data.twist.twist.linear.x
	message.linear.y = 0.0
	message.linear.z = 0.0
	
	message.angular.z = data.twist.twist.angular.z
	message.angular.y = 0.0
	message.angular.x = 0.0


def os_node():
	global message                              
	rospy.init_node('os_node', anonymous=True) 
	message = Twist()                             
	
	rospy.Subscriber("/odom",  Odometry, callback)
	
	pub  = rospy.Publisher('/set_speed', Twist, queue_size=10)
	rate = rospy.Rate(10) 
	
	while not rospy.is_shutdown():
		pub.publish(message)
		rate.sleep()

if __name__ == '__main__':
	try:
		os_node()
	except rospy.ROSInterruptException:
		pass
