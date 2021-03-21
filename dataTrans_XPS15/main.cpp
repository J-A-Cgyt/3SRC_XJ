#include "dataTrans.h"

int main() { //mat类的数据发送 jpg发送之前就实现过了
	std::string loadingPath("string Load_Path_2nd_5 = F:\\Pictures\\Test For Programming\\香蕉3.jpg");
	cv::Mat src(cv::imread(loadingPath, cv::IMREAD_GRAYSCALE));  //直接初始化
	RoIMatSend(src, "192.168.137.3");
	return 0;
}