//���ڴ���ѧ����ĺ���ʵ�� ��Ӧͷ�ļ�MathCgyt.h
#include "Func_Proj_2nd.h"

#if MathActivate == 1

//��һ��д������Zernike�صļ���
double JingXiang_R_n_m(unsigned int n, unsigned int m, double rho)
{
	if (n <= m)
	{
		cout << "n<=m is not allowed" << endl;
		return 0xffffffffffffffff;
	}
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
	double grayLevel[256];            //�Ҷȼ�����
	double sigmaB[256] = { 0 };       //��׼������ �տ�ʼ����0
	int pix_number[256] = { 0 };      //���Ҷȼ����ؼ�����
	double pix_prob[256] = { 0.0 };        //�Ҷȼ����� Ϊͳ������/��������
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

#endif