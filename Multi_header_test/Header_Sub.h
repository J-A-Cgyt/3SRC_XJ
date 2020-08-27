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
	enum conv_method //�������ö������
	{
		SOBEL_CGYT_2 = 0,
		LAPLACE_CGYT_2 = 1,
		GARDIENT1_CGYT_2 = 2,
		AVE_CGYT_2=3
	};

	cv::Mat Conv_Sel(cv::Mat Src, int method); //���õ�CONV����

	cv::Mat Result; //�����Ľ��ͼ��

protected:
	cv::Mat sobel_cgyt(cv::Mat Src);

	cv::Mat gardient_cgyt(cv::Mat Src);

	cv::Mat laplace_cgyt(cv::Mat Src);

	cv::Mat Ave3_cgyt(cv::Mat Src);

private: //������趨
	//sobel�����
	cv::Mat Sobel_Zong = (cv::Mat_<char>(3, 3) << -1, -2, -1,
		0, 0, 0,
		1, 2, 1);
	cv::Mat Sobel_Heng = (cv::Mat_<char>(3, 3) << -1, 0, 1,
		-2, 0, 2,
		-1, 0, 1);

	//һ���ݶ�
	cv::Mat Gard_Zong = (cv::Mat_<char>(3, 3) << -1, -1, -1,
		0, 0, 0,
		1, 1, 1);
	cv::Mat Gard_Heng = (cv::Mat_<char>(3, 3) << -1, 0, 1,
		-1, 0, 1,
		-1, 0, 1);

	//Laplace���� �ĸ�����
	cv::Mat Laplace = (cv::Mat_<char>(3, 3) << -1, -1, -1,
		-1, 8, -1,
		-1, -1, -1);

	//��ֵ�˲�
	cv::Mat Ave3_Cgyt = (cv::Mat_<float>(3, 3) << 1 / 9, 1 / 9, 1 / 9,
		1 / 9, 1 / 9, 1 / 9,
		1 / 9, 1 / 9, 1 / 9);

private: //�м�����趨
	cv::Mat res1, res2;
	
	cv::Mat end;  //���ս��
	
	std::vector<cv::Mat> Chanel_Queue; //��ͨ������

	cv::Mat Gard_angle;  //���ּ������õ��ݶȽǶ�
	
	cv::Mat Sobel_Grad;  //sobel�ݶȽ����Ҳ��Ϊ���г�Ա���������ռ������ݴ�,������д�ĳ���Ҳ��ֱ����end
};

#endif // ! conv2nd

