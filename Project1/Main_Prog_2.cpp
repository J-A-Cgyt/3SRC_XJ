#include "Func_Proj_2nd.h"

string Load_Path_2nd_1 = "G:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //ƴ��ԭͼ1
string Load_Path_2nd_2 = "G:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //ƴ��ԭͼ2
string Load_Path_2nd_3 = "G:\\Pictures\\Test For Programming\\001.jpg"; //��ˮ��ָ�
string Load_Path_2nd_4 = "G:\\Pictures\\Test For Programming\\�ӵ���.bmp"; // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "G:\\Pictures\\Test For Programming\\�㽶3.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_6 = "G:\\Pictures\\Test For Programming\\sign_20200329.jpg"; // subPixel_Contours detect by Moments

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

	//ԭʼͼ�����ȡ
	SRC_2nd = imread(Load_Path_2nd_4, IMREAD_GRAYSCALE);

	if (!SRC_2nd.data)
	{
		cout << "��ȡʧ��" << endl;
		return -1;
	}

	namedWindow(window_name, WINDOW_NORMAL);
	//namedWindow(window_name, WINDOW_AUTOSIZE);
	imshow(window_name, SRC_2nd);
	waitKey(0);
	Temp_Array.push_back(SRC_2nd);

/*
	Temp_Buffer = Thershold_����(SRC_2nd);
	Temp_Array.push_back(Temp_Buffer);
	//Temp_Buffer.release();
	imshow(window_name, Temp_Array[0]);
	waitKey(0);

	//�ڶ����ֵĶ�ȡ����
	SRC_2nd = imread(Load_Path_2nd_2, IMREAD_GRAYSCALE);
	if (!SRC_2nd.data)
		{
			cout << "��ȡʧ��" << endl;
			return -1;
		}
	imshow(window_name, SRC_2nd);
	waitKey(0);
	Temp_Array.push_back(SRC_2nd);
	//��ȡ�������

	Temp_Buffer = JiaoDian_SURF_CGYT(Temp_Array[0], Temp_Array[1]); //SURF����+����ƥ��ʵ�� 20200215

*/

	//vector<Point2f> subPix_Point;
	//subPix_Point = subPix_pt(Temp_Array[0]);

	//TrackBar_cgyt_canny(0, 0); //TrackBar������Ϥ

	//NLM_CGYT(Temp_Array[0]); //Ҳ������ʵʱ�Լ�����û�в��м�����٣�����������

	//�������Դ�ļ�����δ����������������Ŀ�У� �������� 20200318
	//Temp_Array.push_back(Conv_Cgyt(Temp_Array[0],SOBEL_CGYT)); �������������ڵ�������Ŀ�н������20200321δ�������⣬һ��Դ�ļ�ʵ����������һ��Դ�ļ�ʵ�����Ա���������ඨ��д����һ��ͷ�ļ���

	//FT_CGYT(Temp_Array[0]);  //����Ҷ�任 20200323ͨ��

	//int res_state = Calib_Cgyt(Temp_Array[0]); ע����20200410
	//cout << res_state;

//������������ �ռ�������ؼ����Ҫ�����ؼ���ǰ�ô��룬��code_used��ת������ 20200415
	//�����������ؼ��ʵ�ֵ�ǰ�ô���
	Temp_Buffer = Gaosi_˫��(Temp_Array[0]); //��˹�˲�+��
	//imshow(window_name, Temp_Buffer);
	//waitKey(0);
	Temp_Array.push_back(Temp_Buffer);

	Canny(Temp_Array[1], Temp_Buffer, 80, 240); //canny��Ե���
	//imshow(window_name, Temp_Buffer);
	//waitKey(0);
	Temp_Array.push_back(Temp_Buffer);

	vector<vector<Point>> Contours_Dected, Contours_Seletced;
	vector<Point> Contours_for_SubPixCont;
	vector<Point2d> Contours_subPix_result;
	Moments ��;
	findContours(Temp_Array[2], Contours_Dected, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());  //Բ������������λ	
	for (int i = 0; i < Contours_Dected.size(); i++)
	{
		size_t k = Contours_Dected[i].size();
		if (k < 1000 && k > 700)
		{
			�� = moments(Contours_Dected[i]);
			if (abs(��.nu11) < 0.001)
			{
				//�ж���һ���ĸ߽����ľ���Ϊ�жϱ�׼�������ĸ����׹�һ�����ľؾ�Ϊ��С��10e-4�������Ϊ��x��y�����������ƫ���ԣ�����Ϊ����״����X��Y����Գ�		
				Contours_Seletced.push_back(Contours_Dected[i]);
			}
		}
	}
	Contours_for_SubPixCont = Contours_Seletced[0];
	cvtColor(Temp_Array[0], Temp_Buffer, COLOR_GRAY2BGR);
	drawContours(Temp_Buffer, Contours_Seletced, -1, Scalar(0, 0, 255));
	imshow(window_name, Temp_Buffer);
	waitKey(0);
	Temp_Array.push_back(Temp_Buffer); //ָ������δ��ȷ��ע�⴫���ַ����vector����������һ�µĿ���

	//�����ر�Ե������
	Contours_subPix_result = SubPixel_Contours_Cgyt(Temp_Array[0], Contours_for_SubPixCont, 2);

	return 0;
}