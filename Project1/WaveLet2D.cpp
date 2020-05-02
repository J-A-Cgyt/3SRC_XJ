#include "Func_Proj_2nd.h"

//此文件进行图像小波变换的相关方法实现,看论文吧先，这个算法实现还有很对具体的理论细节20200502
Mat WaveLetHarrD_CGYT(Mat Src, int LevelCount)
{	
	Mat temp = Src.clone();
	int ImgCols = temp.cols;
	int ImgRows = temp.rows;
	if (Src.type() == CV_8UC3)
	{
		vector<Mat> channels;
		split(temp, channels);
		channels[0] = WaveLetHarrD_CGYT(channels[0], 1);
		channels[1] = WaveLetHarrD_CGYT(channels[1], 1);
		channels[2] = WaveLetHarrD_CGYT(channels[2], 1);
		merge(channels, temp);
		return temp;
	}
	else if (Src.type() != CV_8UC1)
	{
		cout << "类型必须为CV_8UC1或8UC3" << endl;
		return Mat();
	}

	Mat Res = Mat(Size(ImgCols,ImgRows),CV_64FC1);
	int  Cord_res = 0;//横坐标定位用计数变量,也可不用？
	
	//行分解
	for (int row = 0; row < ImgRows; row++) //先要求一下行列数必须是偶数吧，这个日后就是+判断和resize的事
	{
		for (int col = 0; col < ImgCols; col = col + 2)
		{
			//横向逼近信号（均值）
			Res.at<double>(row, col / 2) =
				(double(temp.at<uchar>(row, col) +
					temp.at<uchar>(row, col + 1))) / 2;
			//横向细节信号（差值）
			Res.at<double>(row, (col / 2) + (ImgCols / 2)) =
				double(temp.at<uchar>(row, col) -
					temp.at<uchar>(row, col + 1));//+50为了看看有没有变化，差值可能为负
		}
	}
	temp.release();
	temp = Res.clone();
	//测试代码
	Mat map;
	temp.convertTo(map, CV_8UC1);
	imshow("Demo_Result", map);
	waitKey(0);

	//列分解
	for (int col = 0; col < ImgCols; col++) //先要求一下行列数必须是偶数吧，这个日后就是+判断和resize的事
	{
		for ( int row = 0; row < ImgRows;row = row + 2)
		{
			//纵向逼近信号（均值）
			Res.at<double>(row / 2,col ) =
				(temp.at<double>(row, col) +
				temp.at<double>(row + 1, col)) / 2;
			//纵向细节信号（差值）
			Res.at<double>((row / 2) + (ImgRows / 2), col) =
				temp.at<double>(row, col) -
				temp.at<double>(row + 1, col);//+50为了看看有没有变化，差值可能为负
		}
	}
	//看起来速度还挺快的，干脆写多线程了
	//normalize(Res, Res, 0, 255, NORM_MINMAX);
	Res.convertTo(Res,CV_8UC1);

	return Res;
}