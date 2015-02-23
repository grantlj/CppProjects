#include "include.h"


void sleep(long wait)
{
	long goal = clock() + wait;
	while (goal>clock());
}


//初始化
void init(imgFile* img)
{

	img->imgSrc = NULL;

	while (1)
	{
		img->imgSrc = cvLoadImage(img->imgAddr);
		if (img->imgSrc != NULL)break;
		sleep(500);
		cout << "waiting for:" << img->imgAddr << endl;
	}

	img->imgEdge = cvCreateImage(cvGetSize(img->imgSrc), IPL_DEPTH_8U, 1);
	cvCanny(img->imgSrc, img->imgEdge, 50, 150, 3);




	img->rowCount = (img->imgSrc->height / EXCI_HEIGHT) * 2 - 1;
	img->colCount = (img->imgSrc->width / EXCI_WIDTH) * 2 - 1;




	img->imgPieces = new IplImage**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->imgPieces[i] = new IplImage*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->imgPieces[i][j] = new IplImage[1];
		}
	}

	img->imgEdgePieces = new IplImage**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->imgEdgePieces[i] = new IplImage*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->imgEdgePieces[i][j] = new IplImage[1];
		}
	}

	img->hists = new float**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->hists[i] = new float*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->hists[i][j] = new float[HIST_LEN];
		}
	}


	img->whiteCol = new int*[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->whiteCol[i] = new int[img->colCount];
	}

	img->edgeMatConut = 0;


	img->eachClassWeight = (float *)malloc(sizeof(float)*CLASS_NUM);
	img->eachClassCount = (int *)malloc(sizeof(int)*CLASS_NUM);
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->eachClassCount[i] = 0;
	}

	img->eachCenterHist = (double **)malloc(sizeof(double *)*CLASS_NUM);
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->eachCenterHist[i] = (double *)malloc(sizeof(double)*HIST_LEN);
		for (int j = 0; j < HIST_LEN; j++)
			img->eachCenterHist[i][j] = 0;
	}

	img->score = 0;

}

//将图片转化成向量
void transToHist(IplImage * src, float* vec)
{
	IplImage* r_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* g_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* b_plane = cvCreateImage(cvGetSize(src), 8, 1);
	//IplImage* planes[] = {h_plane,s_plane};   
	//!!!!!!!!!!!!!!---------!!!!!!!!!!! 选择是不是RGB
	IplImage* hsv = cvCreateImage(cvGetSize(src), 8, 3);
	cvCvtColor(src, hsv, CV_BGR2HSV);
	cvCvtPixToPlane(hsv, b_plane, g_plane, r_plane, 0);//openCV里面的一个函数,可以看作cvSplit是他的宏:#define cvCvtPixToPlane cvSplit    
	//注意顺序为BGR,OpenCV中不管是Windows中Load的还是摄像头取得的都是BGR顺序排列的   

	//计算直方图     
	int hist_size = PER_HIST_LEN;//个数
	int hist_height = 100;
	float range[] = { 0, 255 };
	float* ranges[] = { range };
	CvHistogram* r_hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);
	CvHistogram* g_hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);
	CvHistogram* b_hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

	cvCalcHist(&r_plane, r_hist, 0, 0);
	cvNormalizeHist(r_hist, 1.0);
	cvCalcHist(&g_plane, g_hist, 0, 0);
	cvNormalizeHist(g_hist, 1.0);
	cvCalcHist(&b_plane, b_hist, 0, 0);
	cvNormalizeHist(b_hist, 1.0);


	int k = 0;

	for (int i = 0; i<hist_size; i++)
	{
		float bin_val = cvQueryHistValue_1D(r_hist, i);
		vec[k++] = bin_val;
	}
	for (int i = 0; i<hist_size; i++)
	{
		float bin_val = cvQueryHistValue_1D(g_hist, i);
		vec[k++] = bin_val;
	}
	for (int i = 0; i<hist_size; i++)
	{
		float bin_val = cvQueryHistValue_1D(b_hist, i);
		vec[k++] = bin_val;
	}

	cvReleaseImage(&r_plane);
	cvReleaseImage(&r_plane);
	cvReleaseImage(&b_plane);
	cvReleaseImage(&hsv);
}


