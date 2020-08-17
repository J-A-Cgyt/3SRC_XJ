//矩阵乘法的测试,避免重复造轮子，干脆把cv::Mat拿来用一下，其基本的数据结构应该就是一个二维数组+表头 难度看起来比较大，如果不行就先略过吧 封存 看思想先
#include "Header_Main.h"

#ifndef Matrix

class Mat_CGYT
{
public: int rows;       //行
public: int cols;       //列
private: double* data;  //下标顺序，行、列

public:
	Mat_CGYT(double * data, int rows, int cols); //重写的构造函数

	~Mat_CGYT();  //析构函数

	void setData(double * data, int rows, int cols);

	void Matrix(Mat_CGYT Matrix1, Mat_CGYT Matrix2, Mat_CGYT Result);
};


#endif // !Matrix


void Mat_CGYT::Matrix(Mat_CGYT Matrix1, Mat_CGYT Matrix2, Mat_CGYT Result)
{
	if (Matrix1.cols = !Matrix2.rows)
	{
		cout << "输入矩阵不合规范，Matrix1.cols =! Matrix2.rows" << endl;
		return;
	}

}

void Mat_CGYT::setData(double * data, int rows, int cols)
{
	this->data = data;
	this->rows = rows;
	this->cols = cols;
}

Mat_CGYT::~Mat_CGYT()  //析构函数
{
	cout << "实例销毁" << endl;
}

Mat_CGYT::Mat_CGYT(double* data, int rows, int cols) //重写的构造函数
{
	this->data = data;
	this->rows = rows;
	this->cols = cols;
}

//double** data = &M1; //M1是一个double指针的数组

Mat_CGYT MA = Mat_CGYT(A, 4, 4);