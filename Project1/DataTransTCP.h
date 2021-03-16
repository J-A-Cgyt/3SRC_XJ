#pragma once
#include <vector>
//数据类型相关 主要是这个point类型的数据该如何传送 最好发过去的时候能避免掉用opencv的库
#include <opencv2/core/core.hpp>
//这个头文件就定义通信函数名称就行了

int ContoursSubpixSend(const std::vector<cv::Point2d>& contoursSubpix, const char* ipAddr);