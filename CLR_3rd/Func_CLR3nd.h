#pragma once
//opencv400基本库
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/photo/photo.hpp>
#include <opencv2/ml.hpp> //机器学习功能模块 SVM DTree ANN

//c++标准文件库
#include <iostream>
#include <vector>
#include <math.h>

//CLI环境下不支持头文件<thread>，需要寻找新的扩散加速方法，不知道CUDA可行不可行，先用 双边滤波或者直接注释掉看看结果一不一样，反正扩散率波我肉眼没看出区别

using namespace cv;
using namespace std;

//要不还是把C++/CLI废掉吧，反正现在功能也没完善，转QT做还来得及
