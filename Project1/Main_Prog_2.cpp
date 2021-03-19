#include "Func_Proj_2nd.h"
#include <ctime>
#include "DataTransTCP.h"

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

#endif

string LoadPath_Msi_B("F:\\Pictures\\Test For Programming\\FreqFilterSrc.png");  
string LoadPath_Msi_C = "F:\\Pictures\\Test For Programming\\1.jpg"; 
string LoadPath_Msi_D("F:\\Pictures\\Test For Programming\\coins\\coin_6.bmp");

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
	namedWindow(window_name, WINDOW_NORMAL);
	//namedWindow(window_name, WINDOW_AUTOSIZE);

	//ԭʼͼ�����ȡ	
	SRC_2nd = imread(LoadPath_Msi_D, IMREAD_GRAYSCALE);
	cout << SRC_2nd.type();
	if (!SRC_2nd.data)
	{
		cout << "��ȡʧ��" << endl;
		return -1;
	}
	imshow(window_name, SRC_2nd);
	waitKey(0);
	Temp_Array.push_back(SRC_2nd);  //Temp_Array[0];
	Temp_Buffer = SRC_2nd.clone();
 
	//GaussianBlur(Temp_Buffer, Temp_Buffer, cv::Size(7, 7), 0);
	Temp_Array.push_back(Temp_Buffer);

	//��Եͼ�����
	Laplacian(Temp_Buffer, Temp_Buffer, CV_8UC1);
	//convertScaleAbs(Temp_Buffer, Temp_Buffer);
	threshold(Temp_Buffer, Temp_Buffer, 14, 1, THRESH_BINARY);  //�����Ϊ�涨����ֵ���ܻᵼ�²�ͬ�ع������ͼ�����һ�� ��ʵ֤��ֱ��coin5�ų������Ե����� ��Ӧ�Ի��Ǻ�ǿ�� ��coin2-4��ֵ�趨Ϊ14
	//��coin5���ع�������������Ѿ��������ֱ�����Ӳ�Ҳ��ֵı�Ե���Գ̶� ������ͼ˵����ֱ��OTSU���и��õĽ����������� �Żᵼ�������Ľ���� COIN5��Ȼ��ֱ��OTSUЧ����
	//ԭͼ���Եͼ���
	Mat masked = Temp_Buffer.mul(Temp_Array[0]);
	imshow(window_name, masked);
	waitKey(0);

	//OTSU֮ǰ���Ū����Ե����
	//double otsu_value = threshold(SRC_2nd, Temp_Buffer, 0, 255, THRESH_OTSU);  //˳���otsu��ֵ��¼һ�� 73 ֱ��OTSU
	double otsu_value = threshold(masked, Temp_Buffer, 0, 255, THRESH_OTSU);     //˳���otsu��ֵ��¼һ�� 54 ��Եǿ��OTSU
	threshold(SRC_2nd, Temp_Buffer, otsu_value, 255, THRESH_BINARY);
	imshow(window_name, Temp_Buffer);
	waitKey(0);

	std::vector<std::vector<cv::Point2i>> contours;								 //��һ������ͼ��ɣ���ΪTCP���͵ľֲ�ԭʼͼ�����ڲ��Ծֲ�ͨ��
	findContours(Temp_Buffer, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	std::vector<std::vector<cv::Point2i>> selected_Contours;

	auto iterC = contours.begin(); //������
	for (; iterC < contours.end(); iterC++) {
		if (iterC->size() >= 3000 && iterC->size()<4000) {
			selected_Contours.push_back(*iterC);
		}
	}

	if (selected_Contours.size() == 0) {
		printf("Error��û���ҵ����ʵı�Ե\n");
		return -3;
	}


	//����һ������ ����һ���ֲ�ͼ�� ���㷨����������
	/*
	 cv::Rect rectRoI(cv::boundingRect(selected_Contours[0])); //��Ҫ������չ �������Ҹ�20pix
	 cv::Rect extendRoI(rectRoI.x - 20, rectRoI.y - 20, rectRoI.width + 40, rectRoI.height + 40);
	 cv::Mat RoI(SRC_2nd(extendRoI));
	 imwrite("F:\\Pictures\\Test For Programming\\coins\\coin_6_RoI.jpg", RoI);
	 */
	 
	contours.clear(); //��ձ�Ե

	cv::Mat doubleSrc;	
	SRC_2nd.convertTo(doubleSrc,CV_64FC1);
	std::vector<cv::Point2d> subpixPoints;  //�����ؼ������������
	subpixPoints = SubPixel_Contours_Cgyt(doubleSrc, selected_Contours[0], 3.0);  
	//�����ʵ�Ѿ�������߼����ش��ͼ�����˻�����TCPЭ�鵫����η��ͻ��Ǹ����� �����ƺ�����Ӧ����ҳ������20210312 �����ܴ���
	
	//Ҫ����ʱ������һ���߳��������� join����Ҫ�� �������õ��ڴ����������˹��Ƶñ��� �ƺ�����Ӧ�������� д�����͵ü��� 20210317��ʱע��
	//std::thread tSend = thread(ContoursSubpixSend,subpixPoints); 
	//tSend.join();

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