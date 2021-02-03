#include "Func_Proj_2nd.h"

string Load_Path_2nd_1 = "F:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //拼接原图1
string Load_Path_2nd_2 = "F:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //拼接原图2
string Load_Path_2nd_3 = "F:\\Pictures\\Test For Programming\\001.jpg"; //分水岭分割
string Load_Path_2nd_4 = "F:\\Pictures\\Test For Programming\\加弹簧.bmp"; // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "F:\\Pictures\\Test For Programming\\香蕉3.jpg"; 
string Load_Path_2nd_6 = "F:\\Pictures\\Test For Programming\\sign_20200329.jpg";
string Load_Path_2nd_7 = "F:\\Pictures\\Test For Programming\\003.1.jpg"; 
string Load_Path_2nd_8 = "F:\\Pictures\\Test For Programming\\eye.jpg"; 
string window_name = "Demo_Result"; //结果显示窗

Mat SRC_2nd; //全局源图
Mat DST_2nd; //全局输出图


//关于自制卷积函数的枚举类型说明
enum Conv_cgyt
{
	SOBEL_CGYT = 0,
	LAPLACE_CGYT = 1,
	GARDIENT1_CGYT = 2,
};

int main()
{
	std::vector<Mat> Temp_Array;
	Mat Temp_Buffer;

	Calib_Cgyt(Mat());

	//原始图像组读取
	SRC_2nd = imread(Load_Path_2nd_4, IMREAD_GRAYSCALE);

	if (!SRC_2nd.data)
	{
		cout << "读取失败" << endl;
		return -1;
	}
	Temp_Array.push_back(SRC_2nd);
	//以下是亚像素检测实现的前置处理

	Temp_Buffer = Gaosi_双边(Temp_Array[0]); //高斯滤波+锐化
	//imshow(window_name, Temp_Buffer);
	//waitKey(0);
	Temp_Array.push_back(Temp_Buffer);

	Canny(Temp_Array[1], Temp_Buffer, 80, 240); //canny边缘检测
	//imshow(window_name, Temp_Buffer);
	//waitKey(0);
	Temp_Array.push_back(Temp_Buffer);

	vector<vector<Point>> Contours_Dected, Contours_Seletced;
	vector<Point> Contours_for_SubPixCont;
	vector<Point2d> Contours_subPix_result;
	Moments 矩;
	findContours(Temp_Array[2], Contours_Dected, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());  //圆形特征初步定位	
	for (int i = 0; i < Contours_Dected.size(); i++)
	{
		size_t k = Contours_Dected[i].size();
		if (k < 1000 && k > 700)
		{
			矩 = moments(Contours_Dected[i]);
			if (abs(矩.nu11) < 0.001)
			{
				//判定归一化的高阶中心距作为判断标准，可能四个三阶归一化中心矩均为极小数10e-4级别可认为在x、y方向均不存在偏向性，可认为该形状本身旋转不变		
				Contours_Seletced.push_back(Contours_Dected[i]);
			}
		}
	}
	Contours_for_SubPixCont = Contours_Seletced[0];
	cvtColor(Temp_Array[0], Temp_Buffer, COLOR_GRAY2BGR);
	drawContours(Temp_Buffer, Contours_Seletced, -1, Scalar(0, 0, 255));
	imshow(window_name, Temp_Buffer);
	waitKey(0);
	Temp_Array.push_back(Temp_Buffer); //指针问题未明确，注意传输地址导致vector容器中内容一致的可能


	/*
	Temp_Array检查
	for (int k = 0; k < Temp_Array.size(); k++)
	{
		imshow(window_name, Temp_Array[k]);
		cout << k << endl;
		waitKey(0);
	}
	*/

	//Temp_Array[1]是canny检测结果
	//SubPixel_Contours_Cgyt(Temp_Array[1],Contours_for_SubPixCont);

	//亚像素边缘检测代码
	Contours_subPix_result = SubPixel_Contours_Cgyt(Temp_Array[0], Contours_for_SubPixCont,1.0);
	cout << Contours_subPix_result[0] << endl;



	return 0;
}