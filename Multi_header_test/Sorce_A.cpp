#include "Header_Main.h"
//好像也没有发生什么奇怪的事啊？为什么第二个项目里不行

#include <immintrin.h>  //似乎是定义了128 256bit数据类型的头文件？
#include <ctime>

clock_t start, endt, diff;

int main()
{
/*
	Test_cgyt t = Test_cgyt(2, 3.4);
	int sum = t.add(2,3);
	cout << sum << endl;
	//t.~Test_cgyt();

	string Loading_path = "G:\\Pictures\\Test For Programming\\香蕉3.jpg";
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

	__m256 Data1, Data2,res;  //AVX的数据 float*8 默认 i是整数数量看基本类型的长度  d是double*4
	
	for (int i = 0; i < 8; i++)
	{
		Data1.m256_f32[i] = (float)i;
		Data2.m256_f32[i] = (float)(8-i);
	}
	start = clock();
	res = _mm256_add_ps(Data1, Data2); 
	//从反汇编可以看见指令执行的次数 就这些操作来说从汇编层面来讲也绝对是快了而且快不少 到时看看有没有更多的SIMD函数可用叭
	endt = clock();
	diff = endt - start;

	start = clock();
	for (int i = 0; i < 8; i++)
	{
		res.m256_f32[i] = Data1.m256_f32[i] + Data2.m256_f32[i];
	}
	endt = clock();
	diff = endt - start;
	return 0; //主函数退出时会自动调用析构函数
}

//试试看AVX