#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
import cv2,cv_bridge


def image_callback(msg):
    ima = cv_bridge.CvBridge().imgmsg_to_cv2(msg,desired_encoding='bgr8')
    ima_g = cv2.cvtColor(ima, cv2.COLOR_BGR2GRAY)
    cv2.imshow("window",ima_g)
    cv2.waitKey(3)

rospy.init_node('follower')
image_sub  = rospy.Subscriber('/usb_cam/image_raw',Image,image_callback)
rospy.spin()
