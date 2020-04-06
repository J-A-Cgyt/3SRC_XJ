#include "Header_Main.h"

//���Ա����ʵ��ͷԴ�ļ�

Test_cgyt::Test_cgyt(int a, double b)
{
	this->test_A = a;
	this->test_B = b;
}

Test_cgyt::~Test_cgyt()
{
	cout << "ʵ��������" << endl;
}

int Test_cgyt::add(int a, int b)
{
	int c = a + b;
	//cout << c << endl;
	return c;
}

void Test_cgyt::set_value(int a, double b)
{
	this->test_A = a;
	this->test_B = b;
}

//һ���Ǿ����ĵڶ��γ���
using namespace cv;

cv::Mat Conv_cgyt_2nd::sobel_cgyt(cv::Mat Src)
{
	filter2D(Src, res1, Src.depth(), Sobel_Zong);
	filter2D(Src, res2, Src.depth(), Sobel_Heng);

	//ת��������
	cout << Src.depth() << endl;
	cout << res1.depth() << endl;
	cout << res2.depth() << endl; //�����ֵ��enum

	res1.convertTo(res1, CV_32FC1);
	res2.convertTo(res2, CV_32FC1);

	Gard_angle = Mat(Src.size(), CV_32FC1);//һ�׵����򣨻Ҷ��ݶȷ���
	for (int i = 0; i < Src.cols; i++)
	{
		for (int j = 0; j < Src.rows; j++)
		{
			Gard_angle.at<float>(j, i) = atan(res1.at<float>(j, i) / res2.at<float>(j, i));
		}
	}
	Chanel_Queue.push_back(res1);
	Chanel_Queue.push_back(res2);
	Chanel_Queue.push_back(Gard_angle);

	Sobel_Grad = Mat(Src.size(), CV_32FC3);
	merge(Chanel_Queue, Sobel_Grad);
	end = Sobel_Grad.clone();
	return end;
}

cv::Mat Conv_cgyt_2nd::gardient_cgyt(cv::Mat Src)
{
	filter2D(Src, res1, Src.depth(), Gard_Zong);
	filter2D(Src, res2, Src.depth(), Gard_Heng);

	//ת��������
	cout << Src.depth() << endl;
	cout << res1.depth() << endl;
	cout << res2.depth() << endl; //�����ֵ��enum

	res1.convertTo(res1, CV_32FC1);
	res2.convertTo(res2, CV_32FC1);

	Gard_angle = Mat(Src.size(), CV_32FC1);//һ�׵����򣨻Ҷ��ݶȷ���
	for (int i = 0; i < Src.cols; i++)
	{
		for (int j = 0; j < Src.rows; j++)
		{
			Gard_angle.at<float>(j, i) = atan(res1.at<float>(j, i) / res2.at<float>(j, i));
		}
	}

	Chanel_Queue.push_back(res1);
	Chanel_Queue.push_back(res2);
	Chanel_Queue.push_back(Gard_angle);

	Sobel_Grad = Mat(Src.size(), CV_32FC3);
	merge(Chanel_Queue, Sobel_Grad);
	end = Sobel_Grad.clone();
	return end;
}

cv::Mat Conv_cgyt_2nd::laplace_cgyt(cv::Mat Src)
{
	filter2D(Src, res1, Src.depth(), Laplace);
	end = res1.clone();
	return end;
}

cv::Mat Conv_cgyt_2nd::Ave3_cgyt(cv::Mat Src)
{
	cv::Mat temp;
	Src.convertTo(temp, CV_32FC1);

	filter2D(temp, temp, temp.depth(), Ave3_Cgyt);

	temp.convertTo(this->end, CV_8UC1);

	return this->end;
}

cv::Mat Conv_cgyt_2nd::Conv_Sel(cv::Mat Src, int method)
{
	switch (method)
	{
	case(SOBEL_CGYT_2):
		Result = sobel_cgyt(Src);
		break;

	case(LAPLACE_CGYT_2):
		Result = laplace_cgyt(Src);
		break;

	case(GARDIENT1_CGYT_2):
		Result = gardient_cgyt(Src);
		break;

	case(AVE_CGYT_2):
		Result = Ave3_cgyt(Src);
		break;
	}
	return Result;
}