/*
��������ƥ����ĳ���
�汾��V2.1
���ߣ����� �����ʵ��ѧ

funcs.cpp
���ļ������ڳ����е����ã�
1 ���еĺ�����
*/
#include"include.h"


//���õȴ�ʱ��
void sleep(long wait)
{
	long goal = clock() + wait;
	while (goal>clock());
}

//��ʼ��
void init(imgFile* img)
{
	//��ȡFTP���������ļ���������ļ�û�д��꣬��ȴ�һ��ʱ���ٴμ��
	img->imgSrc = NULL;
	while (1)
	{
		img->imgSrc = cvLoadImage(img->imgAddr);
		if (img->imgSrc != NULL)break;
		sleep(500);
		cout << "waiting for:" << img->imgAddr << endl;
	}
	//�������ɱ�ԵͼƬ
	img->imgEdge = cvCreateImage(cvGetSize(img->imgSrc), IPL_DEPTH_8U, 1);
	cvCanny(img->imgSrc, img->imgEdge, 50, 150, 3);
	//����ֿ������������,��Ϊ�Ǹ���50%�ָ�,���Գ���2
	img->rowCount = (img->imgSrc->height / EXCI_HEIGHT) * 2 - 1;
	img->colCount = (img->imgSrc->width / EXCI_WIDTH) * 2 - 1;




	//��imgPieces��̬����ռ�
	img->imgPieces = new IplImage**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->imgPieces[i] = new IplImage*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->imgPieces[i][j] = new IplImage[1];
		}
	}

	//��imgEdgePieces��̬����ռ�
	img->imgEdgePieces = new IplImage**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->imgEdgePieces[i] = new IplImage*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->imgEdgePieces[i][j] = new IplImage[1];
		}
	}

	//��hists��̬����ռ�
	img->hists = new float**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->hists[i] = new float*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->hists[i][j] = new float[HIST_LEN];
		}
	}

	//��whiteCol��̬����ռ�
	img->whiteCol = new int*[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->whiteCol[i] = new int[img->colCount];
	}

	//��������
	img->edgeMatConut = 0;

	//��eachClassWeight��̬����ռ�
	img->eachClassWeight = (float *)malloc(sizeof(float)*CLASS_NUM);
	//��eachClassCount��̬����ռ�
	img->eachClassCount = (int *)malloc(sizeof(int)*CLASS_NUM);
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->eachClassCount[i] = 0;
	}
	//��eachCenterHist��̬����ռ�
	img->eachCenterHist = (double **)malloc(sizeof(double *)*CLASS_NUM);
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->eachCenterHist[i] = (double *)malloc(sizeof(double)*HIST_LEN);
		for (int j = 0; j < HIST_LEN; j++)
			img->eachCenterHist[i][j] = 0;
	}

}

