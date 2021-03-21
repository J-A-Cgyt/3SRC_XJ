#include "Func_Proj_2nd.h"

string window_name_f1 = "Demo_Result"; //�����ʾ��

Mat FAST_dect_Cgyt(Mat Src1, Mat Src2)
{

	std::vector<Mat> Temp_Array_f1;
	Mat Temp_Buffer_f1;
	Mat temp_src1, temp_src2;
	temp_src1 = Src1.clone();
	temp_src2 = Src2.clone();
	
	Temp_Array_f1.push_back(temp_src1);
	Temp_Array_f1.push_back(temp_src2);

//FAST�ǵ�����Դ���+ƥ��
	//�ǵ���	2020-1-17����ͨ��
	std::vector<cv::KeyPoint> �ǵ�A;
	std::vector<cv::KeyPoint> �ǵ�B;

	Ptr<FastFeatureDetector> Fast_Test_A = FastFeatureDetector::create(230);
	Fast_Test_A->detect(Temp_Array_f1[0], �ǵ�A);
	Ptr<FastFeatureDetector> Fast_Test_B = FastFeatureDetector::create(230);
	Fast_Test_B->detect(Temp_Array_f1[1], �ǵ�B);

//�ǵ�����չʾ	2020-1-17����ͨ��
	int numbers = �ǵ�A.size();
	cout << numbers << endl;
	/*
	for (int i = 0; i < numbers; i++)
	{
		cout << �ǵ�A[i].pt.x << "," << �ǵ�A[i].pt.y << endl;
	}
	*/
	Temp_Buffer_f1 = Temp_Array_f1[0].clone();
	cvtColor(Temp_Buffer_f1, Temp_Buffer_f1, COLOR_GRAY2BGR);
	const Scalar &color = cv::Scalar_<double>::all(-1);
	drawKeypoints(Temp_Array_f1[0], �ǵ�A, Temp_Buffer_f1, color, DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow(window_name_f1, Temp_Buffer_f1);
	waitKey(0);

	numbers = �ǵ�B.size();
	cout << numbers << endl;
	/*
	for (int i = 0; i < numbers; i++)
	{
		cout << �ǵ�B[i].pt.x << "," << �ǵ�B[i].pt.y << endl;
	}
	*/
	Temp_Buffer_f1 = Temp_Array_f1[1].clone();
	cvtColor(Temp_Buffer_f1, Temp_Buffer_f1, COLOR_GRAY2BGR);
	drawKeypoints(Temp_Array_f1[1], �ǵ�B, Temp_Buffer_f1, color, DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow(window_name_f1, Temp_Buffer_f1);
	waitKey(0);

//�ǵ������Ӽ��㣬KeyPoint Descriptor Brief��������
	Mat ������_1, ������_2;
	Ptr<ORB> Brief_Descriptor_compute = ORB::create();
	Brief_Descriptor_compute->compute(Src1, �ǵ�A, ������_1);
	Brief_Descriptor_compute->compute(Src2, �ǵ�B, ������_2);

	//cout << ������_1 << endl;

	������_1.convertTo(������_1,CV_32F);
	������_2.convertTo(������_2,CV_32F); //��������ת������ƥ��

	//cout << ������_1.type() << endl;
	//imwrite("G:\\Pictures\\Test For Programming\\keypoints.jpg",Temp_Buffer);
	//Ptr<FeatureDetector> Feature_Test;

//KNN����ƥ�����ƥ���ϵ
	FlannBasedMatcher Matcher_FAST_cgyt;
	vector<vector<DMatch>> ƥ���ϵ;
	vector<DMatch> Select_Match;
	//DMatch Match_buffer;

	int k = 2; //number of nearest neighbors

	Matcher_FAST_cgyt.knnMatch(������_1, ������_2, ƥ���ϵ, k, Mat()); 
	/*
		���⣺�����������뺯����ƥ�� ������������Ϊ CV_32F ����ͨ��float�͡�
		���� int k ��ʾ���ͬһ��ͼ�񣬶Բο�ͼ��ԭͼ����ͬһ���㷵�� k �����ܵ���Ե㣨λ��ƥ��ͼ����K-NN��������˼
	*/
	//cout << ƥ���ϵ.size() << endl;

	for (int i = 1; i < ƥ���ϵ.size(); i++)
	{
		Select_Match.push_back(ƥ���ϵ[i][0]);
	}
	std::nth_element(Select_Match.begin(), Select_Match.begin() + 49, Select_Match.end()); //�Զ�����
	Select_Match.erase(Select_Match.begin() + 49, Select_Match.end());

	Mat result_match;
	drawMatches(temp_src1,�ǵ�A,temp_src2,�ǵ�B,ƥ���ϵ,result_match);
	imshow(window_name_f1, result_match);
	waitKey(0);		
	
	drawMatches(temp_src1, �ǵ�A, temp_src2, �ǵ�B, Select_Match, result_match);
	imshow(window_name_f1, result_match);
	waitKey(0);

	return Temp_Buffer_f1;
}

Mat JiaoDian_SURF_CGYT(Mat Src1, Mat Src2) //surf�ǵ������
{
	Mat temp1, temp2;
	temp1 = Src1.clone();
	temp2 = Src2.clone();

	Ptr<xfeatures2d::SurfFeatureDetector> Dect1_Surf1 = xfeatures2d::SURF::create(3000); //��������� ���ҵ�������ͼ��30000
	vector<KeyPoint> KeyPoints_1_Q, KeyPoints_2_T; //����������

	Mat descriptor1_Q, descriptor2_T; //������

	Dect1_Surf1->detectAndCompute(Src1, Mat(), KeyPoints_1_Q, descriptor1_Q);
	Dect1_Surf1->detectAndCompute(Src2, Mat(), KeyPoints_2_T, descriptor2_T); //�����������Ӧ�����Ӽ���

	drawKeypoints(temp1, KeyPoints_1_Q, temp1);
	drawKeypoints(temp2, KeyPoints_2_T, temp2);  //���������

	imshow(window_name_f1, temp1);
	waitKey(0);
	imshow(window_name_f1, temp2);
	waitKey(0);

	//cout << descriptor1_Q.type();// debug fast 20200225
	//����ƥ��
	BFMatcher match_cgyt;
	vector<DMatch> matchs_cgyt; 
	//��Թ�ϵ�࣬�������������ͼ���Ӧ�ؼ������ţ�������Σ�ԴΪquary����ΪtrainĿ���ǽ�trainͼ�任��quaryͼ
	match_cgyt.match(descriptor1_Q, descriptor2_T, matchs_cgyt);
	Mat Result;

	/* �������е�ƥ���
	drawMatches(temp1, KeyPoints_1, temp2, KeyPoints_2, matchs_cgyt,Result);
	imshow(window_name_f1, Result);
	waitKey(0);
	*/

	//����ǰ60��ƥ��㣨ֵС�ģ�����ΪDmatch.distance,��С�����ţ�
	std::nth_element(matchs_cgyt.begin(), matchs_cgyt.begin() + 59, matchs_cgyt.end());
	matchs_cgyt.erase(matchs_cgyt.begin() + 59, matchs_cgyt.end());
	drawMatches(temp1, KeyPoints_1_Q, temp2, KeyPoints_2_T, matchs_cgyt, Result);

	imshow(window_name_f1, Result); //ɸѡƥ�����ƥ����
	waitKey(0);

	vector<Point2f> Point_CPs_Q, Point_CPs_T; //��Ӧ�ؼ������꣨�����ͣ�
	for (int i = 0; i < matchs_cgyt.size(); i++)
	{
		Point_CPs_Q.push_back(KeyPoints_1_Q[matchs_cgyt[i].queryIdx].pt);
		Point_CPs_T.push_back(KeyPoints_2_T[matchs_cgyt[i].trainIdx].pt);
	}
	//�任������㣬��Ӧ(homography)
	Mat Homo_Trans_mat;//�任����3*3
	Homo_Trans_mat = cv::findHomography(Point_CPs_T, Point_CPs_Q, FM_RANSAC);
	cout << Homo_Trans_mat << endl;

	//͸�ӱ任��Ӧ�õ�Ӧ����
	Mat img_trans1;
		
	Size Res_size; 
	Res_size.height = temp2.rows; 
	Res_size.width = 1.3 * temp2.cols;
	warpPerspective(Src2,img_trans1,Homo_Trans_mat,Res_size);
	imshow(window_name_f1, img_trans1);
	waitKey(0);

	//ͼ�񿽱�(�ں�)
	Rect Rang1, Rang2;
	Rang1 = Rect(0, 0, Src1.cols, Src1.rows);
	Rang2 = Rect(0, 0, img_trans1.cols, img_trans1.rows);

	//����ͼ�����λ�ã�����ͼ���С�趨�����س�ʼֵ�趨
	Mat img_trans2(Src1.rows,img_trans1.cols,CV_8UC1);
	img_trans2.setTo(0);

	/*
	imshow(window_name_f1, img_trans2);
	waitKey(0);
*/
	
	//��ͼ��ض�Ӧλ�����ؿ���
	img_trans1.copyTo(img_trans2(Rang2));	
	Src1.copyTo(img_trans2(Rang1));
			
	imshow(window_name_f1, img_trans2);
	waitKey(0);

//���Ӵ��Ż�
	enum Locate_Jiaodian :int //�ĸ��߽�λ��ö��
	{
		����=0,
		����=1,
		����=2,
		����=3
	};
	vector<Mat> Points_Pic;  //�佹λ���������������4*��3*1��
	Mat Cord_buffer1 = Mat(3, 1, CV_64FC1);
	//�ĸ��ǵ��趨�����任��ͼ��
	Cord_buffer1.at<double>(0) = 0;
	Cord_buffer1.at<double>(1) = 0;
	Cord_buffer1.at<double>(2) = 1; 	
	cout << Cord_buffer1 << endl;	
	Points_Pic.push_back(Cord_buffer1); //����

	Mat Cord_buffer2 = Mat(3, 1, CV_64FC1);
	Cord_buffer2.at<double>(0) = 0;
	Cord_buffer2.at<double>(1) = Src2.rows;
	Cord_buffer2.at<double>(2) = 1;
	cout << Cord_buffer2 << endl;
	Points_Pic.push_back(Cord_buffer2); //����

	Mat Cord_buffer3 = Mat(3, 1, CV_64FC1);
	Cord_buffer3.at<double>(0) = Src2.cols;
	Cord_buffer3.at<double>(1) = 0;
	Cord_buffer3.at<double>(2) = 1;
	cout << Cord_buffer3 << endl;
	Points_Pic.push_back(Cord_buffer3); //����

	Mat Cord_buffer4 = Mat(3, 1, CV_64FC1);
	Cord_buffer4.at<double>(0) = Src2.cols;
	Cord_buffer4.at<double>(1) = Src2.rows;
	Cord_buffer4.at<double>(2) = 1;
	Points_Pic.push_back(Cord_buffer4); //����
	
	/*
	��push_back()��������⣬vector.push_back����������ָ�룬�����ƾ������ݡ�
	�����ʹ��ͬһ������θ���ֵͬ�� ��push_back����ѹ��vector��
	���������������е�Ԫ��ֵ��Ϊ���һ�θ�ֵ�Ľ����ע��ע�� ����������Mat�������ָ����� ��ʵ�����ݵĸĶ���δ�Ķ�ָ�� push_back������ѹ�븱���� 20210203
	*/

	cout << Cord_buffer4 << endl << "ԭʼ�����趨���" << endl;

	//����任��ı߽�����꣨��ԭͼ������ϵ�£�
	for (int i = 0; i < 4; i++)
	{		
		cout << Points_Pic[i] << endl;
		
		Points_Pic[i] = Homo_Trans_mat * Points_Pic[i];
		cout << Points_Pic[i] << endl;
		double v0 = Points_Pic[i].at<double>(0);
		double v1 = Points_Pic[i].at<double>(1);
		double v2 = Points_Pic[i].at<double>(2);

		Points_Pic[i].at<double>(0) = v0 / v2;
		Points_Pic[i].at<double>(1) = v1 / v2;
		Points_Pic[i].at<double>(2) = 1;
		cout << Points_Pic[i] << endl << endl;
 	}
	//ss
	cout << "ͼ��任��߽�����������" << endl;

	//�ص��������ػҶ����ã�Դ��Src1 img_trans1��Ŀ�꣺img_trans2

	int start = MIN(Points_Pic[����].at<double>(0), 
		            Points_Pic[����].at<double>(0)); //�ص�������ʼ(��)���꼴����
	//cout << start << endl;
	int end = Src1.cols;
	int Band_Width = end - start; //�˴�������img1��img2�����λ�ñ�����img1����img2���� �����ܷ��ü򵥵ľ���ֵ������⻹����˵
	double Rate = 1;
	for (int i = 0; i < img_trans2.rows; i++)
	{
		for (int j = start; j < end; j++)
		{
			if (img_trans1.at<uchar>(i, j) == 0)
			{
				Rate = 1;
			}
			else
			{
				Rate = (Band_Width - (j - start)) / Band_Width;
			}
			
			img_trans2.at<uchar>(i, j) = uchar(Rate * Src1.at<uchar>(i, j) + (1 - Rate) * img_trans1.at<uchar>(i, j));
			
			if (img_trans2.at<uchar>(i, j) == 0) //�ԻҶ��쳣Ϊ0��̽����� 20200329
			{
				cout << "(" << i << "," << j << ")" << ";";
				uchar scale1 = Src1.at<uchar>(i, j);
				uchar scale2 = img_trans1.at<uchar>(i, j);
				cout << int(scale1) << "," << int(scale2) << ";";
				cout << Rate << endl;
			}
		}	
	
	}

	imshow(window_name_f1, img_trans2);
	waitKey(0);

	return img_trans2;

}

vector<Point2f> subPix_pt(Mat Src) //����ʱ��20200305 ���ǶԽǵ�ļ�⣬�������ӵ�����ж�����������ӿ����ڸ߽��ȵĳߴ����
{
	Mat temp;                     // #1 ������ͼ��8λ��32λ��ͨ��ͼ����
	temp = Src.clone(); 

	vector<Point2f> Corners;      // #2 �Ǽ�⵽�����нǵ㣬����Ϊvector�����飬��ʵ�ʸ����Ĳ������Ͷ�����
								  //�����vector����ô��Ӧ����һ������cv::Point2f��vector�������������cv::Mat,��ô����ÿһ�ж�Ӧһ���ǵ㣬���x��yλ�÷ֱ������С�	
	int Max_num = 50;            // #3 �����޶���⵽�ĵ��������ֵ��
	double Quality_level = 0.09;  // #4 ��ʾ��⵽�Ľǵ������ˮƽ��ͨ����0.10��0.01֮�����ֵ�����ܴ���1.0����
	double minDistance = 20;      // #5 �����������������ǵ����С���루С���������õ㽫���кϲ�����
	
	goodFeaturesToTrack(temp,Corners,Max_num,Quality_level,minDistance);	
	/*
	������������mask�����ָ��������ά�ȱ��������ͼ��һ�£�����maskֵΪ0�������нǵ��⡣
	���߸�������blockSize����ʾ�ڼ���ǵ�ʱ��������������С������ֵΪ3���������ͼ��ķֱ��ʽϸ�����Կ���ʹ�ýϴ�һ���ֵ��
	�ڰ˸���������ָ���ǵ���ķ����������true��ʹ��Harris�ǵ��⣬false��ʹ��Shi Tomasi�㷨��
	�ھŸ���������ʹ��Harris�㷨ʱʹ�ã����ʹ��Ĭ��ֵ0.04��
	*/

	cv::Size Window_size = Size(5, 5);
	cv::Size Zone_0 = Size(-1, -1);

	cv::TermCriteria Criteria_cgyt = cv::TermCriteria(TermCriteria::EPS, 20, 0.04);
	cornerSubPix(temp,Corners,Window_size,Zone_0,Criteria_cgyt);
	/*
	��һ������������ͼ�񣬺�cv::goodFeaturesToTrack()�е�����ͼ����ͬһ��ͼ��
	�ڶ��������Ǽ�⵽�Ľǵ㣬��������Ҳ�������
	�����������Ǽ��������ؽǵ�ʱ���ǵ�����Ĵ�С����СΪNXN; N=(winSize*2+1)��
	���ĸ���������������winSize���������Ǿ��н�С�ķ�Χ��ͨ�����ԣ���Size(-1, -1)����
	������������ڱ�ʾ����������ʱֹͣ�����ı�׼����ѡ��ֵ��cv::TermCriteria::MAX_ITER ��cv::TermCriteria::EPS��������������һ�������߾�ѡ����
	ǰ�߱�ʾ���������ﵽ��������ʱֹͣ�����߱�ʾ�ǵ�λ�ñ仯����Сֵ�Ѿ��ﵽ��Сʱֹͣ������
	���߾�ʹ��cv::TermCriteria()���캯������ָ����
	*/
	
	//�����ʾ
	//temp.convertTo(temp, CV_8UC3); //תͨ��������ת��ɫ��ʾ
	cvtColor(temp, temp, COLOR_GRAY2BGR);
	for (int i = 0; i < Corners.size(); i++)
	{
		circle(temp,Corners[i],10,Scalar(0,0,255),3);
	}
	imshow(window_name_f1, temp);
	waitKey(0);

	return Corners;
}

//��֤����ת��ƽ��ͼ���� 20210204����ͨ��
void pic_Move_Cgyt(const Mat& Src,Mat& Dst,const int& x,const int& y) { 
	Mat transMat = Mat::eye(Size(3, 3), CV_32FC1);

	transMat.at<float>(0, 2) = x;
	transMat.at<float>(1, 2) = y;
	int xx(0), yy(0);
	if (x < 0) {
		printf("Please input distance x aixs(pix), value should be positive:");
		scanf_s("%d", &xx);
		transMat.at<float>(0, 2) = xx;
	}
	if (y < 0) {
		printf("Please input distance y aixs(pix), value should be positive:");
		scanf_s("%d", &yy);
		transMat.at<float>(1, 2) = yy;
	}
	cv::Size res_Size;
	res_Size.height = 2 * Src.rows;
	res_Size.width = 2 * Src.cols;
	warpPerspective(Src, Dst, transMat, res_Size);
	printf("Transform done!\n");
	imshow(window_name_f1, Dst);
	waitKey(0);
}