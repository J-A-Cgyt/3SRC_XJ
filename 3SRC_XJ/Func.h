#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

#ifndef BEFORE

Mat Gaosi_Mohu(Mat Src, int Ksize);

Mat Yuzhi_ErJinZhi(Mat Src, int 阈值);

Mat XingTaiXue(Mat Src);

Mat ZhiFangTu_JunHua(Mat Src);

Mat Adaptive_Median_Filter(Mat Src); //于2019/11/10，用于公路路面特征识别的数字图像处理继续技术积累

Mat Gaosi_双边(Mat Src); //高斯双边滤波与锐化，保持边缘的滤波，用于金属加工件检测预处理 2019/11/14

#endif // !BEFORE

#ifndef Features

vector<vector<Point>> BianYuan(Mat Src);

Mat Canny_边缘(Mat Src, int lowThreshold);

vector<Vec3f> Hough_circle(Mat src, Mat Map);

vector<Vec2f> Hough_Lines(Mat src, Mat Map);

Mat 图像减(Mat 被减, Mat 减);

Mat Harris_XJB(Mat Src); //测试的HARRIS图像特征检测代码，虽然能画图但是没什么卵用

#endif // !Features

#ifndef HoughParam  //霍夫变换参数组类设定，代码简单复用

class Hough_Param
{
public:
	int Hough_Method = HOUGH_GRADIENT;
	double dp;
	double mindist;
	double Param1;
	double Param2;
	int minRadius;
	int maxRadius;
};

#endif // !HoughParam

#ifndef REPEAT

vector<Vec3f> Hough_circle_Copy1(Mat src, Mat Map);

vector<Vec3f> Hough_circle_Copy2(Mat src, Mat Map);   //用于检测同心圆中小小圆设定的副本参数方法 2019/11/15

vector<Vec3f> Hough_circle_Class(Mat src, Mat Map, Hough_Param Param);

void Draw_Circles(vector<vector<Vec3f>> Array_Of_Circles, Mat Map);

#endif