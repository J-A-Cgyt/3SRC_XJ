// ImgTransTCP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
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

std::string LoadPath_Msi_12 = "F:\\Pictures\\Test For Programming\\Mat.type.png";  //用于测试的路径字符串

std::string read_image(const std::string& image_path);

int send_image(SOCKET s, int &fd, std::string &image); //发送函数，不一定用 发是发过去了，可是不清楚能不能还原回数据

int main()
{

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
wVersion
　　Windows Sockets DLL期望调用者使用的Windows Sockets规范的版本。 高位字节存储副版本号, 低位字节存储主版本号，可以用WORD MAKEWORD(BYTE,BYTE ) 返回这个值,例如:MAKEWORD(1,1)　　
wHighVersion
　　这个DLL能够支持的Windows Sockets规范的最高版本。通常它与wVersion相同。
szDescription
　　以null结尾的ASCII字符串，Windows Sockets DLL将对Windows Sockets实现的描述拷贝到这个字符串中，包括制造商标识。文本（最多可以有256个字符）可以包含任何字符，但是要注意不能包含控制字符和格式字符，应用程序对其最可能的使用方式是把它（可能被截断）显示在在状态信息中。
szSystemStatus
　　以null结尾的ASCII字符串，Windows Sockets DLL把有关的状态或配置信息拷贝到该字符串中。Windows Sockets DLL应当仅在这些信息对用户或支持人员有用时才使用它们，它不应被作为szDescription域的扩展。
iMaxSockets
　　单个进程能够打开的socket的最大数目。Windows Sockets的实现能提供一个全局的socket池，可以为任何进程分配；或者它也可以为socket分配属于进程的资源。这个数字能够很好地反映Windows Sockets DLL或网络软件的配置方式。应用程序的编写者可以通过这个数字来粗略地指明Windows Sockets的实现方式对应用程序是否有用。例如，X Windows服务器在第一次启动的时候可能会检查iMaxSockets的值：如果这个值小于8，应用程序将显示一条错误信息，指示用户重新配置网络软件（这是一种可能要使用szSystemStatus文本的场合）。显然无法保证某个应用程序能够真正分配iMaxSockets个socket，因为可能有其它WindowsSockets应用程序正在使用。
iMaxUdpDg Windows Sockets
	应用程序能够发送或接收的最大的用户数据包协议（UDP）的数据包大小，以字节为单位。如果实现方式没有限制，那么iMaxUdpDg为零。在Berkeley sockets的许多实现中，对于UDP数据包有个固有的限制（在必要时被分解），大小为8192字节。Windows Sockets的实现可以对碎片重组缓冲区的分配作出限制。对于适合的WindowsSockets 实现，iMaxUdpDg的最小值为512。注意不管iMaxUdpDg的值是什么，都不推荐你发回一个比网络的最大传送单元（MTU）还大的广播数据包。（Windows Sockets API 没有提供发现MTU的机制，但是它不会小于512个字节)。WinSock2.0版中已被废弃。
lpVendorInfo
	指向销售商的数据结构的指针。这个结构的定义（如果有）超出了WindowsSockets规范的范围。WinSock2.0版中已被废弃。
	*/

	int Result;
	Result = WSAStartup(wVwesionRequested, &wsaData);  //库文件绑定指示函数，启动socket之前
	if (Result != 0)
	{
		printf("WSAStartup() faild\n");
		return -4;
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
	serverAddr.sin_port = htons(2000);
	serverAddr.sin_addr.S_un.S_addr = inet_addr("192.168.137.2");
	//本机地址 192.168.137.1

//连接建立
	Result = connect(sClient, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (Result == SOCKET_ERROR)
	{
		printf("连接失败");
		return - 3;
	}

//图片读取main函数配合代码
	std::string ImgFile; //读取函数看起来是能用的 20200714读入通过，按理说都进来的应该也就是个对的东西
	const std::string &path = LoadPath_Msi_12; //引用
	ImgFile = read_image(path);
	int tempx = 0;
//通过socket发送
	send_image(sClient, tempx, ImgFile);
	
	return 0;
}

//图片文件读取 
std::string read_image(const std::string& image_path) 
{
	//图片文件打开
	std::ifstream is(image_path.c_str(), std::ifstream::in);
	//图片长度计算
	is.seekg(0, is.end);
	int flength = is.tellg(); //长度值
	is.seekg(0, is.beg);
	//创建内存缓冲区
	char * buffer = new char[flength];
	//读取
	is.read(buffer, flength);
	
	std::string image(buffer, flength);
	return image; //返回一整个字符串
}

//此函数不一定使用
int send_image(SOCKET s,int &fd, std::string &image) //此处的&似乎构造了引用？
{
	//创建响应
	int body_length = image.size();
	const char* body = image.data();
	int response_length = body_length;
	char* buffer = new char[response_length];
	memcpy(buffer, body, body_length);
	
	//将响应写入缓冲区并发送 似乎是lnux的命令，看看MSVC 有什么对应的函数
	int ret = 0; //= std::write(fd, buffer, response_length);
	send(s,buffer,body_length,0);

	delete[] buffer;
	return ret;
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件