//用于纯数学计算的函数实现 对应头文件MathCgyt.h
#include "Func_Proj_2nd.h"

#if MathActivate == 1

//第一个写个关于Zernike矩的计算
double JingXiang_R_n_m(unsigned int n, unsigned int m, double rho)
{
	if (n <= m)
	{
		cout << "n<=m is not allowed" << endl;
		return 0xffffffffffffffff;
	}
}

//阶乘 输入参数必须是int
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

//应有一个用于计算OTSU方法的阈值的函数 输入为vector<double> 或vector<unsigned char> 返回double  20210311测试通过 仅用于 unsigned char类型的原始数组
unsigned char OTSU_Value_Calc(const std::vector<unsigned char>& src) {  //注意此版本的适用性 ,最好做一下正确性验证
	//所需变量初始化
	double grayLevel[256];                    //灰度级数组
	double sigmaB[256]     = { 0 };           //标准差数组 刚开始都是0
	int    pix_number[256] = { 0 };           //各灰度级像素计数组
	double pix_prob[256]   = { 0.0f };        //灰度级概率 为统计数组/像素数量
	for (int i = 0; i < 256; i++) { grayLevel[i] = i; }

	//灰度统计
	auto iterSrc_c = src.cbegin(); //常量迭代器 像素值组
	for (; iterSrc_c < src.cend(); iterSrc_c++) {
		pix_number[*iterSrc_c]++;
	}
	//概率计算
	size_t n = src.size();  //像素数量
	for (int i = 0; i < 256; i++) {
		pix_prob[i] = (double)pix_number[i] / (double)n;
	}
	//平均灰度计算
	double Mg = 0;   //平均灰度
	for (int i = 0; i < 256; i++) {
		Mg += pix_prob[i] * grayLevel[i];
	}

	unsigned char OTSU_Value(0);
	//计算类间方差
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
* 看看要不要补充一个局部区域方差和均值计算的工具函数 用于可变阈值 20210915 
* 还是以8UC1作为算法验证的图像吧
* 参数说明：
*  src：  源图像
*  row：  目标像素行坐标（Y）
*  col：  目标像素列坐标（X）
*  ksize：邻域大小（算上中心像素的半长）
*  mean： 均值结果
*  var：  方差结果
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

	unsigned int pix_count = 0;                                  //计数总共参与计算的像素数量

	//左上角坐标
	int row_lt = row - ksize + 1;
	int col_lt = col - ksize + 1;

	//右下角坐标
	int row_rb = row + ksize - 1;
	int col_rb = col + ksize - 1;

	*mean = 0.0f;                                                //均值结果初始化

	//循环求和
	for (int r = row_lt; r <= row_rb; r++) {

		//若行号小于0，则跳过		
		if ((r<0) || (r>src.rows)) {
				continue;
		}
		
		unsigned char* row_head = r * src.step[0] + src.data;   //行头指针计算	
		for (int c = col_lt; c <= col_rb; c++) {
			if ((c<0) || (c>src.cols)) {
				continue;
			}			
			*mean += (double)(*(row_head + c));                 //像素值累加			
			pix_count++;                                        //像素计数+1 在下面的循环中不需要重新计算
		}
	}

	*mean = (*mean) / ((double)pix_count);                      //均值计算

	//循环求方差
	double temp = 0;
	for (int r = row_lt; r <= row_rb; r++) {

		//若行号小于0，则跳过		
		if ((r < 0) || (r > src.rows)) {
			continue;
		}

		unsigned char* row_head = r * src.step[0] + src.data;   //行头指针计算	
		for (int c = col_lt; c <= col_rb; c++) {
			if ((c < 0) || (c > src.cols)) {
				continue;
			}


			temp = pow((double)(*(row_head + c)) - *mean, 2);   //差值平方计算
			*var += temp;
		}
	}
	*var = (*var) / ((double)pix_count);

	return 0;                                                   //成功完成
}

#endif