//����˷��Ĳ���,�����ظ������ӣ��ɴ��cv::Mat������һ�£�����������ݽṹӦ�þ���һ����ά����+��ͷ �Ѷȿ������Ƚϴ�������о����Թ��� ��� ��˼����
#include "Header_Main.h"

#ifndef Matrix

class Mat_CGYT
{
public: int rows;       //��
public: int cols;       //��
private: double* data;  //�±�˳���С���

public:
	Mat_CGYT(double * data, int rows, int cols); //��д�Ĺ��캯��

	~Mat_CGYT();  //��������

	void setData(double * data, int rows, int cols);

	void Matrix(Mat_CGYT Matrix1, Mat_CGYT Matrix2, Mat_CGYT Result);
};


#endif // !Matrix


void Mat_CGYT::Matrix(Mat_CGYT Matrix1, Mat_CGYT Matrix2, Mat_CGYT Result)
{
	if (Matrix1.cols = !Matrix2.rows)
	{
		cout << "������󲻺Ϲ淶��Matrix1.cols =! Matrix2.rows" << endl;
		return;
	}

}

void Mat_CGYT::setData(double * data, int rows, int cols)
{
	this->data = data;
	this->rows = rows;
	this->cols = cols;
}

Mat_CGYT::~Mat_CGYT()  //��������
{
	cout << "ʵ������" << endl;
}

Mat_CGYT::Mat_CGYT(double* data, int rows, int cols) //��д�Ĺ��캯��
{
	this->data = data;
	this->rows = rows;
	this->cols = cols;
}

//double** data = &M1; //M1��һ��doubleָ�������

Mat_CGYT MA = Mat_CGYT(A, 4, 4);