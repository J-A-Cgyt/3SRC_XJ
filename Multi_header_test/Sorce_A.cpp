#include "Header_Main.h"
//����Ҳû�з���ʲô��ֵ��°���Ϊʲô�ڶ�����Ŀ�ﲻ��

int main()
{
	Test_cgyt t = Test_cgyt(2, 3.4);
	int sum = t.add(2,3);
	cout << sum << endl;
	//t.~Test_cgyt();

	string Loading_path = "G:\\Pictures\\Test For Programming\\�㽶3.jpg";
	string WinN = "Demo_Result_2";
	cv::Mat Src;
	Src = cv::imread(Loading_path,cv::IMREAD_GRAYSCALE);
	cv::namedWindow(WinN);
	cv::imshow(WinN,Src);
	cv::waitKey(0);

	Conv_cgyt_2nd k;

	k.Conv_Sel(Src, Conv_cgyt_2nd::GARDIENT1_CGYT_2);
	
	for (int i = 0; i < 3; i++)
	{
		cout << k.Result.at<cv::Vec3f>(34, 65)[i] << endl;
	}

	return 0; //�������˳�ʱ���Զ�������������
}