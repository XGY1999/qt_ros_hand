#include<opencv2/opencv.hpp>
#include<iostream>
#include<math.h>
#include"point_find.h"
using namespace std;
using namespace cv;
class rect_point {
public:
	rect_point(float x, float y, float b, float g, float r,bool edge,int num,double angle_x,double angle_y,float distance) {
		parameter[0] = x;
		parameter[1] = y;
		parameter[2] = b / 255;
		parameter[3] = g / 255;
		parameter[4] = r / 255;
		parameter[5] = edge;
		parameter[6] = num;
		parameter[7] = angle_x;
		parameter[8] = angle_y;
		parameter[9] = distance;
	}
	rect_point(){}
	~rect_point(){}
	double* parameter_return() {
		return parameter;
	}
	void set_parameter(int i,float x){
		if(i<10)
		parameter[i] = x;
		else
		cout<<"cann't set parameters"<<endl;
	}
	void show(){
		for(int i=0;i<10;i++){
			cout<<rect_point::parameter_return()[i]<<",";
		}
		cout<<"\n";

	}
private:
//位置2，颜色3，是否在边缘1，边缘的黑点数量1，黑点夹角tan之和1
	double parameter[10];
};
Mat proccesing(Mat a);
Mat Color2Bin(Mat src);
vector<vector<Point>> findcountours(Mat canny);
Point2f f(vector<Point>at_point);
vector<Point> calculate_center(vector<vector<Point>> &contours);
void draw(Mat& src, vector<Point>centers,vector<bool> out_track);
vector<rect_point>cut_image(Mat src,Mat src_canny,vector<Point>center);
float* color_avrage(Mat k);
vector<Point>find_seq(vector<rect_point>rect1, vector<rect_point>& rect2,vector<bool> &out_track);
vector<Point>new_center(vector<Point>center_old);
double V(rect_point a, rect_point b);
Point2f get_angle(Mat out, Point center,int&num,double&distance);
vector<double> to_standardization(bool is_,vector<rect_point>&rect_j);
static int cnt = 0;
Mat kenel3, kenel2, kenel1;
vector<rect_point> rect_judge0;
vector<rect_point> rect_judge1;
vector<rect_point> rect_judge2;
//mean_x,mean_y,std_x,std_y
vector<double> mean_std;
//用来判断上一次中哪些点是跟踪掉了的

