#include "Func_Proj_2nd.h"
#include <ctime>
#include "DataTransTCP.h"

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
string LoadPath_Msi_1 = "F:\\Pictures\\Test For Programming\\eye.jpg";
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

string LoadPath_Msi_B("F:\\Pictures\\Test For Programming\\FreqFilterSrc.png");  
string LoadPath_Msi_C = "F:\\Pictures\\Test For Programming\\1.jpg"; 
string LoadPath_Msi_D("F:\\Pictures\\Test For Programming\\coins\\coin_6.bmp");

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
	namedWindow(window_name, WINDOW_NORMAL);
	//namedWindow(window_name, WINDOW_AUTOSIZE);

	//原始图像组读取	
	SRC_2nd = imread(LoadPath_Msi_D, IMREAD_GRAYSCALE);
	cout << SRC_2nd.type();
	if (!SRC_2nd.data)
	{
		cout << "读取失败" << endl;
		return -1;
	}
	imshow(window_name, SRC_2nd);
	waitKey(0);
	Temp_Array.push_back(SRC_2nd);  //Temp_Array[0];
	Temp_Buffer = SRC_2nd.clone();
 
	//GaussianBlur(Temp_Buffer, Temp_Buffer, cv::Size(7, 7), 0);
	Temp_Array.push_back(Temp_Buffer);

	//边缘图像计算
	Laplacian(Temp_Buffer, Temp_Buffer, CV_8UC1);
	//convertScaleAbs(Temp_Buffer, Temp_Buffer);
	threshold(Temp_Buffer, Temp_Buffer, 14, 1, THRESH_BINARY);  //这个人为规定的数值可能会导致不同曝光参数的图结果不一样 事实证明直到coin5才出现明显的问题 适应性还是很强的 对coin2-4阈值设定为14
	//而coin5因曝光参数设置问题已经难以区分背景和硬币部分的边缘明显程度 这样的图说不定直接OTSU会有更好的结果（都差不多亮 才会导致这样的结果） COIN5果然是直接OTSU效果好
	//原图与边缘图相乘
	Mat masked = Temp_Buffer.mul(Temp_Array[0]);
	imshow(window_name, masked);
	waitKey(0);

	//OTSU之前最好弄个边缘检测的
	//double otsu_value = threshold(SRC_2nd, Temp_Buffer, 0, 255, THRESH_OTSU);  //顺便把otsu的值记录一下 73 直接OTSU
	double otsu_value = threshold(masked, Temp_Buffer, 0, 255, THRESH_OTSU);     //顺便把otsu的值记录一下 54 边缘强化OTSU
	threshold(SRC_2nd, Temp_Buffer, otsu_value, 255, THRESH_BINARY);
	imshow(window_name, Temp_Buffer);
	waitKey(0);

	std::vector<std::vector<cv::Point2i>> contours;								 //存一个附属图像吧，作为TCP发送的局部原始图像用于测试局部通信
	findContours(Temp_Buffer, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	std::vector<std::vector<cv::Point2i>> selected_Contours;

	auto iterC = contours.begin(); //迭代器
	for (; iterC < contours.end(); iterC++) {
		if (iterC->size() >= 3000 && iterC->size()<4000) {
			selected_Contours.push_back(*iterC);
		}
	}

	if (selected_Contours.size() == 0) {
		printf("Error：没有找到合适的边缘\n");
		return -3;
	}


	//增加一个步骤 保存一个局部图像 在算法试验是无需
	/*
	 cv::Rect rectRoI(cv::boundingRect(selected_Contours[0])); //需要往外扩展 上下左右各20pix
	 cv::Rect extendRoI(rectRoI.x - 20, rectRoI.y - 20, rectRoI.width + 40, rectRoI.height + 40);
	 cv::Mat RoI(SRC_2nd(extendRoI));
	 imwrite("F:\\Pictures\\Test For Programming\\coins\\coin_6_RoI.jpg", RoI);
	 */
	 
	contours.clear(); //清空边缘

	cv::Mat doubleSrc;	
	SRC_2nd.convertTo(doubleSrc,CV_64FC1);
	std::vector<cv::Point2d> subpixPoints;  //亚像素级的轮廓坐标点
	subpixPoints = SubPixel_Contours_Cgyt(doubleSrc, selected_Contours[0], 3.0);  
	//这个其实已经可以向高级主控传送检测结果了还是用TCP协议但是如何发送还是个问题 不过似乎有相应的网页看看先20210312 好像不能传诶
	
	//要不到时单独开一个线程用来传输 join还是要的 否则引用的内存区被清理了估计得报错 似乎不能应用俩参数 写几个就得几个 20210317暂时注释
	//std::thread tSend = thread(ContoursSubpixSend,subpixPoints); 
	//tSend.join();

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