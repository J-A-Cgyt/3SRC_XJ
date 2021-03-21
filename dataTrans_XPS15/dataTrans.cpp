#define _WINSOCK_DEPRECATED_NO_WARNINGS //禁用了C4996的错误代码
//TCP程序，传输轮廓亚像素点集 double类型数据 客户端 此文件未经测试
#include <iostream>

//#include <unistd.h>
//#include <string.h>
#include <string>
#include <vector>
#include <fstream>  //文件流吧 此处的图像发送尽量避免使用OPENCV以免对象设备无相关环境导致读取出错
#include <sstream>

#include "dataTrans.h"

#pragma comment(lib,"ws2_32.lib")  //此处加载了静态库
#include <winsock2.h>

#include <tuple>

enum TransType {
	CGYT_SUBPIX = 0x0,
	CGYT_CVMAT = 0x1,
	CGYT_PICFILE = 0x2
};

int ContoursSubpixSend(const std::vector<cv::Point2d>& contoursSubpix, const char* ipAddr = "192.168.137.2") {
	//先处理点集的事
	size_t buffer_size = contoursSubpix.size() * 2;
	auto buffer = new double[buffer_size];  //数据需要转换为char数组才能发送
	size_t index = 0;
	for (auto iterSrc = contoursSubpix.cbegin(); iterSrc < contoursSubpix.cend(); iterSrc++) {
		buffer[index] = (*iterSrc).x;
		buffer[index + 1] = (*iterSrc).y;
		index += 2;
	}

	//WinsSock 初始化
	WORD wVwesionRequested; //16bit字型变量 （WORD）
	wVwesionRequested = MAKEWORD(2, 2);  //要求的库文件版本号，MAKEWORD宏将两个8bit上下拼成15bit，版本2.2
	WSADATA wsaData;

	/*
	结构原型：　　
	struct WSAData {
　　	WORD wVersion;
　　	WORD wHighVersion;
　　	char szDescription[WSADESCRIPTION_LEN+1];
　　	char szSystemStatus[WSASYSSTATUS_LEN+1];
　　	unsigned short iMaxSockets;
　　	unsigned short iMaxUdpDg;
　　	char *lpVendorInfo;};
　　WSADATA结构被用来保存函数WSAStartup返回的Windows Sockets初始化信息。
	成员：
	wVersion:Windows Sockets DLL期望调用者使用的Windows Sockets规范的版本。 高位字节存储副版本号, 低位字节存储主版本号，可以用WORD MAKEWORD(BYTE,BYTE ) 返回这个值,例如:MAKEWORD(1,1)　　
	wHighVersion:这个DLL能够支持的Windows Sockets规范的最高版本。通常它与wVersion相同。
	szDescription:以null结尾的ASCII字符串，Windows Sockets DLL将对Windows Sockets实现的描述拷贝到这个字符串中，包括制造商标识。文本（最多可以有256个字符）可以包含任何字符，但是要注意不能包含控制字符和格式字符，应用程序对其最可能的使用方式是把它（可能被截断）显示在在状态信息中。
	szSystemStatus:以null结尾的ASCII字符串，Windows Sockets DLL把有关的状态或配置信息拷贝到该字符串中。Windows Sockets DLL应当仅在这些信息对用户或支持人员有用时才使用它们，它不应被作为szDescription域的扩展。
	iMaxSockets:单个进程能够打开的socket的最大数目。Windows Sockets的实现能提供一个全局的socket池，可以为任何进程分配；或者它也可以为socket分配属于进程的资源。这个数字能够很好地反映Windows Sockets DLL或网络软件的配置方式。应用程序的编写者可以通过这个数字来粗略地指明Windows Sockets的实现方式对应用程序是否有用。例如，X Windows服务器在第一次启动的时候可能会检查iMaxSockets的值：如果这个值小于8，应用程序将显示一条错误信息，指示用户重新配置网络软件（这是一种可能要使用szSystemStatus文本的场合）。显然无法保证某个应用程序能够真正分配iMaxSockets个socket，因为可能有其它WindowsSockets应用程序正在使用。
	iMaxUdpDg Windows Sockets:应用程序能够发送或接收的最大的用户数据包协议（UDP）的数据包大小，以字节为单位。如果实现方式没有限制，那么iMaxUdpDg为零。在Berkeley sockets的许多实现中，对于UDP数据包有个固有的限制（在必要时被分解），大小为8192字节。Windows Sockets的实现可以对碎片重组缓冲区的分配作出限制。对于适合的WindowsSockets 实现，iMaxUdpDg的最小值为512。注意不管iMaxUdpDg的值是什么，都不推荐你发回一个比网络的最大传送单元（MTU）还大的广播数据包。（Windows Sockets API 没有提供发现MTU的机制，但是它不会小于512个字节)。WinSock2.0版中已被废弃。
	lpVendorInfo:指向销售商的数据结构的指针。这个结构的定义（如果有）超出了WindowsSockets规范的范围。WinSock2.0版中已被废弃。
	*/

	int Result;
	Result = WSAStartup(wVwesionRequested, &wsaData);  //库文件绑定指示函数，启动socket之前
	if (Result != 0)
	{
		printf("WSAStartup() faild\n");
		return -1;
	}

	// Socket创建
	SOCKET sClient;
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() faild\n");
		return -2;
	}
	//IP地址、协议族、端口设置
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2000);							   //端口
	serverAddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);  //ip地址
	//本机地址 192.168.137.1

	//连接建立
	Result = connect(sClient, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (Result == SOCKET_ERROR)
	{
		printf("连接失败");
		return -3;
	}

	//发送数据
	size_t charSize = buffer_size * sizeof(double) / sizeof(char);
	char* buffer_char = new char[charSize];
	memcpy(buffer_char, buffer, charSize);
	send(sClient, buffer_char, charSize, 0);

	//释放空间并断开连接
	closesocket(sClient);
	delete[] buffer;
	return 0;

}

