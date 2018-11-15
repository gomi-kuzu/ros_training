#!/usr/bin/env python
# coding: utf-8

import rospy
from sensor_msgs.msg import Image
import cv2,cv_bridge
from std_msgs.msg import Int32
from keras.models import load_model
import numpy as np
import os
import argparse
import tensorflow as tf

graph = tf.get_default_graph()
parser = argparse.ArgumentParser()
parser.add_argument('--zuru', '-z', default=0, type=int)
args = parser.parse_args()

size = 48
print("load model")

if args.zuru ==1:
    model = load_model('./zuru/emo.h5')
else:
    model = load_model('emo.h5')

def emo(img):

    data = np.array(img)
    data = data.astype('float32')
    data = data/255.0
    # print(data)
    # print(type(data))
    # print(data.shape)
    global graph
    data = data.reshape(1, size, size, 1)
    print("感情推定開始")
    with graph.as_default():
        pred = model.predict_classes(data)

    emo = ["Neutral", "Angry", "Fear", "Happy", "Sadness", "Surprise"]
    print(pred, emo[pred[0]])

    return pred[0]



class estimate_emotion:
    def __init__(self):
        self.bridge = cv_bridge.CvBridge()
        self.count = 0
        self.vo = 0
        self.phese = 0
        self.cmd_id = rospy.Publisher('toggle_song', Int32, queue_size=1)
        self.voice_id = rospy.Publisher('toggle_voice', Int32, queue_size=1)
        self.image_sub  = rospy.Subscriber('/face_detection/face_image',Image,self.image_callback)
        self.end_sub = rospy.Subscriber('end',Int32,self.end_callback)
        
    def image_callback(self,msg):
        if self.phese == 0:
            img = self.bridge.imgmsg_to_cv2(msg,desired_encoding='bgr8')
            img_g = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
            #cv2.imshow('img_g',img_g)
            #cv2.waitKey(0)
            #rospy.sleep(2)
            print(self.count)
            if self.count == 1 and self.vo == 0:
                self.voice_id.publish(1)
                self.vo = 1
                rospy.sleep(1)
                
            if img_g.shape[0] > 200:
                self.count = self.count + 1
                if self.count > 3:
                    re_img = cv2.resize(img_g,(size,size))
                    # print(in_data)
                    # print(type(in_data))
                    # print(in_data.shape)
                    #self.voice_id.publish(2)
                    #os.system('aplay ./voice/humhum2.wav')
                    emo_id = emo(re_img)
                    os.system('aplay ./voice/start2.wav')
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
            
    def end_callback(self,msg):
        if msg.data == 1:
            os.system('aplay ./voice/matane.wav')            
            self.count = 0
            self.phese = 0
            self.vo = 0
            rospy.sleep(5)
            
if __name__ == '__main__':
    print("START")
    rospy.init_node('estimate_emotion')
    estimater = estimate_emotion()
    rospy.spin()
