#include "Func_Proj_2nd.h"

string window_name_f2 = "Demo_Result"; //�����ʾ��

Mat Thershold_����(Mat Src)
{
	//�Դ�����Ӧ��ֵ������
	double Max_Value = 255;  //���ֵ
	int Block_Size = 159;     //����ߴ磨����ֵ��
	int C = 5;              //��ֵ�����Ժ���ֵ��ƫ���� ��-C��

	Mat Dst;
	adaptiveThreshold(Src, Dst, Max_Value, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, Block_Size, C);

	return Dst;
}

//�ٳ���һ�¸���Ҷ�任�ɣ�û�������������ò��� ����20200323
Mat FT_CGYT(Mat Src)
{
	Mat temp = Src.clone();

	int row_opt = getOptimalDFTSize(Src.rows);
	int col_opt = getOptimalDFTSize(Src.cols);

	copyMakeBorder(Src, temp, 0, row_opt - Src.rows, 
							  0, col_opt - Src.cols, 
							  BORDER_CONSTANT, Scalar::all(0));

	Mat FT_res = Mat(temp.size(), CV_32FC2); //ͼ��ߴ��趨����
	//Mat FT_res = Mat(temp.rows + row_opt, temp.cols + col_opt, CV_32FC2); //�վ��� ע�⣬�˴�����ߴ粢����Ҫ�������趨˫ͨ��float���͵����ݼ���
	
	Mat mForFourier[] = { Mat_<float>(temp),//Դ����ĸ�������ͨ��1 
						  Mat::zeros(temp.size(), CV_32F)  //�ߴ���Դ������ͬ�ĵ�0����ͨ��2
	}; 
						 
	Mat FT_src;
	merge(mForFourier, 2, FT_src); //Դ����ͨ���ϲ�

	dft(FT_src, FT_res); //FT_res������ͨ���ֱ�Ϊ�任�����ʵ�����鲿

	vector<Mat> channels_res;
	split(FT_res, channels_res);
	Mat FT_R = channels_res[0];  //ʵ��
	Mat FT_I = channels_res[1];  //�鲿

	//ģ�����㣬����Ӧ����ĸ���ģ�����㣩
	Mat mAmplitude;
	magnitude(FT_R, FT_I, mAmplitude);  //��ֵ���㺯��

	mAmplitude += Scalar(1); //ȡ����ǰ�����г���Ϊ0�����ػҶ�ֵ��+1��֤���ж���ֵ�Ǹ�
	log(mAmplitude, mAmplitude); //ȡ����

	normalize(mAmplitude, mAmplitude, 0, 255, NORM_MINMAX); //��һ����0~255����uchar�ı�ʾ��Χ

	mAmplitude.convertTo(mAmplitude, CV_8UC1);  //��������ת��
	imshow(window_name_f2, mAmplitude);
	waitKey(0);

	Rect Achor_cgyt[4];
	Achor_cgyt[0] = Rect(0, 0, 
						 col_opt / 2, row_opt / 2); //�˹��캯��Ϊ���Ͻ������볤��ֵ���������Ͻ���������½�����
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

	return Location_rev; //��������仯�����Ļ��󷽿ɽ����˲������������Ժ��ٻ����������ǵÿ�OpenCV�Լ���ʵ�ַ�������Ƶ���˲�������д������
}

//�ڴ˴�������һ�µط�����д��ֱ�߶μ��ĺ����ڴ�
vector<Vec4f> LSD_cgyt(Mat Src)
{
	Mat temp = Src.clone();
	vector<Vec4f> Lines_Decd; //��������߶�����
	
	//ֱ�߼��������ʵ����,ע�����ѡ��
	Ptr<LineSegmentDetector> LSD_CGYT_Dec = createLineSegmentDetector(LSD_REFINE_STD);

	LSD_CGYT_Dec->detect(Src, Lines_Decd); //���ֱ��

	LSD_CGYT_Dec->drawSegments(temp, Lines_Decd); //���ƽ��

	imshow(window_name_f2, temp);
	waitKey(0);

	return Lines_Decd;
	
}

