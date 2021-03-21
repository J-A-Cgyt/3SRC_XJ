#define _WINSOCK_DEPRECATED_NO_WARNINGS //������C4996�Ĵ������
//TCP���򣬴������������ص㼯 double�������� �ͻ��� ���ļ�δ������
#include <iostream>

//#include <unistd.h>
//#include <string.h>
#include <string>
#include <vector>
#include <fstream>  //�ļ����� �˴���ͼ���;�������ʹ��OPENCV��������豸����ػ������¶�ȡ����
#include <sstream>

#include "dataTrans.h"

#pragma comment(lib,"ws2_32.lib")  //�˴������˾�̬��
#include <winsock2.h>

#include <tuple>

enum TransType {
	CGYT_SUBPIX = 0x0,
	CGYT_CVMAT = 0x1,
	CGYT_PICFILE = 0x2
};

int ContoursSubpixSend(const std::vector<cv::Point2d>& contoursSubpix, const char* ipAddr = "192.168.137.2") {
	//�ȴ���㼯����
	size_t buffer_size = contoursSubpix.size() * 2;
	auto buffer = new double[buffer_size];  //������Ҫת��Ϊchar������ܷ���
	size_t index = 0;
	for (auto iterSrc = contoursSubpix.cbegin(); iterSrc < contoursSubpix.cend(); iterSrc++) {
		buffer[index] = (*iterSrc).x;
		buffer[index + 1] = (*iterSrc).y;
		index += 2;
	}

	//WinsSock ��ʼ��
	WORD wVwesionRequested; //16bit���ͱ��� ��WORD��
	wVwesionRequested = MAKEWORD(2, 2);  //Ҫ��Ŀ��ļ��汾�ţ�MAKEWORD�꽫����8bit����ƴ��15bit���汾2.2
	WSADATA wsaData;

	/*
	�ṹԭ�ͣ�����
	struct WSAData {
����	WORD wVersion;
����	WORD wHighVersion;
����	char szDescription[WSADESCRIPTION_LEN+1];
����	char szSystemStatus[WSASYSSTATUS_LEN+1];
����	unsigned short iMaxSockets;
����	unsigned short iMaxUdpDg;
����	char *lpVendorInfo;};
����WSADATA�ṹ���������溯��WSAStartup���ص�Windows Sockets��ʼ����Ϣ��
	��Ա��
	wVersion:Windows Sockets DLL����������ʹ�õ�Windows Sockets�淶�İ汾�� ��λ�ֽڴ洢���汾��, ��λ�ֽڴ洢���汾�ţ�������WORD MAKEWORD(BYTE,BYTE ) �������ֵ,����:MAKEWORD(1,1)����
	wHighVersion:���DLL�ܹ�֧�ֵ�Windows Sockets�淶����߰汾��ͨ������wVersion��ͬ��
	szDescription:��null��β��ASCII�ַ�����Windows Sockets DLL����Windows Socketsʵ�ֵ���������������ַ����У����������̱�ʶ���ı�����������256���ַ������԰����κ��ַ�������Ҫע�ⲻ�ܰ��������ַ��͸�ʽ�ַ���Ӧ�ó����������ܵ�ʹ�÷�ʽ�ǰ��������ܱ��ضϣ���ʾ����״̬��Ϣ�С�
	szSystemStatus:��null��β��ASCII�ַ�����Windows Sockets DLL���йص�״̬��������Ϣ���������ַ����С�Windows Sockets DLLӦ��������Щ��Ϣ���û���֧����Ա����ʱ��ʹ�����ǣ�����Ӧ����ΪszDescription�����չ��
	iMaxSockets:���������ܹ��򿪵�socket�������Ŀ��Windows Sockets��ʵ�����ṩһ��ȫ�ֵ�socket�أ�����Ϊ�κν��̷��䣻������Ҳ����Ϊsocket�������ڽ��̵���Դ����������ܹ��ܺõط�ӳWindows Sockets DLL��������������÷�ʽ��Ӧ�ó���ı�д�߿���ͨ��������������Ե�ָ��Windows Sockets��ʵ�ַ�ʽ��Ӧ�ó����Ƿ����á����磬X Windows�������ڵ�һ��������ʱ����ܻ���iMaxSockets��ֵ��������ֵС��8��Ӧ�ó�����ʾһ��������Ϣ��ָʾ�û����������������������һ�ֿ���Ҫʹ��szSystemStatus�ı��ĳ��ϣ�����Ȼ�޷���֤ĳ��Ӧ�ó����ܹ���������iMaxSockets��socket����Ϊ����������WindowsSocketsӦ�ó�������ʹ�á�
	iMaxUdpDg Windows Sockets:Ӧ�ó����ܹ����ͻ���յ������û����ݰ�Э�飨UDP�������ݰ���С�����ֽ�Ϊ��λ�����ʵ�ַ�ʽû�����ƣ���ôiMaxUdpDgΪ�㡣��Berkeley sockets�����ʵ���У�����UDP���ݰ��и����е����ƣ��ڱ�Ҫʱ���ֽ⣩����СΪ8192�ֽڡ�Windows Sockets��ʵ�ֿ��Զ���Ƭ���黺�����ķ����������ơ������ʺϵ�WindowsSockets ʵ�֣�iMaxUdpDg����СֵΪ512��ע�ⲻ��iMaxUdpDg��ֵ��ʲô�������Ƽ��㷢��һ�������������͵�Ԫ��MTU������Ĺ㲥���ݰ�����Windows Sockets API û���ṩ����MTU�Ļ��ƣ�����������С��512���ֽ�)��WinSock2.0�����ѱ�������
	lpVendorInfo:ָ�������̵����ݽṹ��ָ�롣����ṹ�Ķ��壨����У�������WindowsSockets�淶�ķ�Χ��WinSock2.0�����ѱ�������
	*/

	int Result;
	Result = WSAStartup(wVwesionRequested, &wsaData);  //���ļ���ָʾ����������socket֮ǰ
	if (Result != 0)
	{
		printf("WSAStartup() faild\n");
		return -1;
	}

	// Socket����
	SOCKET sClient;
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() faild\n");
		return -2;
	}
	//IP��ַ��Э���塢�˿�����
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2000);							   //�˿�
	serverAddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);  //ip��ַ
	//������ַ 192.168.137.1

	//���ӽ���
	Result = connect(sClient, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (Result == SOCKET_ERROR)
	{
		printf("����ʧ��");
		return -3;
	}

	//��������
	size_t charSize = buffer_size * sizeof(double) / sizeof(char);
	char* buffer_char = new char[charSize];
	memcpy(buffer_char, buffer, charSize);
	send(sClient, buffer_char, charSize, 0);

	//�ͷſռ䲢�Ͽ�����
	closesocket(sClient);
	delete[] buffer;
	return 0;

}

