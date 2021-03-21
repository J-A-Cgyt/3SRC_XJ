#include "Func_Proj_2nd.h"


#define HK_CAMERA

#ifdef before_2021
string Load_Path_2nd_1 = "F:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //拼接原图1
string Load_Path_2nd_2 = "F:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //拼接原图2
string Load_Path_2nd_3 = "F:\\Pictures\\Test For Programming\\001.jpg";      //分水岭分割
string Load_Path_2nd_4 = "F:\\Pictures\\Test For Programming\\加弹簧.bmp";   // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "F:\\Pictures\\Test For Programming\\香蕉3.jpg"; 
string Load_Path_2nd_6 = "F:\\Pictures\\Test For Programming\\sign_20200329.jpg";
string Load_Path_2nd_7 = "F:\\Pictures\\Test For Programming\\003.1.jpg"; 
string Load_Path_2nd_8 = "F:\\Pictures\\Test For Programming\\eye.jpg";
#endif

#ifdef HK_CAMERA
string Load_Path_2nd_9 = "F:\\Pictures\\Test For Programming\\HIK12MP\\StitchImg_1.jpg";
string Load_Path_2nd_A = "F:\\Pictures\\Test For Programming\\HIK12MP\\StitchImg_2.jpg";
string Load_Path_2nd_B = "F:\\Pictures\\Test For Programming\\HIK12MP\\StitchImg_3.jpg";
string Load_Path_2nd_C = "F:\\Pictures\\Test For Programming\\HIK12MP\\StitchImg_4.jpg";
#endif // HK_CAMERA


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
	namedWindow(window_name, WINDOW_NORMAL);
	//Calib_Cgyt(Mat()); 20210203注释

	//原始图像组读取
	SRC_2nd = imread(Load_Path_2nd_9, IMREAD_GRAYSCALE);
	if (!SRC_2nd.data){
		cout << "读取失败" << endl;
		return -1;
	} 
	Temp_Array.push_back(SRC_2nd);
	
	SRC_2nd = imread(Load_Path_2nd_A, IMREAD_GRAYSCALE);
	if (!SRC_2nd.data) {
		cout << "读取失败" << endl;
		return -1;
	}
	Temp_Array.push_back(SRC_2nd);

	//Temp_Buffer = JiaoDian_SURF_CGYT(Temp_Array[0], Temp_Array[1]); //SURF方法+暴力匹配实现 20200215
	pic_Move_Cgyt(Temp_Array[0], Temp_Buffer, -600, -600);
	
	return 0;
}