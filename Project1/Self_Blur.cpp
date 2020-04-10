#include "Func_Proj_2nd.h"
string window_name_f3 = "Demo_Result"; //结果显示窗

Mat Gaosi_双边(Mat Src) //高斯双边滤波与锐化，保持边缘的滤波 2019/11/14,从测试与积累项目移植
{
	int d = 0;
	double Sigma_Color = 100;
	double Sigma_Space = 15;
	Mat Dst;
	bilateralFilter(Src, Dst, d, Sigma_Color, Sigma_Space);

	//锐化滤镜
	Mat Filter = (Mat_<char>(3, 3) << 0, -1, 0,
									 -1, 5, -1,
									  0, -1, 0);

	filter2D(Dst, Dst, Dst.depth(), Filter);

	return Dst;
}

//非局部均值滤波 20200310 在头文件photo.hpp中 对不起，已经有现成API的就不自己写了，知道原理就行
Mat NLM_CGYT(Mat Src)
{
	Mat temp = Src.clone();
	float h = 10;
	int templateWindowSize = 7; //区块（区域分块）的大小
	int searchWindowSize = 21;  //搜索相似区块的大小
	fastNlMeansDenoising(Src, temp, h,
						 templateWindowSize, 
						 searchWindowSize);
	/*
	h : 决定过滤器强度。h 值高可以很好的去除噪声,但也会把图像的细节抹去。(取 10 的效果不错)
	hForColorComponents : 与 h 相同,但使用与彩色图像。(与 h 相同,10)
	templateWindowSize : 奇数。(推荐值为 7)
	searchWindowSize : 奇数。(推荐值为 21)
	相关原理见NoteExpress文献笔记 “基于Zernike矩亚像素的高反光金属工件缺陷检测”
	*/
	imshow(window_name_f3, temp);
	waitKey(0);
	return temp;
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//矩的实际研究始于 20200225，代码尝试开始 20200226
//同样是借用一个地方，用以实现ROI的Hu矩计算 在应用以前需先对ROI进行提取，或者先提取边缘 形式1，图像类型输入
int Hu_Ju_CGYT(Mat Src,double* Hu_Ju)
{
	Mat Temp;
	Temp = Src.clone();
	Moments Basic_Ju_Cgyt;
	//double Hu_Ju[7];

	Basic_Ju_Cgyt = moments(Temp);
	HuMoments(Basic_Ju_Cgyt, Hu_Ju);

	return 0; //返回指针是否会被销毁未知，此处可能有bug 果然有bug

}

//同样是借用一个地方，用以实现ROI的Hu矩计算 在应用以前需先对ROI进行提取，或者先提取边缘 形式2，边缘，点集类型输入
int Hu_Ju_CGYT(vector<Point> Contour,double* Hu_Ju)
{

	Moments Basic_Ju_Cgyt;
	//double Hu_Ju[7];

	Basic_Ju_Cgyt = moments(Contour);
	HuMoments(Basic_Ju_Cgyt, Hu_Ju);

	return 0; //返回指针是否会被销毁未知，此处可能有bug
}

/*
	Zernike矩的实现尝试，先把它算出来，然后再考虑如何应用与计算边缘的亚像素级别位置 可能需要一个单独的头文件和源文件方能完整地实现Zernike矩的计算
	
	20200227 记录
	对图像进行亚像素边缘检测可能不需要前置Canny、Sobel等算子进行像素级的边缘提取

	明确一下亚像素边缘提取的数据类型为 vector<Point2d> ~contour
	vector<vector<Point2d>> ~contours 亚像素级的结果无法在图像上体现？ 
	似乎也可，但是单元内保存的结果非像素值而是坐标的相对偏移量，相对的参考系在像素中心，向右向下为正，看看别人如何实现的吧。若是矩阵类型，则类型为 CV_64FC2

	20200229 记录
	实现目标更改为使用矩的亚像素轮廓定位实现,先实现几何矩(简单的矩)，再尝试Zernike矩

	20200302 记录
	对于矩的灰度加权模板卷积计算方法的结果仍然存疑，若要计算针对不同坐标轴的p、q阶矩，模板又该如何应用？
	是否能应用OpenCV自身携带的矩计算方法？或者应使用模板将圆外灰度置0后使用自带方法进行计算（此方法应注意坐标原点的设定与偏置）？
	必要的情况下把之前写的代码都扔进rubbish，重新尝试，对两篇论文的计算结果至少进行一个比对 
	
	20200303记录
	简单迭代解方程通过，若方法太多，则考虑建立命名空间与亚像素边缘检测的相关类了
*/
vector<Point2d> SubPixel_Contours_Cgyt(Mat Src, vector<Point> contour)
{
	Mat temp1, temp2;
	Mat Mu_Cal = Mat(temp1.size(), CV_64FC1);
	temp1 = Src.clone();
	cv::imshow(window_name_f3,temp1);
	cv::waitKey(0);
	temp1.setTo(0);

	//为了使用drawContours在外面再套一层壳
	vector<vector<Point>> Contours;	
	Contours.push_back(contour);

	//在此处记录一个普通几何矩进行亚像素检测的模板，尺寸7*7,最好整明白原理完了再算
	/*
	20200228
	猜测只要是基于矩的亚像素检测，应该都有统一的形式，计算几个不同阶数的某像素点一定范围邻域内的矩值，
	再按照一定规则将其转换为实际亚像素精度的坐标值（在计算前按理说是要归一化的，具体的方法得继续学习）
	根据论文[1]　柯洁．基于数学形态学和灰度矩的高温亚像素边缘检测[J]．工具技术．2019，53(03)：132-136．
	*/
//矩卷积计算模板设定
	double Omega[5];
	Omega[0] = 0;
	Omega[1] = 0.00913767235;
	Omega[2] = 0.021840193;
	Omega[3] = 0.025951560;
	Omega[4] = 0.025984481;
	Mat Mask1_JHJ = Mat(7,7,CV_64FC1);
	Mask1_JHJ.setTo(-1);

	cout << Mask1_JHJ << endl;

	Mask1_JHJ.at<double>(0, 0) = Omega[0];  Mask1_JHJ.at<double>(0, 3) = Omega[3];
	Mask1_JHJ.at<double>(0, 6) = Omega[0];  Mask1_JHJ.at<double>(3, 0) = Omega[3];
	Mask1_JHJ.at<double>(6, 0) = Omega[0];  Mask1_JHJ.at<double>(3, 6) = Omega[3];
	Mask1_JHJ.at<double>(6, 6) = Omega[0];  Mask1_JHJ.at<double>(6, 3) = Omega[3];
	
	Mask1_JHJ.at<double>(0, 1) = Omega[1];  Mask1_JHJ.at<double>(0, 2) = Omega[2];
	Mask1_JHJ.at<double>(0, 5) = Omega[1];  Mask1_JHJ.at<double>(0, 4) = Omega[2];
	Mask1_JHJ.at<double>(1, 0) = Omega[1];  Mask1_JHJ.at<double>(2, 0) = Omega[2];
	Mask1_JHJ.at<double>(1, 6) = Omega[1];  Mask1_JHJ.at<double>(2, 6) = Omega[2];
	Mask1_JHJ.at<double>(6, 1) = Omega[1];  Mask1_JHJ.at<double>(4, 0) = Omega[2];
	Mask1_JHJ.at<double>(6, 5) = Omega[1];  Mask1_JHJ.at<double>(4, 6) = Omega[2];
	Mask1_JHJ.at<double>(5, 0) = Omega[1];  Mask1_JHJ.at<double>(6, 2) = Omega[2];
	Mask1_JHJ.at<double>(5, 6) = Omega[1];  Mask1_JHJ.at<double>(6, 4) = Omega[2]; 
	//double sum = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (Mask1_JHJ.at<double>(j, i) == -1)
			{
				Mask1_JHJ.at<double>(j, i) = Omega[4];
			}
			//sum = sum + Mask1_JHJ.at<double>(j, i);
		}
	}
	std::cout << Mask1_JHJ << endl;
	//填充边缘轮廓并展示
	cv::drawContours(temp1,Contours,-1,Scalar::all(255),FILLED);
	cv::imshow(window_name_f3, temp1); //黑白图
	waitKey(0);

	//重新复制原图，此部分代码20200302添加，以下计算使用原图。以下计算应使用二值图还是原始灰度图存疑
	temp1 = Src.clone();
	temp1.convertTo(temp1,CV_64FC1);


	//filter2D(temp, Mu_Cal, Mu_Cal.depth(), Mask1_JHJ);
	//cout << Mu_Cal << endl;
	size_t c_s = contour.size();
	vector<vector<double>> JHJ_value; //各阶矩存储
	vector<Moments> Basic_Mu;
	vector<double> Mu_1; //1阶
	vector<double> Mu_2; //2阶
	vector<double> Mu_3; //3阶 此处计算可多线程

	Mat RoI, RoI_2, RoI_3;    //原图局部，以检测所得的边缘点为中心
	//double Temp_Mu_Value;
	
