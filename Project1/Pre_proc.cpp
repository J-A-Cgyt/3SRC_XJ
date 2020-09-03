#include "Func_Proj_2nd.h"

string window_name_f2 = "Demo_Result"; //结果显示窗

Mat Thershold_区域(Mat Src)
{
	//自带自适应阈值参数组
	double Max_Value = 255;  //最大值
	int Block_Size = 159;     //区块尺寸（像素值）
	int C = 5;              //均值计算以后阈值的偏移量 （-C）

	Mat Dst;
	adaptiveThreshold(Src, Dst, Max_Value, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, Block_Size, C);

	return Dst;
}

//再尝试一下傅里叶变换吧，没道理就这个函数用不了 启动20200323
Mat FT_CGYT(Mat Src)
{
	Mat temp = Src.clone();

	int row_opt = getOptimalDFTSize(Src.rows);
	int col_opt = getOptimalDFTSize(Src.cols);

	copyMakeBorder(Src, temp, 0, row_opt - Src.rows, 
							  0, col_opt - Src.cols, 
							  BORDER_CONSTANT, Scalar::all(0));

	Mat FT_res = Mat(temp.size(), CV_32FC2); //图像尺寸设定存疑
	//Mat FT_res = Mat(temp.rows + row_opt, temp.cols + col_opt, CV_32FC2); //空矩阵 注意，此处矩阵尺寸并非重要参数，设定双通道float类型的数据即可
	
	Mat mForFourier[] = { Mat_<float>(temp),//源矩阵的浮点数化通道1 
						  Mat::zeros(temp.size(), CV_32F)  //尺寸与源矩阵相同的的0矩阵通道2
	}; 
						 
	Mat FT_src;
	merge(mForFourier, 2, FT_src); //源矩阵通道合并

	dft(FT_src, FT_res); //FT_res的两个通道分别为变换结果的实部和虚部

	vector<Mat> channels_res;
	split(FT_res, channels_res);
	Mat FT_R = channels_res[0];  //实部
	Mat FT_I = channels_res[1];  //虚部

	//模长计算，（对应坐标的复数模长计算）
	Mat mAmplitude;
	magnitude(FT_R, FT_I, mAmplitude);  //幅值计算函数

	mAmplitude += Scalar(1); //取对数前不能有长度为0的像素灰度值，+1后保证所有对数值非负
	log(mAmplitude, mAmplitude); //取对数

	normalize(mAmplitude, mAmplitude, 0, 255, NORM_MINMAX); //归一化（0~255，即uchar的表示范围

	mAmplitude.convertTo(mAmplitude, CV_8UC1);  //矩阵类型转换
	imshow(window_name_f2, mAmplitude);
	waitKey(0);

	Rect Achor_cgyt[4];
	Achor_cgyt[0] = Rect(0, 0, 
						 col_opt / 2, row_opt / 2); //此构造函数为左上角坐标与长宽值，不是左上角坐标和右下角坐标
	Achor_cgyt[1] = Rect(col_opt / 2, 0,
						 col_opt / 2, row_opt / 2);
	Achor_cgyt[2] = Rect(0, row_opt / 2,
						 col_opt / 2, row_opt / 2);
	Achor_cgyt[3] = Rect(col_opt / 2, row_opt / 2,
						 col_opt / 2, row_opt / 2);
	Mat PartQ[4];
	for (int i = 0; i < 4; i++)
	{
		PartQ[i] = mAmplitude(Achor_cgyt[i]);
		imshow(window_name_f2, PartQ[i]);
		waitKey(0);
	}

	copyMakeBorder(PartQ[0], PartQ[0], row_opt / 2, 0, col_opt / 2, 0, BORDER_CONSTANT, 0);
	copyMakeBorder(PartQ[2], PartQ[2], 0, row_opt / 2, col_opt / 2, 0, BORDER_CONSTANT, 0);
	copyMakeBorder(PartQ[1], PartQ[1], row_opt / 2, 0, 0, col_opt / 2, BORDER_CONSTANT, 0);
	copyMakeBorder(PartQ[3], PartQ[3], 0, row_opt / 2, 0, col_opt / 2, BORDER_CONSTANT, 0);

	Mat Location_rev = Mat(Size(col_opt, row_opt), CV_8UC1);
	Location_rev.setTo(0);	
	
	Location_rev = PartQ[0] + PartQ[1] + PartQ[2] + PartQ[3];
	imshow(window_name_f2, Location_rev);
	waitKey(0);
	//mAmplitude.copyTo(Location_rev );

	return Location_rev; //因坐标轴变化需中心化后方可进行滤波操作，滤完以后再换回来（还是得看OpenCV自己的实现方法），频域滤波可以再写个类了
}

//在此处借用有一下地方，先写个直线段检测的函数在此
vector<Vec4f> LSD_cgyt(Mat Src)
{
	Mat temp = Src.clone();
	vector<Vec4f> Lines_Decd; //检测所得线段容器
	
	//直线检测器对象实例化,注意参数选择
	Ptr<LineSegmentDetector> LSD_CGYT_Dec = createLineSegmentDetector(LSD_REFINE_STD);

	LSD_CGYT_Dec->detect(Src, Lines_Decd); //检测直线

	LSD_CGYT_Dec->drawSegments(temp, Lines_Decd); //绘制结果

	imshow(window_name_f2, temp);
	waitKey(0);

	return Lines_Decd;
	
}

