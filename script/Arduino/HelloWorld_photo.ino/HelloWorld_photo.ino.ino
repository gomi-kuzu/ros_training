/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char hello[13] = "hello world!";
int val = 0;

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  val = analogRead(0);
  if(val > 800){
  str_msg.data = hello;
  chatter.publish( &str_msg );
  nh.spinOnce();
  }
  delay(1000);
}