//矩计算循环 矩的计算可能需要在原始灰度图上进行（仅预处理）
	for (int i = 0; i < c_s ; i++)
	{
		//1阶矩
		RoI = temp1(Rect(contour[i].x - 3, contour[i].y - 3, 7, 7));
		Mu_1.push_back(RoI.dot(Mask1_JHJ));
		//2阶矩,灰度平方
		RoI_2 = RoI.mul(RoI);
		Mu_2.push_back(RoI_2.dot(Mask1_JHJ));
		//3阶矩，灰度立方
		RoI_3 = RoI_2.mul(RoI);
		Mu_3.push_back(RoI_3.dot(Mask1_JHJ));

		//基本的几何矩
		temp2 = Src(Rect(contour[i].x - 3, contour[i].y - 3, 7, 7));
		Basic_Mu.push_back(moments(temp2));
	}
	//再压一层
	JHJ_value.push_back(Mu_1);
	JHJ_value.push_back(Mu_2);
	JHJ_value.push_back(Mu_3);

//边缘参数计算流程
	//计算参数声明 h2,h1为灰度，sigma，s为中间参数，P_1，P_2为灰度值h1，h2所占面积的比例有关系P_1+P_2=1
	int h2;double sigma, S_Cgyt;
	int h1; //double Rho, Theta;
	double alpha;//中间参量

	vector<double> P_1, P_2,P; 
	vector<double> Theta;
	vector<double> Rho;	 //边缘最终参数，Rho为距离中心长度，Theta为偏转角度，逆时针为正

	Point2d Center_Coordinate; //重心坐标
	vector<Point2d> Contour_subPix; //结果坐标

	//边缘参数计算循环#1
	for (int i = 0; i < c_s; i++)
	{
		sigma = sqrt(Mu_2[i] - Mu_1[i] * Mu_1[i]);
		S_Cgyt = (Mu_3[i] + 2 * Mu_1[i] * Mu_1[i] * Mu_1[i] - 3 * Mu_1[i] * Mu_2[i]) / (sigma*sigma*sigma);
		
		P_1.push_back((1 + S_Cgyt * sqrt(1 / (4 + S_Cgyt * S_Cgyt))) / 2);
		P_2.push_back((1 - S_Cgyt * sqrt(1 / (4 + S_Cgyt * S_Cgyt))) / 2);
		P.push_back(MIN(P_1[i], P_2[i]));
		
		Center_Coordinate.x = (Basic_Mu[i].m10 / Basic_Mu[i].m00) - 3.5;
		Center_Coordinate.y = (Basic_Mu[i].m01 / Basic_Mu[i].m00) - 3.5; //计算重心完成后偏置至图像的重心坐标系以便计算角度theta
		//Weight_Center.push_back(Point2d(Center_Coordinate.x, Center_Coordinate.y)); 重心坐标序列压入，非必要
		
		//角度压入，为弧度制，范围[-Pi,+Pi]
		Theta.push_back(atan2(Center_Coordinate.x, Center_Coordinate.y));
	}

	//边缘参数计算循环#2
	for (int i = 0; i < c_s; i++)
	{
		alpha = Solve_Cgyt(P[i]);
		Rho.push_back(cos(alpha));
		Contour_subPix.push_back(Point2d(3.5 * Rho[i] * cos(Theta[i]) + contour[i].x, 
										 3.5 * Rho[i] * sin(Theta[i]) + contour[i].y));
	}


	return Contour_subPix;  
	/*第一个亚像素边缘检测程序（灰度矩） 20200302运行通过，因缺少另外原理的高精度测量手段，
	其精度无法验证，但是应该不会差太多，毕竟偏移量也就是0~3个像素单位。 
	若要确定其提高精度，则需要具体的手段验证，且需要布光与前置检测算法配合*/
}

double Solve_Cgyt(double P) //非线性方程组求解函数 方程为 x - 0.5*sin(2 * x) = Pi * P,使用简单迭代方法求解 20200302
{
	double Pi = 3.1415926535897935384626;
	double Err = 100;
	double x, y;
	x = 0;
	int i = 0;
	double limit; limit = pow(10, -3);
	while (Err > limit)
	{
		y = 0.5*sin(2 * x) + Pi * P;
		Err = abs(y - x);
		x = y;
		i = i + 1;
		if (i > 1000000) //注意 P=0.5左右时误差收敛较慢估计那会整到导数为0了
		{
			cout << "迭代次数超限" << endl;
			cout << "最终误差" << Err << endl;
			return y;
		}
	}
	return y;
}

//在此处写第二个，基于正常的普通矩的亚像素边缘检测方法。使用几何矩，比较一下OpenCV自带的矩计算方法与模板计算有何区别，使用重载函数，增加一个int型的输入参数用于区分
vector<Point2d> SubPixel_Contours_Cgyt(Mat Src, vector<Point> contour, int second = 2) //20200408
{
	vector<Point2d> Res;

	return Res;
}