#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "std_msgs/String.h"
#include "sensor_msgs/JointState.h"
#include <fstream>
using namespace std;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try   // 如果转换失败，则提跳转到catch语句
    {
        cout<< "image sub is ok"<<endl;
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert for '%s' to 'bgr8'.", msg->encoding.c_str());
    }

}

void m_hand_Callback(const sensor_msgs::JointState::ConstPtr& msg)
{
  cout << "hand sub is ok" << endl;
  //    ofstream ofs;
  //    ofs.open("/home/xgy/XGY/xgy_data/xgy_0509_data/csv/hand_02.csv",ios::out|ios::app);

  //    ofs <<msg->header.stamp <<","
  //    << msg->effort[0] << ","
  //    << msg->effort[1] << ","
  //    << msg->effort[2] << ","
  //    << msg->effort[3] << ","
  //    << msg->effort[4] << ","
  //    << msg->effort[5] << ","
  //    << msg->position[0] << ","
  //    << msg->position[1] << ","
  //    << msg->position[2] << ","
  //    << msg->position[3] << ","
  //    << msg->position[4] << ","
  //    << msg->position[5] << ","
  //    << msg->velocity[0] << ","
  //    << msg->velocity[1] <<endl;
  //    cout << "Get the information of hand and save it."<<endl;
  //    ofs.close();
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "image_subscriber_one");   // 注册节点名
    ros::NodeHandle nh; // 注册句柄
    ros::Subscriber hand_sub = nh.subscribe("/hand_info",1,m_hand_Callback);
    image_transport::ImageTransport it(nh); // 注册句柄
    image_transport::Subscriber imageSub = it.subscribe("/cameraImage", 1000, imageCallback);  // 订阅/cameraImage话题，并添加回调函数
    ros::spin();  // 循环等待回调函数触发
    return 0;
}
