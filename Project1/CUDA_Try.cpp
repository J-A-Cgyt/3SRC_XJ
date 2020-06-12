#pragma once
#include "Func_Proj_2nd.h"
//cuda模块的图像处理应用尝试
#include <opencv2/cudaimgproc.hpp>

Mat MoHu_GPU(Mat Src)
{
	cv::cuda::printCudaDeviceInfo(cv::cuda::getDevice());
	
	cuda::GpuMat TempG;
	TempG.upload(Src);
	


	return Mat();
}