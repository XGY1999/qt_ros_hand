/*
 * Copyright (c) 2019 Flight Dynamics and Control Lab
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>
#include <iostream>
#include <cstdlib>
#include <ros/ros.h> //惯例第一头文件，ROS的源码
#include "sensor_msgs/JointState.h"
#include <std_msgs/Float64.h> //传递的消息类型文件，根据实际需要选择对应的消息类型头文件
#include <iostream>
#include <fstream>



using namespace std;






namespace {
const char* about = "Pose estimation of ArUco marker images";
const char* keys  =
        "{d        |16    | dictionary: DICT_4X4_50=0, DICT_4X4_100=1, "
        "DICT_4X4_250=2, DICT_4X4_1000=3, DICT_5X5_50=4, DICT_5X5_100=5, "
        "DICT_5X5_250=6, DICT_5X5_1000=7, DICT_6X6_50=8, DICT_6X6_100=9, "
        "DICT_6X6_250=10, DICT_6X6_1000=11, DICT_7X7_50=12, DICT_7X7_100=13, "
        "DICT_7X7_250=14, DICT_7X7_1000=15, DICT_ARUCO_ORIGINAL = 16}"
        "{h        |false | Print help }"
        "{l        |      | Actual marker length in meter }"
        "{v        |<none>| Custom video source, otherwise '0' }"
        "{h        |false | Print help }"
        "{l        |      | Actual marker length in meter }"
        "{v        |<none>| Custom video source, otherwise '0' }"
        ;
}





int main(int argc, char **argv)
{
    //每一个节点只有一个main函数

    ros::init(argc, argv, "pose_estimate_pub_node");    // 初始化这个节点， 双引号中的是节点名， 可以通过.launch文件启动时更改节点名（不建议）
    ros::NodeHandle n; 			                        // 创建一个与ROS系统对话的pulisher对象（n是随意命名的）
    ros::Publisher aruco_tf_pos = n.advertise<sensor_msgs::JointState>("translation", 1000);   //Topic is translation
    ros::Rate loop_rate(30);                            //设置发布信息的间隔时间，如果不设置，系统会尽全力去输出，有多快就多快的去发布信息，很多时候是没必要的，浪费CPU
    sensor_msgs::JointState aruco_msg;





    cv::CommandLineParser parser(argc, argv, keys);
    parser.about(about);

    if (argc < 2) {
        parser.printMessage();
        return 1;
    }

    if (parser.get<bool>("h")) {
        parser.printMessage();
        return 0;
    }

    int dictionaryId = parser.get<int>("d");
    float marker_length_m = parser.get<float>("l");
    int wait_time = 10;

    if (marker_length_m <= 0) {
        std::cerr << "marker length must be a positive value in meter"
                  << std::endl;
        return 1;
    }

    cv::String videoInput = "0";
    cv::VideoCapture in_video;
    if (parser.has("v")) {
        videoInput = parser.get<cv::String>("v");
        if (videoInput.empty()) {
            parser.printMessage();
            return 1;
        }
        char* end = nullptr;
        int source = static_cast<int>(std::strtol(videoInput.c_str(), &end, \
            10));
        if (!end || end == videoInput.c_str()) {
            in_video.open(videoInput); // url
        } else {
            in_video.open(source); // id
        }
    } else {
        in_video.open(0);
    }

    if (!parser.check()) {
        parser.printErrors();
        return 1;
    }

    if (!in_video.isOpened()) {
        std::cerr << "failed to open video input: " << videoInput << std::endl;
        return 1;
    }

    cv::Mat image, image_copy;
    cv::Mat camera_matrix, dist_coeffs;
    std::ostringstream vector_to_marker;

    cv::Ptr<cv::aruco::Dictionary> dictionary =
        cv::aruco::getPredefinedDictionary( \
        cv::aruco::PREDEFINED_DICTIONARY_NAME(dictionaryId));

    // cv::FileStorage fs("../../detector_params.yml", cv::FileStorage::READ);
    // cv::FileStorage fs("../../calibration_params.yml", cv::FileStorage::READ);
    // cv::FileStorage fs("/home/scu-robot/dsk_ws/aruco-markers/calibration_params_p15v.yml", cv::FileStorage::READ);///home/scu-robot/aruco_ros_ws/src
    cv::FileStorage fs("/home/xgy/XGY/xgy_lab/kunkun/aruco_ros_ws/src/calibration_params.yml", cv::FileStorage::READ);///home/scu-robot/aruco_ros_ws/src
    fs["camera_matrix"] >> camera_matrix;                                                           //////////////home/scu-robot/dsk_ws/aruco-markers       /home/harry/aruco_marker_ws
    fs["distortion_coefficients"] >> dist_coeffs;

    std::cout << "camera_matrix\n" << camera_matrix << std::endl;
    std::cout << "\ndist coeffs\n" << dist_coeffs << std::endl;


    double a1, a2, a3, b1, b2, b3, c=100.00, d=100.00, precesion=0.01, f1, f2;

    while (in_video.grab())
    {
        in_video.retrieve(image);
        image.copyTo(image_copy);
        std::vector<int> ids;
        std::vector<std::vector<cv::Point2f> > corners;
        cv::aruco::detectMarkers(image, dictionary, corners, ids);

        // if at least one marker detected
        if (ids.size()>0)
        {
            cv::aruco::drawDetectedMarkers(image_copy, corners, ids);
            std::vector<cv::Vec3d> rvecs, tvecs;
            cv::aruco::estimatePoseSingleMarkers(corners, marker_length_m,
                    camera_matrix, dist_coeffs, rvecs, tvecs);

             if(ids.size()==1)
           {
                aruco_msg.header.stamp=ros::Time::now();

                aruco_msg.effort.resize(3);
                aruco_msg.effort[2]=1;
                std::cout<<"time"<<aruco_msg.header.stamp<<"\t是否掉落:"<<aruco_msg.effort[2]<<
                         std::endl;

                //  ofstream ofs;
                //  ofs.open("/home/harry/aruco_marker_ws/src/pose_estimate/data.csv",ios::app);
                //  ofs<<aruco_msg.header.stamp<<","<<aruco_msg.effort[2]<<std::endl;
            }

           if(ids.size()==2)
           {
                aruco_msg.header.stamp=ros::Time::now();
                aruco_msg.position.resize(9);
                aruco_msg.position[0] = tvecs[0](0);
                aruco_msg.position[1] = tvecs[0](1);
                aruco_msg.position[2] = tvecs[0](2);

                aruco_msg.position[3] = tvecs[1](0);
                aruco_msg.position[4] = tvecs[1](1);
                aruco_msg.position[5] = tvecs[1](2);

                a1=aruco_msg.position[0]-aruco_msg.position[3]; //x1
                a2=aruco_msg.position[1]-aruco_msg.position[4]; //y1
                a3=aruco_msg.position[2]-aruco_msg.position[5]; //z1

                aruco_msg.effort.resize(3);
                aruco_msg.effort[0]=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));    //distance between id0 and id1
                aruco_msg.effort[2]=0;

                aruco_msg.name.resize(3);
                aruco_msg.name[0]="stable";

                if (abs(aruco_msg.effort[0]-c)>precesion)
                {
                    aruco_msg.effort[2]=1;

                    aruco_msg.name[0]="fall!!!";
                }

                // std::cout<<"2haoweizi:"<<aruco_msg.position[3]<<aruco_msg.position[4]<<aruco_msg.position[5]<<std::endl;
                std::cout<<"time"<<aruco_msg.header.stamp<<"\tdist_A:"<<aruco_msg.effort[0]<<"\tinit_A:"<<c<<"\t是否掉落:"<<aruco_msg.effort[2]<<"\tcondition:"<<aruco_msg.name[0]<<
                         std::endl;

                //  ofstream ofs;
                //  ofs.open("/home/harry/aruco_marker_ws/src/pose_estimate/data.csv",ios::app);
                //  ofs<<aruco_msg.header.stamp<<","<<aruco_msg.effort[2]<<std::endl;
            }


             if(ids.size()==3)
           {
                aruco_msg.header.stamp=ros::Time::now();
                aruco_msg.position.resize(9);
                aruco_msg.position[0] = tvecs[0](0);
                aruco_msg.position[1] = tvecs[0](1);
                aruco_msg.position[2] = tvecs[0](2);

                aruco_msg.position[3] = tvecs[1](0);
                aruco_msg.position[4] = tvecs[1](1);
                aruco_msg.position[5] = tvecs[1](2);

                aruco_msg.position[6] = tvecs[2](0);
                aruco_msg.position[7] = tvecs[2](1);
                aruco_msg.position[8] = tvecs[2](2);



                a1=aruco_msg.position[0]-aruco_msg.position[3]; //x1
                a2=aruco_msg.position[1]-aruco_msg.position[4]; //y1
                a3=aruco_msg.position[2]-aruco_msg.position[5]; //z1

                b1=aruco_msg.position[0]-aruco_msg.position[6]; //x2
                b2=aruco_msg.position[1]-aruco_msg.position[7]; //y2
                b3=aruco_msg.position[2]-aruco_msg.position[8]; //z2

                aruco_msg.effort.resize(3);
                aruco_msg.effort[0]=sqrt(pow(a1,2)+pow(a2,2)+pow(a3,2));    //distance between id0 and id1
                aruco_msg.effort[1]=sqrt(pow(b1,2)+pow(b2,2)+pow(b3,2));    //distance between id0 and id2
                aruco_msg.effort[2]=0;

                f1=aruco_msg.effort[0]-c;
                f2=aruco_msg.effort[1]-d;
                aruco_msg.name.resize(3);
                aruco_msg.name[0]="stable";

                if ((abs(aruco_msg.effort[0]-c)>precesion)&&(abs(aruco_msg.effort[1]-d)>precesion))
                {
                    aruco_msg.effort[2]=1;

                    aruco_msg.name[0]="fall!!!";
                }

                std::cout<<"time"<<aruco_msg.header.stamp<<"\tdist_A:"<<aruco_msg.effort[0]<<"\tdist_B:"<<aruco_msg.effort[1]<<"\tinit_A:"<<c<<"\tinit_B:"<<d<<"\t是否掉落:"<<aruco_msg.effort[2]<<"\tcondition:"<<aruco_msg.name[0]<<
                         std::endl;
                //  ofstream ofs;
                //  ofs.open("/home/harry/aruco_marker_ws/src/pose_estimate/data.csv",ios::app);
                //  ofs<<aruco_msg.header.stamp<<","<<aruco_msg.effort[2]<<std::endl;
            }
                // std::cout<<"time:"<<aruco_msg.header.stamp<<"pos_x1:"<<aruco_msg.position[0]<<"pos_y1:"<< aruco_msg.position[1]<<"pos_z1:"<<aruco_msg.position[2]
                //          <<"pos_x2:"<<aruco_msg.position[3]<<"pos_y2:"<< aruco_msg.position[4]<<"pos_z2:"<<aruco_msg.position[5]
                //          <<"pos_x3:"<<aruco_msg.position[6]<<"pos_y3:"<< aruco_msg.position[7]<<"pos_z3:"<<aruco_msg.position[8]<< std::endl;

                // 写出数据流到文件
                //  ofstream ofs;
                //  ofs.open("/home/scu-robot/aruco_ros_ws/src/pose_estimate/data.csv",ios::app);
                // ofs<<"time:"<<aruco_msg.header.stamp<<"\tpos_x1:"<<aruco_msg.position[0]<<"pos_y1:"<< aruco_msg.position[1]<<"pos_z1:"<<aruco_msg.position[2]
                //          <<"\tpos_x2:"<<aruco_msg.position[3]<<"pos_y2:"<< aruco_msg.position[4]<<"pos_z2:"<<aruco_msg.position[5]
                //          <<"\tpos_x3:"<<aruco_msg.position[6]<<"pos_y3:"<< aruco_msg.position[7]<<"pos_z3:"<<aruco_msg.position[8]<< std::endl;

                //  ofs<<"time"<<aruco_msg.header.stamp<<"\tdistance_of_01::"<<aruco_msg.effort[0]<<"\tdistance_of_02::"<<aruco_msg.effort[1]<<std::endl;

                    aruco_tf_pos.publish(aruco_msg);
                    ros::spinOnce();
                    loop_rate.sleep();

                    // Draw axis for each marker
                    for(int i=0; i < ids.size(); i++)
                    {
                        cv::aruco::drawAxis(image_copy, camera_matrix, dist_coeffs,
                                rvecs[i], tvecs[i], 0.1);

                        // This section is going to print the data for all the detected
                        // markers. If you have more than a single marker, it is
                        // recommended to change the below section so that either you
                        // only print the data for a specific marker, or you print the
                        // data for each marker separately.
                        vector_to_marker.str(std::string());
                        vector_to_marker << std::setprecision(4)
                                        << "x: " << std::setw(8) << tvecs[0](0);
                        cv::putText(image_copy, vector_to_marker.str(),
                                    cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.6,
                                    cv::Scalar(0, 252, 124), 1, CV_AVX);

                        vector_to_marker.str(std::string());
                        vector_to_marker << std::setprecision(4)
                                        << "y: " << std::setw(8) << tvecs[0](1);
                        cv::putText(image_copy, vector_to_marker.str(),
                                    cv::Point(10, 50), cv::FONT_HERSHEY_SIMPLEX, 0.6,
                                    cv::Scalar(0, 252, 124), 1, CV_AVX);

                        vector_to_marker.str(std::string());
                        vector_to_marker << std::setprecision(4)
                                        << "z: " << std::setw(8) << tvecs[0](2);
                        cv::putText(image_copy, vector_to_marker.str(),
                                    cv::Point(10, 70), cv::FONT_HERSHEY_SIMPLEX, 0.6,
                                    cv::Scalar(0, 252, 124), 1, CV_AVX);

                        //
                        vector_to_marker.str(std::string());
                        vector_to_marker <<std::setprecision(4)
                                        <<"conditon:"<< std::setw(8)<<aruco_msg.name[0];
                        cv::putText(image_copy, vector_to_marker.str(),
                                    cv::Point(10, 90), cv::FONT_HERSHEY_SIMPLEX, 0.6,
                                    cv::Scalar(255, 0, 0), 1, CV_AVX);
                }
            // }
        }

        imshow("Pose estimation", image_copy);
        char key = (char)cv::waitKey(wait_time);
        if (key == 27)
           { break;}
        if(key==103)
        {
             if(ids.size()==3)
             {
            c=aruco_msg.effort[0];
            d=aruco_msg.effort[1];
             }
              if(ids.size()==2)
              {
                  c=aruco_msg.effort[0];
              }
              if(ids.size()==1)
              {
                aruco_msg.effort[2]=1;
              }
        }
    }

    in_video.release();

    return 0;
}
