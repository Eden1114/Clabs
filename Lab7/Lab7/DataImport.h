/*
TODO:
ϵͳ���ݽ���ģ��
�û�ָ���ļ��Ķ�ȡ��
��ʷ�����ļ��Ķ�ȡ
ϵͳ�����ļ��Ķ�ȡ��
*/
#pragma once
#ifndef DATAIMPORT_H_
#define DATAIMPORT_H_
#include"extern.h"
#include "stdafx.h"





/*
��������ImportSimulateResult
���ܣ������ݵ�ǰʱ��״̬д��������ļ��ĺ���
������
FILE  *fp
����ֵ����
*/
void  ImportSimulateResult(FILE  *fp);


/*
��������ImportSimulateParam
���ܣ����������д��������ļ��ĺ���
������
FILE *fp;
����ֵ����
*/
void ImportSimulateParam(FILE *fp);


/*
��������ImportUserCall
���ܣ����û�ָ��д��������ļ��ĺ���
������
FILE *fp
����ֵ����
*/
void ImportUserCall(FILE *fp);

#endif// !DATAIMPORT_H_