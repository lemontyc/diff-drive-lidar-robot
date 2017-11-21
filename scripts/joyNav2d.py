#!/usr/bin/env python
import rospy
from std_msgs.msg import String
from sensor_msgs.msg import Joy
from nav2d_operator.msg import cmd

pub_msg = cmd(0.0,0.0,0)
maxVel = 0.52


def callback(data):
    global pub_msg
    global pub
    pub_msg = cmd(data.axes[1]*maxVel,data.axes[3],0)
    
def node():
	global pub
	rospy.init_node('joyNav2d', anonymous=True)

	rospy.Subscriber("joy", Joy, callback)

	pub = rospy.Publisher('cmd', cmd, queue_size=10)
	rate = rospy.Rate(10) # 10hz
	while not rospy.is_shutdown():
	  pub.publish(pub_msg)
	  rate.sleep()

if __name__ == '__main__':
    try:
        node()
    except rospy.ROSInterruptException:
        pass
