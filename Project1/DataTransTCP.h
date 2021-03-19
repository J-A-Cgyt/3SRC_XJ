#pragma once
#include <vector>
//数据类型相关 主要是这个point类型的数据该如何传送 最好发过去的时候能避免掉用opencv的库
#include <opencv2/core/core.hpp>
//这个头文件就定义通信函数名称就行了

int ContoursSubpixSend(const std::vector<cv::Point2d>& contoursSubpix, const char* ipAddr);

int RoIMatSend(const cv::Mat& src, const char* ipAddr);   //感兴趣区域以Mat的形式发送,单次传送预计数据量<1MByte 如果压缩以稳健的形式发送，可能数据量更小