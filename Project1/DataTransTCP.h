#pragma once
#include <vector>
//����������� ��Ҫ�����point���͵����ݸ���δ��� ��÷���ȥ��ʱ���ܱ������opencv�Ŀ�
#include <opencv2/core/core.hpp>
//���ͷ�ļ��Ͷ���ͨ�ź������ƾ�����

int ContoursSubpixSend(const std::vector<cv::Point2d>& contoursSubpix, const char* ipAddr);