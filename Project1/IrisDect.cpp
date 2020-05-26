#include "Func_Proj_2nd.h"

Point2f IrisDect(Mat Src)
{
	int Hough_Method = HOUGH_GRADIENT;
	double dp = 1;
	double mindist = 10;
	double Param1 = 60;
	double Param2 = 80;
	int minRadius = 80;
	int maxRadius = 120;	 //��Ĥ������

	//��������������

	vector<Vec3f> Circles;
	Mat tempA;

	//����Բ���
	tempA = Src.clone();

	HoughCircles(tempA, Circles, Hough_Method, dp, mindist, Param1, Param2, minRadius, maxRadius);

	Point2f CenterCord;
	CenterCord.x = Circles[0].val[0];
	CenterCord.y = Circles[0].val[1];

	circle(tempA, CenterCord,
		int(Circles[0].val[2]), Scalar(0, 0, 255), 5);

	return Point2f();
}