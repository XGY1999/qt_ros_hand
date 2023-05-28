#include <iostream>
#include <ros/ros.h>
#include <cv_bridge/cv_bridge.h>  // 将ROS下的sensor_msgs/Image消息类型转化为cv::Mat数据类型
#include <sensor_msgs/image_encodings.h> // ROS下对图像进行处理
#include <image_transport/image_transport.h> // 用来发布和订阅图像信息
#include <opencv2/opencv.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::posix_time;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "image_publisher_one");  // ros初始化，定义节点名为image_publisher_one
    ros::NodeHandle nh;                      // 定义ros句柄
    image_transport::ImageTransport it(nh);  //  类似ROS句柄
    image_transport::Publisher image_pub = it.advertise("/cameraImage", 1);   // 发布话题名/cameraImage

    ros::Rate loop_rate(30);   // 设置刷新频率，Hz

    cv::Mat imageRaw;  // 原始图像保存
    cv::VideoCapture capture(0);   // 创建摄像头捕获，并打开摄像头0(一般是0,2....)
    if(capture.isOpened() == 0)      // 如果摄像头没有打开
    {
        std::cout << "Read camera failed!" << std::endl;  
        return -1;
    }
    int count = 1;
    while(nh.ok())
    {   


        capture.read(imageRaw);          // 读取当前图像到imageRaw      
        // cv::imshow("veiwer", imageRaw);  // 将图像输出到窗口   
        sensor_msgs::ImagePtr  msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", imageRaw).toImageMsg();  // 图像格式转换

        msg->header.stamp = ros::Time::now();
        image_pub.publish(msg);         // 发布图像信息
        cout << msg->header.stamp << "第" << count <<"张图像发布成功"<<endl;
        // ROS_INFO("第%d张图像发布成功",count);
        count++;
        ros::spinOnce();                // 官方格式
        loop_rate.sleep();              // 照应上面设置的频率
        // if(cv::waitKey(2) == 27)         // 延时ms,按下ESC键退出(必须要有waitKey，不然是看不到图像的)
        //     break;
    }
}
