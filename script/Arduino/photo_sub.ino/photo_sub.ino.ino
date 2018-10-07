
#include <ros.h>
#include <std_msgs/Int32.h>

ros::NodeHandle  nh;

std_msgs::Int32 int_msg;
ros::Publisher chatter("chatter", &int_msg);

int val = 0;

void setup()
{
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
  val = analogRead(0);
  int_msg.data = val;
  chatter.publish( &int_msg );
  nh.spinOnce();
  delay(1000);
}
