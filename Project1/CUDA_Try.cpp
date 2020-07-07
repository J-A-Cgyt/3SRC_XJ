#pragma once
#include "Func_Proj_2nd.h"
//cuda模块的图像处理应用尝试
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp> //cv::cuda::add函数在此
#include <opencv2/cudafeatures2d.hpp> //特征检测类在此
#include <opencv2/xfeatures2d/cuda.hpp>

string window_nameC = "Demo_Result";

//此函数是部分CUDA功能的实现看看 20200705
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
	//两图像按像素加
	cuda::add(Gimg1, Gimg2, GRes);
	GRes.download(Cres);
	imshow(window_nameC, Cres);
	waitKey(0);
	//两图像按像素减
	cuda::subtract(Gimg1, Gimg2, GRes);
	GRes.download(Cres);
	imshow(window_nameC, Cres);
	waitKey(0);

	return Cres;
}

//Hough变换的GPU版本重写看看吧，这东西用GPU加速性能不知道能快多少 真的是不管多少圆都是秒检测太猛了
Point3f IrisDectH_GPU(Mat Src)
{
	double dp = 1;
	double mindist = 40;
	double Param1 = 55;
	double Param2 = 40;
	int minRadius = 130;
	int maxRadius = 150;
	int maxNumbers = 1;  //GPU圆检测参数组

	cuda::GpuMat SrcG, DstG;
	Mat Dst, Map;
	vector<Vec3f> circles;
	Ptr<cuda::HoughCirclesDetector> Iris_deutector;
	Iris_deutector = cuda::createHoughCirclesDetector(
		dp, mindist, Param1, Param2, minRadius, maxRadius,maxNumbers);

	SrcG.upload(Src);
	Iris_deutector->detect(SrcG, DstG);
	if (!DstG.data)
	{
		cout << "未检测到圆" << endl;
		return Point3f();
	}
	DstG.download(Dst);

	//Map = Src.clone();
	cvtColor(Src, Map, COLOR_GRAY2BGR);
	for (int i = 0; i < Dst.cols; i++) //现有参数下会检测出一堆同心圆
	{
		circles.push_back(Dst.at<Vec3f>(0, i));
		circle(Map,
			Point(circles[i][0], circles[i][1]),
			circles[i][2],
			Scalar(0, 0, 255), 2);
	}
	imshow(window_nameC, Map);
	cout << Dst.size << endl;
	waitKey(0);
	return Point3f();
}


//用GPU的角点检测也试一下，应该大图没问题了，快的一批 真的快的一批，占用率5%
//01-ORB角点检测，并无描述子，需要brief描述子配合
int ORBG_cgyt(Mat Src)
{
	Ptr<cuda::ORB> detectorOG = cuda::ORB::create(); //创建中有参数可选，注意
	vector<KeyPoint> KeyP_ORBG;
	cuda::GpuMat SrcG;
	SrcG.upload(Src);
	detectorOG->detect(SrcG, KeyP_ORBG); //似乎允许显存和内存中的变量进行交互？
	cout << KeyP_ORBG.size() << endl;
	Mat Map;
	cvtColor(Src, Map, COLOR_GRAY2BGR);
	drawKeypoints(Map, KeyP_ORBG, Map);
	imshow(window_nameC, Map);
	waitKey(0);
	return 0;
}

//surf的角点检测，带匹配但不合成
int SURFG_cgyt(Mat Src1,Mat Src2)
{
	cuda::GpuMat Src1G, Src2G;  //显存图像
	cuda::GpuMat KPsG1, KPsG2;  //显存角点存放
	vector<KeyPoint> KPsC1, KPsC2;  //内存角点存放
	cuda::GpuMat DescriptorG1, DescriptorG2; //显存描述子
	Src1G.upload(Src1);
	Src2G.upload(Src2);

	cuda::SURF_CUDA Surf_detector(150);  //surf检测器
	Surf_detector(Src1G, cuda::GpuMat(), KPsG1);
	Surf_detector(Src2G, cuda::GpuMat(), KPsG2);

	Ptr<cuda::DescriptorMatcher> MatcherG = cuda::DescriptorMatcher::createBFMatcher(); //角点匹配
	vector<vector<DMatch>> DMatchesG;  //显存匹配关系
	MatcherG->knnMatch(KPsG1, KPsG2, DMatchesG, 3); //KNN匹配
	Surf_detector.downloadKeypoints(KPsG1, KPsC1);
	Surf_detector.downloadKeypoints(KPsG2, KPsC2);  //匹配结果下载至内存

	vector<DMatch> Selected_matchs;
	for (int i = 0; i < MIN(KPsC1.size() - 1, DMatchesG.size()); i++)
	{
		if ((DMatchesG[i][0].distance < (0.75 * DMatchesG[i][1].distance)) &&
			int(DMatchesG[i].size()) <= 2 &&
			int(DMatchesG[i].size()) > 0
			)
		{
			Selected_matchs.push_back(DMatchesG[i][0]);
		}
	}		
	cout << Selected_matchs.size() << endl;
	Mat Map;
	drawMatches(Src1,KPsC1,Src2,KPsC2,Selected_matchs,Map);
	imshow(window_nameC, Map);
	waitKey(0);
	return 0;
}
