#include "Func_Proj_2nd.h"

string Load_Path_2nd_1 = "G:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //拼接原图1
string Load_Path_2nd_2 = "G:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //拼接原图2
string Load_Path_2nd_3 = "G:\\Pictures\\Test For Programming\\001.jpg"; //分水岭分割
string Load_Path_2nd_4 = "G:\\Pictures\\Test For Programming\\加弹簧.bmp"; // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "G:\\Pictures\\Test For Programming\\香蕉3.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_6 = "G:\\Pictures\\Test For Programming\\sign_20200329.jpg"; // subPixel_Contours detect by Moments

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

	//原始图像组读取
	SRC_2nd = imread(Load_Path_2nd_4, IMREAD_GRAYSCALE);

	if (!SRC_2nd.data)
	{
		cout << "读取失败" << endl;
		return -1;
	}

	namedWindow(window_name, WINDOW_NORMAL);
	//namedWindow(window_name, WINDOW_AUTOSIZE);
	imshow(window_name, SRC_2nd);
	waitKey(0);
	Temp_Array.push_back(SRC_2nd);

/*
	Temp_Buffer = Thershold_区域(SRC_2nd);
	Temp_Array.push_back(Temp_Buffer);
	//Temp_Buffer.release();
	imshow(window_name, Temp_Array[0]);
	waitKey(0);

	//第二部分的读取代码
	SRC_2nd = imread(Load_Path_2nd_2, IMREAD_GRAYSCALE);
	if (!SRC_2nd.data)
		{
			cout << "读取失败" << endl;
			return -1;
		}
	imshow(window_name, SRC_2nd);
	waitKey(0);
	Temp_Array.push_back(SRC_2nd);
	//读取代码结束

	Temp_Buffer = JiaoDian_SURF_CGYT(Temp_Array[0], Temp_Array[1]); //SURF方法+暴力匹配实现 20200215

*/

	//vector<Point2f> subPix_Point;
	//subPix_Point = subPix_pt(Temp_Array[0]);

	//TrackBar_cgyt_canny(0, 0); //TrackBar重新熟悉

	//NLM_CGYT(Temp_Array[0]); //也是属于实时性极差，如果没有并行计算加速，几乎不可能

	//包含类的源文件该如何创建并添加至现有项目中？ 存在问题 20200318
	//Temp_Array.push_back(Conv_Cgyt(Temp_Array[0],SOBEL_CGYT)); 类的相关问题已在第三个项目中解决，至20200321未出现问题，一个源文件实现主函数，一个源文件实现类成员方法。而类定义写在另一个头文件中

	//FT_CGYT(Temp_Array[0]);  //傅里叶变换 20200323通过

	//int res_state = Calib_Cgyt(Temp_Array[0]); 注释与20200410
	//cout << res_state;

//以下启动测试 空间矩亚像素检测需要亚像素检测的前置代码，从code_used中转移至此 20200415
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
				//判定归一化的高阶中心距作为判断标准，可能四个三阶归一化中心矩均为极小数10e-4级别可认为在x、y方向均不存在偏向性，可认为该形状关于X，Y轴均对称		
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

	//亚像素边缘检测代码
	Contours_subPix_result = SubPixel_Contours_Cgyt(Temp_Array[0], Contours_for_SubPixCont, 2);

	return 0;
}