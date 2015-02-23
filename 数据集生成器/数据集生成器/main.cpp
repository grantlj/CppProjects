/*
�����������ݼ�
�汾��V2.1
���ߣ����� �����ʵ��ѧ

mian.cpp
���ļ������ڳ����е����ã�
1 ������
2 ����������
*/
#include"funcs.h"

void main()
{
	//------��Ҫ����Ĳ���------ע�⣺��������б�ܣ���
	//1.ͼƬ�ļ���Ŀ¼(������ֻ����ͼƬ�ļ�,�����������ļ��к��ļ�)
	char * imageFolderLocation = "D:/123/";
	//2.������ݼ��ļ���Ŀ¼
	char * outFolderLocation = "D:/MyClothes/FtpServer/db/";


	//���ļ�����������files��
	vector<string> files;
	getFiles(imageFolderLocation, files);

	//��ȡ�ļ���
	int fileNum = (int)files.size();

	//�ļ�����
	struct imgFile* imgFiles;
	imgFiles = (struct imgFile*)malloc(sizeof(struct imgFile)* fileNum);
	//��files�������ļ��������ļ�����
	loadFiles(files, imgFiles, fileNum);

	//�ֱ������Ϣ
	for (int i = 0; i < fileNum; i++)
	{
		cout << "����:" << i + 1 << "/��:" << fileNum << endl;
		init(imgFiles + i);
		doCore(imgFiles + i);
		handleEdge(imgFiles + i);
		cluster(imgFiles + i);
		handleClustered(imgFiles + i);
		getFileName(imgFiles + i);
	}



	//д���ļ�

	//Ϊ�����������Ҫͳ��һ���ж�����Ʒ���ͺŵ��·�,������.fn���ݼ�
	int fileTypeNum = GetFileCount(imgFiles, fileNum);
	saveFileType *sft = (saveFileType *)malloc(sizeof(saveFileType)*fileTypeNum);
	saveFileTypeInfo(imgFiles, fileNum, sft, fileTypeNum);
	char fileNameTemp[200];
	FILE * fp = fopen(strcat(strcpy(fileNameTemp, outFolderLocation), "db.fn"), "wb");
	fwrite(sft, sizeof(saveFileType)*fileTypeNum, 1, fp);
	fclose(fp);


	//��Ϣת��������.dat�ļ���
	imgSaveFile * imgSave;
	imgSave = (imgSaveFile *)malloc(sizeof(imgSaveFile)*fileNum);
	saveInfo(imgFiles, imgSave, fileNum);
	//dat �����ļ�
	fp = fopen(strcat(strcpy(fileNameTemp, outFolderLocation), "db.dat"), "wb");
	fwrite(imgSave, sizeof(imgSaveFile)*fileNum, 1, fp);
	fclose(fp);

	//.info��Ϣ�ļ�,�����Ҫ�ķֿ�����ֵ��Ϣ
	fp = fopen(strcat(strcpy(fileNameTemp, outFolderLocation), "db.info"), "w");
	fprintf(fp, "%d,%d,%d,%d,%f", fileNum, fileTypeNum, EXCI_WIDTH, EXCI_HEIGHT, MIN_WHITE_PER);
	fclose(fp);

}