//统计小白点：）
int getWhiteCount(IplImage* pCannyImg)
{
	long int s = 0;
	for (int i = 0; i < pCannyImg->height; i++)
	for (int j = 0; j < pCannyImg->width; j++)
	{
		CvScalar t1 = cvGet2D(pCannyImg, i, j);
		if (t1.val[0] != 0)
		{
			s++;
			break;
		}
	}
	return s;
}


//统计边沿矩阵有效的点数
void edgeMatConut(imgFile * img)
{

	for (int i = 0; i < img->rowCount; i++)
	{
		for (int j = 0; j < img->colCount; j++)
		{
			if (img->whiteCol[i][j] <= 2)
				img->edgeMatConut++;
		}
	}
}

//核心函数
void doCore(imgFile* img)
{

	CvRect rect = cvRect(0, 0, EXCI_WIDTH, EXCI_HEIGHT);
	for (int i = 0; i < img->rowCount; i++)
	{
		for (int j = 0; j < img->colCount; j++)
		{
			img->imgPieces[i][j] = cvCreateImage(cvSize(EXCI_WIDTH, EXCI_HEIGHT), img->imgSrc->depth, img->imgSrc->nChannels);
			img->imgEdgePieces[i][j] = cvCreateImage(cvSize(EXCI_WIDTH, EXCI_HEIGHT), img->imgEdge->depth, img->imgEdge->nChannels);

			rect.x = j*(EXCI_WIDTH / 2);
			rect.y = i*(EXCI_HEIGHT / 2);

			cvSetImageROI(img->imgSrc, rect);
			cvSetImageROI(img->imgEdge, rect);

			cvCopyImage(img->imgSrc, img->imgPieces[i][j]);
			cvCopyImage(img->imgEdge, img->imgEdgePieces[i][j]);

			transToHist(img->imgPieces[i][j], img->hists[i][j]);
			if (getWhiteCount(img->imgEdgePieces[i][j])>EXCI_HEIGHT*MIN_WHITE_PER)
			{
				img->whiteCol[i][j] = 0;
			}
			else img->whiteCol[i][j] = 1;

			cvResetImageROI(img->imgSrc);
			cvResetImageROI(img->imgEdge);
		}

	}

}




void handleEdge(imgFile * img)
{
	//左-》右
	for (int i = 0; i < img->rowCount; i++)
	{
		for (int j = 0; j < img->colCount; j++)
		{
			if (img->whiteCol[i][j] == 0)break;
			else img->whiteCol[i][j]++;
		}
	}

	//右-》左
	for (int i = 0; i < img->rowCount; i++)
	{
		for (int j = img->colCount - 1; j >= 0; j--)
		{
			if (img->whiteCol[i][j] == 0)break;
			else img->whiteCol[i][j]++;
		}
	}

	//上-》下
	for (int i = 0; i < img->colCount; i++)
	{
		for (int j = 0; j < img->rowCount; j++)
		{
			if (img->whiteCol[j][i] == 0)break;
			else img->whiteCol[j][i]++;
		}
	}

	//下-》上
	for (int i = 0; i < img->colCount; i++)
	{
		for (int j = img->rowCount - 1; j >= 0; j--)
		{
			if (img->whiteCol[j][i] == 0)break;
			else img->whiteCol[j][i]++;
		}
	}

	edgeMatConut(img);
}

void cluster(struct imgFile * img)
{
	//将imgfile中的向量送入dataMat
	img->dataMat = cvCreateMat(img->edgeMatConut, HIST_LEN, CV_32FC1);
	img->markMat = cvCreateMat(img->edgeMatConut, 1, CV_32SC1);


	//将向量信息写入datamat，如果在边缘中已经删去，直接为负值
	for (int i = 0, l = 0; i < img->rowCount; i++)
	{
		for (int j = 0; j < img->colCount; j++)
		{

			if (img->whiteCol[i][j] <= 2)
			{
				for (int k = 0; k < HIST_LEN; k++)
				{
					cvmSet(img->dataMat, l, k, img->hists[i][j][k]);
				}
				l++;
			}
		}
	}

	cvKMeans2(img->dataMat, CLASS_NUM, img->markMat, cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 1000000000, 0.000000001));

}


