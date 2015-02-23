#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <cstring>

using namespace std;

int main(int argc, char ** argv)
{
	char a[200];
	strcpy(a, argv[1]);
	strcat(a, argv[2]);
	cout << a << endl;
	IplImage * src = cvLoadImage(a, 1);
	CvSize cs = cvGetSize(src);
	int x = src->width;
	int y = src->height;
	FILE * fp = fopen("D:/testServer.txt", "a");
	fputs("@", fp);
	fputs(a, fp);
	fputs("\nwidth", fp);
	fclose(fp);
	cvReleaseImage(&src);
	return 0;
}