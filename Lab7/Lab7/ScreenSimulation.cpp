/*
TODO:
���ڴ洢������Ӧչʾģ�����ع��ܺͺ���Դ����
*/
#include "stdafx.h"
#include "extern.h"




/*
��������ShowMovieAndImport
���ܣ���ʾ����������̲��������ļ��ĺ���
��������
����ֵ��
1�ɹ�
0 ʧ��
*/
int ShowMovieAndImport()
{
	int func_result = 0;
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

	initgraph(m,n);

	while (finish_call_num != usercall_list_len)
	{
		status_change_flag = 0;
		PaintPicture();
		GetNextTimeStatus(&elevator_a);
		GetNextTimeStatus(&elevator_b);
		if (status_change_flag == 1)
		{
			ImportSimulateResult(fp);
		}
		time++;
		Sleep(Delaytime);
	}
	PaintPicture();
	getch();
	closegraph();
	fclose(fp);
	func_result = 1;
	return func_result;
	//TODO:ע��·�����ļ����ڵ���ʱҪע��
}



/*
��������ShowMoive
���ܣ���ʾ����������̺���
������
����ֵ����
*/
void ShowMoive()
{
	time = 0;
	initgraph(m, n);
	while (finish_call_num != usercall_list_len)
	{
		PaintPicture();
		Sleep(1000);
		GetNextTimeStatus(&elevator_a);
		GetNextTimeStatus(&elevator_b);
		time++;
		
	}
	PaintPicture();
	getch();
	closegraph();
	return;
}


