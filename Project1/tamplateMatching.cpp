/**************************************************************************************************
* 这个文件用于尝试实现模板匹配 刚开始先用opencv的自带函数看看效果 然后再根据原理实现底层算法
*  20210924
*   偷个懒直接在这个源文件里写死原始图像的读取路径
*
*
*
*
*
**************************************************************************************************/

#include "Func_Proj_2nd.h"

string loading_path_tm("F:\\Pictures\\Test For Programming\\DSC_3067.JPG");
string loading_path_template("F:\\Pictures\\Test For Programming\\template.jpg");
string window_name_tm("Demo Result");

/**************************************************************************************************
* opencv 模板匹配功能尝试的主函数 后续如果有工具函数则在其外添加
* 图像读取等操作都在这边完成，main函数内只调一个不用传参的接口
*
*
**************************************************************************************************/
int template_matching_test() {

	Mat Src;                                                     //原始图像
	Mat target_template;                                         //要匹配的模板
	Mat Res;                                                     //匹配结果
	Mat Res_norm;
	Mat Res_8UC1;                                                //用于显示的结果
	
	Src = imread(loading_path_tm, IMREAD_GRAYSCALE);             //原始数据读取
	target_template = 
		imread(loading_path_template, IMREAD_GRAYSCALE);         //模板数据读取
	

	namedWindow(window_name_tm, WINDOW_NORMAL);  //创建结果窗口句柄

	//结果读取检测
	//imshow(window_name_tm, Src);
	//waitKey(0);
	//imshow(window_name_tm, target_template);
	//waitKey(0);


	//模板图像抠-滤波似乎好像没什么影响
	GaussianBlur(target_template, target_template, Size(11, 11), 1);

	//OPENCV自己实现的也只是一行代码而已 但是里面的不同算法对结果的影响还不知道
	//输出结果为32FC1 通道数可能和原始图像相关 要显示的话还得归一化先 突然发现 模板匹配会把边缘的一圈扣掉 看来opencv在处理边缘状况的时候也不是很认真啊
	matchTemplate(Src, target_template, Res, TM_CCOEFF);

	//为了显示而做的归一化和类型转换处理
	normalize(Res, Res_norm, 0, 255, NORM_MINMAX);
	Res_norm.convertTo(Res_8UC1, CV_8UC1);

	imshow(window_name_tm, Res_8UC1);
	waitKey(0);
	printf("%d", Res.type());

	destroyAllWindows();

	return 0;

}

