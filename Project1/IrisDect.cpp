#include "Func_Proj_2nd.h"
#include <opencv2/cudaimgproc.hpp>
#include <thread>

Point2f IrisDect(Mat Src,int method)
{
//霍夫变换的检测方法
	if (method == 0)
	{
		int Hough_Method = HOUGH_GRADIENT;
		double dp = 1;
		double mindist = 30;
		double Param1 = 40;
		double Param2 = 45;
		int minRadius = 100;
		int maxRadius = 150;	 //虹膜检测参数 20200528
		//霍夫检测参数组结束

		vector<Vec3f> Circles;
		Mat tempA;

		//霍夫圆检测
		tempA = Src.clone();

		HoughCircles(tempA, Circles, Hough_Method, dp, mindist, Param1, Param2, minRadius, maxRadius);
		
		Point2f CenterCord;
		//检测个圆先看看
		cvtColor(Src, tempA, COLOR_GRAY2BGR);
		for (int i = 0; i < Circles.size(); i++)
		{
			CenterCord.x = Circles[i].val[0];
			CenterCord.y = Circles[i].val[1];

			circle(tempA, CenterCord,
				int(Circles[i].val[2]), Scalar(0, 0, 255), 3);
		}
		imshow("Demo_Result", tempA);
		waitKey(0);
		return CenterCord;
	}
	else if (method == 1)
	{
		Mat tempB1 = Src.clone();		
		Mat tempB2;
		//resize(tempB1,tempB1,Size(980, 740));
		//cout << tempB1.type();

		tempB2 = AnisotropicMT_Cgyt(tempB1, 20, 0.75, 10);
		cout << "end" << endl;
		imshow("Demo_Result", tempB2);
		waitKey(0);
		equalizeHist(tempB2, tempB2);
		//Laplace已经试过了效果不好，试一下形态学吧
		Mat kernel = getStructuringElement(MORPH_CROSS,Size(7,7));  //形态学卷积核
		morphologyEx(tempB2, tempB2, MORPH_OPEN,kernel);  //形态学操作
		imshow("Demo_Result", tempB2);
		waitKey(0);
		//阈值+滤波
		threshold(tempB2, tempB2, 20, 255, THRESH_BINARY);
		GaussianBlur(tempB2, tempB2, Size(15, 15), 0);		
		threshold(tempB2, tempB2, 10, 255, THRESH_BINARY_INV);
		imshow("Demo_Result", tempB2);
		waitKey(0);
		//边缘提取
		vector<vector<Point>> Contours;
		findContours(tempB2, Contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);		
		cvtColor(Src, tempB1, COLOR_GRAY2BGR);
		drawContours(tempB1, Contours, -1, Scalar(0, 0, 255), 3);
		imshow("Demo_Result", tempB1);
		waitKey(0);
	}
	
	return Point2f();
}