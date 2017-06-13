/*
TODO:
用于存储响应结果存储模块的相关功能
包括
将响应计算结果存储到历史仿真文件
将系统配置参数写入系统配置文件
*/
#pragma once
#include "stdafx.h"
#include "extern.h"


/*
函数名：OutputSimulationResult
功能：计算仿真结果并输出为结果文件的函数
参数：
无
返回值：
1成功
0未能打开文件
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