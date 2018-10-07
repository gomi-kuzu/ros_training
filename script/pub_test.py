#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
from geometry_msgs.msg import Twist

rospy.init_node("kame_cntl")
cmd_vel = rospy.Publisher('/turtle1/cmd_vel', Twist, queue_size=1)
move_cmd = Twist()

rate = 10
linear_speed = 0.5
goal_distance = 3.0
linear_duration = goal_distance / linear_speed
ticks = int(linear_duration * rate)
r = rospy.Rate(50)
move_cmd.linear.x = linear_speed
for t in range(ticks):
    cmd_vel.publish(move_cmd)
    r.sleep()