int RoIMatSend(const cv::Mat& src, const char* ipAddr = "192.168.137.2") {

	if (src.type() != CV_8UC1) {   //���ͼ��
		throw std::runtime_error("only mat of type CV_8UC1 can be send");
		return -4;
	}

	//WinsSock ��ʼ��
	WORD wVwesionRequested; //16bit���ͱ��� ��WORD��
	wVwesionRequested = MAKEWORD(2, 2);  //Ҫ��Ŀ��ļ��汾�ţ�MAKEWORD�꽫����8bit����ƴ��15bit���汾2.2
	WSADATA wsaData;

	int Result;
	Result = WSAStartup(wVwesionRequested, &wsaData);  //���ļ���ָʾ����������socket֮ǰ
	if (Result != 0)
	{
		printf("WSAStartup() faild\n");
		return -1;
	}

	// Socket����
	SOCKET sClient;
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	if (sClient == INVALID_SOCKET)
	{
		WSACleanup();
		printf("socket() faild\n");
		return -2;
	}
	//IP��ַ��Э���塢�˿�����
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(2000);							   //�˿�
	serverAddr.sin_addr.S_un.S_addr = inet_addr(ipAddr);  //ip��ַ
	//������ַ 192.168.137.1

	//���ӽ���
	Result = connect(sClient, (sockaddr*)&serverAddr, sizeof(serverAddr));
	if (Result == SOCKET_ERROR)
	{
		printf("����ʧ��");
		return -3;
	}

	size_t picStep = src.step[0];  //����ռ���ڴ�Ŀռ� �ֽ�Ϊ��λ
	size_t sizeOf_size_t = sizeof(size_t) / sizeof(char);
	char* sizeBuffer = new char[sizeOf_size_t];
	memcpy(sizeBuffer, &picStep, sizeOf_size_t);
	send(sClient, sizeBuffer, sizeOf_size_t, 0);    //����mat��step����

	size_t picSizeBytes = src.total() * src.elemSize();   //���ֽڴ�С ������Ҫ����һ�˻ָ����� ����Ҫ֪�����д�С
	char* buffer = new char[picSizeBytes];  //������� memcpy���ܾͲ���Ҫ��
	buffer = reinterpret_cast<char*>(src.data);  //���ܻ���Ҫmemcpy�� �˴����½��� ��������������ʵ��Ϣ�ķ���������ʵ� ��ʽ����ת��
	send(sClient, buffer, picSizeBytes, 0);

	//�ͷſռ䲢�Ͽ�����
	closesocket(sClient);
	delete[] buffer;
	return 0;
}