Mat FenShuiLing_CGYT(Mat Src)
{
	//��ˮ�� 20200222 20200223����ͨ��
	Mat Img_Gray;
	Mat Temp;
	Temp = Src.clone();
	cvtColor(Temp, Img_Gray, COLOR_BGR2GRAY); //�ҶȻ�
	imshow(window_name_f2, Img_Gray);
	waitKey(0);
	GaussianBlur(Img_Gray, Img_Gray, Size(7, 7), 2); //��˹�˲�
	imshow(window_name_f2, Img_Gray);
	waitKey(0);
	Canny(Img_Gray, Img_Gray, 90, 150); //canny
	imshow(window_name_f2, Img_Gray);
	waitKey(0);

	//��������
	vector<vector<Point>> Contours_cgyt;
	vector<Vec4i> Hierarchy_cgyt;  //��νṹ��ű��������ڲ�int������Ϊ��������vector<Point>��������
	//��¼��Ե�ṹ��εı�Ե����
	findContours(Img_Gray, Contours_cgyt, Hierarchy_cgyt, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());
	Mat Img_contours = Mat::zeros(Img_Gray.size(), CV_8UC1);
	Mat Img_mark = Mat(Img_Gray.size(), CV_32S);
	Img_mark = Scalar::all(0); //��ɫ�趨
	int index = 0;
	int compCount = 0;
	for (; index >= 0; index = Hierarchy_cgyt[index][0])
	{

		//��marks���б�ǣ��Բ�ͬ������������б�ţ��൱������עˮ�㣬�ж������������ж���עˮ�� 
		//marks��imageContours����������ɫ�ĸ�ֵ�ϣ�marks�ǲ�ͬ�������費ͬ��ֵ��imageContours��������ֵ��ɫ

		compCount++;//���в�νṹ�ı�Ե����	
		//���в�νṹ�ı�Ե���ƣ���ɫ�ò�ͬǿ�ȻҶ��� Mark
		drawContours(Img_mark, Contours_cgyt, index, Scalar::all(compCount + 1), 1, 8, Hierarchy_cgyt);

		//�����ľ��ǰѱ�Ե�������������ղ�ηֱ���ɫ
		drawContours(Img_contours, Contours_cgyt, index, Scalar(255), 1, 8, Hierarchy_cgyt);
	}
	Mat Marks_see;
	convertScaleAbs(Img_mark, Marks_see); //ת����������From CV_32S(32bit signed int) to CV_8U(8bit usigned int)
	imshow(window_name_f2, Marks_see);
	waitKey(0);
	imshow(window_name_f2, Img_contours);
	waitKey(0);

	watershed(Temp, Img_mark); //��ˮ�뷽��

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
				Img_Color_Filled.at<Vec3b>(j, i) = Vec3b(255, 255, 255); //�߽��ô��׻���
			}
			else
			{
				int seed = index % 255;
				RNG random_color;  //�����������
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

//�Ը��ֺ����ĵ�trackBar�������������½��� �պ�callback����Ҳ����д��,�����Ⲣû�й���ʲô���� ������Ҫ��buttonʲô�Ĳ�����
void ShowHistoCallbcak(int state,Mat Src)
{
	if (Src.type() != CV_8UC1 || Src.type() != CV_8UC3)
	{
		printf("��������ʽ�ǳ���");
	}
	//�ʷ�ͨ��
	else if(Src.type() == CV_8UC3) //BGR
	{	
		vector< Mat> Channels;
		split(Src, Channels);

		int GrayLevels = 256;
		float range[] = { 0,256 };
		const float* histRange{ range };

		//ͳ��
		Mat B_hist, G_hist, R_hist;
		calcHist(&Channels[0], 1,0, Mat(), B_hist, 1, &GrayLevels, &histRange);
		calcHist(&Channels[1], 1,0, Mat(), G_hist, 1, &GrayLevels, &histRange);
		calcHist(&Channels[2], 1,0, Mat(), R_hist, 1, &GrayLevels, &histRange);

		//��ͼ
		int width = 512;
		int hight = 384;
		Mat HistGram(hight, width, CV_8UC3, Scalar(20, 20, 20));

		//��һ��
		normalize(B_hist, B_hist, 0, hight, NORM_MINMAX);
		normalize(G_hist, G_hist, 0, hight, NORM_MINMAX);
		normalize(R_hist, R_hist, 0, hight, NORM_MINMAX);

		int binStep = cvRound((float)width / (float)GrayLevels);  //Բ��
		for (int i = 0; i < GrayLevels; i++)
		{
			line(HistGram,  //��ɫֱ��ͼ
				Point(binStep*(i-1),hight-cvRound(B_hist.at<float>(i-1))),
				Point(binStep*(i),hight-cvRound(B_hist.at<float>(i))),
				Scalar(255,0,0));
			line(HistGram,  //��ɫֱ��ͼ
				Point(binStep*(i - 1), hight - cvRound(G_hist.at<float>(i - 1))),
				Point(binStep*(i), hight - cvRound(G_hist.at<float>(i))),
				Scalar(0, 255, 0));
			line(HistGram,  //��ɫֱ��ͼ
				Point(binStep*(i - 1), hight - cvRound(R_hist.at<float>(i - 1))),
				Point(binStep*(i), hight - cvRound(R_hist.at<float>(i))),
				Scalar(0, 0, 255));
		}
		imshow(window_name_f2, HistGram);
		waitKey(0);
	}

}