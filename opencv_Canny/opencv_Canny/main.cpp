#include "cv.h"
#include "cxcore.h"
#include "highgui.h"


int getWhiteCount(IplImage* pCannyImg)
{
	long int s = 0;
	//IplImage *img1 = cvCreateImage(cvGetSize(pCannyImg), IPL_DEPTH_8U, 1);
	//cvCvtColor(pCannyImg, img1, CV_BGR2GRAY);

	for (int i = 0; i < pCannyImg->height;i++)
	    for (int j = 0; j < pCannyImg->width; j++)
	{
			CvScalar t1 = cvGet2D(pCannyImg, i, j);
			if (t1.val[0] != 0)
			{

				//printf("%d,%d,%d", t1.val[0], t1.val[1], t1.val[2]);
				s++;
				//system("pause");
			}
	}
//	cvReleaseImage(&img1);
		printf("%d\n", pCannyImg->height*pCannyImg->width);
	return s;
}

int main(int argc, char** argv)
{
	//����IplImageָ��
	IplImage* pImg = NULL;
	IplImage* pCannyImg = NULL;
	//����ͼ��ǿ��ת��ΪGray
	pImg = cvLoadImage("D:\\MyClothes\\1.jpg", 0);
	//Ϊcanny��Եͼ������ռ�
	pCannyImg = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);
	//canny��Ե���
	cvCanny(pImg, pCannyImg, 50, 150, 3);
	//��������
	cvNamedWindow("src", 1);
	cvNamedWindow("canny", 1);
	//��ʾͼ��
	cvShowImage("src", pImg);
	cvShowImage("canny", pCannyImg);
	//�ȴ�����
	cvWaitKey(0);
	//���ٴ���
	cvDestroyWindow("src");
	cvDestroyWindow("canny");
	//�ͷ�ͼ��
	cvReleaseImage(&pImg);
	
	printf("%d\n", getWhiteCount(pCannyImg));
	
	
	cvReleaseImage(&pCannyImg);
	system("pause");
	return 0;

}
