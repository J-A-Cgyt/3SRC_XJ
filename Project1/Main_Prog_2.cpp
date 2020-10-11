#include "Func_Proj_2nd.h"
#include <ctime>

/*----------------------------------------------XPS15 ����·��-----------------------------------------------------------------------*/
string Load_Path_2nd_1 = "G:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //ƴ��ԭͼ1
string Load_Path_2nd_2 = "G:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //ƴ��ԭͼ2
string Load_Path_2nd_3 = "G:\\Pictures\\Test For Programming\\001.jpg"; //��ˮ��ָ�
string Load_Path_2nd_4 = "G:\\Pictures\\Test For Programming\\�ӵ���.bmp"; // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "G:\\Pictures\\Test For Programming\\�㽶3.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_6 = "G:\\Pictures\\Test For Programming\\sign_20200329.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_7 = "G:\\Pictures\\Test For Programming\\003.1.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_8 = "G:\\Pictures\\Test For Programming\\eye.jpg"; // subPixel_Contours detect by Moments

/*--------------------------------------------̨ʽ��MSI ����·��---------------------------------------------------------------------*/
string LoadPath_Msi_0 = "F:\\Pictures\\Test For Programming\\DSC_8967.jpg";
string LoadPath_Msi_1 = "F:\\Pictures\\Test For Programming\\eye.jpg";
string LoadPath_Msi_2 = "F:\\Pictures\\Test For Programming\\DSC_15774.jpg";
string LoadPath_Msi_3 = "F:\\Pictures\\Test For Programming\\DSC_15774-4.jpg";
string LoadPath_Msi_4 = "F:\\Pictures\\Test For Programming\\��ɽ���ƴ.jpg";
string LoadPath_Msi_5 = "F:\\Pictures\\Test For Programming\\xzf.jpg";  //���������ͼ1
string LoadPath_Msi_6 = "F:\\Pictures\\Test For Programming\\DSC_21516.jpg";  //���������ͼ1
string LoadPath_Msi_7 = "F:\\Pictures\\Test For Programming\\��.png";  //��ͨ������;
string LoadPath_Msi_8 = "F:\\Pictures\\Test For Programming\\pai.png";  
string LoadPath_Msi_9 = "F:\\Pictures\\Test For Programming\\gpgpu.png";  
string LoadPath_Msi_A = "F:\\Pictures\\Test For Programming\\��������ͼ��.png";  
string LoadPath_Msi_B = "F:\\Pictures\\Test For Programming\\FreqFilterSrc.png";  

/*-----------------------------------------------------------------------------------------------------------------------------------*/

string window_name = "Demo_Result"; //�����ʾ��

Mat SRC_2nd; //ȫ��Դͼ
Mat DST_2nd; //ȫ�����ͼ
//clock_t Start, End;


//�������ƾ��������ö������˵��
enum Conv_cgyt
{
	SOBEL_CGYT = 0,
	LAPLACE_CGYT = 1,
	GARDIENT1_CGYT = 2,
};
//ͫ�׼��ķ���ѡ��
enum Iris_dect
{
	HOUGH = 0,
	COUNTOUR = 1,
};

int main()
{
	std::vector<Mat> Temp_Array;
	Mat Temp_Buffer;
	//namedWindow(window_name, WINDOW_KEEPRATIO);
	namedWindow(window_name, WINDOW_AUTOSIZE);

	//ԭʼͼ�����ȡ	
	SRC_2nd = imread(LoadPath_Msi_B, IMREAD_GRAYSCALE);
	if (!SRC_2nd.data)
	{
		cout << "��ȡʧ��" << endl;
		return -1;
	}
	imshow(window_name, SRC_2nd);
	waitKey(0);

	//HistogramCGYT(SRC_2nd);
	FT_CGYT(SRC_2nd, Temp_Buffer);
	Filter_Freq(Temp_Buffer,2);


	
	//imshow(window_name, DST_2nd);
	//waitKey(0);

	//Temp_Buffer = CannyG_Cgyt(SRC_2nd);
	//HoughLineG_Cgyt(Temp_Buffer);
	//threshold(SRC_2nd, Temp_Buffer, 200, 255, THRESH_BINARY);
	//Components_Connected_cgyt(Temp_Buffer);
	//FaceG_cgyt(SRC_2nd);  //�˺���GPU�汾���� �����ò�֪��ɶûʵ�� CPU����
	//IrisDectH_GPU(SRC_2nd);
	//ORBG_cgyt(SRC_2nd);
	//SURFG_cgyt(SRC_2nd, Temp_Buffer); //surf��GPU�汾��ϴ��룬20200723ע��

	/*	
	Point3f center;
	center = IrisDect(Temp_Array[0],COUNTOUR);
	cvtColor(SRC_2nd, Temp_Buffer, COLOR_GRAY2BGR);
	circle(Temp_Buffer, Point(center.x, center.y), center.z, Scalar(0, 0, 255), 3);
	imshow(window_name, Temp_Buffer);
	waitKey(0);  //�۶�������������룬ע����20200705


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

	//vector<Point2f> subPix_Point;
	//subPix_Point = subPix_pt(Temp_Array[0]);

	//TrackBar_cgyt_canny(0, 0); //TrackBar������Ϥ

	//�������Դ�ļ�����δ����������������Ŀ�У� �������� 20200318
	//Temp_Array.push_back(Conv_Cgyt(Temp_Array[0],SOBEL_CGYT)); �������������ڵ�������Ŀ�н������20200321δ�������⣬һ��Դ�ļ�ʵ����������һ��Դ�ļ�ʵ�����Ա���������ඨ��д����һ��ͷ�ļ���

	//FT_CGYT(Temp_Array[0]);  //����Ҷ�任 20200323ͨ��

	//int res_state = Calib_Cgyt(Temp_Array[0]); ע����20200410
	//cout << res_state;

	Temp_Buffer = Anisotropic_Cgyt(Temp_Array[0], 20, 0.75, 10);
	imshow(window_name, Temp_Buffer);	
	imwrite("G:\\Pictures\\Test For Programming\\003.2.jpg", Temp_Buffer);
	cout << "end" << endl;
	waitKey(0);
	
	Temp_Buffer = AnisotropicMT_Cgyt(Temp_Array[0], 20, 0.75, 10);

	Temp_Buffer = WaveLetHarrD_CGYT(Temp_Array[0], 1);
	imshow(window_name, Temp_Buffer);
	waitKey(0);

	Temp_Array[0] = WaveLetHarrR_CGYT(Temp_Buffer, 1);
	imshow(window_name, Temp_Array[0]);
	waitKey(0);
*/

	destroyAllWindows(); //�������д��ڣ��ֶ��ڴ����

	return 0;
}