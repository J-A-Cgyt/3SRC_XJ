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

#endif