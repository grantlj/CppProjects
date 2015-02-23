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

int  EXCI_WIDTH;
int  EXCI_HEIGHT;

#define CLASS_NUM 4
#define PER_HIST_LEN 16
#define HIST_LEN (3*PER_HIST_LEN)

//舍弃指标不好的百分比
#define ABANDON 0.20

//有效的白块行数控制阈值
float MIN_WHITE_PER;


using namespace std;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;

typedef struct imgFile
{
	char* imgAddr;
	char* fileName;
	IplImage* imgSrc;
	IplImage* imgEdge;
	IplImage*** imgPieces;
	IplImage*** imgEdgePieces;



	int rowCount;
	int colCount;
	int** whiteCol;
	float*** hists;

	int * eachClassCount;
	float * eachClassWeight;

	double ** eachCenterHist;

	int edgeMatConut;

	CvMat* dataMat, *markMat;

	double score;


}imgFile;


typedef struct imgSaveFile
{
	char  fileName[100];
	float eachClassWeight[CLASS_NUM];
	double eachCenterHist[CLASS_NUM][HIST_LEN];
	double score;
}imgSaveFile;

typedef struct resAss
{
	char name[100];
	int time;
	double scoreSum;
}resAss;