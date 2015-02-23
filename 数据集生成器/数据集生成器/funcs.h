/*
程序：生成数据集
版本：V2.1
作者：沈涛 重庆邮电大学

funcs.cpp
本文件功能在程序中的作用：
1 所有的函数体
*/

#include"include.h"

//读取某文件夹下所有文件名
void getFiles(string path, vector<string>& files)
{
	//文件句柄
	__int64   hFile = 0;
	//文件信息
	struct _finddatai64_t fileinfo;
	string p;
	if ((hFile = _findfirsti64(p.assign(path).append("/*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
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

//将所有文件向量的值读入文件结构体指针
void loadFiles(vector<string> files, imgFile* imgFiles, int num)
{

	char **pca = new char*[num];
	char **ptmp = pca;
	for (vector<string>::iterator iter = files.begin(); iter != files.end(); ++iter, ++ptmp)
	{
		//为vector<string>的每个元素创建一个字符数组
		char *p = new char[(*iter).size() + 1];
		//string的c_str()函数将string转化为const char*型，并复制给新的字符数组
		strcpy(p, (*iter).c_str());
		//指向数组的指针存入字符指针数组pca中
		*ptmp = p;
	}
	//将字符数组的内容存入imgFile结构体数组中
	for (int k = 0; k<num; k++)
	{
		(imgFiles + k)->imgAddr = *(pca + k);
	}
}

//初始化
void init(imgFile* img)
{
	//cv载入图片
	img->imgSrc = cvLoadImage(img->imgAddr);
	//创建生成边缘图片
	img->imgEdge = cvCreateImage(cvGetSize(img->imgSrc), IPL_DEPTH_8U, 1);
	cvCanny(img->imgSrc, img->imgEdge, 50, 150, 3);

	//计算分块的行数与列数,因为是覆盖50%分割,所以乘上2
	img->rowCount = ((img->imgSrc->height) / EXCI_HEIGHT) * 2 - 1;
	img->colCount = ((img->imgSrc->width) / EXCI_WIDTH) * 2 - 1;

	//给imgPieces动态分配空间
	img->imgPieces = new IplImage**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->imgPieces[i] = new IplImage*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->imgPieces[i][j] = new IplImage[1];
		}
	}

	//给imgEdgePieces动态分配空间
	img->imgEdgePieces = new IplImage**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->imgEdgePieces[i] = new IplImage*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->imgEdgePieces[i][j] = new IplImage[1];
		}
	}

	//给hists动态分配空间
	img->hists = new float**[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->hists[i] = new float*[img->colCount];
		for (int j = 0; j < img->colCount; j++)
		{
			img->hists[i][j] = new float[HIST_LEN];
		}
	}

	//给whiteCol动态分配空间
	img->whiteCol = new int*[img->rowCount];
	for (int i = 0; i < img->rowCount; i++)
	{
		img->whiteCol[i] = new int[img->colCount];
	}

	//计数归零
	img->edgeMatConut = 0;

	//给eachClassWeight动态分配空间
	img->eachClassWeight = (float *)malloc(sizeof(float)*CLASS_NUM);
	//给eachClassCount动态分配空间
	img->eachClassCount = (int *)malloc(sizeof(int)*CLASS_NUM);
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->eachClassCount[i] = 0;
	}
	//给eachCenterHist动态分配空间
	img->eachCenterHist = (double **)malloc(sizeof(double *)*CLASS_NUM);
	for (int i = 0; i < CLASS_NUM; i++)
	{
		img->eachCenterHist[i] = (double *)malloc(sizeof(double)*HIST_LEN);
		for (int j = 0; j < HIST_LEN; j++)
			img->eachCenterHist[i][j] = 0;
	}

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
	cvReleaseImage(&g_plane);
	cvReleaseImage(&b_plane);
	cvReleaseImage(&hsv);
	cvReleaseHist(&r_hist);
	cvReleaseHist(&g_hist);
	cvReleaseHist(&b_hist);
}


//统计存在边界点的行数
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

//核心函数,用于分块计算边缘与直方图
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
			//二值化
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

//对二值化的边缘矩阵进行扫描检测边缘
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

//聚类
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

	//使用KMeans进行聚类
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
			img->eachCenterHist[cluster_idx][j] += pow(cvmGet(img->dataMat, i, j), 1);
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

//获得品牌型号名
void getFileName(imgFile * img)
{
	//获取最后一个'/'或者'\'的位置（可以加上1），获取最后一个‘_’位置
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


//计算有多少种文件名,用于保存,用于核心匹配程序的同一文件名的分数统计
//1.计算有多少种不同的文件名
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
				//存在直接break
				break;
			}
		}
		//不存在，加入链表
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
//2.不重复的品牌型号数据转存到 saveFileType结构体数组中
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


//数据转存,将图片文件的特征信息从imgFile,转移到imgSaveFile,以方便保存
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