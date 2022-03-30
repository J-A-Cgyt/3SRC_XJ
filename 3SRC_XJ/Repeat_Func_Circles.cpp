#include "Func.h"
/*
  ����һ�� ���������Ϊ�˸��ò������õ�Դ�ļ������Բ��ƥ�䲻ͬ��������������
  ���Ǽ�⾫�ȴ��ɣ�Ϊ��֤��⾫�ȣ���Ҫ���յ��豸�ϸ���Ƽ�������
*/
string Window_name_copy = "Demo_Result";

vector<Vec3f> Hough_circle_Copy1(Mat src, Mat Map) //���ڼ��ͬ��Բ��СԲ�趨�ĸ�����������
{
	int Hough_Method = HOUGH_GRADIENT;
	double dp = 1;
	double mindist = 10;
	double Param1 = 60;
	double Param2 = 80;
	int minRadius = 80;
	int maxRadius = 120;	 //������е�����Բ����

	//��������������

	vector<Vec3f> Circles;
	Mat tempA;

	//����Բ���
	tempA = src.clone();
	

	HoughCircles(tempA, Circles, Hough_Method, dp, mindist, Param1, Param2, minRadius, maxRadius);
	/*�˴���Ҫ�жԼ�����������ɸѡ�Ĵ��룬��Բ�ͬ������Ҫ���ò�ͬ����ֵ����*/

	return Circles;
}

vector<Vec3f> Hough_circle_Copy2(Mat src, Mat Map) //���ڼ��ͬ��Բ��ССԲ�趨�ĸ�����������
{
	int Hough_Method = HOUGH_GRADIENT;
	double dp = 1;
	double mindist = 10;
	double Param1 = 20;
	double Param2 = 40;
	int minRadius = 40;
	int maxRadius = 60;	 //������е�����Բ����

	//��������������

	vector<Vec3f> Circles;
	Mat tempA;

	//����Բ���
	tempA = src.clone();


	HoughCircles(tempA, Circles, Hough_Method, dp, mindist, Param1, Param2, minRadius, maxRadius);
	/*�˴���Ҫ�жԼ�����������ɸѡ�Ĵ��룬��Բ�ͬ������Ҫ���ò�ͬ����ֵ����*/

	return Circles;
}

vector<Vec3f> Hough_circle_Class(Mat src, Mat Map, Hough_Param Param) //�໯������Բ��ⷽ��
{
	//��������������
	vector<Vec3f> Circles;
	Mat tempA;

	//����Բ���
	tempA = src.clone();

	HoughCircles(tempA,
		         Circles,
		         Param.Hough_Method,
		         Param.dp,
		         Param.mindist,
		         Param.Param1,
		         Param.Param2,
		         Param.minRadius,
		         Param.maxRadius);

	/*�˴���Ҫ�жԼ�����������ɸѡ�Ĵ��룬��Բ�ͬ������Ҫ���ò�ͬ����ֵ����*/

	return Circles;
}

void Draw_Circles(vector<vector<Vec3f>> Array_Of_Circles, Mat Map)  //��Բ�ĺ�������ʱ�ϵ�����任Բ����ʱ����ڲ�����
{
	Mat tempB;
	int Loop1 = Array_Of_Circles.size();
	tempB = Map.clone();
	for (int i = 0; i < Loop1; i++)
	{
		for (int k = 0; k < Array_Of_Circles[i].size(); k++)
		{
			circle(tempB, Point(Array_Of_Circles[i][k].val[0], Array_Of_Circles[i][k].val[1]), 
				    int(Array_Of_Circles[i][k].val[2]), Scalar(0, 0, 255), 5);
			/*
					string R = std::to_string(int(Circles[k].val[0]));
					R.push_back(',');
					R=cout //�ƺ����˹��캯��������string�����ַ���ʱ����Խ���һ����������������� 2019-6-19
					putText(tempB, R, Point(Circles[k].val[0], Circles[k].val[1]), FONT_HERSHEY_DUPLEX, 0.8, Scalar(0, 0, 255));
			*/
			cout << Array_Of_Circles[i][k].val[0] << "," << Array_Of_Circles[i][k].val[1] << endl;
			cout << "R=" << Array_Of_Circles[i][k].val[2] << endl;

		}
	}	
	
	imshow(Window_name_copy, tempB);
	waitKey(0);
}