//��ͼƬת��������
void transToHist(IplImage * src, float* vec)
{
	IplImage* r_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* g_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* b_plane = cvCreateImage(cvGetSize(src), 8, 1);
	//IplImage* planes[] = {h_plane,s_plane};   
	//!!!!!!!!!!!!!!---------!!!!!!!!!!! ѡ���ǲ���RGB
	IplImage* hsv = cvCreateImage(cvGetSize(src), 8, 3);
	cvCvtColor(src, hsv, CV_BGR2HSV);
	cvCvtPixToPlane(hsv, b_plane, g_plane, r_plane, 0);//openCV�����һ������,���Կ���cvSplit�����ĺ�:#define cvCvtPixToPlane cvSplit    
	//ע��˳��ΪBGR,OpenCV�в�����Windows��Load�Ļ�������ͷȡ�õĶ���BGR˳�����е�   

	//����ֱ��ͼ     
	int hist_size = PER_HIST_LEN;//����
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


//ͳ�ƴ��ڱ߽�������
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


//ͳ�Ʊ��ؾ�����Ч�ĵ���
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

//���ĺ��������ڷֿ�����Ե��ֱ��ͼ
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

//�Զ�ֵ���ı�Ե�������ɨ�����Ե
void handleEdge(imgFile * img)
{
	//��-����
	for (int i = 0; i < img->rowCount; i++)
	{
		for (int j = 0; j < img->colCount; j++)
		{
			if (img->whiteCol[i][j] == 0)break;
			else img->whiteCol[i][j]++;
		}
	}

	//��-����
	for (int i = 0; i < img->rowCount; i++)
	{
		for (int j = img->colCount - 1; j >= 0; j--)
		{
			if (img->whiteCol[i][j] == 0)break;
			else img->whiteCol[i][j]++;
		}
	}

	//��-����
	for (int i = 0; i < img->colCount; i++)
	{
		for (int j = 0; j < img->rowCount; j++)
		{
			if (img->whiteCol[j][i] == 0)break;
			else img->whiteCol[j][i]++;
		}
	}

	//��-����
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

//����
void cluster(struct imgFile * img)
{
	//��imgfile�е���������dataMat
	img->dataMat = cvCreateMat(img->edgeMatConut, HIST_LEN, CV_32FC1);
	img->markMat = cvCreateMat(img->edgeMatConut, 1, CV_32SC1);


	//��������Ϣд��datamat������ڱ�Ե���Ѿ�ɾȥ��ֱ��Ϊ��ֵ
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
	//ʹ��KMeans���о���
	cvKMeans2(img->dataMat, CLASS_NUM, img->markMat, cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 1000000000, 0.000000001));

}


//����ÿ���������hist������ÿ����İٷֱȣ�Weight��
void handleClustered(imgFile * img)
{
	//��������ƽ����
	for (int i = 0; i < img->edgeMatConut; i++)
	{
		int cluster_idx = img->markMat->data.i[i];
		img->eachClassCount[cluster_idx]++;
		for (int j = 0; j < HIST_LEN; j++)
		{
			img->eachCenterHist[cluster_idx][j] += pow(cvmGet(img->dataMat, i, j), 2);
		}
	}


	//��ÿ�����Ȩ��
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->eachClassWeight[i] = img->eachClassCount[i] / (float)img->edgeMatConut;
	}
	//ȡƽ��ֵ
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

//��һ�ִ�ֵķ���
//���һ��������һ����������С�ľ���,����Ȩ�ص�ʹ�÷�ʽ,�����ַ���,��Ӧscore��4��mod
double minDistance1(imgSaveFile * img, int the, imgFile * fromNet, int num)
{
	//��ʼ��
	double dis[CLASS_NUM];
	float wei[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		dis[i] = distance(img->eachCenterHist[the], fromNet->eachCenterHist[i]);
		wei[i] = fromNet->eachClassWeight[i];
	}
	//����
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
		re += (1 - img->eachClassWeight[the]) * (1 - wei[i]) *dis[i];
	}
	return re;


}

double minDistance2(imgSaveFile * img, int the, imgFile * fromNet, int num)
{
	//��ʼ��
	double dis[CLASS_NUM];
	float wei[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		dis[i] = distance(img->eachCenterHist[the], fromNet->eachCenterHist[i]);
		wei[i] = fromNet->eachClassWeight[i];
	}
	//����
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
		re += (2 - wei[i] - img->eachClassWeight[the]) * dis[i];
	}
	return re;
}

double minDistance3(imgSaveFile * img, int the, imgFile * fromNet, int num)
{
	//��ʼ��
	double dis[CLASS_NUM];
	float wei[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		dis[i] = distance(img->eachCenterHist[the], fromNet->eachCenterHist[i]);
		wei[i] = fromNet->eachClassWeight[i];
	}
	//����
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
		re += dis[i] * (1 - img->eachClassWeight[the]);
	}
	return re;
}

double minDistance4(imgSaveFile * img, int the, imgFile * fromNet, int num)
{
	//��ʼ��
	double dis[CLASS_NUM];
	float wei[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		dis[i] = distance(img->eachCenterHist[the], fromNet->eachCenterHist[i]);
		wei[i] = fromNet->eachClassWeight[i];
	}
	//����
	for (int j = 0; j < CLASS_NUM - 1; j++)
	{
		for (int i = 0; i < CLASS_NUM - 1 - j; i++)
		{
			if (dis[i] * (1 - wei[i])>dis[i + 1] * (1 - wei[i + 1]))
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
		re += (1 - img->eachClassWeight[the]) * (1 - wei[i]) *dis[i];
	}
	return re;


}
//��ÿ��imgSaveFile��������ļ����д�֣�minTime:ȥ��С�ĸ���   mod:1/2/3/4�ֱ�Ϊ��������Сֵ�ķ���
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
			break;
		case 2:
			s[i] = minDistance2(img, i, fromNet, minTime);
			break;
		case 3:
			s[i] = minDistance3(img, i, fromNet, minTime);
			break;
		case 4:
			s[i] = minDistance4(img, i, fromNet, minTime);
			break;

		}

	}
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->score += s[i];
	}
	delete[] s;
}