int RoIMatSend(const cv::Mat& src, const char* ipAddr = "192.168.137.2") {

	if (src.type() != CV_8UC1) {   //类型检查
		throw std::runtime_error("only mat of type CV_8UC1 can be send");
		return -4;
	}

	//WinsSock 初始化
	WORD wVwesionRequested; //16bit字型变量 （WORD）
	wVwesionRequested = MAKEWORD(2, 2);  //要求的库文件版本号，MAKEWORD宏将两个8bit上下拼成15bit，版本2.2
	WSADATA wsaData;

	int Result;
	Result = WSAStartup(wVwesionRequested, &wsaData);  //库文件绑定指示函数，启动socket之前
	if (Result != 0)
	{
		printf("WSAStartup() faild\n");
		return -1;
	}

	// Socket创建
	SOCKET sClient;
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() faild\n");
		return -2;
	}
	//IP地址、协议族、端口设置
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2000);							   //端口
	serverAddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);  //ip地址
	//本机地址 192.168.137.1

	//连接建立
	Result = connect(sClient, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (Result == SOCKET_ERROR)
	{
		printf("连接失败");
		return -3;
	}

	size_t picStep = src.step[0];  //单行占据内存的空间 字节为单位
	size_t sizeOf_size_t = sizeof(size_t) / sizeof(char);
	char* sizeBuffer = new char[sizeOf_size_t];
	memcpy(sizeBuffer, &picStep, sizeOf_size_t);
	send(sClient, sizeBuffer, sizeOf_size_t, 0);    //传输mat的step属性

	size_t picSizeBytes = src.total() * src.elemSize();   //总字节大小 但是若要在另一端恢复数据 还需要知道单行大小
	char* buffer = new char[picSizeBytes];  //如此以来 memcpy可能就不需要了
	buffer = reinterpret_cast<char*>(src.data);  //可能还是要memcpy？ 此处重新解释 用于无视数据真实信息的发送是最合适的 显式类型转换
	send(sClient, buffer, picSizeBytes, 0);

	//释放空间并断开连接
	closesocket(sClient);
	delete[] buffer;
	return 0;
}