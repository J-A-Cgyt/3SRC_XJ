//用于纯数学计算的函数实现 对应头文件MathCgyt.h
#include "Func_Proj_2nd.h"
#include "MathCgyt.h"

#if MathActivate == 1

//第一个写个关于Zernike矩的计算 MATLAB已实现 无需再C++中计算
double JingXiang_R_n_m(unsigned int n, unsigned int m, double rho)
{
	if (n <= m)
	{
		cout << "n<=m is not allowed" << endl;
		return 0xffffffff;
	}
	return 0;
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


/**************************************************************************************************
*  看来还得要一个最小二乘拟合圆的C++版本
*      contour      -I        拟合的亚像素样本点集
*      circle_info  -O        输出的圆信息 x:中心横坐标 y:中心纵坐标 z:半径
*      error        -O        输出的拟合误差
*  返回值：参与拟合的点数量
*  20211210测试通过 对比霍夫变换还是有比较好的结果，不用设置那么多参数
**************************************************************************************************/
int minSqureFitCircle(const std::vector<cv::Point2d>& contour,
      	              cv::Point3d&                    circle_info,
	                  double&                         error) {

	circle_info.x = 0.0f;         //圆心x
	circle_info.y = 0.0f;         //圆心y
	circle_info.z = 0.0f;         //半径

	//中间变量1(求和操作) 以下标识符均省略sigma求和符号
	double x   = 0.0f;                  // Σ(x)
	double y   = 0.0f;                  // Σ(y)
	double x2  = 0.0f;                  // Σ(x*x)
	double xy  = 0.0f;                  // Σ(x*y)
	double y2  = 0.0f;                  // Σ(y*y)
	double x3  = 0.0f;                  // Σ(x*x*x)
	double x2y = 0.0f;                  // Σ(x*x*y)
	double xy2 = 0.0f;                  // Σ(x*y*y)
	double y3  = 0.0f;                  // Σ(y*y*y)

	size_t n = contour.size();          //样本点数量

	double C = 0.0f, D = 0.0f, E = 0.0f, G = 0.0f, H = 0.0f;
	double a = 0.0f, b = 0.0f, c = 0.0f;

	//计算上述循环
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
*  要不要再整一个RANSAC拟合圆的？
*      contour      -I        拟合的亚像素样本点集
*      circle_info  -O        输出的圆信息 x:中心横坐标 y:中心纵坐标 z:半径
*      error        -O        输出的拟合误差
*  返回值：参与拟合的点数量
*
**************************************************************************************************/
int ransacFitCircle(const std::vector<cv::Point2d>& contour,
	                cv::Point3d&                    circle_info,
	                double&                         error) 
{
	circle_info.x = 0.0f;         //圆心x
	circle_info.y = 0.0f;         //圆心y
	circle_info.z = 0.0f;         //半径



	return 0;
}


#endif