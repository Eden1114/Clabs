/****************************************************\
������Ϣ��
���������ѷ�
��ҵ����ˣ�����		ѧ�ţ�16281237
��Ȩ������
��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ�߼��������ѵ���γ�������
ģ������:
CodeForLab6.CPP
ժҪ:
��ѧ�������룬���ʵ��6
����˵��:

ģ����ʷ:
���ѷ���2011��10��26�մ�����ģ�飬email: yflin@bjtu.edu.cn
���ѷ���2012��10��19���޸ı�ģ�飬email: yflin@bjtu.edu.cn
���ѷ���2013��10��11���޸ı�ģ�飬email: yflin@bjtu.edu.cn
������2017��2��16���޸ı�ģ�飬email��shhan@bjtu.edu.cn

**********************************************************/
#include "CodeForLab6.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "LabFunctions.h"
#include "direct.h"

/*  AllocateSpaceForTextFilesInfo
 *	���ܣ�����FILESINFO������Ĵ洢�ռ�
 *  �������ļ�ͳ����Ϣ�ṹ�����
 *  ע�⣺
 *		1.�ڵ��øú���ǰ�����ȸ���pMyfiles���ļ���ĿnFileNumber
 *		2.����������Ҫ�޸ģ���ֱ��ʹ��
 *  ����ֵ: 0�� �ɹ���-1���������Ϸ���-2���洢�ռ䲻��
 * 	ģ����ʷ��
 *    ���ѷ�����2011.10.26��� 2011.10.19�޸�
 */

int AllocateSpaceForTextFilesInfo(FILESINFO *pMyFiles)
{
	//�����Ϸ����ж�
	if (NULL == pMyFiles || pMyFiles->nFileNumber <= 0)
		return -1;

	//������pMyFiles->nFileNumber��TEXTFILEINFO���ͽṹ������Ĵ洢�ռ�
	//���������뵽��pMyFiles->nFileNumber * sizeof(TEXTFILEINFO)���ֽڵ�
	//�洢�ռ��׵�ַ��ŵ�pMyFiles->pFileInfos��
	pMyFiles->pFileInfos = (TEXTFILEINFO *)malloc(pMyFiles->nFileNumber * sizeof(TEXTFILEINFO));

	if (NULL == pMyFiles->pFileInfos)
		return -2;
	return 0;

}


/***********************************************\
��������:
CountWordsOfEuropeanTxtFile
��������:
ͳ��ŷ�������ı��ļ��дʵĸ���
��������:
char *szFileName �ļ���
����ֵ:
int �ʵĸ���
ģ����ʷ:
������2010.10.28, by ���ѷ�
2013.10.11 ���������޸� by ���ѷ�
\**********************************************/
int CountWordsOfEuropeanTxtFile(char *szFileName)
{
	int nWords = 0;//�ʼ�����������ʼֵΪ0
	FILE *fp; //�ļ�ָ��
	char carrBuffer[1024];//ÿ���ַ����壬ÿ�����1024���ַ�

	//���ļ�
	if ((fp = fopen(szFileName, "r")) == NULL)
	{
		return -1;	//�ļ��򿪲��ɹ��Ƿ���-1
	}

	while (!feof(fp))//���û�ж����ļ�ĩβ 
	{
		//���ļ��ж�һ��

		if (fgets(carrBuffer, sizeof(carrBuffer), fp) != NULL)
		{
			//ͳ��ÿ�д���
			nWords += CountWordsInOneLine(carrBuffer);
		}
	}
	//�ر��ļ�
	fclose(fp);

	return nWords;
}


/*
 *  ��������:
 *		CountWordsInOneLine
 *	���ܣ�ͳ��һ��ŷ�����������дʵĸ���
 *	������const char *szLine һ��ŷ����������
 *	����ֵ��
 *	int ������
 *	ģ����ʷ��
 *	    ���ѷ�����2011.10.26���
 *				2012.10.19�޸ģ��ĺ���������ȷΪͳ��һ���ı��ĵĵ�����
 *		��ҵ����ˣ�����			��ʼʱ�䣺		���ʱ�䣺
 */
int CountWordsInOneLine(const char *szLine)
{
	if (NULL == szLine) return 0;
	
	int nWords = 0;
	char c;
	int status = 2;
	//status��ʾ��ǰ��ȡ��״̬����һ���ַ����ͣ�����ʼ״̬��2����ȡ���ַ�Ϊ1����ȡ�Ŀո�Ϊ0
	while(c = *szLine++)
	{
		if (c == '\0') break;
		
		
		if (status == 2)
		{
			//��ʼ״̬�£������ȡ�Ĳ��ǿո񣬾�nWords++������ͱ�ɿո�״̬
			if (c != ' ' && c != '\t'  && c != '\n')//&& c != '\r'
			{
				nWords++;
				status = 1;
			}
			else
			{
				status = 0;
			}
		}
		else if (status == 1)
		{
			//�ַ�״̬�������ȡ���ǿո񣬱�ɿո�״̬����������������Ҫ�˳���
			if (c == ' ' || c == '\t'  || c == '\n')//|| c == '\r'
			{
				status = 0;
			}
		}
		else if (status == 0)
		{
			//�ո�״̬�£������ȡ�����ַ�����nWords++��ת��״̬���ַ�״̬,���������������˳���
			if (c != ' ' && c != '\t' && c != '\n')// && c != '\r'
			{
				nWords++;
				status = 1;
			}
		}
		else break;
	}
	return nWords;
	
}


