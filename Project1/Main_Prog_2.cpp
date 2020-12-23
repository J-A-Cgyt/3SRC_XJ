#include "Func_Proj_2nd.h"
#include <ctime>

//#define XPS15
#ifdef XPS15
/*----------------------------------------------XPS15 所用路径-----------------------------------------------------------------------*/
string Load_Path_2nd_1 = "G:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //拼接原图1
string Load_Path_2nd_2 = "G:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //拼接原图2
string Load_Path_2nd_3 = "G:\\Pictures\\Test For Programming\\001.jpg"; //分水岭分割
string Load_Path_2nd_4 = "G:\\Pictures\\Test For Programming\\加弹簧.bmp"; // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "G:\\Pictures\\Test For Programming\\香蕉3.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_6 = "G:\\Pictures\\Test For Programming\\sign_20200329.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_7 = "G:\\Pictures\\Test For Programming\\003.1.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_8 = "G:\\Pictures\\Test For Programming\\eye.jpg"; // subPixel_Contours detect by Moments
#endif

/*--------------------------------------------台式机MSI 所用路径---------------------------------------------------------------------*/
//#define USE_ALL
#ifdef USE_ALL
string LoadPath_Msi_0 = "F:\\Pictures\\Test For Programming\\DSC_8967.jpg";

string LoadPath_Msi_2 = "F:\\Pictures\\Test For Programming\\DSC_15774.jpg";
string LoadPath_Msi_3 = "F:\\Pictures\\Test For Programming\\DSC_15774-4.jpg";
string LoadPath_Msi_4 = "F:\\Pictures\\Test For Programming\\天山天池拼.jpg";
string LoadPath_Msi_5 = "F:\\Pictures\\Test For Programming\\xzf.jpg";  //人脸检测用图1
string LoadPath_Msi_6 = "F:\\Pictures\\Test For Programming\\DSC_21516.jpg";  //人脸检测用图1
string LoadPath_Msi_7 = "F:\\Pictures\\Test For Programming\\憨.png";  //连通域检测用途
string LoadPath_Msi_8 = "F:\\Pictures\\Test For Programming\\pai.png";  
string LoadPath_Msi_9 = "F:\\Pictures\\Test For Programming\\gpgpu.png";  
string LoadPath_Msi_A = "F:\\Pictures\\Test For Programming\\噪声测试图像.png"; 

#endif
string LoadPath_Msi_1 = "F:\\Pictures\\Test For Programming\\eye.jpg";
string LoadPath_Msi_B("F:\\Pictures\\Test For Programming\\FreqFilterSrc.png");  
string LoadPath_Msi_C = "F:\\Pictures\\Test For Programming\\1.jpg";  

/*-----------------------------------------------------------------------------------------------------------------------------------*/

string window_name = "Demo_Result"; //结果显示窗

Mat SRC_2nd; //全局源图
Mat DST_2nd; //全局输出图
//clock_t Start, End;


//关于自制卷积函数的枚举类型说明
enum Conv_cgyt
{
	SOBEL_CGYT = 0,
	LAPLACE8_CGYT = 1,
	LAPLACE4_CGYT = 2,
	GARDIENT1_CGYT = 3,
	SOBEK_X_CGYT = 4,
};
//瞳孔检测的方法选择
enum Iris_dect
{
	HOUGH = 0,
	COUNTOUR = 1,
};

int main()
{
	std::vector<Mat> Temp_Array;
	Mat Temp_Buffer;
	//namedWindow(window_name, WINDOW_KEEPRATIO);
	namedWindow(window_name, WINDOW_AUTOSIZE);

	//原始图像组读取	
	SRC_2nd = imread(LoadPath_Msi_1, IMREAD_GRAYSCALE);
	cout << SRC_2nd.type();
	if (!SRC_2nd.data)
	{
		cout << "读取失败" << endl;
		return -1;
	}
	imshow(window_name, SRC_2nd);
	waitKey(0);
 

	//以下是亚像素检测实现的前置处理
	Temp_Array.push_back(SRC_2nd);

	Temp_Buffer = Gaosi_双边(Temp_Array[0]); //高斯滤波+锐化
	equalizeHist(Temp_Buffer,Temp_Buffer);
	GaussianBlur(Temp_Buffer, Temp_Buffer, Size(7, 7), 1);
	imshow(window_name, Temp_Buffer);
	waitKey(0);
	Temp_Array.push_back(Temp_Buffer);

	Canny(Temp_Array[1], Temp_Buffer, 30, 150); //canny边缘检测
	imshow(window_name, Temp_Buffer);
	waitKey(0);
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
	if (Contours_for_SubPixCont.size() == 0) { throw out_of_range("没有符合条件的素材边缘!"); return -1; }
	Contours_for_SubPixCont = Contours_Seletced[0];
	cvtColor(Temp_Array[0], Temp_Buffer, COLOR_GRAY2BGR);
	drawContours(Temp_Buffer, Contours_Seletced, -1, Scalar(0, 0, 255));
	imshow(window_name, Temp_Buffer);
	waitKey(0);
	Temp_Array.push_back(Temp_Buffer); //指针问题未明确，注意传输地址导致vector容器中内容一致的可能

	//亚像素边缘检测代码
	Contours_subPix_result = SubPixel_Contours_Cgyt(Temp_Array[0], Contours_for_SubPixCont, 2.0);


	//HistogramCGYT(SRC_2nd);
	//FT_CGYT(SRC_2nd, Temp_Buffer);
	//Filter_Freq(Temp_Buffer,4);
	//Temp_Buffer = HarmonicMeanFilter(SRC_2nd, 2,1,1);
	
	//imshow(window_name, Temp_Buffer);
	//waitKey(0)
	;
//一下内容 20201025玩一下 C++习惯和新知识的练习试验

	
	//imshow(window_name, DST_2nd);
	//waitKey(0);

	//Temp_Buffer = CannyG_Cgyt(SRC_2nd);
	//HoughLineG_Cgyt(Temp_Buffer);
	//threshold(SRC_2nd, Temp_Buffer, 200, 255, THRESH_BINARY);
	//Components_Connected_cgyt(Temp_Buffer);
	//FaceG_cgyt(SRC_2nd);  //此函数GPU版本报错 不可用不知道啥没实现 CPU可行
	//IrisDectH_GPU(SRC_2nd);
	//ORBG_cgyt(SRC_2nd);
	//SURFG_cgyt(SRC_2nd, Temp_Buffer); //surf的GPU版本配合代码，20200723注释


	destroyAllWindows(); //销毁所有窗口，手动内存管理

	return 0;
}

//和师兄聊天以后发现 效率方面的优化还有很多事情可以做，实现了方法以后还是要讲求效率，指令集这块似乎也是一个好的方法