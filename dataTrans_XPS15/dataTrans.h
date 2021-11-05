#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct Point_cgyt {  //这个顺便练一下之前学的那些？ 这个类也许不会使用
	double x;
	double y;

	//拷贝控制相关复习一边
	Point_cgyt() :x(0), y(0) { };                            //默认构造函数
	Point_cgyt(double xx, double yy) :x(xx), y(yy) { };      //构造函数
	Point_cgyt(const Point_cgyt &pt) :x(pt.x), y(pt.y) { };  //拷贝构造函数
	Point_cgyt(Point_cgyt &&pt) :x(pt.x), y(pt.y) { };       //移动构造函数
	Point_cgyt& operator=(const Point_cgyt &pt) { x = pt.x; y = pt.y; return *this; }; //拷贝赋值运算符 运算符的返回类型应是一个左值p129
	Point_cgyt& operator=(Point_cgyt &&pt) { x = pt.x; y = pt.y; return *this; };      //移动赋值运算符
	~Point_cgyt() { };    //析构函数
};

int ContoursSubpixSend(const std::vector<cv::Point2d>& contoursSubpix, const char* ipAddr);

int RoIMatSend(const cv::Mat& src, const char* ipAddr);

int videoTrans(const char* ipAddr);                         //摄像头拍摄图像上传