/*
程序：生成数据集
版本：V2.1
作者：沈涛 重庆邮电大学

mian.cpp
本文件功能在程序中的作用：
1 主函数
2 参数的输入
*/
#include"funcs.h"

void main()
{
	//------需要输入的参数------注意：请输入正斜杠）：
	//1.图片文件夹目录(必须是只包含图片文件,不能有其他文件夹和文件)
	char * imageFolderLocation = "D:/123/";
	//2.输出数据集文件的目录
	char * outFolderLocation = "D:/MyClothes/FtpServer/db/";


	//将文件名读入向量files中
	vector<string> files;
	getFiles(imageFolderLocation, files);

	//获取文件数
	int fileNum = (int)files.size();

	//文件数组
	struct imgFile* imgFiles;
	imgFiles = (struct imgFile*)malloc(sizeof(struct imgFile)* fileNum);
	//将files集合中文件名读进文件数组
	loadFiles(files, imgFiles, fileNum);

	//分别计算信息
	for (int i = 0; i < fileNum; i++)
	{
		cout << "进度:" << i + 1 << "/共:" << fileNum << endl;
		init(imgFiles + i);
		doCore(imgFiles + i);
		handleEdge(imgFiles + i);
		cluster(imgFiles + i);
		handleClustered(imgFiles + i);
		getFileName(imgFiles + i);
	}



	//写入文件

	//为最后输出结果，要统计一共有多少种品牌型号的衣服,并生成.fn数据集
	int fileTypeNum = GetFileCount(imgFiles, fileNum);
	saveFileType *sft = (saveFileType *)malloc(sizeof(saveFileType)*fileTypeNum);
	saveFileTypeInfo(imgFiles, fileNum, sft, fileTypeNum);
	char fileNameTemp[200];
	FILE * fp = fopen(strcat(strcpy(fileNameTemp, outFolderLocation), "db.fn"), "wb");
	fwrite(sft, sizeof(saveFileType)*fileTypeNum, 1, fp);
	fclose(fp);


	//信息转存后输出到.dat文件中
	imgSaveFile * imgSave;
	imgSave = (imgSaveFile *)malloc(sizeof(imgSaveFile)*fileNum);
	saveInfo(imgFiles, imgSave, fileNum);
	//dat 数据文件
	fp = fopen(strcat(strcpy(fileNameTemp, outFolderLocation), "db.dat"), "wb");
	fwrite(imgSave, sizeof(imgSaveFile)*fileNum, 1, fp);
	fclose(fp);

	//.info信息文件,保存必要的分块与阈值信息
	fp = fopen(strcat(strcpy(fileNameTemp, outFolderLocation), "db.info"), "w");
	fprintf(fp, "%d,%d,%d,%d,%f", fileNum, fileTypeNum, EXCI_WIDTH, EXCI_HEIGHT, MIN_WHITE_PER);
	fclose(fp);

}