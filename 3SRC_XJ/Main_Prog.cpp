#include "Func.h"
//解释一下，这个解决方案是我的试验台，各种瞎几把写的代码都有专门用于hough变换的圆检测吧 写个类
//形成功能的代码可以从这里移植出去，到其他的项目

Mat SRC,DST;

string Load_Path_1 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Circle_in_slot_2\\CIS_2.jpg";
string Load_Path_2 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Circle_in_slot_2_BackLight\\CIS_B_1.jpg";
string Load_Path_3 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Full_circle\\20191114-102834-305.jpg"; //20200335 完成
string Load_Path_4 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Side_slot\\20191114-110032-155.jpg";
string Load_Path_5 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Top_slot\\20191114-110910-75.jpg";

string Window_Name = "Demo_Result";

int GS_Ksize = 27;
int Thershold = 4; //橡胶垫检测为40


int main()
{
	Mat Temp1, Temp2, Temp3, Temp4;	
	//vector<vector<Point>> BY_Contours;
	vector<Vec3f> Circles;
	vector<vector<Vec3f>> Array_of_circles;
	vector<Vec2f> Lines;  //直线检测的测试代码，于2019/11/12开始更新
    
	namedWindow(Window_Name, WINDOW_NORMAL);
	
	SRC = imread(Load_Path_5);
	if (!SRC.data)
	{
		cout << "图像读取失败" << endl;
		return -1;
	}

	//resize(SRC, SRC, Size(800, 600));
	Mat Map = SRC.clone();//该图像（矩阵）用于标识特征
	cvtColor(SRC, SRC, COLOR_BGR2GRAY);
	imshow(Window_Name, SRC);
	waitKey(0);

	//Temp1 = ZhiFangTu_JunHua(SRC);
	//imshow(Window_Name, Temp1);
	//waitKey(0);

	Temp1 = Gaosi_Mohu(SRC, GS_Ksize); //高斯模糊
	//Temp3 = Gaosi_双边(SRC);  //边缘保持滤波尝试
	imshow(Window_Name, Temp1);
	waitKey(0);

//以下是金属盘型零件空洞位置及尺寸检测的测试代码，精度未验证，起始时间	
	//Circles = Hough_circle(Temp1, Map);  //一级圆检测

/*
	针对顶部就有导流槽的大圆孔轮廓现想到两种办法：
	1、使用两次Hough变换分别识别大圆与凹槽轮廓半圆，并依据其相对位置关系进行检测判定

	2、使用canny等算子提取边缘轮廓，计算其矩以相似度匹配，通过轮廓边长、各属性矩值等

	值得注意的是，此二者实现的匹配方法仍旧需设定较为严格的拍摄条件，容错能力较差且缺乏尺度不变性。
	两种方法均需获取设计的无误差图纸以计算理想模板方能完成质量检测。
	且考虑到分辨率限制，预估精度不会高于0.1mm数量级。
	具体方法实现如下，霍夫变换代码与前面三类图像复用
*/

//-------------------------------------------------以下为Hough变换方法实现----------------------------------------------------------------------------------------------------
	Hough_Param Param_FC;

	Temp2 = ZhiFangTu_JunHua(Temp1);
	cout << "直方图均化结果" << endl;
	imshow(Window_Name, Temp2);
	waitKey(0);

	Circles = Hough_circle_Class(Temp1,Map,Param_FC);
	if (Circles.size() == 0)
	{
		cout << "未检测到圆" << endl;
		//return 1;
	}
	Array_of_circles.push_back(Circles);

/*
	Circles = Hough_circle_Copy1(Temp1, Map); //二级圆检测
	if (Circles.size() == 0)
	{
		cout << "未检测到圆" << endl;
		//return 1;
	}
	Array_of_circles.push_back(Circles);

	Circles = Hough_circle_Copy2(Temp1, Map); //槽内小圆检测
	if (Circles.size() == 0)
	{
		cout << "未检测到圆" << endl;
		//return 1;
	}
	Array_of_circles.push_back(Circles);
*/	

	if (Array_of_circles.size() == 0)
	{
		cout << "未检测到圆" << endl;
		return 1;
	}

	Draw_Circles(Array_of_circles, Map);

	//Hough_Lines(Temp1, Map);

//----------------------------------------------------------以下为矩方法实现--------------------------------------------------------------------------------------------------
	return 0;
}