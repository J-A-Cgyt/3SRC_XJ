#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

#ifndef BEFORE

Mat Gaosi_Mohu(Mat Src, int Ksize);

Mat Yuzhi_ErJinZhi(Mat Src, int ��ֵ);

Mat XingTaiXue(Mat Src);

Mat ZhiFangTu_JunHua(Mat Src);

Mat Adaptive_Median_Filter(Mat Src); //��2019/11/10�����ڹ�··������ʶ�������ͼ���������������

Mat Gaosi_˫��(Mat Src); //��˹˫���˲����񻯣����ֱ�Ե���˲������ڽ����ӹ������Ԥ���� 2019/11/14

#endif // !BEFORE

#ifndef Features

vector<vector<Point>> BianYuan(Mat Src);

Mat Canny_��Ե(Mat Src, int lowThreshold);

vector<Vec3f> Hough_circle(Mat src, Mat Map);

vector<Vec2f> Hough_Lines(Mat src, Mat Map);

Mat ͼ���(Mat ����, Mat ��);

Mat Harris_XJB(Mat Src); //���Ե�HARRISͼ�����������룬��Ȼ�ܻ�ͼ����ûʲô����

#endif // !Features

#ifndef HoughParam  //����任���������趨������򵥸���

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

vector<Vec3f> Hough_circle_Copy2(Mat src, Mat Map);   //���ڼ��ͬ��Բ��ССԲ�趨�ĸ����������� 2019/11/15

vector<Vec3f> Hough_circle_Class(Mat src, Mat Map, Hough_Param Param);

void Draw_Circles(vector<vector<Vec3f>> Array_Of_Circles, Mat Map);

#endif