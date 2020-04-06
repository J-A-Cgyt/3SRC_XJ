#include "Func.h"

Mat Gaosi_Mohu(Mat Src, int Ksize)
{
	Mat temp1 = Src.clone();
	Size Ks = Size(Ksize, Ksize);
	GaussianBlur(temp1, temp1, Ks, 0, 0);
	return temp1;
}

Mat Gaosi_˫��(Mat Src) //��˹˫���˲����񻯣����ֱ�Ե���˲� 2019/11/14
{
	int d = 0;
	double Sigma_Color = 100;
	double Sigma_Space = 15;
	Mat Dst;
	bilateralFilter(Src, Dst, d, Sigma_Color, Sigma_Space);
	
	Mat Filter = (Mat_<char>(3, 3) << 0, -1, 0,
		                             -1, 5, -1,
		                              0, -1, 0);
	
	filter2D(Dst, Dst, Dst.depth(), Filter);
	
	return Dst;
}

Mat Yuzhi_ErJinZhi(Mat Src,int ��ֵ)
{
	int threshold_level = ��ֵ; //��ֵ
	int threshold_max = 255;  //�������ֵ
	int threshold_type = 0;   //��ֵ��������
	Mat step1, step2;
	step1 = Src.clone();
	threshold(step1, step2, threshold_level, threshold_max, threshold_type);
	return step2;
}

Mat XingTaiXue(Mat Src) //��̬ѧ����
{
	int morph_operator = 2;
	int morph_elem = 1;
	int morph_size = 1;

	int operation = morph_operator + 2;

	Mat middle1;
	Mat element = getStructuringElement(morph_elem,
		Size(morph_size * 2 + 1, morph_size * 2 + 1),
		Point(morph_size, morph_size));
	morphologyEx(Src, middle1, operation, element);

	return middle1;
}

Mat ZhiFangTu_JunHua(Mat Src)  //ֱ��ͼ����
{
	Mat temp = Src.clone();
	equalizeHist(temp, temp);
	return temp;
}

Mat Adaptive_Median_Filter(Mat Src) //ûд��
{
	Mat Temp,Dst;
	Temp = Src.clone();

	return Dst;
}