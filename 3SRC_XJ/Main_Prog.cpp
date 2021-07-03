#include "Func.h"
//����һ�£��������������ҵ�����̨������Ϲ����д�Ĵ��붼��ר������hough�任��Բ���� д����
//�γɹ��ܵĴ�����Դ�������ֲ��ȥ������������Ŀ

Mat SRC,DST;

string Load_Path_1 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Circle_in_slot_2\\CIS_2.jpg";
string Load_Path_2 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Circle_in_slot_2_BackLight\\CIS_B_1.jpg";
string Load_Path_3 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Full_circle\\20191114-102834-305.jpg"; //20200335 ���
string Load_Path_4 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Side_slot\\20191114-110032-155.jpg";
string Load_Path_5 = "G:\\Pictures\\Test For Programming\\PIC_BXG\\Top_slot\\20191114-110910-75.jpg";

string Window_Name = "Demo_Result";

int GS_Ksize = 27;
int Thershold = 4; //�𽺵���Ϊ40


int main()
{
	Mat Temp1, Temp2, Temp3, Temp4;	
	//vector<vector<Point>> BY_Contours;
	vector<Vec3f> Circles;
	vector<vector<Vec3f>> Array_of_circles;
	vector<Vec2f> Lines;  //ֱ�߼��Ĳ��Դ��룬��2019/11/12��ʼ����
    
	namedWindow(Window_Name, WINDOW_NORMAL);
	
	SRC = imread(Load_Path_5);
	if (!SRC.data)
	{
		cout << "ͼ���ȡʧ��" << endl;
		return -1;
	}

	//resize(SRC, SRC, Size(800, 600));
	Mat Map = SRC.clone();//��ͼ�񣨾������ڱ�ʶ����
	cvtColor(SRC, SRC, COLOR_BGR2GRAY);
	imshow(Window_Name, SRC);
	waitKey(0);

	//Temp1 = ZhiFangTu_JunHua(SRC);
	//imshow(Window_Name, Temp1);
	//waitKey(0);

	Temp1 = Gaosi_Mohu(SRC, GS_Ksize); //��˹ģ��
	//Temp3 = Gaosi_˫��(SRC);  //��Ե�����˲�����
	imshow(Window_Name, Temp1);
	waitKey(0);

//�����ǽ�����������ն�λ�ü��ߴ���Ĳ��Դ��룬����δ��֤����ʼʱ��	
	//Circles = Hough_circle(Temp1, Map);  //һ��Բ���

/*
	��Զ������е����۵Ĵ�Բ���������뵽���ְ취��
	1��ʹ������Hough�任�ֱ�ʶ���Բ�밼��������Բ�������������λ�ù�ϵ���м���ж�

	2��ʹ��canny��������ȡ��Ե������������������ƶ�ƥ�䣬ͨ�������߳��������Ծ�ֵ��

	ֵ��ע����ǣ��˶���ʵ�ֵ�ƥ�䷽���Ծ����趨��Ϊ�ϸ�������������ݴ������ϲ���ȱ���߶Ȳ����ԡ�
	���ַ��������ȡ��Ƶ������ͼֽ�Լ�������ģ�巽�����������⡣
	�ҿ��ǵ��ֱ������ƣ�Ԥ�����Ȳ������0.1mm��������
	���巽��ʵ�����£�����任������ǰ������ͼ����
*/

//-------------------------------------------------����ΪHough�任����ʵ��----------------------------------------------------------------------------------------------------
	Hough_Param Param_FC;

	Temp2 = ZhiFangTu_JunHua(Temp1);
	cout << "ֱ��ͼ�������" << endl;
	imshow(Window_Name, Temp2);
	waitKey(0);

	Circles = Hough_circle_Class(Temp1,Map,Param_FC);
	if (Circles.size() == 0)
	{
		cout << "δ��⵽Բ" << endl;
		//return 1;
	}
	Array_of_circles.push_back(Circles);

/*
	Circles = Hough_circle_Copy1(Temp1, Map); //����Բ���
	if (Circles.size() == 0)
	{
		cout << "δ��⵽Բ" << endl;
		//return 1;
	}
	Array_of_circles.push_back(Circles);

	Circles = Hough_circle_Copy2(Temp1, Map); //����СԲ���
	if (Circles.size() == 0)
	{
		cout << "δ��⵽Բ" << endl;
		//return 1;
	}
	Array_of_circles.push_back(Circles);
*/	

	if (Array_of_circles.size() == 0)
	{
		cout << "δ��⵽Բ" << endl;
		return 1;
	}

	Draw_Circles(Array_of_circles, Map);

	//Hough_Lines(Temp1, Map);

//----------------------------------------------------------����Ϊ�ط���ʵ��--------------------------------------------------------------------------------------------------
	return 0;
}