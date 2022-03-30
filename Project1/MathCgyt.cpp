//���ڴ���ѧ����ĺ���ʵ�� ��Ӧͷ�ļ�MathCgyt.h
#include "Func_Proj_2nd.h"
#include "MathCgyt.h"

#if MathActivate == 1

//��һ��д������Zernike�صļ��� MATLAB��ʵ�� ������C++�м���
double JingXiang_R_n_m(unsigned int n, unsigned int m, double rho)
{
	if (n <= m)
	{
		cout << "n<=m is not allowed" << endl;
		return 0xffffffff;
	}
	return 0;
}

//�׳� �������������int
double JieCheng(const unsigned int &i)  
{
	int Res = 1;

	if (i == 0)
	{
		return (double)Res;
	}
	else {	
		int para = i;
		while (para)
		{
			Res = Res * para;
			para = para - 1;
		}
		return (double)Res;
	}
}

//Ӧ��һ�����ڼ���OTSU��������ֵ�ĺ��� ����Ϊvector<double> ��vector<unsigned char> ����double  20210311����ͨ�� ������ unsigned char���͵�ԭʼ����
unsigned char OTSU_Value_Calc(const std::vector<unsigned char>& src) {  //ע��˰汾�������� ,�����һ����ȷ����֤
	//���������ʼ��
	double grayLevel[256];                    //�Ҷȼ�����
	double sigmaB[256]     = { 0 };           //��׼������ �տ�ʼ����0
	int    pix_number[256] = { 0 };           //���Ҷȼ����ؼ�����
	double pix_prob[256]   = { 0.0f };        //�Ҷȼ����� Ϊͳ������/��������
	for (int i = 0; i < 256; i++) { grayLevel[i] = i; }

	//�Ҷ�ͳ��
	auto iterSrc_c = src.cbegin(); //���������� ����ֵ��
	for (; iterSrc_c < src.cend(); iterSrc_c++) {
		pix_number[*iterSrc_c]++;
	}
	//���ʼ���
	size_t n = src.size();  //��������
	for (int i = 0; i < 256; i++) {
		pix_prob[i] = (double)pix_number[i] / (double)n;
	}
	//ƽ���Ҷȼ���
	double Mg = 0;   //ƽ���Ҷ�
	for (int i = 0; i < 256; i++) {
		Mg += pix_prob[i] * grayLevel[i];
	}

	unsigned char OTSU_Value(0);
	//������䷽��
	for (int i = 0; i < 256; i++) {
		double P1k(0.0);
		double Mk(0.0);
		for (int k = 0; k < i; k++) {
			P1k += pix_prob[k];
			Mk += pix_prob[k] * grayLevel[k];
		}
		if (P1k == 0.0 || P1k == 1.0) {
			sigmaB[i] = -1;
		}
		else {
			sigmaB[i] = pow((Mg*P1k - Mk), 2) / (P1k*(1 - P1k));
		}
		//if (sigmaB[i] == nan()) { sigmaB[i] = -1; }
		if (sigmaB[i] > sigmaB[OTSU_Value]) {
			OTSU_Value = i;
		}
	}
	return OTSU_Value;
}


/**************************************************************************************************
* ����Ҫ��Ҫ����һ���ֲ����򷽲�;�ֵ����Ĺ��ߺ��� ���ڿɱ���ֵ 20210915 
* ������8UC1��Ϊ�㷨��֤��ͼ���
* ����˵����
*  src��  Դͼ��
*  row��  Ŀ�����������꣨Y��
*  col��  Ŀ�����������꣨X��
*  ksize�������С�������������صİ볤��
*  mean�� ��ֵ���
*  var��  ������
**************************************************************************************************/
int localMeanVarCalc(const Mat           &src, 
	                 const int            row,
	                 const int            col,
	                 const unsigned int  &ksize, 
                     double              *mean, 
	                 double              *var){

	if (src.type() != CV_8UC1) {
		printf("Mat Type Must Be CV_8UC1\n");
		return -1;
	}

	if ((row < 0) || (row >= src.rows)||
		(col < 0) || (col >= src.cols)) {
		printf("center point out of range\n");
		return -2;
	}

	unsigned int pix_count = 0;                                  //�����ܹ�����������������

	//���Ͻ�����
	int row_lt = row - ksize + 1;
	int col_lt = col - ksize + 1;

	//���½�����
	int row_rb = row + ksize - 1;
	int col_rb = col + ksize - 1;

	*mean = 0.0f;                                                //��ֵ�����ʼ��

	//ѭ�����
	for (int r = row_lt; r <= row_rb; r++) {

		//���к�С��0��������		
		if ((r<0) || (r>src.rows)) {
				continue;
		}
		
		unsigned char* row_head = r * src.step[0] + src.data;   //��ͷָ�����	
		for (int c = col_lt; c <= col_rb; c++) {
			if ((c<0) || (c>src.cols)) {
				continue;
			}			
			*mean += (double)(*(row_head + c));                 //����ֵ�ۼ�			
			pix_count++;                                        //���ؼ���+1 �������ѭ���в���Ҫ���¼���
		}
	}

	*mean = (*mean) / ((double)pix_count);                      //��ֵ����

	//ѭ���󷽲�
	double temp = 0;
	for (int r = row_lt; r <= row_rb; r++) {

		//���к�С��0��������		
		if ((r < 0) || (r > src.rows)) {
			continue;
		}

		unsigned char* row_head = r * src.step[0] + src.data;   //��ͷָ�����	
		for (int c = col_lt; c <= col_rb; c++) {
			if ((c < 0) || (c > src.cols)) {
				continue;
			}


			temp = pow((double)(*(row_head + c)) - *mean, 2);   //��ֵƽ������
			*var += temp;
		}
	}
	*var = (*var) / ((double)pix_count);

	return 0;                                                   //�ɹ����
}


