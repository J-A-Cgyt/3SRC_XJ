#include "Func_Proj_2nd.h"
string window_name_f3 = "Demo_Result"; //�����ʾ��

Mat Gaosi_˫��(Mat Src) //��˹˫���˲����񻯣����ֱ�Ե���˲� 2019/11/14,�Ӳ����������Ŀ��ֲ
{
	int d = 0;
	double Sigma_Color = 100;
	double Sigma_Space = 15;
	Mat Dst;
	bilateralFilter(Src, Dst, d, Sigma_Color, Sigma_Space);

	//���˾�
	Mat Filter = (Mat_<char>(3, 3) << 0, -1, 0,
									 -1, 5, -1,
									  0, -1, 0);

	filter2D(Dst, Dst, Dst.depth(), Filter);

	return Dst;
}

//�Ǿֲ���ֵ�˲� 20200310 ��ͷ�ļ�photo.hpp�� �Բ����Ѿ����ֳ�API�ľͲ��Լ�д�ˣ�֪��ԭ�����
Mat NLM_CGYT(Mat Src)
{
	Mat temp = Src.clone();
	float h = 10;
	int templateWindowSize = 7; //���飨����ֿ飩�Ĵ�С
	int searchWindowSize = 21;  //������������Ĵ�С
	fastNlMeansDenoising(Src, temp, h,
						 templateWindowSize, 
						 searchWindowSize);
	/*
	h : ����������ǿ�ȡ�h ֵ�߿��Ժܺõ�ȥ������,��Ҳ���ͼ���ϸ��Ĩȥ��(ȡ 10 ��Ч������)
	hForColorComponents : �� h ��ͬ,��ʹ�����ɫͼ��(�� h ��ͬ,10)
	templateWindowSize : ������(�Ƽ�ֵΪ 7)
	searchWindowSize : ������(�Ƽ�ֵΪ 21)
	���ԭ���NoteExpress���ױʼ� ������Zernike�������صĸ߷����������ȱ�ݼ�⡱
	*/
	imshow(window_name_f3, temp);
	waitKey(0);
	return temp;
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//�ص�ʵ���о�ʼ�� 20200225�����볢�Կ�ʼ 20200226
//ͬ���ǽ���һ���ط�������ʵ��ROI��Hu�ؼ��� ��Ӧ����ǰ���ȶ�ROI������ȡ����������ȡ��Ե ��ʽ1��ͼ����������
int Hu_Ju_CGYT(Mat Src,double* Hu_Ju)
{
	Mat Temp;
	Temp = Src.clone();
	Moments Basic_Ju_Cgyt;
	//double Hu_Ju[7];

	Basic_Ju_Cgyt = moments(Temp);
	HuMoments(Basic_Ju_Cgyt, Hu_Ju);

	return 0; //����ָ���Ƿ�ᱻ����δ֪���˴�������bug ��Ȼ��bug

}

//ͬ���ǽ���һ���ط�������ʵ��ROI��Hu�ؼ��� ��Ӧ����ǰ���ȶ�ROI������ȡ����������ȡ��Ե ��ʽ2����Ե���㼯��������
int Hu_Ju_CGYT(vector<Point> Contour,double* Hu_Ju)
{

	Moments Basic_Ju_Cgyt;
	//double Hu_Ju[7];

	Basic_Ju_Cgyt = moments(Contour);
	HuMoments(Basic_Ju_Cgyt, Hu_Ju);

	return 0; //����ָ���Ƿ�ᱻ����δ֪���˴�������bug
}

/*
	Zernike�ص�ʵ�ֳ��ԣ��Ȱ����������Ȼ���ٿ������Ӧ��������Ե�������ؼ���λ�� ������Ҫһ��������ͷ�ļ���Դ�ļ�����������ʵ��Zernike�صļ���
	
	20200227 ��¼
	��ͼ����������ر�Ե�����ܲ���Ҫǰ��Canny��Sobel�����ӽ������ؼ��ı�Ե��ȡ

	��ȷһ�������ر�Ե��ȡ����������Ϊ vector<Point2d> ~contour
	vector<vector<Point2d>> ~contours �����ؼ��Ľ���޷���ͼ�������֣� 
	�ƺ�Ҳ�ɣ����ǵ�Ԫ�ڱ���Ľ��������ֵ������������ƫ��������ԵĲο�ϵ���������ģ���������Ϊ���������������ʵ�ֵİɡ����Ǿ������ͣ�������Ϊ CV_64FC2

	20200229 ��¼
	ʵ��Ŀ�����Ϊʹ�þص�������������λʵ��,��ʵ�ּ��ξ�(�򵥵ľ�)���ٳ���Zernike��

	20200302 ��¼
	���ھصĻҶȼ�Ȩģ�������㷽���Ľ����Ȼ���ɣ���Ҫ������Բ�ͬ�������p��q�׾أ�ģ���ָ����Ӧ�ã�
	�Ƿ���Ӧ��OpenCV����Я���ľؼ��㷽��������Ӧʹ��ģ�彫Բ��Ҷ���0��ʹ���Դ��������м��㣨�˷���Ӧע������ԭ����趨��ƫ�ã���
	��Ҫ������°�֮ǰд�Ĵ��붼�ӽ�rubbish�����³��ԣ�����ƪ���ĵļ��������ٽ���һ���ȶ� 
	
	20200303��¼
	�򵥵����ⷽ��ͨ����������̫�࣬���ǽ��������ռ��������ر�Ե�����������
*/
vector<Point2d> SubPixel_Contours_Cgyt(Mat Src, vector<Point> contour)
{
	Mat temp1, temp2;
	Mat Mu_Cal = Mat(temp1.size(), CV_64FC1);
	temp1 = Src.clone();
	cv::imshow(window_name_f3,temp1);
	cv::waitKey(0);
	temp1.setTo(0);

	//Ϊ��ʹ��drawContours����������һ���
	vector<vector<Point>> Contours;	
	Contours.push_back(contour);

	//�ڴ˴���¼һ����ͨ���ξؽ��������ؼ���ģ�壬�ߴ�7*7,���������ԭ����������
	/*
	20200228
	�²�ֻҪ�ǻ��ھص������ؼ�⣬Ӧ�ö���ͳһ����ʽ�����㼸����ͬ������ĳ���ص�һ����Χ�����ڵľ�ֵ��
	�ٰ���һ��������ת��Ϊʵ�������ؾ��ȵ�����ֵ���ڼ���ǰ����˵��Ҫ��һ���ģ�����ķ����ü���ѧϰ��
	��������[1]���½࣮������ѧ��̬ѧ�ͻҶȾصĸ��������ر�Ե���[J]�����߼�����2019��53(03)��132-136��
	*/
//�ؾ������ģ���趨
	double Omega[5];
	Omega[0] = 0;
	Omega[1] = 0.00913767235;
	Omega[2] = 0.021840193;
	Omega[3] = 0.025951560;
	Omega[4] = 0.025984481;
	Mat Mask1_JHJ = Mat(7,7,CV_64FC1);
	Mask1_JHJ.setTo(-1);

	cout << Mask1_JHJ << endl;

	Mask1_JHJ.at<double>(0, 0) = Omega[0];  Mask1_JHJ.at<double>(0, 3) = Omega[3];
	Mask1_JHJ.at<double>(0, 6) = Omega[0];  Mask1_JHJ.at<double>(3, 0) = Omega[3];
	Mask1_JHJ.at<double>(6, 0) = Omega[0];  Mask1_JHJ.at<double>(3, 6) = Omega[3];
	Mask1_JHJ.at<double>(6, 6) = Omega[0];  Mask1_JHJ.at<double>(6, 3) = Omega[3];
	
	Mask1_JHJ.at<double>(0, 1) = Omega[1];  Mask1_JHJ.at<double>(0, 2) = Omega[2];
	Mask1_JHJ.at<double>(0, 5) = Omega[1];  Mask1_JHJ.at<double>(0, 4) = Omega[2];
	Mask1_JHJ.at<double>(1, 0) = Omega[1];  Mask1_JHJ.at<double>(2, 0) = Omega[2];
	Mask1_JHJ.at<double>(1, 6) = Omega[1];  Mask1_JHJ.at<double>(2, 6) = Omega[2];
	Mask1_JHJ.at<double>(6, 1) = Omega[1];  Mask1_JHJ.at<double>(4, 0) = Omega[2];
	Mask1_JHJ.at<double>(6, 5) = Omega[1];  Mask1_JHJ.at<double>(4, 6) = Omega[2];
	Mask1_JHJ.at<double>(5, 0) = Omega[1];  Mask1_JHJ.at<double>(6, 2) = Omega[2];
	Mask1_JHJ.at<double>(5, 6) = Omega[1];  Mask1_JHJ.at<double>(6, 4) = Omega[2]; 
	//double sum = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (Mask1_JHJ.at<double>(j, i) == -1)
			{
				Mask1_JHJ.at<double>(j, i) = Omega[4];
			}
			//sum = sum + Mask1_JHJ.at<double>(j, i);
		}
	}
	std::cout << Mask1_JHJ << endl;
	//����Ե������չʾ
	cv::drawContours(temp1,Contours,-1,Scalar::all(255),FILLED);
	cv::imshow(window_name_f3, temp1); //�ڰ�ͼ
	waitKey(0);

	//���¸���ԭͼ���˲��ִ���20200302��ӣ����¼���ʹ��ԭͼ�����¼���Ӧʹ�ö�ֵͼ����ԭʼ�Ҷ�ͼ����
	temp1 = Src.clone();
	temp1.convertTo(temp1,CV_64FC1);


	//filter2D(temp, Mu_Cal, Mu_Cal.depth(), Mask1_JHJ);
	//cout << Mu_Cal << endl;
	size_t c_s = contour.size();
	vector<vector<double>> JHJ_value; //���׾ش洢
	vector<Moments> Basic_Mu;
	vector<double> Mu_1; //1��
	vector<double> Mu_2; //2��
	vector<double> Mu_3; //3�� �˴�����ɶ��߳�

	Mat RoI, RoI_2, RoI_3;    //ԭͼ�ֲ����Լ�����õı�Ե��Ϊ����
	//double Temp_Mu_Value;
	
