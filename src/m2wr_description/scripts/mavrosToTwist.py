#! /usr/bin/env python
import rospy
from geometry_msgs.msg import Twist, TwistStamped

def callback(data):
    twist = Twist()


    twist.linear.x = -data.twist.linear.x
    twist.angular.z = -data.twist.angular.z
    rospy.loginfo(twist)
    pub.publish(twist)


# Intializes everything
def start():
    global pub
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=10)
    rospy.loginfo('Init mavrosToTwist')
    # subscribed to mavros output on topic "mavros/local_position/velocity_local"
    rospy.Subscriber("/mavros/local_position/velocity_local", TwistStamped, callback)
    # starts the node
    rospy.init_node('mavrosToTwist')
    rospy.spin()

if __name__ == '__main__':
    start()

