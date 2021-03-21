#include "Func_Proj_2nd.h"

string Source_Path[10];
string Window_calib = "Corners_dected";

/*����������궨�ĺ���������о�����ƺ��Ƚϴ󣬲���matlab�ı궨������ӽ�S10����ı�Ʋ�����
�������ĵı궨����ǲ��ģ�ֻ�н��������˲��죬�Ӵ���ʵ�ֵĽǶ���˵�������⣬�ѵ�����Ϊ�㷨���У�*/
int Calib_Cgyt(Mat InputOutputArray)
{
	//ͼ�����·��
	Source_Path[0] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_4.jpg";
	Source_Path[1] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_2.jpg";
	Source_Path[2] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_3.jpg";
	Source_Path[3] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_4.jpg";
	Source_Path[4] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_5.jpg";
	Source_Path[5] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_6.jpg";
	Source_Path[6] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_7.jpg";
	Source_Path[7] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_8.jpg";
	Source_Path[8] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_9.jpg";
	Source_Path[9] = "F:\\Pictures\\Test For Programming\\HIK12MP\\CalibImg_10.jpg";

	//����չʾ
	namedWindow(Window_calib, WINDOW_NORMAL);
	
	//ͼ���ȡ
	vector<Mat> Src_img;
	for (int i = 0; i < 1; i++)
	{
		Src_img.push_back(imread(Source_Path[i], IMREAD_GRAYSCALE));
	}
	cv::Size ChessboardSize = Size(11, 8);   //���̸������
	vector<vector<Point2f>> Corners_queue;   //������õ�ͼ���������
	vector<Point2f> Corners;                 //����ͼ����ͼ����ݴ�

	//�����ؽǵ�����趨
	cv::Size Window_size = Size(5, 5);
	cv::Size Zone_0 = Size(-1, -1);
	//������ֹ����ģ����
	cv::TermCriteria Criteria_cgyt = cv::TermCriteria(
		TermCriteria::MAX_ITER + 
		TermCriteria::EPS, 
		30,     //����������
		0.01);  //��С����
	
	//���ѭ��
	for (int i = 0; i < 1; i++)
	{
		//resize(Src_img[i], Src_img[i], Size(2012, 1518));
		bool ifFound = findChessboardCorners(Src_img[i], ChessboardSize, Corners);
		if (ifFound = false)
		{
			cout << "find corners failed" << endl;
			return -2;
		}
		cornerSubPix(Src_img[i], Corners, Window_size, Zone_0, Criteria_cgyt);
		Corners_queue.push_back(Corners);
	}
	//�ǵ����չʾ
	Mat map;	
	cvtColor(Src_img[0], map, COLOR_GRAY2BGR);
	drawChessboardCorners(map,ChessboardSize,Corners,true);
	imshow(Window_calib,map);
	waitKey(0);

//����μ���
	//�����������
	cv::Size GridSize = cv::Size(6, 6);
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
	for (int i = 0; i < 1; i++)
	{
		Cord_world.push_back(Cord_WordQueue);
	}

	//������궨���������
	Mat K_CameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));  //������ڲξ���K
	Mat distortion = Mat(1, 5, CV_32FC1, Scalar::all(0));  //����������������5��
	vector<Mat> RotationV; //ͼ����ת����
	vector<Mat> MoveV;  //ͼ��ƽ������

	calibrateCamera(Cord_world, Corners_queue, 
		Src_img[0].size(), 
		K_CameraMatrix, 
		distortion, RotationV, MoveV, 
		0); //������Ϊȡ����K3�����¶Դ�����νϴ�ĳ���ǵĽ����ж�ʧ��20200406 ����0��һ�� CALIB_FIX_K3

	cout << K_CameraMatrix << endl;

//�����������
	Mat res;
	undistort(map, res, K_CameraMatrix, distortion);
	imshow(Window_calib, res);  //Ч�������е��ͷ��
	waitKey(0);

	return 0;
}