//计算每个类的中心hist，计算每个类的百分比（Weight）
void handleClustered(imgFile * img)
{
	//计算所有平方和
	for (int i = 0; i < img->edgeMatConut; i++)
	{
		int cluster_idx = img->markMat->data.i[i];
		img->eachClassCount[cluster_idx]++;
		for (int j = 0; j < HIST_LEN; j++)
		{
			img->eachCenterHist[cluster_idx][j] += pow(cvmGet(img->dataMat, i, j), 2);
		}
	}


	//求每个类的权重
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->eachClassWeight[i] = img->eachClassCount[i] / (float)img->edgeMatConut;
	}
	//取平均值
	for (int i = 0; i < CLASS_NUM; i++)
	{
		for (int j = 0; j < HIST_LEN; j++)
		{
			img->eachCenterHist[i][j] = sqrt(img->eachCenterHist[i][j] / img->eachClassCount[i]);
		}
	}
}


double distance(double * hist1, double * hist2)
{
	double s = 0;
	for (int i = 0; i < HIST_LEN; i++)
		s += pow(hist1[i] - hist2[i], 2);
	return sqrt(s);
}

//第一种打分的方法
//求出一个向量和一个向量组最小的距离
double minDistance1(imgSaveFile * img, int the, imgFile * fromNet, int num)
{
	//初始化
	double dis[CLASS_NUM];
	float wei[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		dis[i] = distance(img->eachCenterHist[the], fromNet->eachCenterHist[i]);
		wei[i] = fromNet->eachClassWeight[i];
	}
	//排序
	for (int j = 0; j < CLASS_NUM - 1; j++)
	{
		for (int i = 0; i < CLASS_NUM - 1 - j; i++)
		{
			if (dis[i]>dis[i + 1])
			{
				double td = dis[i];
				dis[i] = dis[i + 1];
				dis[i + 1] = td;

				float tf = wei[i];
				wei[i] = wei[i + 1];
				wei[i + 1] = tf;

			}
		}
	}

	double re = 0;
	for (int i = 0; i < num; i++)
	{
		re += img->eachClassWeight[the] * wei[i] * dis[i];
	}
	return re;


}

double minDistance2(imgSaveFile * img, int the, imgFile * fromNet, int num)
{
	//初始化
	double dis[CLASS_NUM];
	float wei[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		dis[i] = distance(img->eachCenterHist[the], fromNet->eachCenterHist[i]);
		wei[i] = fromNet->eachClassWeight[i];
	}
	//排序
	for (int j = 0; j < CLASS_NUM - 1; j++)
	{
		for (int i = 0; i < CLASS_NUM - 1 - j; i++)
		{
			if (dis[i]>dis[i + 1])
			{
				double td = dis[i];
				dis[i] = dis[i + 1];
				dis[i + 1] = td;

				float tf = wei[i];
				wei[i] = wei[i + 1];
				wei[i + 1] = tf;

			}
		}
	}

	double re = 0;
	for (int i = 0; i < num; i++)
	{
		re += (wei[i] + img->eachClassWeight[the]) * dis[i];
	}
	return re;
}

double minDistance3(imgSaveFile * img, int the, imgFile * fromNet, int num)
{
	//初始化
	double dis[CLASS_NUM];
	float wei[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		dis[i] = distance(img->eachCenterHist[the], fromNet->eachCenterHist[i]);
		wei[i] = fromNet->eachClassWeight[i];
	}
	//排序
	for (int j = 0; j < CLASS_NUM - 1; j++)
	{
		for (int i = 0; i < CLASS_NUM - 1 - j; i++)
		{
			if (dis[i]>dis[i + 1])
			{
				double td = dis[i];
				dis[i] = dis[i + 1];
				dis[i + 1] = td;

				float tf = wei[i];
				wei[i] = wei[i + 1];
				wei[i + 1] = tf;

			}
		}
	}

	double re = 0;
	for (int i = 0; i < num; i++)
	{
		re += dis[i] * img->eachClassWeight[the];
	}
	return re;
}

