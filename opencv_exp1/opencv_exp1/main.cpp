#include"funcs.h"

int  main(int argc ,char ** argv)
{
	//
	imgFile  fromNet[1];
	fromNet->imgAddr = argv[1];

	//��ȡ������Ϣ�ļ�������
	int fileNum;
	int fileTypeNum;
	FILE * fp = fopen(argv[2], "r");
	fscanf(fp, "%d,%d,%d,%d,%f", &fileNum, &fileTypeNum, &EXCI_WIDTH, &EXCI_HEIGHT, &MIN_WHITE_PER);
	fclose(fp);


	//���������ļ�
	init(fromNet);
	doCore(fromNet);
	handleEdge(fromNet);
	cluster(fromNet);
	handleClustered(fromNet);


	//��ȡ�����ļ�����Ϣ
	imgSaveFile * imgs = (imgSaveFile *)malloc(sizeof(imgSaveFile)*fileNum);
	fp = fopen(argv[3], "rb");
	fread(imgs, sizeof(imgSaveFile)*fileNum, 1, fp);
	fclose(fp);

	//��ʼ���
	for (int i = 0; i < fileNum; i++)
	{
		getScore1(imgs + i, fromNet, 2, 1);
	}

	//��img����С�ķ���ǰ�棩
	//reorder(imgs, fileNum);	
	fp = fopen(argv[4], "rb");
	resAss * res = (resAss *)malloc(sizeof(resAss)*fileTypeNum);
	fread(res, sizeof(resAss)*fileTypeNum, 1, fp);
	fclose(fp);

	//ͳ�Ʒ���
	countScore(imgs, fileNum, res, fileTypeNum);




	//д�����
	fp = fopen(argv[5], "w");
	for (int i = 0; i < 20; i++)
	{
		fputs(res[i].name, fp);
		fputs("\n", fp);
	}
	fclose(fp);


	return 0;
}