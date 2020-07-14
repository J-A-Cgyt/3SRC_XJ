#define _WINSOCK_DEPRECATED_NO_WARNINGS //禁用了C4996的错误代码
//TCP程序，传输照片客户端 20200709 中断
#include <iostream>

//#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>  //文件流吧 此处的图像发送尽量避免使用OPENCV以免对象设备无相关环境导致读取出错
#include <sstream>

#pragma comment(lib,"ws2_32.lib")
#include <winsock2.h>