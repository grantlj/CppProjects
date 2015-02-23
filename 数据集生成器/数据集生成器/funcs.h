/*
�����������ݼ�
�汾��V2.1
���ߣ����� �����ʵ��ѧ

funcs.cpp
���ļ������ڳ����е����ã�
1 ���еĺ�����
*/

#include"include.h"

//��ȡĳ�ļ����������ļ���
void getFiles(string path, vector<string>& files)
{
	//�ļ����
	__int64   hFile = 0;
	//�ļ���Ϣ
	struct _finddatai64_t fileinfo;
	string p;
	if ((hFile = _findfirsti64(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//�����Ŀ¼,����֮
			//�������,�����б�
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("/").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));
			}
		} while (_findnexti64(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

//�������ļ�������ֵ�����ļ��ṹ��ָ��
void loadFiles(vector<string> files, imgFile* imgFiles, int num)
{

	char **pca = new char*[num];
	char **ptmp = pca;
	for (vector<string>::iterator iter = files.begin(); iter != files.end(); ++iter, ++ptmp)
	{
		//Ϊvector<string>��ÿ��Ԫ�ش���һ���ַ�����
		char *p = new char[(*iter).size() + 1];
		//string��c_str()������stringת��Ϊconst char*�ͣ������Ƹ��µ��ַ�����
		strcpy(p, (*iter).c_str());
		//ָ�������ָ������ַ�ָ������pca��
		*ptmp = p;
	}
	//���ַ���������ݴ���imgFile�ṹ��������
	for (int k = 0; k<num; k++)
	{
		(imgFiles + k)->imgAddr = *(pca + k);
	}
}

//��ʼ��
void init(imgFile* img)
{
	//cv����ͼƬ
	img->imgSrc = cvLoadImage(img->imgAddr);
	//�������ɱ�ԵͼƬ
	img->imgEdge = cvCreateImage(cvGetSize(img->imgSrc), IPL_DEPTH_8U, 1);
	cvCanny(img->imgSrc, img->imgEdge, 50, 150, 3);

	//����ֿ������������,��Ϊ�Ǹ���50%�ָ�,���Գ���2
	img->rowCount = ((img->imgSrc->height) / EXCI_HEIGHT) * 2 - 1;
	img->colCount = ((img->imgSrc->width) / EXCI_WIDTH) * 2 - 1;

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
	cvReleaseImage(&g_plane);
	cvReleaseImage(&b_plane);
	cvReleaseImage(&hsv);
	cvReleaseHist(&r_hist);
	cvReleaseHist(&g_hist);
	cvReleaseHist(&b_hist);
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

//���ĺ���,���ڷֿ�����Ե��ֱ��ͼ
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
			//��ֵ��
			if (getWhiteCount(img->imgEdgePieces[i][j])>EXCI_HEIGHT*MIN_WHITE_PER)
			{
				img->whiteCol[i][j] = 0;
			}
			else img->whiteCol[i][j] = 1;

			cvResetImageROI(img->imgSrc);
			cvResetImageROI(img->imgEdge);

			cvReleaseImage(&img->imgPieces[i][j]);
			cvReleaseImage(&img->imgEdgePieces[i][j]);

		}

	}
	cvReleaseImage(&img->imgSrc);
	cvReleaseImage(&img->imgEdge);

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
			img->eachCenterHist[cluster_idx][j] += pow(cvmGet(img->dataMat, i, j), 1);
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

//���Ʒ���ͺ���
void getFileName(imgFile * img)
{
	//��ȡ���һ��'/'����'\'��λ�ã����Լ���1������ȡ���һ����_��λ��
	int start;
	int end;
	for (int i = strlen(img->imgAddr) - 1; i >= 0; i--)
	{
		if (img->imgAddr[i] == '/' || img->imgAddr[i] == '\\')
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


//�����ж������ļ���,���ڱ���,���ں���ƥ������ͬһ�ļ����ķ���ͳ��
//1.�����ж����ֲ�ͬ���ļ���
int GetFileCount(imgFile * imgs, int fileNum)
{
	typedef struct forFuncGetFileCount
	{
		char  name[100];
		forFuncGetFileCount * next;

		forFuncGetFileCount * head, *tail;
		int num;
	}forFuncGetFileCount;

	forFuncGetFileCount * link = (forFuncGetFileCount *)malloc(sizeof(forFuncGetFileCount));

	forFuncGetFileCount * fcp = (forFuncGetFileCount *)malloc(sizeof(forFuncGetFileCount));
	strcpy(fcp->name, imgs->fileName);
	fcp->next = NULL;
	link->head = fcp;
	link->tail = fcp;
	link->num = 1;
	for (int i = 1; i < fileNum; i++)
	{
		forFuncGetFileCount * tfcp = link->head;
		int j;
		for (j = 0; j < link->num; j++, tfcp = tfcp->next)
		{
			if (!strcmp(imgs[i].fileName, tfcp->name))
			{
				//����ֱ��break
				break;
			}
		}
		//�����ڣ���������
		if (j == link->num)
		{
			forFuncGetFileCount * pp = (forFuncGetFileCount *)malloc(sizeof(forFuncGetFileCount));
			strcpy(pp->name, imgs[i].fileName);
			pp->next = NULL;
			link->tail->next = pp;
			link->tail = link->tail->next;
			link->num++;
		}
	}
	return link->num;
}
//2.���ظ���Ʒ���ͺ�����ת�浽 saveFileType�ṹ��������
void saveFileTypeInfo(imgFile * imgs, int fileNum, saveFileType * sft, int fileTypeNum)
{
	strcpy(sft->name, imgs->fileName);
	int num = 1;
	for (int i = 0; i < fileNum; i++)
	{
		int j;
		for (j = 0; j < num; j++)
		{
			if (!strcmp(sft[j].name, imgs[i].fileName))
				break;
		}

		if (j == num)
		{
			strcpy(sft[num].name, imgs[i].fileName);
			num++;
		}
		if (num == fileTypeNum)
			break;
	}

}


//����ת��,��ͼƬ�ļ���������Ϣ��imgFile,ת�Ƶ�imgSaveFile,�Է��㱣��
void saveInfo(imgFile * img, imgSaveFile * imgSave, int fileNum)
{


	for (int i = 0; i < fileNum; i++)
	{
		strcpy(imgSave[i].fileName, img[i].fileName);
		for (int j = 0; j < CLASS_NUM; j++)
		{
			imgSave[i].eachClassWeight[j] = img[i].eachClassWeight[j];
			for (int k = 0; k < HIST_LEN; k++)
			{
				imgSave[i].eachCenterHist[j][k] = img[i].eachCenterHist[j][k];
			}
		}
	}
}