Mat get_image(int i) {
	string p;
  p = "/home/xgy/XGY/xgy_data/xgy_1220_data/picture/1220_1/sample" + to_string(i) + ".jpg";
	return imread(p);
}
vector<Point> out(Mat&src,vector<bool>&t) {
	Mat proc, cut;
	vector<vector<Point>>contour;
	vector<Point>center;
	string p, q;
/*	cout << src.cols << "," << src.rows << endl;*/
					//常态化处理
					//cut = crop_source(src);
				/*	src=crop_source(src);*/
	proc = proccesing(src);
				//imshow("proc",proc);
				//waitKey();
	contour = findcountours(proc);
				//imshow("src", src);
				//waitKey();
	center = calculate_center(contour);
	if (!rect_judge1.empty()) {
					//得到判别矩阵新
		rect_judge2 = cut_image(src,proc,center);
		to_standardization(0,rect_judge2);
		// for(int i=0;i<rect_judge2.size();i++)
		// 	rect_judge2[i].show();
					//计算判断矩阵的相识程度并输出最可能是对应点的新中点集,center输入的是新的center
		center = find_seq(rect_judge1,rect_judge2,t);
		// cout<<center<<endl;
		rect_judge1 = rect_judge2;
	}
	else {
		//排序
		center = new_center(center);
		//得到判别矩形
		rect_judge1 = cut_image(src,proc,center);
		mean_std=to_standardization(1,rect_judge1);
		rect_judge0 = rect_judge1;
		//初始化
		t.resize(rect_judge1.size());
	}
	draw(src, center,t);
	// cv::imshow("out", src);
	// if (rect_judge2.empty()) {
	// 	waitKey(10);
	// }
	// cv::waitKey(10);
	return center;
}
Mat proccesing(Mat a) {
	Mat Bin;
	Mat canny;
	//	imshow("Gassian",Gaussian);
	//	imshow("a",a);
	//	waitKey(10);
	//}
	//二值化
	Bin = Color2Bin(a);
	Canny(Bin, canny, 100, 150);
	//imshow("canny", canny);
	//waitKey();
	return canny;
}
Mat Color2Bin(Mat src) {
	Mat mask, morph, Gaussian;
	int size1 = 8, size2 = 3, size3 = 10;
	int x=1;
	//int x = 3;
	//namedWindow("tiaozeng",WINDOW_FREERATIO);
	//createTrackbar("size1", "tiaozeng", &size1, 255);
	//createTrackbar("size2", "tiaozeng", &size2, 255);
	//createTrackbar("size3", "tiaozeng", &size3, 255);
	//createTrackbar("x", "tiaozeng", &x, 255);
	//while (1) {
	kenel1 = getStructuringElement(MORPH_RECT, Size(size1, size1));
	kenel2 = getStructuringElement(MORPH_RECT, Size(size2, size2));
	kenel3 = getStructuringElement(MORPH_RECT, Size(size3, size3));
	//morphologyEx(src, morph,MORPH_TOPHAT, kenel3);
	//morphologyEx(morph, morph, MORPH_BLACKHAT, kenel3);
	//inRange(morph, lower, upper, mask);
	//GaussianBlur(src, Gaussian, Size(2 * x + 1, 2 * x + 1), 0);
	/*namedWindow("xxx");
	createTrackbar("x","xxx",&x,255);
	while (1) {*/
	GaussianBlur(src, Gaussian, Size(2 * x + 1, 2 * x + 1), 0);
	cvtColor(Gaussian,morph,COLOR_BGR2GRAY);
	threshold(morph, mask, 0, 255,THRESH_OTSU);
	threshold(mask, mask, 0, 255, THRESH_BINARY_INV);
	erode(mask, mask, kenel2);
	dilate(mask, mask, kenel1);
	imshow("mask", mask);
	//imshow("Gaussian", Gaussian);
	////imshow("morph", morph);
	//imshow("src",src);
	//waitKey(10);
	//}
	return mask;
}
vector<vector<Point>> findcountours(Mat canny) {
	vector<vector<Point>>contours;
	vector<vector<Point>>BlackSpace(0);
	findContours(canny, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//drawContours(canny, contours, -1, Scalar(255, 0, 255), -1);
	//imshow("canny", canny);
	//waitKey();
	int j = 0;
	for (int i = 0; i < contours.size(); i++) {
		if (contourArea(contours[i]) > limt_s) {
			BlackSpace.push_back(contours[i]);
		}
	}
	return BlackSpace;
}
vector<Point> calculate_center(vector<vector<Point>>&contours) {
	vector<Point> center_points(0);
	//cout << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++) {
		if (f(contours[i]).x > (width - meanful_width) / 2 && f(contours[i]).x<((width - meanful_width) / 2 + meanful_width) && f(contours[i]).y>(height - meanful_height) / 2 && f(contours[i]).y < ((height - meanful_height) / 2 + meanful_height))
			center_points.push_back(f(contours[i]));
	}
	return center_points;
}
//求中点
Point2f f(vector<Point>at_point) {
	Point2f out;
	double x = 0, y = 0;
	int i;
	for (i = 0; i < at_point.size(); i++) {
		x += at_point[i].x;
		y += at_point[i].y;
	}
	out.x = x / at_point.size();
	out.y = y / at_point.size();
	return out;
}
void draw(Mat& src, vector<Point>centers,vector<bool> out_track) {
	for (int i = 0; i < centers.size(); i++) {
		if(!out_track[i]){
			circle(src, centers[i], 3, Scalar(0, 0, 255), -1);
			string text = to_string(i);
			putText(src, text, Point(centers[i].x, centers[i].y + 5), FONT_HERSHEY_PLAIN, 1, Scalar(0, 255, 0), 1);
		}
		else{
			circle(src, centers[i], 3, Scalar(255, 0, 0), -1);
			string text = to_string(i);
			putText(src, text, Point(centers[i].x, centers[i].y + 5), FONT_HERSHEY_PLAIN, 1, Scalar(255, 0, 0), 1);
		}
	}
}
//返回所有被剪裁掉的图片
vector<rect_point>cut_image(Mat src,Mat src_canny,vector<Point>center) {
	//imshow("src", src);
	//waitKey();
	double distance=0;
	bool is_edge;
	int num=0;
	Point2f angel_direction=Point(0,0);
	vector<rect_point> rect_j(0);
	Mat out;
	Mat out_canny;
	int a[2];
	int b[2];
	for (int i = 0; i < center.size(); i++) {
		is_edge=0;
		a[0] = center[i].y - cutrect_height / 2;
		a[1] = center[i].y + cutrect_height / 2;
		b[0] = center[i].x - cutrect_width / 2;
		b[1] = center[i].x + cutrect_width / 2;
		for (int j = 0; j < 2; j++) {
			if (a[j] < 0){
				a[j] = 0;
				is_edge=1;
			}
			if (a[j] > height){
				a[j] = height;
				is_edge=1;
			}
			if (b[j] < 0){
				b[j] = 0;
				is_edge=1;
			}
			if (b[j] > width){
				b[j] = width;
				is_edge=1;
				}
		}
		if (abs(a[0] - a[1]) != 0 && abs(b[0] - b[1]) != 0) {
			out = src(Range(a[0], a[1]), Range(b[0], b[1]));
			out_canny= src_canny(Range(a[0], a[1]), Range(b[0], b[1]));
			//计算所有tan之和
			angel_direction=get_angle(out_canny,Point((b[1]-b[0])/2,(a[1]-a[0])/2),num,distance);
			//放入特征
			 rect_point rect_jud(center[i].x,center[i].y, color_avrage(out)[0], color_avrage(out)[1], color_avrage(out)[2],is_edge,num,angel_direction.x,angel_direction.y,distance);
			 rect_j.push_back(rect_jud);
			// imshow("out",out);
			// imshow("out_cannt", out_canny);
			// for (int i = 0; i < 10; i++) {
			// 	cout<<rect_jud.parameter_return()[i] << endl;
			// }
			// if(i==60){
			// 	rect_j[i].show();
			// 	imshow("ouot",out);
			// 	waitKey();
			// }
			// cout<<"\n"<<endl;
			// waitKey();

		}
		else
			continue;
		//cout << out[i].cols << out[i].rows << endl;
		//imshow("out", out[i]);
		//waitKey();
	}
	return rect_j;
}
//提取角度特征输入为切割后的小图片和中点坐标
Point2f get_angle(Mat out, Point center,int&num,double&distance){
	vector<vector<Point>>contours;
	Point2f angle=Point(0,0);
	double lenth;
	double x,y;
	//计算轮廓
	contours=findcountours(out);
	//将轮廓数返回给num
	num=contours.size();
	//计算轮廓中黑点的中点
	Point2f temp_Point;
	distance=0;
	for(int i=0;i<num;i++){
		//找中点
		temp_Point=f(contours[i]);
		x=temp_Point.x-center.x;
		y=temp_Point.y-center.y;
		lenth=sqrt(x*x+y*y);
		if(lenth)
		angle=Point(x/lenth,y/lenth);
		distance=distance+lenth;
	}
	distance/=num;
	return Point2f(x,y);
}
//返回图片中白点的质心
float*color_avrage(Mat k) {
	static float color[3];
	for(int i=0;i<3;i++)
		color[i]=0;
	int col = k.cols;
	int row = k.rows;
	int n = 0;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
				color[0] = color[0] + k.at<Vec3b >(i, j)[0];
				color[1] = color[1] + k.at<Vec3b >(i, j)[1];
				color[2] = color[2] + k.at<Vec3b >(i, j)[2];
		}
	}
	color[0] = color[0] / (col * row);
	color[1] = color[1] / (col * row);
	color[2] = color[2] / (col * row);

	/*cout<<Mass_center<<endl;
	circle(k,Mass_center,1,255,-1);
	imshow("asdasdasd", k);
	waitKey();*/
	return color;
}
vector<Point>find_seq(vector<rect_point>rect1, vector<rect_point>& rect2,vector<bool> &out_track) {
	vector<Point>center(0);
	vector<rect_point> rect_temp(0);
	static vector<bool> track(rect1.size());
	static const double singe_v_max=V_max*V_max/(mean_std[2]*mean_std[2])+V_max*V_max/(mean_std[3]*mean_std[3]);
	int point_num1, point_num2;
	double V_min;
	double Sum_V=0;
	bool refind = 0;
	for (int i = 0; i < rect1.size(); i++) {
		refind = 0;
		point_num1 = 0;
		point_num2 = 0;
		//按照初始图像匹配跟踪(初始化)
		V_min = V(rect_judge0[i], rect2[0]);
		for (int k = 0; k < rect_judge0.size(); k++) {
			if (V_min > V(rect_judge0[i], rect2[k])) {
				V_min = V(rect_judge0[i], rect2[k]);
				//temp为最小的点
				point_num1 = k;
			}
		}
		Sum_V += V_min;
			//进行正常匹配重新匹配
			V_min = V(rect1[i], rect2[0]);
			for (int j = 0; j < rect2.size(); j++) {
				if (V_min > V(rect1[i], rect2[j])) {
					V_min = V(rect1[i], rect2[j]);
					//temp为最小的点
					point_num2= j;
				}
				// if (i == 74) {
				// 	cout << "point_num=" << point_num2 << endl;
				// 	cout << "V_min=" << V_min << endl;
				// 	cout << "前一张图：" << "x,y,b,g,r=" << rect1[i].parameter_return()[0] << "," << rect1[i].parameter_return()[1] << "," << rect1[i].parameter_return()[2] << "," << rect1[i].parameter_return()[3] << "," << rect1[i].parameter_return()[4] << endl;
				// 	cout << "后一张图：" << "x,y,b,g,r=" << rect2[point_num2].parameter_return()[0] << "," << rect2[point_num2].parameter_return()[1] << "," << rect2[point_num2].parameter_return()[2] << "," << rect2[point_num2].parameter_return()[3] << "," << rect2[point_num2].parameter_return()[4] << endl;
				// }
			}
			//cout << V_min << endl;

			//判断点是否跟丢只能增加，只有进入cnt之后才能重置
			if(V_min>singe_v_max)
				track.at(i)=true;
			//到达临界值按照默认图匹配
			if (cnt == 5) {
				refind = 1;
				center.push_back(Point(rect2[point_num1].parameter_return()[0]*mean_std[2]+mean_std[0], rect2[point_num1].parameter_return()[1]*mean_std[3]+mean_std[1]));
				rect_temp.push_back(rect2[point_num1]);
				track.at(i)=false;
				// std::cout<<track[i]<<std::endl;
			}
			else {
				center.push_back(Point(rect2[point_num2].parameter_return()[0]*mean_std[2]+mean_std[0], rect2[point_num2].parameter_return()[1]*mean_std[3]+mean_std[1]));
				rect_temp.push_back(rect2[point_num2]);
			}
				// if(V_min>singe_v_max)
				// cout << "i,V_min,singe_v_max="<<i<<"," << V_min<<","<<singe_v_max << endl;
				// cout << "序号：" << point_num << endl;
				// cout << "第"<<i<<"个点=" << endl;
				// cout << "前一张图：" << "x,y,b,g,r=" << rect1[i].parameter_return()[0] << "," << rect1[i].parameter_return()[1] << "," << rect1[i].parameter_return()[2] << "," << rect1[i].parameter_return()[3] << "," << rect1[i].parameter_return()[4] << endl;
				// cout << "后一张图：" << "x,y,b,g,r=" << rect2[i].parameter_return()[0] << "," << rect2[i].parameter_return()[1] << "," << rect2[i].parameter_return()[2] << "," << rect2[i].parameter_return()[3] << "," << rect2[i].parameter_return()[4] << endl;
		}
		//rect2更新
		rect2 = rect_temp;
		Sum_V *= 50;
		if (Sum_V <Sum_V_max)
			cnt++;
		else
			cnt = 0;
		if (refind) {
			cnt = 0;
			// cout << "_________________________" << endl;
		}
		//cout << center << endl;
		// std::cout << Sum_V << endl;
		//cout << cnt << endl;
		// cout << "_________________________" << endl;
		//cv::waitKey();
		out_track=track;
		return center;
	}
