#include "Func_Proj_2nd.h"
#include <ctime>

//#define XPS15
#ifdef XPS15
/*----------------------------------------------XPS15 ����·��-----------------------------------------------------------------------*/
string Load_Path_2nd_1 = "G:\\Pictures\\Test For Programming\\DSC_7114.jpg"; //ƴ��ԭͼ1
string Load_Path_2nd_2 = "G:\\Pictures\\Test For Programming\\DSC_7115.jpg"; //ƴ��ԭͼ2
string Load_Path_2nd_3 = "G:\\Pictures\\Test For Programming\\001.jpg"; //��ˮ��ָ�
string Load_Path_2nd_4 = "G:\\Pictures\\Test For Programming\\�ӵ���.bmp"; // subPixel_Contours detect by Moments
string Load_Path_2nd_5 = "G:\\Pictures\\Test For Programming\\�㽶3.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_6 = "G:\\Pictures\\Test For Programming\\sign_20200329.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_7 = "G:\\Pictures\\Test For Programming\\003.1.jpg"; // subPixel_Contours detect by Moments
string Load_Path_2nd_8 = "G:\\Pictures\\Test For Programming\\eye.jpg"; // subPixel_Contours detect by Moments
#endif

/*--------------------------------------------̨ʽ��MSI ����·��---------------------------------------------------------------------*/
//#define USE_ALL
#ifdef USE_ALL
string LoadPath_Msi_0 = "F:\\Pictures\\Test For Programming\\DSC_8967.jpg";

string LoadPath_Msi_2 = "F:\\Pictures\\Test For Programming\\DSC_15774.jpg";
string LoadPath_Msi_3 = "F:\\Pictures\\Test For Programming\\DSC_15774-4.jpg";
string LoadPath_Msi_4 = "F:\\Pictures\\Test For Programming\\��ɽ���ƴ.jpg";
string LoadPath_Msi_5 = "F:\\Pictures\\Test For Programming\\xzf.jpg";  //���������ͼ1
string LoadPath_Msi_6 = "F:\\Pictures\\Test For Programming\\DSC_21516.jpg";  //���������ͼ1
string LoadPath_Msi_7 = "F:\\Pictures\\Test For Programming\\��.png";  //��ͨ������;
string LoadPath_Msi_8 = "F:\\Pictures\\Test For Programming\\pai.png";  
string LoadPath_Msi_9 = "F:\\Pictures\\Test For Programming\\gpgpu.png";  
string LoadPath_Msi_A = "F:\\Pictures\\Test For Programming\\��������ͼ��.png"; 

#endif
string LoadPath_Msi_1 = "F:\\Pictures\\Test For Programming\\eye.jpg";
string LoadPath_Msi_B("F:\\Pictures\\Test For Programming\\FreqFilterSrc.png");  
string LoadPath_Msi_C = "F:\\Pictures\\Test For Programming\\1.jpg";  

/*-----------------------------------------------------------------------------------------------------------------------------------*/

string window_name = "Demo_Result"; //�����ʾ��

Mat SRC_2nd; //ȫ��Դͼ
Mat DST_2nd; //ȫ�����ͼ
//clock_t Start, End;


//�������ƾ��������ö������˵��
enum Conv_cgyt
{
	SOBEL_CGYT = 0,
	LAPLACE8_CGYT = 1,
	LAPLACE4_CGYT = 2,
	GARDIENT1_CGYT = 3,
	SOBEK_X_CGYT = 4,
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
	SRC_2nd = imread(LoadPath_Msi_1, IMREAD_GRAYSCALE);
	cout << SRC_2nd.type();
	if (!SRC_2nd.data)
	{
		cout << "��ȡʧ��" << endl;
		return -1;
	}
	imshow(window_name, SRC_2nd);
	waitKey(0);
 

	//�����������ؼ��ʵ�ֵ�ǰ�ô���
	Temp_Array.push_back(SRC_2nd);

	Temp_Buffer = Gaosi_˫��(Temp_Array[0]); //��˹�˲�+��
	equalizeHist(Temp_Buffer,Temp_Buffer);
	GaussianBlur(Temp_Buffer, Temp_Buffer, Size(7, 7), 1);
	imshow(window_name, Temp_Buffer);
	waitKey(0);
	Temp_Array.push_back(Temp_Buffer);

	Canny(Temp_Array[1], Temp_Buffer, 30, 150); //canny��Ե���
	imshow(window_name, Temp_Buffer);
	waitKey(0);
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
	if (Contours_for_SubPixCont.size() == 0) { throw out_of_range("û�з����������زı�Ե!"); return -1; }
	Contours_for_SubPixCont = Contours_Seletced[0];
	cvtColor(Temp_Array[0], Temp_Buffer, COLOR_GRAY2BGR);
	drawContours(Temp_Buffer, Contours_Seletced, -1, Scalar(0, 0, 255));
	imshow(window_name, Temp_Buffer);
	waitKey(0);
	Temp_Array.push_back(Temp_Buffer); //ָ������δ��ȷ��ע�⴫���ַ����vector����������һ�µĿ���

	//�����ر�Ե������
	Contours_subPix_result = SubPixel_Contours_Cgyt(Temp_Array[0], Contours_for_SubPixCont, 2.0);


	//HistogramCGYT(SRC_2nd);
	//FT_CGYT(SRC_2nd, Temp_Buffer);
	//Filter_Freq(Temp_Buffer,4);
	//Temp_Buffer = HarmonicMeanFilter(SRC_2nd, 2,1,1);
	
	//imshow(window_name, Temp_Buffer);
	//waitKey(0)
	;
//һ������ 20201025��һ�� C++ϰ�ߺ���֪ʶ����ϰ����

	
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


	destroyAllWindows(); //�������д��ڣ��ֶ��ڴ����

	return 0;
}

//��ʦ�������Ժ��� Ч�ʷ�����Ż����кܶ������������ʵ���˷����Ժ���Ҫ����Ч�ʣ�ָ�����ƺ�Ҳ��һ���õķ���