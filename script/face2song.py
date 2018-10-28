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

    # img = cv2.imread("./kao.jpg",0)
    # img = cv2.resize(img,(size, size))

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
        self.cmd_id = rospy.Publisher('toggle_song', Int32, queue_size=1)
        self.face_cascade = cv2.CascadeClassifier('/home/inoma/haarcascade_frontalface_default.xml')
        self.image_sub  = rospy.Subscriber('/face_detection/face_image',Image,self.image_callback)
        self.end_sub = rospy.Subscriber('chatter',Int32,self.song_end_callback)
        
    def image_callback(self,msg):
        img = self.bridge.imgmsg_to_cv2(msg,desired_encoding='bgr8')
        img_g = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        #cv2.imshow('img_g',img_g)
        #cv2.waitKey(0)
        #rospy.sleep(2)
        print(self.count)
        if img_g.shape[0] > 200:
            self.count = self.count + 1
            if self.count > 5:
                re_img = cv2.resize(img_g,(size,size))
                # in_data = np.array(re_img)
                # in_data = in_data.astype('float32')
                # in_data = in_data/255.0
                # print(in_data)
                # print(type(in_data))
                # print(in_data.shape)

                # in_data = data.reshape(1, size, size, 1)

                # model = load_model('emo.h5')
                # K.clear_session()
                # graph = tf.get_default_graph()
                # pred = model.predict_classes(in_data)
                # emo = ["Neutral", "Angry", "Fear", "Happy", "Sadness", "Surprise"]
                # print(pred, emo[pred[0]])
                # cv2.imwrite("./kao.jpg",re_img)
                emo_id = emo(re_img)
                self.cmd_id.publish(emo_id)
                # cv2.imshow('img',re_img)
                # cv2.waitKey(0)
                self.count = 0

        else:
            self.count = 0
            
            
    def song_end_callback(self,msg):
        if msg.data == 1:
            pass
            
if __name__ == '__main__':
    
    rospy.init_node('estimate_emotion')
    estimater = estimate_emotion()
    rospy.spin()