vector<Point>new_center(vector<Point>center_old) {
	Point temp;
	for (int i = 0; i < center_old.size() - 1; i++) {
		for (int n = 0; n < center_old.size() - 1 - i; n++) {
			if (center_old[n + 1].x < center_old[n].x) {
				temp = center_old[n];
				center_old[n] = center_old[n + 1];
				center_old[n + 1] = temp;
			}
			else if (center_old[n + 1].x == center_old[n].x) {
				if (center_old[n + 1].y < center_old[n].y) {
					temp = center_old[n];
					center_old[n] = center_old[n + 1];
					center_old[n + 1] = temp;
				}
			}
		}
	}
	return center_old;
}
double V(rect_point a, rect_point b) {
	double V = 0;
	// float rate[5] = {0.5,0.1,0.1,0.1,0.1};
	float rate[6]={1,0,0,0,0,0};
	//位置
	V = V + rate[0] * (a.parameter_return()[0] - b.parameter_return()[0]) * (a.parameter_return()[0] - b.parameter_return()[0]);
	V = V + rate[0] * (a.parameter_return()[1] - b.parameter_return()[1]) * (a.parameter_return()[1] - b.parameter_return()[1]);
	//颜色
	V = V + rate[1] * (a.parameter_return()[2] - b.parameter_return()[2]) * (a.parameter_return()[2] - b.parameter_return()[2]);
	V = V + rate[1] * (a.parameter_return()[3] - b.parameter_return()[3]) * (a.parameter_return()[3] - b.parameter_return()[3]);
	V = V + rate[1] * (a.parameter_return()[4] - b.parameter_return()[4]) * (a.parameter_return()[4] - b.parameter_return()[4]);
	//是否为边缘
	V = V +	rate[2] * (a.parameter_return()[5] - b.parameter_return()[5]) * (a.parameter_return()[5] - b.parameter_return()[5]);
	//旁边黑点数量
	V = V + rate[3] * (a.parameter_return()[6] - b.parameter_return()[6]) * (a.parameter_return()[6] - b.parameter_return()[6]);
	//角度方向之和
	V = V + rate[4] * (a.parameter_return()[7] - b.parameter_return()[7]) * (a.parameter_return()[7] - b.parameter_return()[7]);
	V = V + rate[4] * (a.parameter_return()[8] - b.parameter_return()[8]) * (a.parameter_return()[8] - b.parameter_return()[8]);
	//距离之和
	V = V + rate[5] * (a.parameter_return()[9] - b.parameter_return()[9]) * (a.parameter_return()[9] - b.parameter_return()[9]);
	return sqrt(V);
}
vector<double> to_standardization(bool is_,vector<rect_point>&rect_j){
	vector<double>mean_std;
	static double mean[10]={};
	static double std[10]={};
	if(is_){
	for(int i=0;i<rect_j.size();i++){
		for(int j=0;j<10;j++){
			if(j!=5){
				//先求和
				mean[j]+=rect_j[i].parameter_return()[j];
			}
		}
	}
	//计算均值
	for(int i=0 ;i<10;i++){
		if(i!=5)
		mean[i]/=rect_j.size();
	}
	//计算标准差
	for(int i=0;i<rect_j.size();i++){
		for(int j=0;j<10;j++){
			if(j!=5){
				//先求方差
				std[j]+=(rect_j[i].parameter_return()[j]-mean[j])*(rect_j[i].parameter_return()[j]-mean[j]);
			}
		}
	}
	//计算标准差
	for(int i=0;i<10;i++){
		if(i!=5)
		std[i]=sqrt(std[i]/rect_j.size());
	}
	}
	//计算标准数据
	for(int i=0;i<rect_j.size();i++){
		for(int j=0;j<10;j++){
			if(j!=5){
				rect_j[i].set_parameter(j,(rect_j[i].parameter_return()[j]-mean[j])/std[j]);
			}
		}
	}
	mean_std.push_back(mean[0]);
	mean_std.push_back(mean[1]);
	mean_std.push_back(std[0]);
	mean_std.push_back(std[1]);
	return mean_std;
}