/*
 *	��������PrepareBasicInfoOfFiles
 *	���ܣ�׼�������ļ��Ļ�����Ϣ
 *      1. ����ʵ�����ı��ļ��ĸ���
 *      2. ��������ļ�������FILESINFO������Ĵ洢�ռ�
 *      3. �������������ļ���
 *  ������FILESINFO *pFilesInfo���ļ�ͳ����Ϣ�ṹ��ָ��
 *	����ֵ��int
 *       -1   ����������
 *        0   ��������
 *	ģ����ʷ��
 *	    ���ѷ�����2011.10.26���
 *      ���ѷ�����2013.10.11�޸ĺ���˵��
 *		��ҵ����ˣ�����			��ʼʱ�䣺		���ʱ�䣺
 */
int PrepareBasicInfoOfFiles(FILESINFO *pFilesInfo)
{
	//�����ļ�����
	printf("Please input the number of textfiles:");
	scanf("%d", &pFilesInfo->nFileNumber);

	if (pFilesInfo->nFileNumber <= 0) return -1;


	//����ռ䣬û�м�����ݵĺϷ��Ժͷ���ֵ
	if (
		AllocateSpaceForTextFilesInfo(pFilesInfo) != 0
		)
		return -1;
	
	//�����ļ���
	char c;
	while ((c = getchar()) != '\n');//��ջ�����
	printf("Please input the name of textfile name!\n");
	
	for (int i = 0; i < pFilesInfo->nFileNumber; i++)
	{
		scanf("%s", pFilesInfo->pFileInfos[i].szFileName);
	}

	return 0;
}


/*
 *	��������CountFilesInfo
 *	���ܣ�ͳ�Ƹ�����Ϣ
 *		1. ͳ�Ƹ����ļ��е�Ӣ�Ĵʸ���
 *		2. ͳ�Ƹ����ļ��и��������ַ�����
 *	������FILESINFO *pFilesInfo���ļ�ͳ����Ϣ�ṹ��ָ��
 *	����ֵ��int
 *		     0--����
 *         ������������
 *	ģ����ʷ��
 *	    ���ѷ�����2011.10.26���
 *		���ѷ�����2013.10.11�޸ĺ����ӿ�˵���еķ���ֵ˵��
 *		��ҵ����ˣ�����			��ʼʱ�䣺		���ʱ�䣺
 */
int CountFilesInfo(FILESINFO *pFilesInfo)
{
	for (int i = 0; i < pFilesInfo->nFileNumber; i++)
	{
		pFilesInfo->pFileInfos[i].nWords =
			CountWordsOfEuropeanTxtFile(pFilesInfo->pFileInfos[i].szFileName);
		CountDifferentCharactersInFile(&pFilesInfo->pFileInfos[i]);
	}
	return 0;
}


/*
 *	��������CountDifferentCharactersInFile
 *	���ܣ�ͳ�Ƹ����ļ��и����ַ��ĸ���
 *		1. �����ļ���Ϣ�ṹ��ָ��pTextFileInfo���������ļ��������ļ�
 *		2. ˳������ļ��е��ַ���ͳ���и����ַ���
 *		3. �ر��ļ�
 *  ������TEXTFILEINFO *pTextFileInfo
 *	����ֵ��0 �ɹ�  -1 �޷����ļ�
 *	ģ����ʷ��
 *	    ���ѷ�����2011.10.26���
 *	    2013.10.11�����������޸�
 *		��ҵ����ˣ�	����		��ʼʱ�䣺		���ʱ�䣺 
 */
int CountDifferentCharactersInFile(TEXTFILEINFO *pTextFileInfo)
{
	FILE *fp; //�ļ�ָ��
	char c;//������ʱ�洢������ַ�

	//��ʼ������
	pTextFileInfo->nSize = 0;
	pTextFileInfo->nDigits = 0;
	pTextFileInfo->nSpaces = 0;
	pTextFileInfo->nAlphabets = 0;
	pTextFileInfo->nOthers = 0;

	//���ļ�
	if ((fp = fopen(pTextFileInfo->szFileName, "r")) == NULL)
	{
		return -1;	//�ļ��򿪲��ɹ�ʱ����-1
	}

	while ((c = fgetc(fp)) != EOF)
	{
		if (c >= '0' && c <= '9')
		{
			pTextFileInfo->nDigits++;
			pTextFileInfo->nSize++;
		}
		else if (c == ' ' || c == '\n' || c == '\t')// || c == '\r'
		{
			pTextFileInfo->nSpaces++;
			pTextFileInfo->nSize++;
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			pTextFileInfo->nAlphabets++;
			pTextFileInfo->nSize++;
		}
		else
		{
			pTextFileInfo->nOthers++;
			pTextFileInfo->nSize++;
		}
	}

	//�ر��ļ�
	fclose(fp);
	return 0;
}


