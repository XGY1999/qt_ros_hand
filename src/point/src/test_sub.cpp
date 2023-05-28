#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include "std_msgs/String.h"
#include"point/point.h"
#include<math.h>
#include"point/point_find.h"
std::vector<cv::Point>   Center;
std::vector<bool> out_track;
ros::Publisher imagePub;

void vector_to_msg(std::vector<cv::Point>center){
    //每次调用创建一个新的消息msg
    point::point msg;
    //将center中点的坐标放入到msg中
    for(int i=0;i<center.size();i++){
        msg.x.push_back(center[i].x);
        msg.y.push_back(center[i].y);
        msg.out_of_track.push_back(out_track[i]);
    }
    //发出消息
    imagePub.publish(msg);
}

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try   // 如果转换失败，则提跳转到catch语句
    {

        cv::Mat out_image=cv_bridge::toCvShare(msg, "bgr8")->image;
        // double t = msg->header.stamp.toSec();//把时间戳转化成浮点型格式
        // ROS_INFO("time:%f\n",t);//输出显示
       static int count = 0;
       double image_time = msg->header.stamp.toSec();
       cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);   // 将图像转换openCV的格式，并输出到窗口
        // cv::imwrite("/home/xgy/xgy_files/xgy_file/picture_for_matlab/"+std::to_string(image_time)+".jpg", cv_bridge::toCvShare(msg,"bgr8")->image);
//       cv::imwrite("/home/xgy/xgy_files/xgy_file/picture_for_matlab/1125_5/sample"+std::to_string(count)+".jpg", cv_bridge::toCvShare(msg,"bgr8")->image);
       count ++;

    //收到图片消息之后,处理图片信息得到所有中点坐标数组,center就是所有处理完之后的中点坐标
    // Center=out(cv_bridge::toCvShare(msg, "bgr8")->image,Center);
    Center=out(out_image,out_track);
    //将vector中点的信息转化到msg中;
    // vector_to_msg(Center);
    //发布消息
    cv::imshow("out_image",out_image);
    cv::waitKey(10); // 一定要有waitKey(),要不然是黑框或者无窗口
    }
    catch(cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert for '%s' to 'bgr8'.", msg->encoding.c_str());
    }

}
int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_subscriber_one");   // 注册节点名
    ros::NodeHandle nh; // 注册句柄
    image_transport::ImageTransport it(nh); // 注册句柄
    //创建一个发布者
    imagePub=nh.advertise<point::point>("/points",1);
    image_transport::Subscriber imageSub = it.subscribe("/cameraImage", 1, imageCallback);  // 订阅/cameraImage话题，并添加回调函数
    ros::spin();  // 循环等待回调函数触发
    return 0;
}
