#include "Func_Proj_2nd.h"

string Load_Path_2nd_1 = "G:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //拼接原图1
string Load_Path_2nd_2 = "G:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //拼接原图2
string Load_Path_2nd_3 = "G:\\Pictures\\Test For Programming\\001.jpg"; //分水岭分割
string Load_Path_2nd_4 = "G:\\Pictures\\Test For Programming\\加弹簧.bmp"; // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "G:\\Pictures\\Test For Programming\\香蕉3.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_6 = "G:\\Pictures\\Test For Programming\\sign_20200329.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_7 = "G:\\Pictures\\Test For Programming\\003.1.jpg"; // subPixel_Contours detect by Moments

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
	SRC_2nd = imread(Load_Path_2nd_1, IMREAD_GRAYSCALE);

	if (!SRC_2nd.data)
	{
		cout << "读取失败" << endl;
		return -1;
	}

	namedWindow(window_name, WINDOW_AUTOSIZE);
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

	//vector<Point2f> subPix_Point;
	//subPix_Point = subPix_pt(Temp_Array[0]);

	//TrackBar_cgyt_canny(0, 0); //TrackBar重新熟悉

	//包含类的源文件该如何创建并添加至现有项目中？ 存在问题 20200318
	//Temp_Array.push_back(Conv_Cgyt(Temp_Array[0],SOBEL_CGYT)); 类的相关问题已在第三个项目中解决，至20200321未出现问题，一个源文件实现主函数，一个源文件实现类成员方法。而类定义写在另一个头文件中

	//FT_CGYT(Temp_Array[0]);  //傅里叶变换 20200323通过

	//int res_state = Calib_Cgyt(Temp_Array[0]); 注释与20200410
	//cout << res_state;

	Temp_Buffer = Anisotropic_Cgyt(Temp_Array[0], 20, 0.75, 10);
	imshow(window_name, Temp_Buffer);	
	imwrite("G:\\Pictures\\Test For Programming\\003.2.jpg", Temp_Buffer);
	cout << "end" << endl;
	waitKey(0);
	
	Temp_Buffer = AnisotropicMT_Cgyt(Temp_Array[0], 20, 0.75, 10);
*/

	Temp_Buffer = WaveLetHarrD_CGYT(Temp_Array[0], 1);
	imshow(window_name, Temp_Buffer);
	waitKey(0);

	Temp_Array[0] = WaveLetHarrR_CGYT(Temp_Buffer, 1);
	imshow(window_name, Temp_Array[0]);
	waitKey(0);

	return 0;
}