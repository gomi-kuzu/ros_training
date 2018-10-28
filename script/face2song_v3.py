#!/usr/bin/env python
# coding: utf-8

import rospy
from sensor_msgs.msg import Image
import cv2,cv_bridge
from std_msgs.msg import Int32
from keras.models import load_model
import numpy as np

size = 48


def emo(img):
    model = load_model('emo.h5')

    data = np.array(img)
    data = data.astype('float32')
    data = data/255.0
    # print(data)
    # print(type(data))
    # print(data.shape)

    data = data.reshape(1, size, size, 1)
    
    pred = model.predict_classes(data)

    emo = ["Neutral", "Angry", "Fear", "Happy", "Sadness", "Surprise"]
    print(pred, emo[pred[0]])

    return pred[0]



class estimate_emotion:
    def __init__(self):
        self.bridge = cv_bridge.CvBridge()
        self.count = 0
        self.phese = 0
        self.cmd_id = rospy.Publisher('toggle_song', Int32, queue_size=1)
        self.face_cascade = cv2.CascadeClassifier('/home/inoma/haarcascade_frontalface_default.xml')
        self.image_sub  = rospy.Subscriber('/face_detection/face_image',Image,self.image_callback)
        self.end_sub = rospy.Subscriber('chatter',Int32,self.song_end_callback)
        
    def image_callback(self,msg):
        if self.phese == 0:
            img = self.bridge.imgmsg_to_cv2(msg,desired_encoding='bgr8')
            img_g = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            #cv2.imshow('img_g',img_g)
            #cv2.waitKey(0)
            #rospy.sleep(2)
            print(self.count)
            if img_g.shape[0] > 200:
                self.count = self.count + 1
                if self.count > 4:
                    re_img = cv2.resize(img_g,(size,size))
                    # print(in_data)
                    # print(type(in_data))
                    # print(in_data.shape)
                    emo_id = emo(re_img)
                    self.cmd_id.publish(emo_id)
                    # cv2.imshow('img',re_img)
                    # cv2.waitKey(0)
                    print("send ID >> Arduino")
                    rospy.sleep(2)
                    self.phese = 1

            else:
                self.count = 0
        else:
            pass
            
    def song_end_callback(self,msg):
        if msg.data == 1:
            self.count = 0
            self.phese = 0
            
if __name__ == '__main__':
    rospy.init_node('estimate_emotion')
    estimater = estimate_emotion()
    rospy.spin()
