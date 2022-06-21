#! /usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import Float32

def callback(data):
    vel = Float32()
    vel.data =  data.angular.z
    rospy.loginfo(vel)
    pub.publish(vel)


# Intializes everything
def start():
    global pub
    pub = rospy.Publisher('/vel', Float32, queue_size=10)
    rospy.loginfo('Init TwistDecoder')
    # subscribed to cmd output on topic "cmd_vel"
    rospy.Subscriber("/cmd_vel", Twist, callback)
    # starts the node
    rospy.init_node('TwistDecoder')
    rospy.spin()

if __name__ == '__main__':
    start()

