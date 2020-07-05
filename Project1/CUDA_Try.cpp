#pragma once
#include "Func_Proj_2nd.h"
//cudaģ���ͼ����Ӧ�ó���
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp> //cv::cuda::add�����ڴ�

string window_nameC = "Demo_Result";
//�˺����ǲ���CUDA���ܵ�ʵ�ֿ���
Mat GPU_func_study(Mat Src1,Mat Src2)
{
	cv::cuda::printCudaDeviceInfo(cv::cuda::getDevice());

	namedWindow(window_nameC, WINDOW_NORMAL);

	if (!Src1.data || !Src2.data)
	{
		printf("����ͼ��Ϊ��\n");
		return Mat();
	}

	cuda::GpuMat GRes, Gimg1, Gimg2;
	Mat Cres;
	//ͼ�����Դ�
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