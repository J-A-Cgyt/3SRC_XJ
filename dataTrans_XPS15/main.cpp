#include "dataTrans.h"

int main() { //mat类的数据发送 jpg发送之前就实现过了
	std::string loadingPath("F:\\Pictures\\Test For Programming\\香蕉3.jpg");
	cv::Mat src(cv::imread(loadingPath, cv::IMREAD_GRAYSCALE));  //直接初始化
	//unsigned char pixPin = src.at<unsigned char>(0, 233);
	//unsigned char pixPin = src.data[233];
	//cv::Mat src = cv::Mat::zeros(cv::Size(3,3),CV_8UC1);
	//src.at<unsigned char>(1, 1) = 29;
	RoIMatSend(src, "192.168.137.3");   //此IP为工位台式机IP
	return 0;
}