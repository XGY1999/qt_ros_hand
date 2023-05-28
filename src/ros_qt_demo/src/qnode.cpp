/**
 * @file /src/qnode.cpp
 *
 * @brief Ros communication central!
 *
 * @date February 2011
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include <ros/ros.h>
#include <ros/network.h>
#include <string>
#include <std_msgs/String.h>
#include <sstream>
#include "../include/ros_qt_demo/qnode.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace ros_qt_demo {

/*****************************************************************************
** Implementation
*****************************************************************************/

QNode::QNode(int argc, char** argv ) :
	init_argc(argc),
	init_argv(argv)
	{}

QNode::~QNode() {
    if(ros::isStarted()) {
      ros::shutdown(); // explicitly needed since we use ros::start();
      ros::waitForShutdown();
    }
	wait();
}

bool QNode::init() {
  ros::init(init_argc,init_argv,"gelsight_publisher");
	if ( ! ros::master::check() ) {
		return false;
	}
  ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
  chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
	start();
	return true;
}

bool QNode::init(const std::string &master_url, const std::string &host_url) {
	std::map<std::string,std::string> remappings;
	remappings["__master"] = master_url;
	remappings["__hostname"] = host_url;
  ros::init(remappings,"gelsight_publisher");
	if ( ! ros::master::check() ) {
		return false;
	}
  ros::start(); // explicitly needed since our nodehandle is going out of scope.
	ros::NodeHandle n;
	// Add your ros communications here.
  chatter_publisher = n.advertise<std_msgs::String>("chatter", 1000);
	start();
	return true;
}


void QNode::run() {
  ros::NodeHandle nh;                      // 定义ros句柄
  image_transport::ImageTransport it(nh);  //  类似ROS句柄
  image_transport::Publisher image_pub = it.advertise("/cameraImage", 1000);   // 发布话题名/cameraImage
  ros::Rate loop_rate(30);
  cv::Mat imageRaw;  // 原始图像保存
  cv::VideoCapture capture(0);   // 创建摄像头捕获，并打开摄像头0(一般是0,2....)
  if(capture.isOpened() == 0)      // 如果摄像头没有打开
  {
      std::cout << "Read camera failed!" << std::endl;
      return;
  }
  int count = 1;
  image_flag = false;

  while(ros::ok()){
    if (image_flag){
      capture.read(imageRaw);          // 读取当前图像到imageRaw
//      cv::imshow("veiwer", imageRaw);  // 将图像输出到窗口
      sensor_msgs::ImagePtr  msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", imageRaw).toImageMsg();  // 图像格式转换
      msg->header.stamp = ros::Time::now();
      image_pub.publish(msg);         // 发布图像信息
      QImage im = ros_qt_demo::QNode::Mat2QImage(imageRaw);
      Q_EMIT image_val(im);//发送转换完的数据作为信号
      log(Info,std::to_string(count)+std::string("th image is succeed!"));
//      cout << msg->header.stamp << "第" << count <<"张图像发布成功"<<endl;
      // ROS_INFO("第%d张图像发布成功",count);
      ++count;
      ros::spinOnce();                // 官方格式
      loop_rate.sleep();              // 照应上面设置的频率
//      if(cv::waitKey(2) == 27)         // 延时ms,按下ESC键退出(必须要有waitKey，不然是看不到图像的)
//          break;
    }
  }

  //	while ( ros::ok() ) {

  //		std_msgs::String msg;
  //		std::stringstream ss;
  //		ss << "hello world " << count;
  //		msg.data = ss.str();
  //		chatter_publisher.publish(msg);
  //		log(Info,std::string("I sent: ")+msg.data);
  //		ros::spinOnce();
  //		loop_rate.sleep();
  //		++count;
  //	}
	std::cout << "Ros shutdown, proceeding to close the gui." << std::endl;
	Q_EMIT rosShutdown(); // used to signal the gui for a shutdown (useful to roslaunch)
}


void QNode::log( const LogLevel &level, const std::string &msg) {
	logging_model.insertRows(logging_model.rowCount(),1);
	std::stringstream logging_model_msg;
	switch ( level ) {
		case(Debug) : {
				ROS_DEBUG_STREAM(msg);
				logging_model_msg << "[DEBUG] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Info) : {
				ROS_INFO_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Warn) : {
				ROS_WARN_STREAM(msg);
				logging_model_msg << "[INFO] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Error) : {
				ROS_ERROR_STREAM(msg);
				logging_model_msg << "[ERROR] [" << ros::Time::now() << "]: " << msg;
				break;
		}
		case(Fatal) : {
				ROS_FATAL_STREAM(msg);
				logging_model_msg << "[FATAL] [" << ros::Time::now() << "]: " << msg;
				break;
		}
	}
	QVariant new_row(QString(logging_model_msg.str().c_str()));
	logging_model.setData(logging_model.index(logging_model.rowCount()-1),new_row);
	Q_EMIT loggingUpdated(); // used to readjust the scrollbar
}

QImage QNode::Mat2QImage(cv::Mat const& src){
  QImage dest(src.cols, src.rows, QImage::Format_ARGB32);

  const float scale = 255.0;

  if (src.depth() == CV_8U) {
    if (src.channels() == 1) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          int level = src.at<quint8>(i, j);
          dest.setPixel(j, i, qRgb(level, level, level));
        }
      }
    } else if (src.channels() == 3) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          cv::Vec3b bgr = src.at<cv::Vec3b>(i, j);
          dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
        }
      }
    }
  } else if (src.depth() == CV_32F) {
    if (src.channels() == 1) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          int level = scale * src.at<float>(i, j);
          dest.setPixel(j, i, qRgb(level, level, level));
        }
      }
    } else if (src.channels() == 3) {
      for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
          cv::Vec3f bgr = scale * src.at<cv::Vec3f>(i, j);
          dest.setPixel(j, i, qRgb(bgr[2], bgr[1], bgr[0]));
        }
      }
    }
  }

  return dest;
}


}  // namespace ros_qt_demo
