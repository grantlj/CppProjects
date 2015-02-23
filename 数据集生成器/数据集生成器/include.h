/*
�����������ݼ�
�汾��V2.1
���ߣ����� �����ʵ��ѧ

include.h
���ļ������ڳ����е����ã�
1 �����ļ�
2 �궨����ȫ�ֱ����Ķ���
3 ���ֽṹ��Ķ���
*/


#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <io.h>
#include <direct.h>
#include <string>
#include <vector>
#include <bitset>
#include <iomanip>
#include <ctime>
#include <string.h>
#include <time.h>
#include <opencv.hpp> //opencv 2
#include<cxcore.h>

//�ָ�ÿһ��Ŀ�͸�
#define EXCI_WIDTH 32
#define EXCI_HEIGHT 32
//�������
#define CLASS_NUM 3
//һ��ͨ����ֱ��ͼ�������ܳ���
#define PER_HIST_LEN 16
#define HIST_LEN (3*PER_HIST_LEN)
//��Ч�İ׿�����������ֵ
#define MIN_WHITE_PER 0.6


using namespace std;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

//�ļ��ṹ�壬���ڴ��ͼƬ���Ͳ����Ķ���
typedef struct imgFile
{
	char* imgAddr;//ͼƬ�ľ���Ŀ¼
	char* fileName;//�ļ���
	IplImage* imgSrc;//ԭͼƬ
	IplImage* imgEdge;//canny���ӵı�ԵͼƬ
	IplImage*** imgPieces;//ԭͼƬ�ֿ�
	IplImage*** imgEdgePieces;//��ԵͼƬ�ֿ�

	int rowCount;//�ֿ������
	int colCount;//�ֿ������
	int** whiteCol;//��Ե'��ֵ'����
	float*** hists;//���зֿ��ֱ��ͼֱ��ͼ

	int * eachClassCount;//ÿ�����������ͼƬ��
	float * eachClassWeight;//ÿ�������Ȩ��
	double ** eachCenterHist;//ÿ���������ֱ��ͼ

	int edgeMatConut;//��ȥ��Ե��ʣ�µĿ���

	//���ھ������������
	CvMat* dataMat;
	CvMat *markMat;

}imgFile;

//���ڱ���ÿ��ͼƬ������Ϣ�Ľṹ��
typedef struct imgSaveFile
{
	char  fileName[100];//�ļ���
	float eachClassWeight[CLASS_NUM];//ÿ�������Ȩ��
	double eachCenterHist[CLASS_NUM][HIST_LEN];//ÿ���������ֱ��ͼ
	double score;//����
}imgSaveFile;



//���ڱ����ļ�����Ϣ,����ƥ�����ͳ��һ��ͼƬ�ķ���
typedef struct saveFileType
{
	char name[100];//�ļ���
	int time;//���ִ���
	double scoreSum;//�ܷ���
}saveFileType;