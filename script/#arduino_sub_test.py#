#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from std_msgs.msg import Int32

def callback(msg):
    print msg.data

rospy.init_node('catter_sub')

sub = rospy.Subscriber('chatter',Int32,callback)
rospy.spin()
