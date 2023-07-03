#include "ros/ros.h"
#include "sensor_msgs/JointState.h"
#include <fstream>

using namespace std;



// void poseCallback(const std::vector<sensor_msgs::JointState::ConstPtr>&  aruco_msg)
void poseCallback(const sensor_msgs::JointState::ConstPtr&  aruco_msg)
{
   

     ofstream ofs;
    ofs.open("/home/harry/aruco_marker_ws/src/pose_estimate/data03.csv",ios::app);
    ofs<<aruco_msg->header.stamp<<","<<aruco_msg->effort[2]<<std::endl;
   
}

int main(int argc,char **argv)
{
    ros::init(argc,argv,"listener");
    ros::NodeHandle n;
    ros::Subscriber aruco_tf_pos_sub =n.subscribe("translation",10,poseCallback);
    ros::spin();
    return 0;
}

