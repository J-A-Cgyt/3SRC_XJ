#include "Func_Proj_2nd.h"


#define HK_CAMERA

#ifdef before_2021
string Load_Path_2nd_1 = "F:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //ƴ��ԭͼ1
string Load_Path_2nd_2 = "F:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //ƴ��ԭͼ2
string Load_Path_2nd_3 = "F:\\Pictures\\Test For Programming\\001.jpg";      //��ˮ��ָ�
string Load_Path_2nd_4 = "F:\\Pictures\\Test For Programming\\�ӵ���.bmp";   // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "F:\\Pictures\\Test For Programming\\�㽶3.jpg"; 
string Load_Path_2nd_6 = "F:\\Pictures\\Test For Programming\\sign_20200329.jpg";
string Load_Path_2nd_7 = "F:\\Pictures\\Test For Programming\\003.1.jpg"; 
string Load_Path_2nd_8 = "F:\\Pictures\\Test For Programming\\eye.jpg";
#endif

#ifdef HK_CAMERA
string Load_Path_2nd_9 = "F:\\Pictures\\Test For Programming\\HIK12MP\\StitchImg_1.jpg";
string Load_Path_2nd_A = "F:\\Pictures\\Test For Programming\\HIK12MP\\StitchImg_2.jpg";
string Load_Path_2nd_B = "F:\\Pictures\\Test For Programming\\HIK12MP\\StitchImg_3.jpg";
string Load_Path_2nd_C = "F:\\Pictures\\Test For Programming\\HIK12MP\\StitchImg_4.jpg";
#endif // HK_CAMERA


string window_name = "Demo_Result"; //�����ʾ��

Mat SRC_2nd; //ȫ��Դͼ
Mat DST_2nd; //ȫ�����ͼ


//�������ƾ��������ö������˵��
enum Conv_cgyt
{
	SOBEL_CGYT = 0,
	LAPLACE_CGYT = 1,
	GARDIENT1_CGYT = 2,
};

int main()
{
	std::vector<Mat> Temp_Array;
	Mat Temp_Buffer;
	namedWindow(window_name, WINDOW_NORMAL);
	//Calib_Cgyt(Mat()); 20210203ע��

	//ԭʼͼ�����ȡ
	SRC_2nd = imread(Load_Path_2nd_9, IMREAD_GRAYSCALE);
	if (!SRC_2nd.data){
		cout << "��ȡʧ��" << endl;
		return -1;
	} 
	Temp_Array.push_back(SRC_2nd);
	
	SRC_2nd = imread(Load_Path_2nd_A, IMREAD_GRAYSCALE);
	if (!SRC_2nd.data) {
		cout << "��ȡʧ��" << endl;
		return -1;
	}
	Temp_Array.push_back(SRC_2nd);

	//Temp_Buffer = JiaoDian_SURF_CGYT(Temp_Array[0], Temp_Array[1]); //SURF����+����ƥ��ʵ�� 20200215
	pic_Move_Cgyt(Temp_Array[0], Temp_Buffer, -600, -600);
	
	return 0;
}