#include "dataTrans.h"

int main() { 
	//mat������ݷ��� jpg����֮ǰ��ʵ�ֹ���
	std::string loadingPath("F:\\Pictures\\Test For Programming\\�ӵ���.bmp");
	cv::Mat src(cv::imread(loadingPath, cv::IMREAD_GRAYSCALE));  //ֱ�ӳ�ʼ��
	//unsigned char pixPin = src.at<unsigned char>(0, 233);
	//unsigned char pixPin = src.data[233];
	//cv::Mat src = cv::Mat::zeros(cv::Size(3,3),CV_8UC1);
	//RoIMatSend(src, "192.168.137.3");   //��IPΪ��λ̨ʽ��IP
	videoTrans("192.168.137.3");
	return 0;
}