//�ڶ��ִ�ַ���
double minSum(const double * arr, int num, int * posi, const int * flagVal)
{

	double val[CLASS_NUM];
	int index[CLASS_NUM];
	int flag[CLASS_NUM];
	for (int i = 0; i < CLASS_NUM; i++)
	{
		val[i] = arr[i];
		index[i] = i;
		flag[i] = flagVal[i];

	}
	//����
	for (int j = 0; j < CLASS_NUM - 1; j++)
	{
		for (int i = 0; i < CLASS_NUM - 1 - j; i++)
		{
			if (val[i]>val[i + 1])
			{
				double tempVal = val[i];
				val[i] = val[i + 1];
				val[i + 1] = tempVal;

				int  tempIndex = index[i];
				index[i] = index[i + 1];
				index[i + 1] = tempIndex;

				int tempFlag = flag[i];
				flag[i] = flag[i + 1];
				flag[i + 1] = tempFlag;
			}
		}
	}

	double minS = 0;
	int k = 0;;
	for (int i = 0; i < CLASS_NUM; i++)
	{
		if (flag[i]>0)
		{
			minS += val[i];
			posi[k] = index[i];
			k++;
		}

		if (k == num)break;

	}
	return minS;

}

void getScore2(imgSaveFile * img, imgFile * fromNet, int minTime)
{
	double dis[CLASS_NUM][CLASS_NUM];
	int flag[CLASS_NUM];
	int  sumFlag[CLASS_NUM];
	double sum[CLASS_NUM];

	for (int i = 0; i < CLASS_NUM; i++)
	{
		for (int j = 0; j < CLASS_NUM; j++)
		{
			dis[i][j] = distance(img->eachCenterHist[i], fromNet->eachCenterHist[j]);

		}
		flag[i] = minTime;
		sumFlag[i] = 1;

	}

	for (int i = 0; i < CLASS_NUM; i++)
	{
		double tempSum[CLASS_NUM];


		int ** posi;
		posi = (int **)malloc(sizeof(int *)*CLASS_NUM);
		for (int j = 0; j < CLASS_NUM; j++)
		{
			posi[j] = (int *)malloc(sizeof(int)*minTime);
		}


		int * minSumPos;
		minSumPos = (int *)malloc(sizeof(int));

		for (int j = 0; j < CLASS_NUM; j++)
		{
			tempSum[j] = minSum(dis[j], minTime, posi[j], flag);
		}

		minSum(tempSum, 1, minSumPos, sumFlag);
		sum[*minSumPos] = minSum(tempSum, 1, minSumPos, sumFlag);
		if (i == CLASS_NUM - 1)break;
		sumFlag[*minSumPos]--;
		for (int j = 0; j < minTime; j++)
		{
			flag[posi[*minSumPos][j]]--;
		}
	}

	img->score = 0;

	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->score += sum[i] * (1 - img->eachClassWeight[i]);
	}

}


//��ȡ�ַ���
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


//���ļ��ṹ������,������SCORE���ӵ͵���
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

//���ֽܷ�������,������������
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

//�������
void countScore(imgSaveFile * imgs, int fileNum, resAss * res, int fileTypeNum)
{
	//�ȸ�λ
	for (int i = 0; i < fileTypeNum; i++)
	{
		res[i].scoreSum = 0;
		res[i].time = 0;
	}
	//����
	reorder(imgs, fileNum);

	//��������ǰ��img��С����
	for (int i = 0; i < fileNum; i++)
	{
		if (i < fileNum*0.3)
		{
			imgs[i].score *= pow(98.0 / 100.0, (int)(fileNum*0.3) - i);
		}
	}


	//ͳ���ֺܷʹ���
	for (int i = 0; i < fileNum*(1 - ABANDON); i++)
	{
		for (int j = 1; j <fileTypeNum; j++)
		{
			if (!strcmp(imgs[i].fileName, res[j].name))
			{
				res[j].scoreSum += imgs[i].score;
				res[j].time++;
				break;
			}
		}
	}

	//��ƽ��ֵ
	for (int i = 0; i < fileTypeNum; i++)
	{
		if (res[i].scoreSum == 0)
		{
			//��ֹһ��Ҳû����,���ǽṹ�ǳ�С
			res[i].scoreSum = 1000;
		}
		res[i].scoreSum /= res[i].time;
	}

	//��������
	reorderResAss(res, fileTypeNum);
}



