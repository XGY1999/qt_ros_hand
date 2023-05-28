#ifndef __point_find_h__
#define __point_find_h__
#include<opencv2/opencv.hpp>
#include<iostream>
//图片宽度
#define width 640
//图片高度
#define height 480
//调整图片的宽度减少值
#define cut_width 100
//调整图片的高度减少值
#define cut_height 30
//剪裁图片宽度
#define cutrect_width 100
//剪裁图片高度
#define cutrect_height 100
#define start 0
#define end 1340
#define meanful_width 580
#define meanful_height 420
//判断是否在保持追踪的条件下可以初始化跟踪
#define Sum_V_max 100
//判断是否单个点跟踪掉(认为在相邻两帧中移动像素距离大于V_max)
#define V_max 35
//定义最小过滤面积
#define limt_s 0
std::vector<cv::Point> out(cv::Mat&src,std::vector<bool> &out_track);
#endif
