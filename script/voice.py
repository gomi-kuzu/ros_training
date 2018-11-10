#!/usr/bin/env python
import rospy
import os
from std_msgs.msg import Int32


def callback(msg):
    if msg.data == 1:
        os.system('aplay ./voice/setsumei.wav')
    if msg.data == 2:
        os.system('aplay ./voice/humhum.wav')

def song_end_callback(msg):
    if msg.data == 1:
        os.system('aplay ./voice/end.wav')
    if msg.data ==2:
        os.system('aplay ./voice/shaken.wav')
        
    end_id.publish(1)
        
rospy.init_node('voice')
voice_id_sub  = rospy.Subscriber('toggle_voice',Int32,callback)
end_sub = rospy.Subscriber('chatter',Int32,song_end_callback)
end_id = rospy.Publisher('end', Int32, queue_size=1)


rospy.spin()