//对每个imgSaveFile相对网络文件进行打分，minTime:去最小的个数   mod:1/2/3分别为三种求最小值的方法
void getScore1(imgSaveFile * img, imgFile * fromNet, int minTime, int mod)
{
	img->score = 0;
	double * s = new double[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		switch (mod)
		{
		case 1:
			s[i] = minDistance1(img, i, fromNet, minTime);
		case 2:
			s[i] = minDistance2(img, i, fromNet, minTime);
		case 3:
			s[i] = minDistance3(img, i, fromNet, minTime);

		}

	}
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->score += s[i];
	}
	delete[] s;
}




//数转换为字符串
char * zhuanhuan(int num, int wei)
{
	int n = pow(10, wei - 1);
	char * cp = (char *)malloc(sizeof(char)*(wei + 1));
	int i = 0;
	for (; i < wei - 1; i++)
	{
		int t = num / n;
		num = num %n;
		cp[i] = t + 48;
		n /= 10;
	}
	cp[i] = num + 48;
	cp[i + 1] = '\0';
	return cp;
}

//截取字符串
char * jiequ(char * a, int indexSta, int indexEnd)
{
	char * cp = new char[indexEnd - indexSta + 1];
	for (int i = indexSta, j = 0; i < indexEnd; i++, j++)
	{
		*(cp + j) = *(a + i);
	}
	*(cp + indexEnd - indexSta) = '\0';
	return cp;
}

//获得文件名
void getFileName(imgFile * img)
{
	//获取最后一个'/'位置（可以加上1），获取最后一个‘_’位置
	int start;
	int end;
	for (int i = strlen(img->imgAddr) - 1; i >= 0; i--)
	{
		if (img->imgAddr[i] == '/')
		{
			start = i + 1;
			break;
		}
	}
	for (int i = strlen(img->imgAddr) - 1; i >= 0; i--)
	{
		if (img->imgAddr[i] == '_')
		{
			end = i;
			break;
		}
	}
	img->fileName = jiequ(img->imgAddr, start, end);
}




//用于输出结果的函数库


//给文件结构体排序,分数（SCORE）从低到高
void reorder(struct imgSaveFile * imgFiles, int fileNum)
{
	imgSaveFile tempFile;
	for (int j = 0; j<fileNum - 1; j++)
	{
		for (int i = 0; i<fileNum - 1 - j; i++)
		{
			if (imgFiles[i].score>imgFiles[i + 1].score)
			{
				tempFile = imgFiles[i];
				imgFiles[i] = imgFiles[i + 1];
				imgFiles[i + 1] = tempFile;
			}
		}
	}
}

void reorderResAss(resAss * res, int fileTypeNum)
{
	resAss temp;
	for (int j = 0; j < fileTypeNum - 1; j++)
	{
		for (int i = 0; i < fileTypeNum - 1 - j; i++)
		{
			if (res[i].scoreSum>res[i + 1].scoreSum)
			{
				temp = res[i];
				res[i] = res[i + 1];
				res[i + 1] = temp;
			}
		}
	}
}

void countScore(imgSaveFile * imgs, int fileNum, resAss * res, int fileTypeNum)
{
	//先复位
	for (int i = 0; i < fileTypeNum; i++)
	{
		res[i].scoreSum = 0;
		res[i].time = 0;
	}
	reorder(imgs, fileNum);


	for (int i = 0; i < fileNum*(1 - ABANDON); i++)
	{
		for (int j = 0; j <fileTypeNum; j++)
		{
			if (!strcmp(imgs[i].fileName, res[j].name))
			{
				res[j].scoreSum += imgs[i].score;
				res[j].time++;
				break;
			}
		}
	}

	//求平均值
	for (int i = 0; i < fileTypeNum; i++)
	{
		if (res[i].scoreSum == 0)
		{
			res[i].scoreSum = 1000;
		}
		res[i].scoreSum /= res[i].time;
	}

	//排序
	reorderResAss(res, fileTypeNum);
}

