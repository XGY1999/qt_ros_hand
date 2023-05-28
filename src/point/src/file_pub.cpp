#include <ros/ros.h>
#include <image_transport/image_transport.h> // 用来发布和订阅图像信息
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>  // 将ROS下的sensor_msgs/Image消息类型转化为cv::Mat数据类型
#include <sensor_msgs/image_encodings.h> // ROS下对图像进行处理
 
int main(int argc, char** argv)
{
  ros::init(argc, argv, "image_publisher");
  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("/cameraImage", 1);
  // std::string image_name="sample";  //创建读取路径字符串
  int n=0;
  while(n<100){
    // std::stringstream ss;                  //创建字符串流，实现数字转化成字符
    // std::string str;
    // ss<<n;
    // ss>>str;
    // image_name=image_name+str;
    std::string image_name = "/home/xgy/XGY/xgy_data/xgy_1220_data/picture/1220_1/sample"+std::to_string(n)+".jpg"; // 读取到具体的文件即本地路径
    cv::Mat image = cv::imread(image_name);                   //利用opencv读取本地图片
    cv::imshow("veiwer", image);  // 将图像输出到窗口
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg(); //将opencv读取到的图片转换成ros中消息类型
  
    ros::Rate loop_rate(5);   //设置发布频率
    // ros::Duration(1).sleep();  //延时3s后开始传送数据

    pub.publish(msg);
    std::cout << "sample"<<n<<"发送成功"<<std::endl;
    n++;
    ros::spinOnce();
    loop_rate.sleep();
     if(cv::waitKey(2) == 27)         // 延时ms,按下ESC键退出(必须要有waitKey，不然是看不到图像的)
       break;
  
}
}
