#pragma once
#include "Func_Proj_2nd.h"
//cuda模块的图像处理应用尝试
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp> //cv::cuda::add函数在此

string window_nameC = "Demo_Result";
//此函数是部分CUDA功能的实现看看
Mat GPU_func_study(Mat Src1,Mat Src2)
{
	cv::cuda::printCudaDeviceInfo(cv::cuda::getDevice());

	namedWindow(window_nameC, WINDOW_NORMAL);

	if (!Src1.data || !Src2.data)
	{
		printf("传入图像为空\n");
		return Mat();
	}

	cuda::GpuMat GRes, Gimg1, Gimg2;
	Mat Cres;
	//图像传至显存
	Gimg1.upload(Src1);
	Gimg2.upload(Src2);

	cuda::add(Gimg1, Gimg2, GRes);
	GRes.download(Cres);
	imshow(window_nameC, Cres);
	waitKey(0);

	cuda::subtract(Gimg1, Gimg2, GRes);
	GRes.download(Cres);
	imshow(window_nameC, Cres);
	waitKey(0);

	return Cres;
}