/**************************************************************************************************
*  ��������Ҫһ����С�������Բ��C++�汾
*      contour      -I        ��ϵ������������㼯
*      circle_info  -O        �����Բ��Ϣ x:���ĺ����� y:���������� z:�뾶
*      error        -O        �����������
*  ����ֵ��������ϵĵ�����
*  20211210����ͨ�� �ԱȻ���任�����бȽϺõĽ��������������ô�����
**************************************************************************************************/
int minSqureFitCircle(const std::vector<cv::Point2d>& contour,
      	              cv::Point3d&                    circle_info,
	                  double&                         error) {

	circle_info.x = 0.0f;         //Բ��x
	circle_info.y = 0.0f;         //Բ��y
	circle_info.z = 0.0f;         //�뾶

	//�м����1(��Ͳ���) ���±�ʶ����ʡ��sigma��ͷ���
	double x   = 0.0f;                  // ��(x)
	double y   = 0.0f;                  // ��(y)
	double x2  = 0.0f;                  // ��(x*x)
	double xy  = 0.0f;                  // ��(x*y)
	double y2  = 0.0f;                  // ��(y*y)
	double x3  = 0.0f;                  // ��(x*x*x)
	double x2y = 0.0f;                  // ��(x*x*y)
	double xy2 = 0.0f;                  // ��(x*y*y)
	double y3  = 0.0f;                  // ��(y*y*y)

	size_t n = contour.size();          //����������

	double C = 0.0f, D = 0.0f, E = 0.0f, G = 0.0f, H = 0.0f;
	double a = 0.0f, b = 0.0f, c = 0.0f;

	//��������ѭ��
	for (size_t i = 0; i < n; i++) {
		x += contour[i].x;
		y += contour[i].y;

		x2 += contour[i].x * contour[i].x;
		xy += contour[i].x * contour[i].y;
		y2 += contour[i].y * contour[i].y;

		x3  += contour[i].x * contour[i].x * contour[i].x;
		x2y += contour[i].x * contour[i].x * contour[i].y;
		xy2 += contour[i].x * contour[i].y * contour[i].y;
		y3  += contour[i].y * contour[i].y * contour[i].y;
	}

	C = n * x2 - x * x;
	D = n * xy - x * y;
	E = n * x3 + n * xy2 - (x2 + y2) * x;
	G = n * y2 - y * y;
	H = n * y3 + n * x2y - (x2 + y2) * y;

	a = (H*D - E * G) / (C*G - D * D);
	b = (H*C - E * D) / (D*D - G * C);
	c = -(a*x + b * y + x2 + y2) / n;

	circle_info.x = -a * 0.5;
	circle_info.y = -b * 0.5;
	circle_info.z = sqrt(a * a + b * b - 4 * c) * 0.5;

	return (int)n;
}


/**************************************************************************************************
*  Ҫ��Ҫ����һ��RANSAC���Բ�ģ�
*      contour      -I        ��ϵ������������㼯
*      circle_info  -O        �����Բ��Ϣ x:���ĺ����� y:���������� z:�뾶
*      error        -O        �����������
*  ����ֵ��������ϵĵ�����
*
**************************************************************************************************/
int ransacFitCircle(const std::vector<cv::Point2d>& contour,
	                cv::Point3d&                    circle_info,
	                double&                         error) 
{
	circle_info.x = 0.0f;         //Բ��x
	circle_info.y = 0.0f;         //Բ��y
	circle_info.z = 0.0f;         //�뾶



	return 0;
}


#endif