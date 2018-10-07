#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle nh;

void messageCb( const std_msgs::Int32& toggle_msg) {
  Serial.println(toggle_msg.data);
  if(toggle_msg.data==0){
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  }else if (toggle_msg.data==1){
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  }else if (toggle_msg.data==2){
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  }else if (toggle_msg.data==3){
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, LOW);
  }else{
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  }
}

ros::Subscriber<std_msgs::Int32> sub("toggle_led", &messageCb );

void setup(){
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  nh.initNode();
  nh.subscribe(sub);
}

void loop(){
  nh.spinOnce();
  delay(1);
}
