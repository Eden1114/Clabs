/*
TODO:
���ڴ洢ϵͳ����ģ�����ع��ܺͺ���Դ����
������ϵͳ���������Լ캯�����ü��߼���
*/
#pragma once
#ifndef ELEVATORSIMLATION_H_
#define ELEVATORSIMLATION_H_
#include"extern.h"

/*
��������SystemInit
���ܣ�����ϵͳ���������ļ�����ϵͳ�����ڶ��������У���ļ�Ŀ¼�������ļ�������������ֵ����ȷ��
��������
����ֵ��
1	�Լ�����
0	�Լ��Ҳ���SysConfĿ¼
-1	�Ҳ���SysConfĿ¼�µ�SysParam.txt
-2	SysParam.txt��ʧ��
-3	�û��Զ���Ĵ���û�ָ���ļ�Ŀ¼������
-4	�û��Զ���Ĵ����ʷ�����ļ�Ŀ¼������
-5	����¥���������
-6	���ݶ��������ӳٲ�������
-7	ʵ�ʶ�����ϵͳ�����������ļ���һ�������Ĳ�����������
-8	�Ӳ����ļ���û���ҵ��κ�ϵͳ����Ĳ���
*/
int SystemInit();


/*
��������ShowMenu
���ܣ���Ҫ����ϵͳ�˵�ʹ��printf������ӡ�����������
չʾ���û�
ʹ���û���ͨ��ϵͳ�˵��˽⵽ϵͳ���ܼ�������Ӧ���ܵķ���
������
menu_flag ��ѡ��Ĳ˵��ţ�1-6��
����ֵ����
*/
void ShowMenu(int menu_flag);

/*
��������SilenceSimulate
���ܣ�����ʵ�־�Ĭ����ģ�鹦�ܣ�
	����Ϊ�û���ӡģ��˵�
	�����û�����
	�����������ֱ�ӽ�������Ϊ��ʷ�����ļ�
������
����ֵ��
*/
void SilenceSimulate();

/*
��������MovieSimulate
���ܣ�����ʵ�־�Ĭ����ģ�鹦�ܣ�
	����Ϊ�û���ӡģ��˵�
	�����û�����
	�����������ֱ�ӽ�������Ϊ��ʷ�����ļ�
������
����ֵ����
*/
void MovieSimulate();


/*
��������FullSimulate
���ܣ��û�ʵ��ȫ�����ģ�鹦��
	���ö������з������չʾ��ͬʱ�����������浽����ļ���ȥ
������
����ֵ����
*/
void FullSimulate();

/*
��������HistorySimlate
���ܣ�����ʵ����ʷ����ط�ģ�鹦�ܣ������û���ʷ�����ļ����ö����ķ�ʽ�����ݷ������չʾ����
��������
����ֵ����
*/
void HistorySimulate();




/*
��������InitSimulation
���ܣ���ʼ�������������
��������
����ֵ����
*/
void InitSimulation();

/*
��������InitElevator
���ܣ���ʼ������״̬��������
������
ELEVATORSTATE *elevator
����ֵ����
*/
void InitElevator(ELEVATORSTATE *elevator);

/*
��������LoadUserCallArray
���ܣ��û�ָ������������ݺ���
������
FILE *fp
����ֵ��
*/
int LoadUserCallArray(FILE *fp);



/*
��������ImportUserCall
���ܣ����û�ָ��д��������ļ��ĺ���
������
FILE *fp
����ֵ����
*/
void ImportUserCall(FILE *fp);

/*
��������ImportSimulateParam
���ܣ����������д��������ļ��ĺ���
������
FILE *fp;
����ֵ����
*/
void ImportSimulateParam(FILE *fp);



/*
���������������ú���
���ܣ�
���ȶ�ģ��˵��߼��Ŀ��ƺͶ��û�����������
��������
����ֵ����
*/
void ParamConf();



#endif