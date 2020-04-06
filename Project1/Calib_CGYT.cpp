#include "Func_Proj_2nd.h"


string Source_Path[10];
string Window_calib = "Corners_dected";

int Calib_Cgyt(Mat InputOutputArray)
{
	//图像加载路径
	Source_Path[0] = "G:\\Pictures\\Test For Programming\\calb13\\1.jpg";
	Source_Path[1] = "G:\\Pictures\\Test For Programming\\calb13\\2.jpg";
	Source_Path[2] = "G:\\Pictures\\Test For Programming\\calb13\\3.jpg";
	Source_Path[3] = "G:\\Pictures\\Test For Programming\\calb13\\4.jpg";
	Source_Path[4] = "G:\\Pictures\\Test For Programming\\calb13\\5.jpg";
	Source_Path[5] = "G:\\Pictures\\Test For Programming\\calb13\\6.jpg";
	Source_Path[6] = "G:\\Pictures\\Test For Programming\\calb13\\7.jpg";
	Source_Path[7] = "G:\\Pictures\\Test For Programming\\calb13\\8.jpg";
	Source_Path[8] = "G:\\Pictures\\Test For Programming\\calb13\\9.jpg";
	Source_Path[9] = "G:\\Pictures\\Test For Programming\\calb13\\10.jpg";

	//窗口展示
	namedWindow(Window_calib, WINDOW_AUTOSIZE);
	
	//图像读取
	vector<Mat> Src_img;
	for (int i = 0; i < 10; i++)
	{
		Src_img.push_back(imread(Source_Path[i], IMREAD_GRAYSCALE));
	}
	cv::Size ChessboardSize = Size(9, 6);  //棋盘格格子数
	vector<Point2f> Corners[10];  //
	//棋盘格路径
	bool ifFound = findChessboardCorners(Src_img[0], ChessboardSize, Corners[0]);
	if (ifFound = false)
	{
		cout << "find corners failed" << endl;
		return -2;
	}

//亚像素角点
	//参数设定
 
	cv::Size Window_size = Size(5, 5);
	cv::Size Zone_0 = Size(-1, -1);
	cv::TermCriteria Criteria_cgyt = cv::TermCriteria(TermCriteria::EPS, 20, 0.04);
	//检测
	cornerSubPix(Src_img[0], Corners[0], Window_size, Zone_0, Criteria_cgyt);

	//角点绘制展示
	Mat map;	
	cvtColor(Src_img[0], map, COLOR_GRAY2BGR);
	drawChessboardCorners(map,ChessboardSize,Corners[0],true);
	imshow(Window_calib,map);
	waitKey(0);

//内外参计算
	//世界坐标计算
	cv::Size GridSize = cv::Size(20, 20);
	vector<vector<Point3f>> Cord_world;

	vector<Point3f> Cord_WordQueue;
	for (int j = 0; j < ChessboardSize.height; j++)
	{
		for (int i = 0; i < ChessboardSize.width; i++)
		{
			Point3f Cord_Temp;
			Cord_Temp.x = i * GridSize.width;
			Cord_Temp.y = j * GridSize.height;
			Cord_Temp.z = 0;
			Cord_WordQueue.push_back(Cord_Temp);
		}
	}
	Cord_world.push_back(Cord_WordQueue);

	return 0;
}