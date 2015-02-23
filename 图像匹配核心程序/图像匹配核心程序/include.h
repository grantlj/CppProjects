/*
程序：生成匹配核心程序
版本：V2.1
作者：沈涛 重庆邮电大学

include.h
本文件功能在程序中的作用：
1 引入文件
2 宏定义与全局变量的定义
3 各种结构体的定义
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

//分割每一块的宽和高
int  EXCI_WIDTH;
int  EXCI_HEIGHT;

//有效的白块行数控制阈值
float MIN_WHITE_PER;

//聚类个数
#define CLASS_NUM 3
//一个通道的直方图长度与总长度
#define PER_HIST_LEN 16
#define HIST_LEN (3*PER_HIST_LEN)

//舍弃指标不好的百分比
#define ABANDON 0.20

using namespace std;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

//文件结构体，用于存放图片，和操作的对象
typedef struct imgFile
{
	char* imgAddr;//图片的绝对目录
	char* fileName;//文件名
	IplImage* imgSrc;//原图片
	IplImage* imgEdge;//canny算子的边缘图片
	IplImage*** imgPieces;//原图片分块
	IplImage*** imgEdgePieces;//边缘图片分块

	int rowCount;//分块的行数
	int colCount;//分块的列数
	int** whiteCol;//边缘'二值'矩阵
	float*** hists;//所有分块的直方图直方图

	int * eachClassCount;//每个聚类包含的图片数
	float * eachClassWeight;//每个聚类的权重
	double ** eachCenterHist;//每个类的中心直方图

	int edgeMatConut;//在去边缘后剩下的块数

	//用于聚类的两个矩阵
	CvMat* dataMat;
	CvMat *markMat;

}imgFile;

//用于读取数据集中文件特征信息的结构体
typedef struct imgSaveFile
{
	char  fileName[100];//文件名
	float eachClassWeight[CLASS_NUM];//每个聚类的权重
	double eachCenterHist[CLASS_NUM][HIST_LEN];//每个类的中心直方图
	double score;//分数
}imgSaveFile;

//从数据集中读取文件名信息
typedef struct resAss
{
	char name[100];//文件名
	int time;//出现次数
	double scoreSum;//总分数
}resAss;