#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from geometry_msgs.msg import Twist
from std_msgs.msg import Int32
from math import pi

sp = 0

def callback(msg):
    global sp
    sp = msg.data

rospy.init_node("kame_cntl")
   

rate = 30
linear_speed = 0.5
goal_distance = 2.0
angular_speed = 1.0
goal_angular = pi/2.
linear_duration = goal_distance / linear_speed
angular_duration = goal_angular /angular_speed    
r = rospy.Rate(50)
for i in range(30):
    cmd_vel = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=1)
    sub = rospy.Subscriber('chatter',Int32,callback)
    print(sp)
    move_cmd = Twist()
    if sp < 500:
        move_cmd.linear.x = 0
        move_cmd.angular.z = 0
        ticks = int(linear_duration * rate)
    elif 500 <= sp < 700:
        move_cmd.linear.x = linear_speed
        move_cmd.angular.z = 0
        ticks = int(linear_duration * rate)
    elif sp >= 700:
        move_cmd.linear.x = 0
        move_cmd.angular.z = angular_speed
        ticks = int(angular_duration * rate)
    
    for t in range(ticks):
        cmd_vel.publish(move_cmd)
        r.sleep()        
