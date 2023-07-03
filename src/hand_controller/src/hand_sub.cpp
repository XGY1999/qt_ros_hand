#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include <fstream>
using namespace std;

void m_hand_Callback(const sensor_msgs::JointState::ConstPtr& msg)
{
    ofstream ofs;
    ofs.open("/home/xgy/ws_xgy/ws_data/xgy_0702_data/csv/hand_02.csv",ios::out|ios::app);

      ofs <<msg->header.stamp <<","
      << msg->effort[0] << ","
      << msg->effort[1] << ","
      << msg->effort[2] << ","
      << msg->effort[3] << ","
      << msg->effort[4] << ","
      << msg->effort[5] << ","
      << msg->position[0] << ","
      << msg->position[1] << ","
      << msg->position[2] << ","
      << msg->position[3] << ","
      << msg->position[4] << ","
      << msg->position[5] << ","
      << msg->velocity[0] << ","
      << msg->velocity[1] <<endl;
      cout << "Get the information of hand and save it."<<endl;
      ofs.close();

    //打印接受到的消息
//    for(int i=0;i<6;i++){
//        cout<<"header: " << msg->header.seq
//        <<" time: "<< msg->header.stamp
//        <<" name: " << msg->name[i]
//        <<" load: " << msg->effort[i] <<endl;
//    }

//      cout<<"header: " << msg->name[0]
//      <<" time: "<< msg->header.stamp
//      <<" name: " << msg->name[0]
//      <<" load: " << msg->effort[0] <<endl;
}

int main (int argc,char ** argv)
{
    //初始化ROS节点
    ros::init(argc,argv,"hand_listener");
    //创建节点句柄
    ros::NodeHandle n;
    //创建一个subscriber，订阅m_hand话题，注册回调函数m_hand_callback
    ros::Subscriber hand_sub = n.subscribe("/hand_info",1,m_hand_Callback);

    ros::spin();

    return 0;
}
