#include "Header_Main.h"
//����Ҳû�з���ʲô��ֵ��°���Ϊʲô�ڶ�����Ŀ�ﲻ��

#include <immintrin.h>  //�ƺ��Ƕ�����128 256bit�������͵�ͷ�ļ���
#include <ctime>

clock_t start, endt, diff;

int main()
{
/*
	Test_cgyt t = Test_cgyt(2, 3.4);
	int sum = t.add(2,3);
	cout << sum << endl;
	//t.~Test_cgyt();

	string Loading_path = "G:\\Pictures\\Test For Programming\\�㽶3.jpg";
	string WinN = "Demo_Result_2";
	cv::Mat Src;
	Src = cv::imread(Loading_path,cv::IMREAD_GRAYSCALE);
	cv::namedWindow(WinN);
	cv::imshow(WinN,Src);
	cv::waitKey(0);

	Conv_cgyt_2nd k;

	k.Conv_Sel(Src, Conv_cgyt_2nd::GARDIENT1_CGYT_2);
	
	for (int i = 0; i < 3; i++)
	{
		cout << k.Result.at<cv::Vec3f>(34, 65)[i] << endl;
	}

	vector<vector<double>> M1;
	M1.max_size = 4;
	M1[0].max_size = 4;
	M1[1].max_size = 4;
	M1[2].max_size = 4;
	M1[3].max_size = 4;

	M1[0][0] = 2;   M1[0][1] = 45;   M1[0][2] = 22;    M1[0][3] = 2.1;
	M1[1][0] = 211; M1[1][1] = 45;   M1[1][2] = 5.2;   M1[1][3] = 1.2;
	M1[2][0] = 10;  M1[2][1] = 4.3;  M1[2][2] = 72.54; M1[2][3] = 4.2;
	M1[3][0] = 3;   M1[3][1] = 46.6; M1[3][2] = 2.92;  M1[3][3] = 9.2;

*/

	__m256 Data1, Data2,res;  //AVX������ float*8 Ĭ�� i�������������������͵ĳ���  d��double*4
	
	for (int i = 0; i < 8; i++)
	{
		Data1.m256_f32[i] = (float)i;
		Data2.m256_f32[i] = (float)(8-i);
	}
	start = clock();
	res = _mm256_add_ps(Data1, Data2); 
	//�ӷ������Կ���ָ��ִ�еĴ��� ����Щ������˵�ӻ���������Ҳ�����ǿ��˶��ҿ첻�� ��ʱ������û�и����SIMD�������ð�
	endt = clock();
	diff = endt - start;

	start = clock();
	for (int i = 0; i < 8; i++)
	{
		res.m256_f32[i] = Data1.m256_f32[i] + Data2.m256_f32[i];
	}
	endt = clock();
	diff = endt - start;
	return 0; //�������˳�ʱ���Զ�������������
}

//���Կ�AVX