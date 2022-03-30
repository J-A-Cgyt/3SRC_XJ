#include "Func.h"
/*
  解释一下 这个代码是为了复用参数设置的源文件，多个圆需匹配不同的特征检测参数，
  但是检测精度存疑，为保证检测精度，需要最终的设备严格控制检测的条件
*/
string Window_name_copy = "Demo_Result";

vector<Vec3f> Hough_circle_Copy1(Mat src, Mat Map) //用于检测同心圆中小圆设定的副本参数方法
{
	int Hough_Method = HOUGH_GRADIENT;
	double dp = 1;
	double mindist = 10;
	double Param1 = 60;
	double Param2 = 80;
	int minRadius = 80;
	int maxRadius = 120;	 //金属机械件检测圆参数

	//霍夫检测参数组结束

	vector<Vec3f> Circles;
	Mat tempA;

	//霍夫圆检测
	tempA = src.clone();
	

	HoughCircles(tempA, Circles, Hough_Method, dp, mindist, Param1, Param2, minRadius, maxRadius);
	/*此处需要有对检测的特征进行筛选的代码，针对不同对象需要设置不同的阈值参数*/

	return Circles;
}

vector<Vec3f> Hough_circle_Copy2(Mat src, Mat Map) //用于检测同心圆中小小圆设定的副本参数方法
{
	int Hough_Method = HOUGH_GRADIENT;
	double dp = 1;
	double mindist = 10;
	double Param1 = 20;
	double Param2 = 40;
	int minRadius = 40;
	int maxRadius = 60;	 //金属机械件检测圆参数

	//霍夫检测参数组结束

	vector<Vec3f> Circles;
	Mat tempA;

	//霍夫圆检测
	tempA = src.clone();


	HoughCircles(tempA, Circles, Hough_Method, dp, mindist, Param1, Param2, minRadius, maxRadius);
	/*此处需要有对检测的特征进行筛选的代码，针对不同对象需要设置不同的阈值参数*/

	return Circles;
}

vector<Vec3f> Hough_circle_Class(Mat src, Mat Map, Hough_Param Param) //类化参数的圆检测方法
{
	//霍夫检测参数组结束
	vector<Vec3f> Circles;
	Mat tempA;

	//霍夫圆检测
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

	/*此处需要有对检测的特征进行筛选的代码，针对不同对象需要设置不同的阈值参数*/

	return Circles;
}

void Draw_Circles(vector<vector<Vec3f>> Array_Of_Circles, Mat Map)  //画圆的函数，暂时废掉霍夫变换圆检测的时候的内部功能
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
					R=cout //似乎除了构造函数，在往string里填字符的时候可以接收一般的数字型数据类型 2019-6-19
					putText(tempB, R, Point(Circles[k].val[0], Circles[k].val[1]), FONT_HERSHEY_DUPLEX, 0.8, Scalar(0, 0, 255));
			*/
			cout << Array_Of_Circles[i][k].val[0] << "," << Array_Of_Circles[i][k].val[1] << endl;
			cout << "R=" << Array_Of_Circles[i][k].val[2] << endl;

		}
	}	
	
	imshow(Window_name_copy, tempB);
	waitKey(0);
}