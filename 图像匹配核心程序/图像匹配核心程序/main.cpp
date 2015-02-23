/*
程序：生成匹配核心程序
版本：V2.1
作者：沈涛 重庆邮电大学

main.cpp
本文件功能在程序中的作用：
1 主函数

说明:程序不能直接运行,只要链接
*/
#include"funcs.h"

int  main(int argc, char ** argv)
{
	imgFile  fromNet[1];
	fromNet->imgAddr = argv[1];

	//读取基本信息文件的数据
	int fileNum;
	int fileTypeNum;
	FILE * fp = fopen(argv[2], "r");
	fscanf(fp, "%d,%d,%d,%d,%f", &fileNum, &fileTypeNum, &EXCI_WIDTH, &EXCI_HEIGHT, &MIN_WHITE_PER);
	fclose(fp);

	//处理来自FTP服务器的文件
	init(fromNet);
	doCore(fromNet);
	handleEdge(fromNet);
	cluster(fromNet);
	handleClustered(fromNet);

	//获取所有文件的信息
	imgSaveFile * imgs = (imgSaveFile *)malloc(sizeof(imgSaveFile)*fileNum);
	fp = fopen(argv[3], "rb");
	fread(imgs, sizeof(imgSaveFile)*fileNum, 1, fp);
	fclose(fp);

	//开始打分
	for (int i = 0; i < fileNum; i++)
	{
		getScore1(imgs + i, fromNet, 2, 3);
	}

	//读取.fn文件
	fp = fopen(argv[4], "rb");
	resAss * res = (resAss *)malloc(sizeof(resAss)*fileTypeNum);
	fread(res, sizeof(resAss)*fileTypeNum, 1, fp);
	fclose(fp);

	//统计分数
	countScore(imgs, fileNum, res, fileTypeNum);


	//写出结果
	fp = fopen(argv[5], "w");
	for (int i = 0; i < 5; i++)
	{
		fputs(res[i].name, fp);
		fputs("\n", fp);
	}
	fclose(fp);

	return 0;

}