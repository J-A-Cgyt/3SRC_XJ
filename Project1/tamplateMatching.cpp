/**************************************************************************************************
* ����ļ����ڳ���ʵ��ģ��ƥ�� �տ�ʼ����opencv���Դ���������Ч�� Ȼ���ٸ���ԭ��ʵ�ֵײ��㷨
*  20210924
*   ͵����ֱ�������Դ�ļ���д��ԭʼͼ��Ķ�ȡ·��
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
* opencv ģ��ƥ�书�ܳ��Ե������� ��������й��ߺ��������������
* ͼ���ȡ�Ȳ������������ɣ�main������ֻ��һ�����ô��εĽӿ�
*
*
**************************************************************************************************/
int template_matching_test() {

	Mat Src;                                                     //ԭʼͼ��
	Mat target_template;                                         //Ҫƥ���ģ��
	Mat Res;                                                     //ƥ����
	Mat Res_norm;
	Mat Res_8UC1;                                                //������ʾ�Ľ��
	
	Src = imread(loading_path_tm, IMREAD_GRAYSCALE);             //ԭʼ���ݶ�ȡ
	target_template = 
		imread(loading_path_template, IMREAD_GRAYSCALE);         //ģ�����ݶ�ȡ
	

	namedWindow(window_name_tm, WINDOW_NORMAL);  //����������ھ��

	//�����ȡ���
	//imshow(window_name_tm, Src);
	//waitKey(0);
	//imshow(window_name_tm, target_template);
	//waitKey(0);


	//ģ��ͼ���-�˲��ƺ�����ûʲôӰ��
	GaussianBlur(target_template, target_template, Size(11, 11), 1);

	//OPENCV�Լ�ʵ�ֵ�Ҳֻ��һ�д������ ��������Ĳ�ͬ�㷨�Խ����Ӱ�컹��֪��
	//������Ϊ32FC1 ͨ�������ܺ�ԭʼͼ����� Ҫ��ʾ�Ļ����ù�һ���� ͻȻ���� ģ��ƥ���ѱ�Ե��һȦ�۵� ����opencv�ڴ����Ե״����ʱ��Ҳ���Ǻ����氡
	matchTemplate(Src, target_template, Res, TM_CCOEFF);

	//Ϊ����ʾ�����Ĺ�һ��������ת������
	normalize(Res, Res_norm, 0, 255, NORM_MINMAX);
	Res_norm.convertTo(Res_8UC1, CV_8UC1);

	imshow(window_name_tm, Res_8UC1);
	waitKey(0);
	printf("%d", Res.type());

	destroyAllWindows();

	return 0;

}

