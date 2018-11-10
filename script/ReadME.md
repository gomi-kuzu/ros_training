# おもろまつりアイコン用プログラム動かし方
　　
1. roscore 立ち上げ  
`$ roscore`  
2. webカメノード起動  
`$ rosrun usb_cam usb_cam_node`  
3. openCVアプリ起動  
`$ rosrun image_view image_view image:=/usb_cam/image_raw`  
4. シリアルポートの権限変更  
`$ sudo chmod 666 /dev/ttyACM0`  
5. シリアル通信用のノードを立てる  
`$ rosrun rosserial_python serial_node.py /dev/ttyACM0`  
6. 喋らせる用プログラム起動  
`$ python voice.py`  
7. mainプログラム起動  
`$ python face2song_v4.py`  
