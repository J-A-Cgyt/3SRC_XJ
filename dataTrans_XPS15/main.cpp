#include "dataTrans.h"

int main() { //mat������ݷ��� jpg����֮ǰ��ʵ�ֹ���
	std::string loadingPath("string Load_Path_2nd_5 = F:\\Pictures\\Test For Programming\\�㽶3.jpg");
	cv::Mat src(cv::imread(loadingPath, cv::IMREAD_GRAYSCALE));  //ֱ�ӳ�ʼ��
	RoIMatSend(src, "192.168.137.3");
	return 0;
}