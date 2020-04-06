#include "Func.h"

string Window_name = "Demo_Result";

vector<vector<Point>> BianYuan(Mat Src)
{
	Mat temp1, temp2;
	temp1 = Src.clone();
	vector<vector<Point>> Contours_Points;
	vector<vector<Point>> Contours_Selected;

	findContours(temp1, Contours_Points, RETR_EXTERNAL, CHAIN_APPROX_NONE);

	size_t K = Contours_Points.size();
	for (int k = 0; k < K; k++)
	{
		int Length = Contours_Points[k].size();

		//橡胶垫参数600-1600
		if (Length > 4000)
		{
			RotatedRect MinRect;
			MinRect = minAreaRect(Contours_Points[k]);
			double Width;

			Width = abs(MinRect.size.width - MinRect.size.height);

			//if (Width < 60)橡胶垫判定需求
			//{
				Contours_Selected.push_back(Contours_Points[k]);
			//}
		}

	}

	cvtColor(temp1, temp2, COLOR_GRAY2BGR);
	drawContours(temp2, Contours_Selected, -1, Scalar(0, 0, 255), 1, 8);
	
	imshow(Window_name, temp2);
	waitKey(0);
	
	return Contours_Points;
}

Mat Canny_边缘(Mat Src, int lowThreshold)
{
	Mat dst, detected_edges,src;
	src = Src.clone();	
	
	dst.create(Src.size(), Src.type());
	dst = Scalar::all(0);
	
	int edgeThresh = 1;//？	  
	int Ratio = 20;
	int kernel_size = 5;

	blur(Src, detected_edges, Size(kernel_size, kernel_size));//以3*3的矩形为核降噪
	Canny(detected_edges, detected_edges, lowThreshold, lowThreshold * Ratio, kernel_size);//canny边缘检测
	//lowThreshold最大100,高低阈值之比可不为3，但此处默认为3

	src.copyTo(dst, detected_edges);//将检测所得的结果作为掩码使源图像拷贝至输出矩阵
	imshow(Window_name, dst);//显示图像
	waitKey(0);

	return detected_edges;
}

vector<Vec3f> Hough_circle(Mat src,Mat Map)
{
	int Hough_Method = HOUGH_GRADIENT;
	double dp = 1;
/*	
    double mindist = 15;
	double Param1 = 80;
	double Param2 = 75;
	int minRadius = 0;
	int maxRadius = 200; 2019-6-19 螺纹弹簧.JPG 圆检测参数
	
	double mindist = 30;
	double Param1 = 120;
	double Param2 = 75;
	int minRadius = 80;
	int maxRadius = 120;	 //橡胶垫圆点检测参数
*/	
	
	double mindist = 50;
	double Param1 = 70;
	double Param2 = 50;
	int minRadius = 80;
	int maxRadius = 400;	 //金属机械件检测圆参数 20200309
	
	//霍夫检测参数组结束

	vector<Vec3f> Circles;
	Mat tempA;

	//霍夫圆检测
	tempA = src.clone();
	

	HoughCircles(tempA, Circles, Hough_Method, dp, mindist, Param1, Param2, minRadius, maxRadius);
     /*此处需要有对检测的特征进行筛选的代码，针对不同对象需要设置不同的阈值参数*/

	 /*
	 tempB = Map.clone();
	for (size_t k = 0; k < Circles.size(); k++)
	{
		circle(tempB, Point(Circles[k].val[0], Circles[k].val[1]), int(Circles[k].val[2]), Scalar(0, 0, 255), 5);
		
				string R = std::to_string(int(Circles[k].val[0]));
				R.push_back(',');
				R=cout //似乎除了构造函数，在往string里填字符的时候可以接收一般的数字型数据类型 2019-6-19
				putText(tempB, R, Point(Circles[k].val[0], Circles[k].val[1]), FONT_HERSHEY_DUPLEX, 0.8, Scalar(0, 0, 255));
		
		cout << Circles[k].val[0] << "," << Circles[k].val[1] << endl;
		cout << "R=" << Circles[k].val[2] << endl;
	}

	imshow(Window_name, tempB);
	waitKey(0);
    */

	return Circles;
}