/*  ��������ExportFilesInfoToWebPage
 *	���ܣ����ļ�ͳ����Ϣ�����һ��HTML�ļ���
 *  ������
 *		FILESINFO *pMyFiles �����ļ���ͳ����Ϣ�ṹ��ָ��
 *		char *szHtmlFile ��ҳ�ļ���
 *  ����ֵ��0�ɹ���-1���޷������ļ�
 *		���ѷ�����2011.10.26���
 *
 */
int ExportFilesInfoToWebPage(FILESINFO *pMyFiles, char *szHtmlFile)
{
	FILE *fp;  //����һ���ļ�ָ��
	int i; //ѭ������

	fp = fopen(szHtmlFile, "w+"); //���ļ�
	if (NULL == fp) //�жϴ��Ƿ�ɹ�
	{
		printf("�޷������ļ���\n");  //���ɹ�
		return -1;
	}
	//��ʼ���ļ���д����
	//����һЩ��Ҫ��html��ʽ����
	fprintf(fp, "<HTML>\n<HEAD>\n<TITLE>�ļ�ͳ�ƽ��</TITLE>\n<meta charset=\"gbk\"></meta>\n</HEAD>");
	fprintf(fp, "<BODY>\n");


	fprintf(fp, "<H4>ʵ��6�ļ���Ϣͳ�ƽ�����£�</H6>\n");

	//����һ�����
	fprintf(fp, "<table border=""2"">\n");
	//��ͷ
	fprintf(fp, "<td>���</td><td>�ļ���</td><td>���ʸ���</td><td>�ļ���С</td>"
		"<td>���ָ���</td><td>�հ��ַ���</td><td>Ӣ���ַ���</td><td>�����ַ���</td>\n");

	//ѭ������ÿһ��
	for (i = 0; i < pMyFiles->nFileNumber; ++i)
	{
		fprintf(fp, "<tr>"); //����һ��

							 //��ÿһ���ļ���ͳ����Ϣ����Ŀ���ַ�����д���ļ���
		fprintf(fp, "<td>%4d</td>"
			"<td>%s</td>"
			"<td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td><td>%d</td>\n",
			i + 1,
			pMyFiles->pFileInfos[i].szFileName,
			pMyFiles->pFileInfos[i].nWords,
			pMyFiles->pFileInfos[i].nSize,
			pMyFiles->pFileInfos[i].nDigits,
			pMyFiles->pFileInfos[i].nSpaces,
			pMyFiles->pFileInfos[i].nAlphabets,
			pMyFiles->pFileInfos[i].nOthers
		);
		fprintf(fp, "</tr>\n");//����һ��
	}
	//����������
	fprintf(fp, "</table>\n");

	fprintf(fp, "<H4>�����ʵ��˶�ͳ�ƽ���Ƿ���ȷ��</H6><BR>\n");
	//�����Ҫ��html������־
	fprintf(fp, "</BODY>\n</HTML>\n");

	fclose(fp); //�ر��ļ�

	return 0;//���سɹ���־
}


/*
 *	��������TestCountFilesInfo
 * 	���ܣ����Ժ���ʵ��7�ļ���Ϣͳ�Ƶ������Ժ���
 *	��������
 *	����ֵ����
 *	ģ����ʷ��
 *		���ѷ�����2011.10.26���
 *		��ҵ����ˣ�����			��ʼʱ�䣺		���ʱ�䣺
 */
void TestCountFilesInfo()
{

	//׼���������ļ���ͳ����Ϣ�Ľṹ�����
	FILESINFO MyFilesInfo;
	char szHtmlFile[120] = "FileInfoResult.html";

	//�ļ�������Ϣ׼��
	PrepareBasicInfoOfFiles(&MyFilesInfo);

	//testcode
	//MyFilesInfo.pFileInfos[0].szFileName = "DataMining.txt";
	//MyFilesInfo.pFileInfos[1].szFileName = "Example.txt";
	//MyFilesInfo.pFileInfos[2].szFileName = "Programing.txt";
	//MyFilesInfo.pFileInfos[3].szFileName = "reality";
	

	//����ͳ�ƺ���
	CountFilesInfo(&MyFilesInfo);


	//��ͳ�ƽ���������Web Page��
	
	ExportFilesInfoToWebPage(&MyFilesInfo, szHtmlFile);

	//����ҳ�ļ�
	
	char pwd[200];
	_getcwd(pwd, sizeof(pwd));
	strcat(pwd, "\\");
	strcat(pwd, szHtmlFile);
	printf("%s", pwd);

	ShowWebPageInIE(pwd);

	return;
}
