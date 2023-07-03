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
//        cout<< "image sub is ok"<<endl;
          ofstream ofs;
          ofs.open("/home/xgy/ws_xgy/ws_data/xgy_0702_data/csv/gelsight_01.csv",ios::out|ios::app);
          ofs <<msg->header.stamp <<endl;
          cout << "Get image and save its time."<<endl;
          ofs.close();

//          double t = msg->header.stamp.toSec();//把时间戳转化成浮点型格式
//          ROS_INFO("time:%f\n",t);//输出显示
//          static int count = 0;
//          double image_time = msg->header.stamp.toSec();

//          cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);   // 将图像转换openCV的格式，并输出到窗口
//          cv::imwrite("/home/xgy/xgy_files/xgy_file/picture_for_matlab/"+std::to_string(image_time)+".jpg", cv_bridge::toCvShare(msg,"bgr8")->image);
//          cv::imwrite("/home/xgy/xgy_files/xgy_0111_data/picture/0111_3/sample"+std::to_string(count)+".jpg", cv_bridge::toCvShare(msg,"bgr8")->image);
//          count ++;
//          cv::waitKey(1); // 一定要有waitKey(),要不然是黑框或者无窗口
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert for '%s' to 'bgr8'.", msg->encoding.c_str());
    }

}

void m_hand_Callback(const sensor_msgs::JointState::ConstPtr& msg)
{
      ofstream ofs;
      ofs.open("/home/xgy/ws_xgy/ws_data/xgy_0702_data/csv/hand_01.csv",ios::out|ios::app);

      ofs <<msg->header.stamp <<"," ;//时间
      //当前Load & 目标Load
      for (int i =0;i<12;i++) {
        ofs << msg->effort[i]<<",";
      }
      //当前position & 目标position
      for (int i =0;i<12;i++) {
        ofs << msg->position[i]<<",";
      }
      //B & K
      for (int i =0;i<11;i++) {
        ofs << msg->velocity[i]<<",";
      }
      ofs << msg->velocity[11]<<endl;
      cout << "Get the information of hand and save it."<<endl;
      ofs.close();
}

int main(int argc, char** argv)
{

    ros::init(argc, argv, "image_subscriber_one");   // 注册节点名
    ros::NodeHandle nh; // 注册句柄
    ros::Subscriber hand_sub = nh.subscribe("/hand_info",1,m_hand_Callback);
    image_transport::ImageTransport it(nh); // 注册句柄
    image_transport::Subscriber imageSub = it.subscribe("/cameraImage", 1, imageCallback);  // 订阅/cameraImage话题，并添加回调函数
    ros::spin();  // 循环等待回调函数触发
    return 0;
}
