#pragma once

#if MathActivate == 1

//��һ��дһ����˹�ֲ���������������������ƺ�opencv��RNG::Gaussian�Ϳɣ���Ȼ��˾Ͳ��˷�ʱ���˵�ʱ�����϶������и��෽����Ҫ��ѧ���㣬������д��

//�׳�
double JieCheng(const unsigned int &i);

//�򻯰�OTSU 20210311����ͨ�� ������ unsigned char���͵�ԭʼ����
unsigned char OTSU_Value_Calc(const std::vector<unsigned char>& src);

//�ֲ���ֵ�뷽�����
int localMeanVarCalc(const Mat           &src,
	                 const int            row,
	                 const int            col,
	                 const unsigned int  &ksize,
	                 double              *mean,
	                 double              *var);
#endif

//�������ǰ���Դ�ļ����е�˳������ ���ͷ�ļ������Ժ���calib ����û��ֺ�ֱ�Ӻ��汨�� ע����������