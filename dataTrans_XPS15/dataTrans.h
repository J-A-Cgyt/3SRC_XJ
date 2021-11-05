#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

struct Point_cgyt {  //���˳����һ��֮ǰѧ����Щ�� �����Ҳ����ʹ��
	double x;
	double y;

	//����������ظ�ϰһ��
	Point_cgyt() :x(0), y(0) { };                            //Ĭ�Ϲ��캯��
	Point_cgyt(double xx, double yy) :x(xx), y(yy) { };      //���캯��
	Point_cgyt(const Point_cgyt &pt) :x(pt.x), y(pt.y) { };  //�������캯��
	Point_cgyt(Point_cgyt &&pt) :x(pt.x), y(pt.y) { };       //�ƶ����캯��
	Point_cgyt& operator=(const Point_cgyt &pt) { x = pt.x; y = pt.y; return *this; }; //������ֵ����� ������ķ�������Ӧ��һ����ֵp129
	Point_cgyt& operator=(Point_cgyt &&pt) { x = pt.x; y = pt.y; return *this; };      //�ƶ���ֵ�����
	~Point_cgyt() { };    //��������
};

int ContoursSubpixSend(const std::vector<cv::Point2d>& contoursSubpix, const char* ipAddr);

int RoIMatSend(const cv::Mat& src, const char* ipAddr);

int videoTrans(const char* ipAddr);                         //����ͷ����ͼ���ϴ