vector<Vec2f> Hough_Lines(Mat src, Mat Map) //包括随机颜色的绘制完成时间20200310
{
	vector<Vec2f> Lines;
	Mat temp = Map.clone();

	//Hough检测参数
	double Rho = 100;
	double Theta = 0.3;
	double Threshold = 200;
	HoughLines(src, Lines, Rho,Theta,Threshold);
	/*
	第一个参数，InputArray类型的image，输入图像，即源图像，需为8位的单通道二进制图像，可以将任意的源图载入进来后由函数修改成此格式后，再填在这里。
	第二个参数，InputArray类型的lines，经过调用HoughLines函数后储存了霍夫线变换检测到线条的输出矢量。每一条线由具有两个元素的矢量表示，其中，是离坐标原点((0,0)（也就是图像的左上角）的距离。 是弧度线条旋转角度（0~垂直线，π/2~水平线）。
	第三个参数，double类型的rho，以像素为单位的距离精度。另一种形容方式是直线搜索时的进步尺寸的单位半径。PS:Latex中/rho就表示 。
	第四个参数，double类型的theta，以弧度为单位的角度精度。另一种形容方式是直线搜索时的进步尺寸的单位角度。
	第五个参数，int类型的threshold，累加平面的阈值参数，即识别某部分为图中的一条直线时它在累加平面中必须达到的值。大于阈值threshold的线段才可以被检测通过并返回到结果中。
	第六个参数，double类型的srn，有默认值0。对于多尺度的霍夫变换，这是第三个参数进步尺寸rho的除数距离。粗略的累加器进步尺寸直接是第三个参数rho，而精确的累加器进步尺寸为rho/srn。
	第七个参数，double类型的stn，有默认值0，对于多尺度霍夫变换，srn表示第四个参数进步尺寸的单位角度theta的除数距离。且如果srn和stn同时为0，就表示使用经典的霍夫变换。否则，这两个参数应该都为正数。
	第八个参数，double类型的 min_theta，对于标准和多尺度Hough变换，检查线条的最小角度。必须介于0和max_theta之间。
	第九个参数，double类型的 max_theta, 对于标准和多尺度Hough变换，检查线条的最大角度。必须介于min_theta和CV_PI之间.
	*/
	
	//绘制参数
	const int s = 10000;
	double Cos_cgyt, Sin_cgyt;
	float Rho_cgyt, Theta_cgyt;
	double x, y;

	for (int i = 0; i < Lines.size(); i++)
	{
		Rho_cgyt = Lines[i][0];
		Theta_cgyt = Lines[i][1];
		
		Cos_cgyt = cos(Theta_cgyt);
		Sin_cgyt = sin(Theta_cgyt);
		
		x = Sin_cgyt * Rho_cgyt; 
		y = Cos_cgyt * Rho_cgyt;

		Point2i Pt1 = Point2i(cvRound(x + Sin_cgyt * s), cvRound(y - Cos_cgyt * s));
		Point2i Pt2 = Point2i(cvRound(x - Sin_cgyt * s), cvRound(y + Cos_cgyt * s));

		RNG random_color;  //随机数生成器
		int seed = (i + 500) % 255; //这应该是最大值范围？
		Scalar Color_ran = Scalar(random_color.uniform(0, seed),
								  random_color.uniform(0, seed),
								  random_color.uniform(0, seed));

		line(temp,Pt1,Pt2,Color_ran);
	}
	
	imshow(Window_name, temp);
	waitKey(0);

	return Lines;
}

Mat 图像减(Mat 被减, Mat 减)
{
	Mat Result(Size(被减.rows, 被减.cols), 被减.type());
	if (被减.rows == 减.rows & 被减.cols == 减.cols)
	{
		if (被减.channels() != 减.channels())
		{
			cout << "图像相减出错(通道数不吻合)" << endl;
			return Result;
		}
		else
		{
			Result = 被减 - 减;
			return Result;
		}
	}
	else
	{
		cout << "图像相减出错(尺寸不吻合)" << endl;
		return Result;
	}
}

Mat Harris_XJB(Mat Src)
{
	Mat Temp_Buffer;
	//harris角点检测测试 2020/1/16
	Temp_Buffer = Src.clone();
	cout << Temp_Buffer.at<uchar>(2329, 29) << endl;

	cornerHarris(Src, Temp_Buffer, 11, 11, 0.03);
	/* 
	//看起来输出的mat不能直接用imshow，不是可以显示的图像类型
	Harris的输出为范围float32单通道图像矩阵，确定需要自行确定角点位置，
	但是数据不如cv::KeyPoints类中那么全，就现在而言没空写底层的特征点匹配算法
	*/
	
	normalize(Temp_Buffer, Temp_Buffer, 0, 255, NORM_MINMAX);
	cout << Temp_Buffer.at<float>(2329, 29) << endl;

	Temp_Buffer.convertTo(Temp_Buffer, CV_8U);

	imshow(Window_name, Temp_Buffer);
	waitKey(0);

	return(Temp_Buffer);
	//以上代码于2020/1/16调试通过，可圈出角点但是没什么卵用
}