Mat FenShuiLing_CGYT(Mat Src)
{
	//分水岭 20200222 20200223测试通过
	Mat Img_Gray;
	Mat Temp;
	Temp = Src.clone();
	cvtColor(Temp, Img_Gray, COLOR_BGR2GRAY); //灰度化
	imshow(window_name_f2, Img_Gray);
	waitKey(0);
	GaussianBlur(Img_Gray, Img_Gray, Size(7, 7), 2); //高斯滤波
	imshow(window_name_f2, Img_Gray);
	waitKey(0);
	Canny(Img_Gray, Img_Gray, 90, 150); //canny
	imshow(window_name_f2, Img_Gray);
	waitKey(0);

	//查找轮廓
	vector<vector<Point>> Contours_cgyt;
	vector<Vec4i> Hierarchy_cgyt;  //层次结构存放变量（其内部int型数据为轮廓容器vector<Point>的索引）
	//记录边缘结构层次的边缘查找
	findContours(Img_Gray, Contours_cgyt, Hierarchy_cgyt, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	Mat Img_contours = Mat::zeros(Img_Gray.size(), CV_8UC1);
	Mat Img_mark = Mat(Img_Gray.size(), CV_32S);
	Img_mark = Scalar::all(0); //颜色设定
	int index = 0;
	int compCount = 0;
	for (; index >= 0; index = Hierarchy_cgyt[index][0])
	{

		//对marks进行标记，对不同区域的轮廓进行编号，相当于设置注水点，有多少轮廓，就有多少注水点 
		//marks与imageContours差别就是在颜色的赋值上，marks是不同轮廓赋予不同的值，imageContours是轮廓赋值白色

		compCount++;//具有层次结构的边缘计数	
		//带有层次结构的边缘绘制，颜色用不同强度灰度嘛 Mark
		drawContours(Img_mark, Contours_cgyt, index, Scalar::all(compCount + 1), 1, 8, Hierarchy_cgyt);

		//单纯的就是把边缘画出来，不按照层次分别着色
		drawContours(Img_contours, Contours_cgyt, index, Scalar(255), 1, 8, Hierarchy_cgyt);
	}
	Mat Marks_see;
	convertScaleAbs(Img_mark, Marks_see); //转换数据类型From CV_32S(32bit signed int) to CV_8U(8bit usigned int)
	imshow(window_name_f2, Marks_see);
	waitKey(0);
	imshow(window_name_f2, Img_contours);
	waitKey(0);

	watershed(Temp, Img_mark); //分水岭方法

	Mat Mark_after_fsl;
	convertScaleAbs(Img_mark, Mark_after_fsl);
	imshow(window_name_f2, Mark_after_fsl);
	waitKey(0);

	Mat Img_Color_Filled = Mat::zeros(Temp.size(), CV_8UC3);
	for (int i = 0; i < Img_mark.cols; i++)
	{
		for (int j = 0; j < Img_mark.rows; j++)
		{
			int index = Img_mark.at<int>(j, i);
			if (Img_mark.at<int>(j, i) == -1)
			{
				Img_Color_Filled.at<Vec3b>(j, i) = Vec3b(255, 255, 255); //边界用纯白绘制
			}
			else
			{
				int seed = index % 255;
				RNG random_color;  //随机数生成器
				Img_Color_Filled.at<Vec3b>(j, i)[0] = random_color.uniform(0, seed);
				Img_Color_Filled.at<Vec3b>(j, i)[1] = random_color.uniform(0, seed);
				Img_Color_Filled.at<Vec3b>(j, i)[2] = random_color.uniform(0, seed);
			}
		}
	}
	imshow(window_name_f2, Img_Color_Filled);
	waitKey(0);

	return Img_mark;
}

//对各种函数的的trackBar参数试验在以下进行 刚好callback函数也在这写呗,不过这并没有关联什么按键 估计是要有button什么的才有用
void ShowHistoCallbcak(int state,Mat Src)
{
	if (Src.type() != CV_8UC1 || Src.type() != CV_8UC3)
	{
		printf("输入矩阵格式非常规");
	}
	//剖分通道
	else if(Src.type() == CV_8UC3) //BGR
	{	
		vector< Mat> Channels;
		split(Src, Channels);

		int GrayLevels = 256;
		float range[] = { 0,256 };
		const float* histRange{ range };

		//统计
		Mat B_hist, G_hist, R_hist;
		calcHist(&Channels[0], 1,0, Mat(), B_hist, 1, &GrayLevels, &histRange);
		calcHist(&Channels[1], 1,0, Mat(), G_hist, 1, &GrayLevels, &histRange);
		calcHist(&Channels[2], 1,0, Mat(), R_hist, 1, &GrayLevels, &histRange);

		//画图
		int width = 512;
		int hight = 384;
		Mat HistGram(hight, width, CV_8UC3, Scalar(20, 20, 20));

		//归一化
		normalize(B_hist, B_hist, 0, hight, NORM_MINMAX);
		normalize(G_hist, G_hist, 0, hight, NORM_MINMAX);
		normalize(R_hist, R_hist, 0, hight, NORM_MINMAX);

		int binStep = cvRound((float)width / (float)GrayLevels);  //圆整
		for (int i = 0; i < GrayLevels; i++)
		{
			line(HistGram,  //蓝色直方图
				Point(binStep*(i-1),hight-cvRound(B_hist.at<float>(i-1))),
				Point(binStep*(i),hight-cvRound(B_hist.at<float>(i))),
				Scalar(255,0,0));
			line(HistGram,  //绿色直方图
				Point(binStep*(i - 1), hight - cvRound(G_hist.at<float>(i - 1))),
				Point(binStep*(i), hight - cvRound(G_hist.at<float>(i))),
				Scalar(0, 255, 0));
			line(HistGram,  //红色直方图
				Point(binStep*(i - 1), hight - cvRound(R_hist.at<float>(i - 1))),
				Point(binStep*(i), hight - cvRound(R_hist.at<float>(i))),
				Scalar(0, 0, 255));
		}
		imshow(window_name_f2, HistGram);
		waitKey(0);
	}

}