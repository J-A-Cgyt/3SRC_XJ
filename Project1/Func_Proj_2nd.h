#pragma once
//opencv400������
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/photo/photo.hpp>
#include <opencv2/ml.hpp> //����ѧϰ����ģ�� SVM DTree ANN

//c++��׼�ļ���
#include <iostream>
#include <vector>
#include <math.h>

//��ǿ���֣��������
#include <opencv2/xfeatures2d/nonfree.hpp>
//����ͷ�ļ���ɶ��һ����
#include <opencv2/xfeatures2d.hpp>

//#include "D:/���/OpenCV/opencv_contrib-4.0.0/modules/xfeatures2d/include/opencv2/xfeatures2d.hpp"

using namespace std;
using namespace cv;

#ifndef Self_Blur //���н������˲�����

Mat Gaosi_˫��(Mat Src); //��˹˫���˲����񻯣����ֱ�Ե���˲� 2019/11/14,�Ӳ����������Ŀ��ֲ

Mat NLM_CGYT(Mat Src); //NLM���Ǿֲ���ֵ�˲�

int Hu_Ju_CGYT(Mat Src,double* Hu_Ju); //Hu�ؼ��㷽��������ͼ��

int Hu_Ju_CGYT(vector<Point> Contour,double* Hu_Ju); //Hu�ؼ��㷽��,����㼯

vector<Point2d> SubPixel_Contours_Cgyt(Mat Src, vector<Point> contours); //Zernike�ص�ʵ�ֳ��ԣ�����+���ģ����������� ���ξ���ʵ�֣���ʱ���ǿ�ɶ��̵߳�

double Solve_Cgyt(double P); //�����Է�������⺯�� ����Ϊ x - 0.5*sin(2 * x) = Pi * P,ʹ�ü򵥵����������,���Լ���ط���������������ֵ���м����

vector<Point2d> SubPixel_Contours_Cgyt(Mat Src_2, vector<Point> Contours_2, int second); //��ͨ�ط����������ر�Ե�������

#endif // !Self_Blur

#ifndef Pre_Proc

Mat Thershold_����(Mat Src); //������ֵ

Mat FT_CGYT(Mat Src); //����Ҷ�任

Mat Conv_Cgyt(Mat Src,int K_mod); //ͼ��Ҷ��ݶȼ��� Դ�ļ�Cgyt_conv.cpp

vector<Vec4f> LSD_cgyt(Mat Src); //LSD�߶μ��

Mat FenShuiLing_CGYT(Mat Src);   //��ˮ�뷽��+���������ɫ�����չʾ

int Calib_Cgyt(Mat InputOutputArray);

#endif // !Pre_Proc

#ifndef Features2nd

Mat FAST_dect_Cgyt(Mat Src1, Mat Src2); //FAST�ǵ���

Mat JiaoDian_SURF_CGYT(Mat Src1, Mat Src2); //SURF�ǵ��������

vector<Point2f> subPix_pt(Mat Src); //���������ؼ��ǵ������Ļ�����ϸ����ʹ��OpenCV�Դ��ĺ���

#endif // !Features2nd


#ifndef buffer  //����������ݴ��ļ������������¶������ʱ���麯��

int TrackBar_cgyt_canny(int, char** argv);

static void CannyThreshold(int, void*);

#endif // !buffer