//�ؼ���ѭ�� �صļ��������Ҫ��ԭʼ�Ҷ�ͼ�Ͻ��У���Ԥ����
	for (int i = 0; i < c_s ; i++)
	{
		//1�׾�
		RoI = temp1(Rect(contour[i].x - 3, contour[i].y - 3, 7, 7));
		Mu_1.push_back(RoI.dot(Mask1_JHJ));
		//2�׾�,�Ҷ�ƽ��
		RoI_2 = RoI.mul(RoI);
		Mu_2.push_back(RoI_2.dot(Mask1_JHJ));
		//3�׾أ��Ҷ�����
		RoI_3 = RoI_2.mul(RoI);
		Mu_3.push_back(RoI_3.dot(Mask1_JHJ));

		//�����ļ��ξ�
		temp2 = Src(Rect(contour[i].x - 3, contour[i].y - 3, 7, 7));
		Basic_Mu.push_back(moments(temp2));
	}
	//��ѹһ��
	JHJ_value.push_back(Mu_1);
	JHJ_value.push_back(Mu_2);
	JHJ_value.push_back(Mu_3);

//��Ե������������
	//����������� h2,h1Ϊ�Ҷȣ�sigma��sΪ�м������P_1��P_2Ϊ�Ҷ�ֵh1��h2��ռ����ı����й�ϵP_1+P_2=1
	int h2;double sigma, S_Cgyt;
	int h1; //double Rho, Theta;
	double alpha;//�м����

	vector<double> P_1, P_2,P; 
	vector<double> Theta;
	vector<double> Rho;	 //��Ե���ղ�����RhoΪ�������ĳ��ȣ�ThetaΪƫת�Ƕȣ���ʱ��Ϊ��

	Point2d Center_Coordinate; //��������
	vector<Point2d> Contour_subPix; //�������

	//��Ե��������ѭ��#1
	for (int i = 0; i < c_s; i++)
	{
		sigma = sqrt(Mu_2[i] - Mu_1[i] * Mu_1[i]);
		S_Cgyt = (Mu_3[i] + 2 * Mu_1[i] * Mu_1[i] * Mu_1[i] - 3 * Mu_1[i] * Mu_2[i]) / (sigma*sigma*sigma);
		
		P_1.push_back((1 + S_Cgyt * sqrt(1 / (4 + S_Cgyt * S_Cgyt))) / 2);
		P_2.push_back((1 - S_Cgyt * sqrt(1 / (4 + S_Cgyt * S_Cgyt))) / 2);
		P.push_back(MIN(P_1[i], P_2[i]));
		
		Center_Coordinate.x = (Basic_Mu[i].m10 / Basic_Mu[i].m00) - 3.5;
		Center_Coordinate.y = (Basic_Mu[i].m01 / Basic_Mu[i].m00) - 3.5; //����������ɺ�ƫ����ͼ�����������ϵ�Ա����Ƕ�theta
		//Weight_Center.push_back(Point2d(Center_Coordinate.x, Center_Coordinate.y)); ������������ѹ�룬�Ǳ�Ҫ
		
		//�Ƕ�ѹ�룬Ϊ�����ƣ���Χ[-Pi,+Pi]
		Theta.push_back(atan2(Center_Coordinate.x, Center_Coordinate.y));
	}

	//��Ե��������ѭ��#2
	for (int i = 0; i < c_s; i++)
	{
		alpha = Solve_Cgyt(P[i]);
		Rho.push_back(cos(alpha));
		Contour_subPix.push_back(Point2d(3.5 * Rho[i] * cos(Theta[i]) + contour[i].x, 
										 3.5 * Rho[i] * sin(Theta[i]) + contour[i].y));
	}


	return Contour_subPix;  
	/*��һ�������ر�Ե�����򣨻ҶȾأ� 20200302����ͨ������ȱ������ԭ��ĸ߾��Ȳ����ֶΣ�
	�侫���޷���֤������Ӧ�ò����̫�࣬�Ͼ�ƫ����Ҳ����0~3�����ص�λ�� 
	��Ҫȷ������߾��ȣ�����Ҫ������ֶ���֤������Ҫ������ǰ�ü���㷨���*/
}

double Solve_Cgyt(double P) //�����Է�������⺯�� ����Ϊ x - 0.5*sin(2 * x) = Pi * P,ʹ�ü򵥵���������� 20200302
{
	double Pi = 3.1415926535897935384626;
	double Err = 100;
	double x, y;
	x = 0;
	int i = 0;
	double limit; limit = pow(10, -3);
	while (Err > limit)
	{
		y = 0.5*sin(2 * x) + Pi * P;
		Err = abs(y - x);
		x = y;
		i = i + 1;
		if (i > 1000000) //ע�� P=0.5����ʱ����������������ǻ���������Ϊ0��
		{
			cout << "������������" << endl;
			cout << "�������" << Err << endl;
			return y;
		}
	}
	return y;
}

//�ڴ˴�д�ڶ�����������������ͨ�ص������ر�Ե��ⷽ����ʹ�ü��ξأ��Ƚ�һ��OpenCV�Դ��ľؼ��㷽����ģ������к�����ʹ�����غ���������һ��int�͵����������������
vector<Point2d> SubPixel_Contours_Cgyt(Mat Src, vector<Point> contour, int second = 2) //20200408
{
	vector<Point2d> Res;

	return Res;
}