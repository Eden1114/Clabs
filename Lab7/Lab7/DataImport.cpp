/*
TODO:
系统数据接入模块
用户指令文件的读取，
历史仿真文件的读取
系统配置文件的读取。
*/
#pragma once
#include "stdafx.h"
#include "extern.h"


/*
函数名：ImportSimulateResult
功能：将电梯当前时刻状态写入仿真结果文件的函数
参数：
FILE  *fp
返回值：无
*/
void  ImportSimulateResult(FILE  *fp)
{
	FILE* p = fp;
	fseek(p, 0, SEEK_END);
	fprintf(p, "%d,A,%d,%c,B,%d,%c;"
		, time
		, elevator_a.current_floor
		, elevator_a.run_state
		, elevator_b.current_floor
		, elevator_b.run_state);
	/*
	RESPONSELISTNODE *sp =  response_list->head;
	while (sp != response_list->tail)
	{
		fprintf(p, "<%d,%d,%d,"
			, sp->usercall_index
			, usercall_list[sp->usercall_index].user_floor
			, usercall_list[sp->usercall_index].user_target
		);
		if (&usercall_list[sp->usercall_index] == elevator_a.serve_list->user_call)
		{
			fprintf(p, "%c,A>",elevator_a.serve_list->serve_state);
		}

		else if (&usercall_list[sp->usercall_index] == elevator_b.serve_list->user_call)
		{
			fprintf(p, "%c,B>", elevator_b.serve_list->serve_state);
		}

		else
		{
			fprintf(p, "N,N>");
		}
		
		sp = sp->next_node;
	}
	for (int i = 0; i < usercall_list_len; i++)
	{
		if (elevator_a.serve_list != NULL && &usercall_list[i] == elevator_a.serve_list->user_call)
			

		if (elevator_b.serve_list != NULL && &usercall_list[i] == elevator_b.serve_list->user_call)
			fprintf(fp, "<%d,%d,%d,%c,B>"
				, i + 1, elevator_b.serve_list->user_call->user_floor
				, elevator_b.serve_list->user_call->user_target
				, elevator_b.serve_list->serve_state);
	}
	*/
	SERVELISTNODE *tp = elevator_a.serve_list;
	while (tp != NULL)
	{
		for (int i = 0; i < usercall_list_len; i++)
		{
			if (tp->user_call == &usercall_list[i])
			{
				fprintf(fp, "<%d,%d,%d,%c,A>"
					, i + 1
					, elevator_a.serve_list->user_call->user_floor
					, elevator_a.serve_list->user_call->user_target
					, elevator_a.serve_list->serve_state);
			}

		}
		tp = tp->next_node;
	}
	
	tp = elevator_b.serve_list;

	while (tp != NULL)
	{
		for (int i = 0; i < usercall_list_len; i++)
		{
			if (tp->user_call == &usercall_list[i])
			{
				fprintf(fp, "<%d,%d,%d,%c,B>"
					, i + 1
					, elevator_b.serve_list->user_call->user_floor
					, elevator_b.serve_list->user_call->user_target
					, elevator_b.serve_list->serve_state);
			}
		}
		tp = tp->next_node;
	}
	tp = NULL;
	
	RESPONSELISTNODE *sp = response_list->head;
	while (sp != NULL)
	{
		fprintf(p, "<%d,%d,%d,N,N>"
			, sp->usercall_index + 1
			, usercall_list[sp->usercall_index].user_floor
			, usercall_list[sp->usercall_index].user_target
		);
		sp = sp->next_node;
	}

	fprintf(p, "\n");
}


/*
函数名：ImportSimulateParam
功能：将仿真参数写入仿真结果文件的函数
参数：
FILE *fp;
返回值：无
*/
void ImportSimulateParam(FILE *fp)
{
	FILE* p = fp;
	fseek(p, 0, SEEK_END);
	fprintf(p, "%d\n", param_num - 1);
	fprintf(p, "ElevatorHeight %d\n", ElevatorHeight);
	fprintf(p, "ElevatorSpeed %d\n", ElevatorSpeed);
	fprintf(p, "SimulateSpeed %d\n", SimulateSpeed);
	fprintf(p, "*******************************************************************\n");
}


/*
函数名：ImportUserCall
功能：将用户指令写入仿真结果文件的函数
参数：
FILE *fp
返回值：无
*/
void ImportUserCall(FILE *fp)
{
	//TODO:清空文件已有内容
	fprintf(fp, "%d\n", usercall_list_len);
	for (int i = 0; i < usercall_list_len; i++)
	{
		fprintf(fp, "%d,%d,%d\n"
			, usercall_list[i].user_floor
			, usercall_list[i].user_target
			, usercall_list[i].call_time);
	}
	fprintf(fp, "*******************************************************************\n");
}


