#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Image
import cv2,cv_bridge
from std_msgs.msg import Int32

class face_count:
    def __init__(self):
        self.bridge = cv_bridge.CvBridge()
        self.image_sub  = rospy.Subscriber('/usb_cam/image_raw',Image,self.image_callback)
        self.cmd_id = rospy.Publisher('toggle_led', Int32, queue_size=1)
        
    def image_callback(self,msg):
        img = self.bridge.imgmsg_to_cv2(msg,desired_encoding='bgr8')
        img_g = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        face_cascade = cv2.CascadeClassifier('/home/inoma/haarcascade_frontalface_default.xml')
        faces = face_cascade.detectMultiScale(img_g,minNeighbors=30)
        face_c = len(faces)
        self.cmd_id.publish(face_c)
        print(face_c)
        for (x,y,w,h) in faces:
            cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,0),2)

        cv2.imshow('img',img)
        cv2.waitKey(0)

if __name__ == '__main__':
    
    rospy.init_node('face_count')
    counter = face_count()
    rospy.spin()
