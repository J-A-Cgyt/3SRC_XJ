#pragma once
#include "Func_Proj_2nd.h"
//cudaģ���ͼ����Ӧ�ó���
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudaarithm.hpp> //cv::cuda::add�����ڴ�
#include <opencv2/cudafeatures2d.hpp> //����������ڴ�
#include <opencv2/xfeatures2d/cuda.hpp>
#include <opencv2/cudaobjdetect.hpp>

#include <opencv2/objdetect/objdetect.hpp> //haar�����������ƺ�Ҫ��

string window_nameC = "Demo_Result";

//�˺����ǲ���CUDA���ܵ�ʵ�ֿ��� 20200705
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
	//��ͼ�����ؼ�
	cuda::add(Gimg1, Gimg2, GRes);
	GRes.download(Cres);
	imshow(window_nameC, Cres);
	waitKey(0);
	//��ͼ�����ؼ�
	cuda::subtract(Gimg1, Gimg2, GRes);
	GRes.download(Cres);
	imshow(window_nameC, Cres);
	waitKey(0);

	return Cres;
}

//Hough�任��GPU�汾��д�����ɣ��ⶫ����GPU�������ܲ�֪���ܿ���� ����ǲ��ܶ���Բ��������̫����
Point3f IrisDectH_GPU(Mat Src)
{
	double dp = 1;
	double mindist = 40;
	double Param1 = 55;
	double Param2 = 40;
	int minRadius = 130;
	int maxRadius = 150;
	int maxNumbers = 1;  //GPUԲ��������

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
		cout << "δ��⵽Բ" << endl;
		return Point3f();
	}
	DstG.download(Dst);

	//Map = Src.clone();
	cvtColor(Src, Map, COLOR_GRAY2BGR);
	for (int i = 0; i < Dst.cols; i++) //���в����»����һ��ͬ��Բ
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


//��GPU�Ľǵ���Ҳ��һ�£�Ӧ�ô�ͼû�����ˣ����һ�� ��Ŀ��һ����ռ����5%
//01-ORB�ǵ��⣬���������ӣ���Ҫbrief���������
int ORBG_cgyt(Mat Src)
{
	Ptr<cuda::ORB> detectorOG = cuda::ORB::create(); //�������в�����ѡ��ע��
	vector<KeyPoint> KeyP_ORBG;
	cuda::GpuMat SrcG;
	SrcG.upload(Src);
	detectorOG->detect(SrcG, KeyP_ORBG); //�ƺ������Դ���ڴ��еı������н�����
	cout << KeyP_ORBG.size() << endl;
	Mat Map;
	cvtColor(Src, Map, COLOR_GRAY2BGR);
	drawKeypoints(Map, KeyP_ORBG, Map);
	imshow(window_nameC, Map);
	waitKey(0);
	return 0;
}

//surf�Ľǵ��⣬��ƥ�䵫���ϳ� ����CUDEVģ������⣬���п���Ҫʹ�ã�ԭ����CUDA����֧��2.0�ܹ��������Ǽ����������������Ҫ�õ�ʱ���ڰ������ϵİ취���±������԰�
int SURFG_cgyt(Mat Src1,Mat Src2)
{
	cuda::GpuMat Src1G, Src2G;  //�Դ�ͼ��
	cuda::GpuMat KPsG1, KPsG2;  //�Դ�ǵ���
	vector<KeyPoint> KPsC1, KPsC2;  //�ڴ�ǵ���
	cuda::GpuMat DescriptorG1, DescriptorG2; //�Դ�������
	Src1G.upload(Src1);
	Src2G.upload(Src2);

	cuda::SURF_CUDA Surf_detector(150);  //surf�����
	Surf_detector(Src1G, cuda::GpuMat(), KPsG1, DescriptorG1);
	Surf_detector(Src2G, cuda::GpuMat(), KPsG2, DescriptorG2);

	Ptr<cuda::DescriptorMatcher> MatcherG = cuda::DescriptorMatcher::createBFMatcher(); //�ǵ�ƥ��
	vector<vector<DMatch>> DMatchesG;  //�Դ�ƥ���ϵ
	MatcherG->knnMatch(DescriptorG1, DescriptorG1, DMatchesG, 3); //KNNƥ��
	Surf_detector.downloadKeypoints(KPsG1, KPsC1);
	Surf_detector.downloadKeypoints(KPsG2, KPsC2);  //ƥ�����������ڴ�

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


//�����ӵ㶫��,�ƺ��и�����ʶ��ɶ�Ļ�ͦ���� �б�����õ���������ķ�����
int FaceG_cgyt(Mat Src) //ʹ�õ���HAAR�ļ��������� �趨������Ҷ�ͼ��
{
	cv::cuda::printCudaDeviceInfo(cv::cuda::getDevice());

	Mat Temp = Src.clone();
	
	Ptr<cuda::CascadeClassifier> Cas_cgyt = cuda::CascadeClassifier::create("E:\\DIP\\OpencvPlus\\install\\etc\\lbpcascades\\lbpcascade_frontalface.xml");

	cuda::GpuMat d_Buffer;
	cuda::GpuMat d_Img;       //�����豸�Դ�
	d_Img.upload(Temp);       //����ͼ�����Դ�
	Cas_cgyt->detectMultiScale(d_Img, d_Buffer);   //�������
	vector< Rect> Detected;
	Cas_cgyt->convert(d_Buffer, Detected);   //�������������������gpu�ļ�����Ż������ڴ�
	if (Detected.empty())
	{
		printf("û�Ҽ���\n");
		return 0;
	}
	cvtColor(Src, Temp, COLOR_GRAY2BGR);
	for (int i = 0; i < Detected.size(); i++)
	{
		rectangle(Temp, Detected[i], Scalar(0, 0, 255), 2);
	}
	imshow(window_nameC, Temp);
	waitKey(0);
	return 0;
}