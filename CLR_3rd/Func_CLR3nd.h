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

//CLI�����²�֧��ͷ�ļ�<thread>����ҪѰ���µ���ɢ���ٷ�������֪��CUDA���в����У����� ˫���˲�����ֱ��ע�͵��������һ��һ����������ɢ�ʲ�������û��������

using namespace cv;
using namespace std;

//Ҫ�����ǰ�C++/CLI�ϵ��ɣ��������ڹ���Ҳû���ƣ�תQT�������ü�
