/*
TODO:
���ڴ洢������Ӧչʾģ�����ع��ܺͺ���Դ����
*/
#pragma once
#ifndef SCREENSIMLATION_H_
#define SCREENSIMLATION_H_

#include"extern.h"



/*
��������ShowMovieAndImport
���ܣ���ʾ����������̲��������ļ��ĺ���
��������
����ֵ����
*/
int ShowMovieAndImport();

/*
��������ShowMoive
���ܣ���ʾ����������̺���
������
����ֵ����
*/
void ShowMoive();


/*
��������PaintPicture
���ܣ�����ǰʱ�̵��ݻ��Ƴ�ͼ�εĺ���
������
����ֵ����
*/
void PaintPicture();


/*
��������ShowMovieAndImportHISTORY
���ܣ�ͨ����ʷ�����ļ���ʾ����������̲��������ļ��ĺ���
������char HistorySimulateFilesName[]
����ֵ��
1�ɹ�
0 ʧ��
*/
int ShowMovieAndImportHISTORY(char HistorySimulateFilesName[]);

#endif// !SCREENSIMLATION_H_