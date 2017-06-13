#pragma once
/****************************************************\
������Ϣ��
���������ѷ�
��Ȩ������
��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ�߼��������ѵ���γ�������
ģ������:
CodeForLab6.h
ժҪ:
��ѧ�������룬���ʵ��7
����˵��:

ģ����ʷ:
�������ѷ���2010��10��26�մ�����ģ�飬email: yflin@bjtu.edu.cn
  �������ѷ���2012��10��19���޸ı�ģ�飬email: yflin@bjtu.edu.cn
	���ѷ���2015.11.10�޸ı�ģ��
	������2016��2��16���޸ı�ģ�飬email��shhan@bjtu.edu.cn

	**********************************************************/
	//�˴���ֹ���ظ�����ͷ�ļ����������ظ�����
#ifndef CODEFORLAB6_H_  
#define CODEFORLAB6_H_



	//�ı��ļ�ͳ����Ϣ�ṹ��
	//��ʾ��ͨ��typedefʹTEXTFILEINFO�ȼ���struct TextFileInfo
typedef struct TextFileInfo
{
	char szFileName[120]; //the file name, should be less than 120 characters
	int nWords; //the number of words separated by spaces
	int nSize; //the size of file in bytes
	int nDigits; //the number of digital charactors
	int nSpaces; //the number of spaces including space , ��\t��, ��\r��, ��\n��
	int nAlphabets; //the number of charactors 'A'--'Z', 'a'--'z'
	int nOthers; //the number of other characters
}TEXTFILEINFO;


//�����ļ�ͳ����Ϣ�ṹ�壬�ýṹ�д�Ÿ����ı��ļ���ͳ����Ϣ
//�����ļ���Ϣ�Ľṹ˳����
typedef struct FilesInfo
{
	TEXTFILEINFO *pFileInfos;
	////�׸��ļ���ͳ����Ϣ�ṹ���׵�ַ������nFileNumber-1���ļ�����Ϣ˳���������
	////��ʾ����ʹ��pFileInfosʱ�ɽ��俴��һ��������ʹ��,��pFileInfos[i]

	int nFileNumber; //�ļ���Ŀ
}FILESINFO;


/*
 *
 */


/*  ��������AllocateSpaceForTextFileInfos
 *	���ܣ�����FILESINFO������Ĵ洢�ռ�
 *  �������ļ�ͳ����Ϣ�ṹ��ָ��
 *  ����ֵ: 1�� �ɹ���0�����ɹ�
 */
int AllocateSpaceForTextFilesInfo(FILESINFO *pMyFiles);



/*
 *	��������PrepareBasicInfoOfFiles
 *	���ܣ�׼�������ļ��Ļ�����Ϣ
 *      1. �����ļ�����
 *      2. ��������ļ�����FILESINFO������Ĵ洢�ռ�
 *		3. �������������ļ���
 *  ������FILESINFO *pFilesInfo���ļ�ͳ����Ϣ�ṹ��ָ��
 *	����ֵ��int
 */
int PrepareBasicInfoOfFiles(FILESINFO *pFilesInfo);

/*
 *	��������CountFilesInfo
 *	���ܣ�ͳ�Ƹ�����Ϣ
 *		1. ͳ�Ƹ����ļ��е�Ӣ�Ĵʸ���
 *		2. ͳ�Ƹ����ļ��и��������ַ�����
 *	������FILESINFO *pFilesInfo���ļ�ͳ����Ϣ�ṹ��ָ��
 *	����ֵ��int
 */
int CountFilesInfo(FILESINFO *pFilesInfo);

/*
 *	��������CountDifferentCharactersInFile
 *	���ܣ����ܸ����ļ��и����ַ��ĸ���
 *		1. �����ļ���Ϣ�ṹ��ָ��pTextFileInfo���������ļ��������ļ�
 *		2. ˳������ļ��е��ַ���ͳ���и����ַ���
 *		3. �ر��ļ�
 *  ������TEXTFILEINFO *pTextFileInfo
 *	����ֵ��0 �ɹ�  -1 �޷����ļ�
 */

int CountDifferentCharactersInFile(TEXTFILEINFO *pTextFileInfo);

/*  ��������ExportFilesInfoToWebPage
 *	���ܣ�������ļ�ͳ����Ϣ��һ��HTML�ļ���
 *  ������
 *		FILESINFO *pMyFiles �����ļ���ͳ����Ϣ�ṹ��ָ��
 *		char *szHtmlFile ��ҳ�ļ���
 *  ����ֵ��0�ɹ���-1���޷������ļ�
 */
int ExportFilesInfoToWebPage(FILESINFO *pMyFiles, char *szHtmlFile);

/*
 *	��������TestCountFilesInfo
 *	���ܣ����Ժ���ʵ��6�ļ���Ϣͳ�Ƶ������Ժ���
 *	��������
 *	����ֵ����
 *
 */
void TestCountFilesInfo();


/*
 *	��������CountWordsOfEuropeanTxtFile
 *	���ܣ�ͳ��ŷ�������ı��ļ��дʵĸ���
 *	������char *szFileName �ļ���
 *	����ֵ��������
 */

int CountWordsOfEuropeanTxtFile(char *szFileName);//ͳ��ŷ�������ı��ļ��дʵĸ���

/*
 *	��������CountWordsInOneLine
 *	���ܣ�ͳ��һ��ŷ�����������дʵĸ���
 *	������const char *szLine һ��ŷ����������
 *	����ֵ��������
 */
int CountWordsInOneLine(const char *szLine);



#endif
