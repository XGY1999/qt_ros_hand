#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/exact_time.h>
#include "ros/ros.h"
#include <sensor_msgs/Image.h>
#include "sensor_msgs/JointState.h"
#include <fstream>
using std::cout;
using std::endl;

#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>

using namespace sensor_msgs;
using namespace message_filters;

void callback(const sensor_msgs::ImageConstPtr& image_msg, const sensor_msgs::JointState::ConstPtr& hand_msg)
{
  // Solve all of perception here...
  std::ofstream ofs_01;
  ofs_01.open("/home/xgy/XGY/xgy_data/xgy_0509_data/csv/gelsight_03.csv",std::ios::out|std::ios::app);
  std::ofstream ofs_02;
  ofs_02.open("/home/xgy/XGY/xgy_data/xgy_0509_data/csv/hand_03.csv",std::ios::out|std::ios::app);

  ros::Time right_now = ros::Time::now();

  ofs_01 <<right_now <<endl;
  cout << "Get image and save its time."<<endl;
  ofs_02 <<right_now <<","
  << hand_msg->effort[0] <<endl;
  cout << "Get the information of hand and save it."<<endl;

  ofs_01.close();
  ofs_02.close();
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "sync_node");

  ros::NodeHandle nh;
  message_filters::Subscriber<Image> image_sync_sub(nh, "/cameraImage", 1);
  message_filters::Subscriber<JointState> hand_sync_sub(nh,"/hand_info",1);

  message_filters::TimeSynchronizer<Image, JointState> sync(image_sync_sub, hand_sync_sub, 10);
  sync.registerCallback(boost::bind(&callback, _1, _2));

  ros::spin();

  return 0;
}
