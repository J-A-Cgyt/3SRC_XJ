#pragma once
#include "Func_Proj_2nd.h"
//cudaģ���ͼ����Ӧ�ó���
#include <opencv2/cudaimgproc.hpp>

Mat MoHu_GPU(Mat Src)
{
	cv::cuda::printCudaDeviceInfo(cv::cuda::getDevice());
	
	cuda::GpuMat TempG;
	TempG.upload(Src);
	


	return Mat();
}