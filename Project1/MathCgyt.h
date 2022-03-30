#pragma once

#ifndef MATH_FUNC
#define MATH_FUNC

#if MathActivate == 1

//��һ��дһ����˹�ֲ���������������������ƺ�opencv��RNG::Gaussian�Ϳɣ���Ȼ��˾Ͳ��˷�ʱ���˵�ʱ�����϶������и��෽����Ҫ��ѧ���㣬������д��

//�׳�
double JieCheng(const unsigned int &i);

//�򻯰�OTSU 20210311����ͨ�� ������ unsigned char���͵�ԭʼ����
unsigned char OTSU_Value_Calc(const std::vector<unsigned char>& src);

//�ֲ���ֵ�뷽�����
int localMeanVarCalc(const Mat           &src,
	                 const int            row,
	                 const int            col,
	                 const unsigned int  &ksize,
	                 double              *mean,
	                 double              *var);


/**************************************************************************************************
*  ��������Ҫһ����С�������Բ��C++�汾
*      contour      -I        ��ϵ������������㼯
*      circle_info  -O        �����Բ��Ϣ x:���ĺ����� y:���������� z:�뾶
*      error        -O        �����������
*  ����ֵ��������ϵĵ�����
*  20211210����ͨ�� �ԱȻ���任�����бȽϺõĽ��������������ô�����
**************************************************************************************************/
int minSqureFitCircle(const std::vector<cv::Point2d>& contour,
	                  cv::Point3d&              circle_info,
	                  double&                   error);




#endif

#endif
//�������ǰ���Դ�ļ����е�˳������ ���ͷ�ļ������Ժ���calib ����û��ֺ�ֱ�Ӻ��汨�� ע����������