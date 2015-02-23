/*

#include <opencv2/opencv.hpp>
#include <stdlib.h>
#include <Windows.h>
using namespace cv;


void doCannyTransfer(IplImage* pImg)
{
	IplImage* pCannyImg = NULL;
	pCannyImg = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);


	cvCanny(pImg, pCannyImg, 50, 150, 3);
	cvNamedWindow("canny", 1);
    cvShowImage("canny", pCannyImg);
	cvWaitKey();
	cvDestroyWindow("src"); cvDestroyWindow("canny");
	cvReleaseImage(&pCannyImg);
}

void doCounterDetector(IplImage* pImg)
{
	IplImage* pCounterImg = NULL;

}


void doRotateTransfer(IplImage* pImg)
{
	IplImage* dst = NULL;
	dst = cvCloneImage(pImg);

	float m[6];
	CvMat M = cvMat(2, 3, CV_32F, m);
	int w = pImg->height;
	int h = pImg->width;

	int angle = 45;
	m[0] = (float)(cos(-angle * 2 * CV_PI / 180.));
	m[1] = (float)(sin(-angle * 2 * CV_PI / 180.));
	m[3] = -m[1];
	m[4] = m[0];
	m[2] = w*0.5f;
	m[5] = h*0.5f;
	cvZero(dst);
	cvGetQuadrangleSubPix(pImg, dst, &M);
	cvNamedWindow("dst", 1);
	cvShowImage("dst", dst);
	waitKey();
	


}

int main()
{
	IplImage* pImg = NULL;
	pImg = cvLoadImage("d:/lena.png", 0);
	cvNamedWindow("src", 1);
	cvShowImage("src", pImg);

	//doCannyTransfer(pImg);
	//doCounterDetector(pImg);
	//doRotateTransfer(pImg);
	cvReleaseImage(&pImg);
	return 0;


}
*/
#include <opencv/highgui.h>
#include <opencv/cv.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	IplImage * src;
	if (!(src = cvLoadImage("D:\\1.JPG")))
	{
		cout << "没有找到源文件" << endl;
		return -1;
	}

	IplImage* hsv = cvCreateImage(cvGetSize(src), 8, 3);
	IplImage* h_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* s_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* v_plane = cvCreateImage(cvGetSize(src), 8, 1);
	IplImage* planes[] = { h_plane, s_plane };

	/** H 分量划分为16个等级，S分量划分为8个等级 */
	int h_bins = 16, s_bins = 8;
	int hist_size[] = { h_bins, s_bins };

	/** H 分量的变化范围 */
	float h_ranges[] = { 0, 180 };

	/** S 分量的变化范围*/
	float s_ranges[] = { 0, 255 };
	float* ranges[] = { h_ranges, s_ranges };

	/** 输入图像转换到HSV颜色空间 */
	cvCvtColor(src, hsv, CV_BGR2HSV);
	cvNamedWindow("hsv", 1);
	cvShowImage("hsv", hsv);

	cvCvtPixToPlane(hsv, h_plane, s_plane, v_plane, 0);
	cvNamedWindow("h_plane", 1);
	cvShowImage("h_plane", h_plane);
	cvNamedWindow("s_plane", 1);
	cvShowImage("s_plane", s_plane);
	cvNamedWindow("v_plane", 1);
	cvShowImage("v_plane", v_plane);

	/** 创建直方图，二维, 每个维度上均分 */
	CvHistogram * hist = cvCreateHist(2, hist_size, CV_HIST_ARRAY, ranges, 1);
	/** 根据H,S两个平面数据统计直方图 */
	cvCalcHist(planes, hist, 0, 0);

	/** 获取直方图统计的最大值，用于动态显示直方图 */
	float max_value;
	cvGetMinMaxHistValue(hist, 0, &max_value, 0, 0);


	/** 设置直方图显示图像 */
	int height = 240;
	int width = (h_bins*s_bins * 6);
	IplImage* hist_img = cvCreateImage(cvSize(width, height), 8, 3);
	cvZero(hist_img);

	/** 用来进行HSV到RGB颜色转换的临时单位图像 */
	IplImage * hsv_color = cvCreateImage(cvSize(1, 1), 8, 3);
	IplImage * rgb_color = cvCreateImage(cvSize(1, 1), 8, 3);
	int bin_w = width / (h_bins * s_bins);
	for (int h = 0; h < h_bins; h++)
	{
		for (int s = 0; s < s_bins; s++)
		{
			int i = h*s_bins + s;
			/** 获得直方图中的统计次数，计算显示在图像中的高度 */
			float bin_val = cvQueryHistValue_2D(hist, h, s);
			int intensity = cvRound(bin_val*height / max_value);

			/** 获得当前直方图代表的颜色，转换成RGB用于绘制 */
			cvSet2D(hsv_color, 0, 0, cvScalar(h*180.f / h_bins, s*255.f / s_bins, 255, 0));
			cvCvtColor(hsv_color, rgb_color, CV_HSV2BGR);
			CvScalar color = cvGet2D(rgb_color, 0, 0);

			cvRectangle(hist_img, cvPoint(i*bin_w, height),
				cvPoint((i + 1)*bin_w, height - intensity),
				color, -1, 8, 0);
		}
	}

	cvNamedWindow("Source", 1);
	cvShowImage("Source", src);

	cvNamedWindow("H-S Histogram", 1);
	cvShowImage("H-S Histogram", hist_img);

	cvWaitKey(0);
}