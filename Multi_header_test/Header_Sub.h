#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#ifndef  Test_A

class Test_cgyt
{
public:
	Test_cgyt(int a,double b);

	~Test_cgyt();

	int add(int a, int b);

	void set_value(int a, double b);

private:
	int test_A;
	double test_B;
	cv::Mat Pic_Test;
};
#endif // ! Test_A

#ifndef conv2nd

class Conv_cgyt_2nd
{
public:
	enum conv_method //卷积方法枚举类型
	{
		SOBEL_CGYT_2 = 0,
		LAPLACE_CGYT_2 = 1,
		GARDIENT1_CGYT_2 = 2,
		AVE_CGYT_2=3
	};

	cv::Mat Conv_Sel(cv::Mat Src, int method); //调用的CONV函数

	cv::Mat Result; //反馈的结果图像

protected:
	cv::Mat sobel_cgyt(cv::Mat Src);

	cv::Mat gardient_cgyt(cv::Mat Src);

	cv::Mat laplace_cgyt(cv::Mat Src);

	cv::Mat Ave3_cgyt(cv::Mat Src);

private: //卷积核设定
	//sobel卷积核
	cv::Mat Sobel_Zong = (cv::Mat_<char>(3, 3) << -1, -2, -1,
		0, 0, 0,
		1, 2, 1);
	cv::Mat Sobel_Heng = (cv::Mat_<char>(3, 3) << -1, 0, 1,
		-2, 0, 2,
		-1, 0, 1);

	//一阶梯度
	cv::Mat Gard_Zong = (cv::Mat_<char>(3, 3) << -1, -1, -1,
		0, 0, 0,
		1, 1, 1);
	cv::Mat Gard_Heng = (cv::Mat_<char>(3, 3) << -1, 0, 1,
		-1, 0, 1,
		-1, 0, 1);

	//Laplace算子 四个方向
	cv::Mat Laplace = (cv::Mat_<char>(3, 3) << -1, -1, -1,
		-1, 8, -1,
		-1, -1, -1);

	//均值滤波
	cv::Mat Ave3_Cgyt = (cv::Mat_<float>(3, 3) << 1 / 9, 1 / 9, 1 / 9,
		1 / 9, 1 / 9, 1 / 9,
		1 / 9, 1 / 9, 1 / 9);

private: //中间变量设定
	cv::Mat res1, res2;
	
	cv::Mat end;  //最终结果
	
	std::vector<cv::Mat> Chanel_Queue; //各通道队列

	cv::Mat Gard_angle;  //各种计算所得的梯度角度
	
	cv::Mat Sobel_Grad;  //sobel梯度结果，也作为所有成员函数的最终计算结果暂存,后续编写的程序也可直接用end
};

#endif // ! conv2nd

