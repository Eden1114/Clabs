/*
TODO:
���ڴ洢��Ӧ����洢ģ�����ع���
����
����Ӧ�������洢����ʷ�����ļ�
��ϵͳ���ò���д��ϵͳ�����ļ�
*/
#pragma once
#include "stdafx.h"
#include "extern.h"


/*
��������OutputSimulationResult
���ܣ���������������Ϊ����ļ��ĺ���
������
��
����ֵ��
1�ɹ�
0δ�ܴ��ļ�
*/
int OutputSimulationResult()
{
	int func_result = 1;
	char simulationFiles[200];
	
		strcpy(simulationFiles, SimulationFilesPath);
		strcat(simulationFiles, "\\");
		strcat(simulationFiles, user_file_name);
		int temp = strlen(simulationFiles);
		simulationFiles[temp - 4] = '\0';
		strcat(simulationFiles, "simeResult.txt");

	FILE* fp = fopen(simulationFiles, "w");
	if (fp == NULL)
	{
		func_result = 0;
		return func_result;
	}
	ImportUserCall(fp);
	ImportSimulateParam(fp);
	time = 0;

	while (finish_call_num != usercall_list_len)
	{
		status_change_flag = 0;

		GetNextTimeStatus(&elevator_a);
		GetNextTimeStatus(&elevator_b);

		if (status_change_flag == 1 || time == 0)
		{
			ImportSimulateResult(fp);
		}

		time++;
	}
	
	fclose(fp);
	return func_result;
}