/*
��������PaintPicture
���ܣ�����ǰʱ�̵��ݻ��Ƴ�ͼ�εĺ���
������
����ֵ����
*/
void PaintPicture()
{
	cleardevice();
	for (int i = 1; i < ElevatorHeight + 1; i++)
	{
		rectangle(m / 20, i * n / (ElevatorHeight + 2), m * 7 / 20, (i + 1) * n / (ElevatorHeight + 2));
		TCHAR str[20];
		_stprintf(str, _T("%d"), ElevatorHeight + 1 - i);
		outtextxy(m / 50, i*n / (ElevatorHeight + 2) + n / 24, str);
	}
	//10��¥��ͱ��

	setfillcolor(LIGHTBLUE);

	solidrectangle(2 * m / 20,
		(ElevatorHeight + 1 - elevator_a.current_floor)*n / 12 + n/100
		, 3.5 * m / 20
		, (ElevatorHeight + 1 - elevator_a.current_floor + 1)*n / 12 - n/100);//elevator_a

	solidrectangle(4.5 * m / 20
		, (ElevatorHeight + 1 - elevator_b.current_floor)*n / 12 + n/100
		, 6 * m / 20
		, (ElevatorHeight + 1 - elevator_b.current_floor + 1)*n / 12 - n/100);//elevator_b


	RECT a_current_floor = { m * 8 / 20, n / 12, m * 13 / 20, n * 2 / 12 };
	RECT a_run_state = { m * 8 / 20, n * 2 / 12, m * 13 / 20, n * 3 / 12 };
	RECT a_serve_head = { m * 8 / 20, n * 3 / 12, m * 13 / 20, n * 4 / 12 };
	RECT a_serve_list = { m * 8 / 20, n * 4 / 12, m * 13 / 20, n * 7 / 12 };

	RECT b_current_floor = { m * 14 / 20, n / 12, m * 19 / 20, n * 2 / 12 };
	RECT b_run_state = { m * 14 / 20, n * 2 / 12, m * 19 / 20, n * 3 / 12 };
	RECT b_serve_head = { m * 14 / 20, n * 3 / 12, m * 19 / 20, n * 4 / 12 };
	RECT b_serve_list = { m * 14 / 20, n * 4 / 12, m * 19 / 20, n * 7 / 12 };

	
	
	RECT c_response_list = { m * 8 / 20, n * 17 / 24, m * 19 / 20, n * 23 / 24 };
	RECT c_time = { m * 8 / 20, n * 16 / 24,n * 19 / 20,n * 17 / 24 };
		
	roundrect(m * 15 / 40, n / 24, m * 26 / 40, n * 15 / 24, 30, 30);
	roundrect(m * 27 / 40, n / 24, m * 38 / 40, n * 15 / 24, 30, 30);
	roundrect(m * 15 / 40, n * 15 / 24, m * 38 / 40, n * 23 / 24, 30, 30);
	
	TCHAR  str_temp1[80];
	_stprintf(str_temp1, _T("A���ݵ�ǰ¥�㣺%d"), elevator_a.current_floor);
	drawtext(str_temp1, &a_current_floor, DT_TOP | DT_LEFT );
	
	TCHAR  str_temp2[80];
	_stprintf(str_temp2, _T("A���ݵ�ǰ״̬��%c"), elevator_a.run_state);
	drawtext(str_temp2, &a_run_state, DT_TOP | DT_LEFT);
	
	TCHAR str_temp3[80];
	_stprintf(str_temp3, _T("A���ݷ���ָ�"));
	drawtext(str_temp3, &a_serve_head, DT_TOP | DT_LEFT);

	TCHAR  str_temp4[80];
	_stprintf(str_temp4, _T("B���ݵ�ǰ¥�㣺%d"), elevator_b.current_floor);
	drawtext(str_temp4, &b_current_floor, DT_TOP | DT_LEFT);

	TCHAR  str_temp5[80];
	_stprintf(str_temp5, _T("B���ݵ�ǰ״̬��%c"), elevator_b.run_state);
	drawtext(str_temp5, &b_run_state, DT_TOP | DT_LEFT);

	TCHAR str_temp6[80];
	_stprintf(str_temp6, _T("B���ݷ���ָ�"));
	drawtext(str_temp6, &b_serve_head, DT_TOP | DT_LEFT);
	
	TCHAR str_temp7[300];
	str_temp7[0] = '\0';
	SERVELISTNODE *tp = elevator_a.serve_list;
	while (tp != NULL)
	{

		_stprintf(str_temp7, _T("�û�¥�㣺%d\nĿ��¥�㣺%d\n����״̬��%c\n")
			, tp->user_call->user_floor
			, tp->user_call->user_target
			, tp->serve_state);
		tp = tp->next_node;
	}
	drawtext(str_temp7, &a_serve_list, DT_TOP | DT_LEFT | DT_WORD_ELLIPSIS);

	TCHAR str_temp8[150];
	str_temp8[0] = '\0';
	tp = elevator_b.serve_list;
	while (tp != NULL)
	{
		_stprintf(str_temp8, _T("�û�¥�㣺%d\nĿ��¥�㣺%d\n����״̬��%c\n")
			, tp->user_call->user_floor
			, tp->user_call->user_target
			, tp->serve_state);
		tp = tp->next_node;
	}
	drawtext(str_temp8, &b_serve_list, DT_TOP | DT_LEFT | DT_WORD_ELLIPSIS);


	TCHAR str_temp9[10];
	_stprintf(str_temp9, _T("��ǰʱ��:%d"), time);
	drawtext(str_temp9, &c_time, DT_TOP | DT_LEFT | DT_WORD_ELLIPSIS);

	RESPONSELISTNODE *rtp = response_list->head;

	TCHAR str_temp10[300];
	str_temp10[0] = '\0';
	while (rtp != NULL)
	{
		_stprintf(str_temp10
			, _T("ָ�����:%d  �û�¥�㣺%d  �û�Ŀ��¥�㣺%d  ָ������:%c\n")
			, rtp->usercall_index + 1
			, usercall_list[rtp->usercall_index].user_floor
			, usercall_list[rtp->usercall_index].user_target
			, usercall_list[rtp->usercall_index].call_type
		);
		rtp = rtp->next_node;
	}
	drawtext(str_temp10, &c_response_list, DT_TOP | DT_LEFT | DT_WORDBREAK);
	return;
}

/*
��������ShowMovieAndImportHISTORY
���ܣ�ͨ����ʷ�����ļ���ʾ����������̲��������ļ��ĺ���
������char HistorySimulateFilesName[]
����ֵ��
1�ɹ�
0 ʧ��
*/
int ShowMovieAndImportHISTORY(char HistorySimulateFilesName[])
{
	int func_result = 0;
	char simulationFiles[200];

	strcpy(simulationFiles, SimulationFilesPath);
	strcat(simulationFiles, "\\");
	strcat(simulationFiles, HistorySimulateFilesName);
	int temp = strlen(simulationFiles);
	simulationFiles[temp - 4] = '\0';
	strcat(simulationFiles, "simsResult.txt");

	FILE* fp = fopen(simulationFiles, "w");
	if (fp == NULL)
	{
		func_result = 0;
		return func_result;
	}
	ImportUserCall(fp);
	ImportSimulateParam(fp);
	time = 0;

	initgraph(m, n);

	while (finish_call_num != usercall_list_len)
	{
		status_change_flag = 0;
		PaintPicture();
		GetNextTimeStatus(&elevator_a);
		GetNextTimeStatus(&elevator_b);
		if (status_change_flag == 1)
		{
			ImportSimulateResult(fp);
		}
		time++;
		Sleep(Delaytime);
	}
	PaintPicture();
	getch();
	closegraph();
	fclose(fp);
	func_result = 1;
	return func_result;
}