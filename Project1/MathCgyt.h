#pragma once

#ifndef MATH_FUNC
#define MATH_FUNC

#if MathActivate == 1

//第一个写一个高斯分布的随机数生成器，不过似乎opencv的RNG::Gaussian就可，既然如此就不浪费时间了到时后续肯定还会有更多方法需要数学计算，在这里写吧

//阶乘
double JieCheng(const unsigned int &i);

//简化版OTSU 20210311测试通过 仅用于 unsigned char类型的原始数组
unsigned char OTSU_Value_Calc(const std::vector<unsigned char>& src);

//局部均值与方差计算
int localMeanVarCalc(const Mat           &src,
	                 const int            row,
	                 const int            col,
	                 const unsigned int  &ksize,
	                 double              *mean,
	                 double              *var);


/**************************************************************************************************
*  看来还得要一个最小二乘拟合圆的C++版本
*      contour      -I        拟合的亚像素样本点集
*      circle_info  -O        输出的圆信息 x:中心横坐标 y:中心纵坐标 z:半径
*      error        -O        输出的拟合误差
*  返回值：参与拟合的点数量
*  20211210测试通过 对比霍夫变换还是有比较好的结果，不用设置那么多参数
**************************************************************************************************/
int minSqureFitCircle(const std::vector<cv::Point2d>& contour,
	                  cv::Point3d&              circle_info,
	                  double&                   error);




#endif

#endif
//看来就是按照源文件排列的顺序编译的 这个头文件完了以后是calib 这里没打分号直接后面报错 注意这种问题