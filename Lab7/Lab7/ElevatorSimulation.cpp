#include "stdafx.h"
#include "extern.h"

/*
��������SystemInit(��������)
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
int SystemInit() {
	int check_result = 1;
	
	if (access(".\\SysConf",0))
	{
		check_result = 0;
		return check_result;
	}
	
	if (access(".\\SysConf\\SysParam.txt", 0))
	{
		check_result = -1;
		return check_result;
	}
	
	FILE *fp = fopen(".\\SysConf\\SysParam.txt", "r");
	if (fp == NULL)
	{
		check_result = -2;
		return check_result;
	}

	int argument_num = 0;//��������
	param_num = 0;
	fscanf(fp,"%d", &argument_num);

	while (fscanf(fp, "%s %s"
		, &param_array[param_num].param_name
		, &param_array[param_num].param_value) != EOF)
	{
		
		if (strcmp(param_array[param_num].param_name, "UserRequestFilesPath") == 0)
		{
			if ( access(param_array[param_num].param_value, 0) )
			{
				check_result = -3;
				fclose(fp);
				return check_result;
			}
			strcpy(UserRequestFilesPath, param_array[param_num].param_value);
		}

		else if (strcmp(param_array[param_num].param_name, "SimulationFilesPath") == 0)
		{	
			if (access(param_array[param_num].param_value, 0))
			{
				check_result = -4;
				fclose(fp);
				return check_result;
			}
			strcpy(SimulationFilesPath, param_array[param_num].param_value);
		}

		else if (strcmp(param_array[param_num].param_name,"ElevatorHeight") == 0)
		{
			ElevatorHeight = atoi(param_array[param_num].param_value);
			if (ElevatorHeight <= 0)
			{
				check_result = -5;
				fclose(fp);
				return check_result;
			}
		}

		else if (strcmp(param_array[param_num].param_name, "Delaytime") == 0)
		{
			int Delaytime = atoi(param_array[param_num].param_value);
			if (Delaytime <= 0) {
				check_result = -6;
				fclose(fp);
				return check_result;
			}
		}
		param_num++;
	}

	if (param_num == 0)
		check_result = -8;

	if (param_num < argument_num )
		check_result = -7;
		
	fclose(fp);
	return check_result;
}


/*
��������ShowMenu������������
���ܣ���Ҫ����ϵͳ�˵�ʹ��printf������ӡ�����������
չʾ���û�
ʹ���û���ͨ��ϵͳ�˵��˽⵽ϵͳ���ܼ�������Ӧ���ܵķ���
������
menu_flag ��ѡ��Ĳ˵��ţ�1-6��
����ֵ����
*/
void ShowMenu(int menu_flag) {
	if (menu_flag == 1)
	{
		printf("������Ϊһ�����ݷ�����򣬷����������ݵ��������У��ṩ���¹��ܣ�\n");
		printf("1. ָ���û�ָ���ļ�����Ĭ���棨ֻ����������ļ���\n");
		printf("2. ָ���û�ָ���ļ����������棨������������ļ���\n");
		printf("3. ָ���û�ָ���ļ���ȫ����棨����ʾ���������������ļ���\n");
		printf("4.ָ����ʷ�����ļ���������ʽ�ط�\n");
		printf("5.�޸�ϵͳ����\n");
		printf("0. �˳�\n");
		printf("��������Ҫִ�еĹ�����ţ�");
	}
	else if (menu_flag == 2)
	{
		printf("����ǰ���ڡ���Ĭ���桱ģ�飬��ѡ��Ҫ���еĲ�����\n");
		printf("1. �����û�ָ���ļ����ƣ���ʼ��Ĭ����\n");
		printf("0. �����ϼ��˵�\n");
		printf("����������Ҫ���еĲ�����ţ�");
	}
	else if (menu_flag == 3)
	{
		printf("����ǰ���ڡ��������桱ģ�飬��ѡ��Ҫ���еĲ�����\n");
		printf("1. �����û�ָ���ļ����ƣ���ʼ��������\n");
		printf("0. �����ϼ��˵�\n");
		printf("����������Ҫ���еĲ�����ţ�");
	}
	else if (menu_flag == 4)
	{
		printf("����ǰ���ڡ�ȫ����桱ģ�飬��ѡ��Ҫ���еĲ�����\n");
		printf("1. �����û�ָ���ļ����ƣ���ʼȫ�����\n");
		printf("0. �����ϼ��˵�\n");
		printf("����������Ҫ���еĲ�����ţ�");
	}
	else if (menu_flag == 5)
	{
		printf("����ǰ���ڡ���ʷ�����ļ��طš�ģ�飬��ѡ��Ҫ���еĲ�����\n");
		printf("1. ������ʷ�����ļ����ƣ���ʼ����ط�\n");
		printf("0. �����ϼ��˵�\n");
		printf("����������Ҫ���еĲ�����ţ�");
	}
	else if (menu_flag == 6)
	{
		printf("����ǰ���ڡ�ϵͳ�������á�ģ�飬��ѡ��Ҫ���õĲ�����\n");
		printf("1. �����û�ָ���ļ����Ŀ¼\n");
		printf("2. ������ʷ�����ļ����Ŀ¼\n");
		printf("3. ���õ����ܲ���\n");
		printf("4. ���õ��ݶ�������ʱ���ӳ�ϵ��\n");
		printf("0. �����ϼ��˵�\n");
		printf("����������Ҫ���еĲ�����ţ�");
	}

	else
	{
		printf("Menu Argument error!\n");
	}
}

/*
��������SilenceSimulate(����)
���ܣ�����ʵ�־�Ĭ����ģ�鹦��
����Ϊ�û���ӡģ��˵�
�����û�����
�����������ֱ�ӽ�������Ϊ��ʷ�����ļ�
������
����ֵ��
*/
void SilenceSimulate()
{
	int input;
	char UserRequestFilesPathName[200];
	FILE* fp = NULL;
	
loop:while(1)
	{
		ShowMenu(2);
		scanf("%d",&input);
		while (getchar() != '\n');
		if (input == 0) return;
		if (input == 1) break;
		else printf("Input error!\n");
	}
	strcpy(UserRequestFilesPathName, UserRequestFilesPath);
	strcat(UserRequestFilesPathName, "\\");
	
	while(1)
	{
		printf("Please input the name of UserRequestFile��");
		scanf("%s", &user_file_name);
		while (getchar() != '\n');
		strcat(UserRequestFilesPathName, user_file_name);

		if (access(UserRequestFilesPathName, 0))
		{
			printf("No Access File!\n");
			continue;
		}
		InitSimulation();
		fp = fopen(UserRequestFilesPathName, "r");
		if (fp == NULL)
		{
			printf("Can't Open This File!\n");
			continue;
		}


		
		if (LoadUserCallArray(fp))
		{	
			if (OutputSimulationResult())
			{
				return;
			}
			else
			{
				goto loop;
			}
		}
		else
		{
			printf("Can't Load UserRequestFile!\n");
			goto loop;
		}
	}

}


/*
��������InitSimulation(��������)
���ܣ���ʼ�������������
��������
����ֵ����
*/
void InitSimulation() {
	if (usercall_list != NULL)
	{
		free(usercall_list);
		usercall_list = NULL;
	}
	usercall_list_len = 0;
	finish_call_num = 0;
	if (response_list != NULL)
	{
		while (response_list->head != NULL)
		{
			ResponseListNode *p = response_list->head;
			response_list->head = response_list->head->next_node;
			free(p);
			p = NULL;
		}
	}
	else
	{
		response_list = (RESPONSELISTHEADNODE*)malloc(sizeof(RESPONSELISTHEADNODE));
		if (response_list == NULL) printf("Can't Ollocate Memory!\n");
	}

	response_list->head = NULL;
	response_list->tail = NULL;
	response_list->list_num = 0;
	response_list->Responsed_num = 0;

	InitElevator(&elevator_a);
	InitElevator(&elevator_b);
}


/*
��������InitElevator(��������)
���ܣ���ʼ������״̬��������
������
ELEVATORSTATE *elevator
����ֵ����
*/
void InitElevator(ELEVATORSTATE *elevator) {
	elevator->current_floor = 1;
	elevator->run_state = 'S';

	while (elevator->serve_list != NULL)
	{
		SERVELISTNODE *p = elevator->serve_list;
		if (p->next_node == NULL)
		{
			elevator->serve_list = NULL;
		}
		else
		{
			elevator->serve_list = p->next_node;
		}
		free(p);
	}
}


/*
��������LoadUserCallArray(��������)
���ܣ��û�ָ������������ݺ���
������
FILE *fp
����ֵ��
1�ɹ�
0ʧ��
*/
int LoadUserCallArray(FILE *fp)
{
	int func_result = 0;
	fscanf(fp, "%d", &usercall_list_len);
	usercall_list = (USERCALL*)malloc(usercall_list_len * sizeof(USERCALL));

	if (usercall_list == NULL) printf("Can't Ollocate Memory!\n");
	
	int item_num = 0;

	while (fscanf(fp,"%d,%d,%d"
		, &usercall_list[item_num].user_floor
		, &usercall_list[item_num].user_target
		, &usercall_list[item_num].call_time
	) != EOF)
	{
		if (usercall_list[item_num].user_target > usercall_list[item_num].user_floor)
			usercall_list[item_num].call_type = 'U';
		else
			usercall_list[item_num].call_type = 'D';
		item_num++;
	}

	if (usercall_list_len == item_num)
	{
		func_result = 1;

		return func_result;
	}
	else
	{
		func_result = 0;
		return func_result;
	}
}




/*
��������MovieSimulate(ûë��)
���ܣ�
����ʵ�ֶ�������ģ�鹦�ܣ�
�������溯�����ڲ��ö����ķ�ʽչ�ֵ��ݷ�����̡�
������
����ֵ����
*/
void MovieSimulate() 
{
	FILE* fp = NULL;
	char UserRequestFilesPathName[200];
loop:while (1)
{
	ShowMenu(3);
	int input;
	scanf("%d", &input);
	while (getchar() != '\n');
	if (input == 0)
	{
		return;
	}
	if (input == 1) break;
	else
	{
		printf("Input Error!\n");
	}
}

	 while (1) {
		 printf("Please input the name of UserRequestFile��");
		 scanf("%s", &user_file_name);
		 while (getchar() != '\n');//������

		 strcpy(UserRequestFilesPathName, UserRequestFilesPath);
		 strcat(UserRequestFilesPathName, "\\");
		 strcat(UserRequestFilesPathName, user_file_name);

		 if (access(UserRequestFilesPathName, 0))
		 {
			 printf("No Access File!\n");
			 continue;
		 }


		 InitSimulation();
		 fp = fopen(UserRequestFilesPathName, "r");
		 if (fp == NULL)
		 {
			 printf("Can't Open this file!\n");
			 continue;
		 }
		 break;
	 }
	 

	if (LoadUserCallArray(fp))
	{
		ShowMoive();
		return;
	}
	else goto loop;
}



/*
��������FullSimulate
���ܣ��û�ʵ��ȫ�����ģ�鹦��
���ö������з������չʾ��ͬʱ�����������浽����ļ���ȥ
������
����ֵ����
*/
void FullSimulate() {
	int input;
	char UserRequestFilesPathName[200];
	FILE* fp = NULL;

loop:while (1)
{
	ShowMenu(4);
	scanf("%d", &input);
	while (getchar() != '\n');
	if (input == 0) return;
	if (input == 1) break;
	else printf("input error!\n");
}
	 strcpy(UserRequestFilesPathName, UserRequestFilesPath);
	 strcat(UserRequestFilesPathName, "\\");

	 while (1)
	 {
		 printf("Please input the name of UserRequestFile��");
		 scanf("%s", &user_file_name);
		 while (getchar() != '\n');
		 strcat(UserRequestFilesPathName, user_file_name);

		 if (access(UserRequestFilesPathName, 0))
		 {
			 printf("No Access File!\n");
			 continue;
		 }
		 InitSimulation();
		 fp = fopen(UserRequestFilesPathName, "r");
		 if (fp == NULL)
		 {
			 printf("Can't Open This File!\n");
			 continue;
		 }



		 if (LoadUserCallArray(fp))
		 {
			 if (ShowMovieAndImport())
			 {
				 return;
			 }
			 else
			 {
				 goto loop;
			 }
		 }
		 else
		 {
			 printf("Can't Load UserRequestFile!\n");
			 goto loop;
		 }
	 }

}


/*
��������HistorySimulate
���ܣ�����ʵ����ʷ����ط�ģ�鹦�ܣ������û���ʷ�����ļ����ö����ķ�ʽ�����ݷ������չʾ����
��������
����ֵ����
*/
void HistorySimulate() {
	int input;
	char HistorySimulateFilesPathName[200];
	char HistorySimulateFilesName[100];
	FILE* fp = NULL;
loop: while (1)
{
	ShowMenu(5);
	scanf("%d", &input);
	while (getchar() != '\n');//��ջ�����
	if (input == 0) return;
	if (input == 1) break;
	else printf("Input Error!\n");
}
	  while (1) {
		  printf("��������ʷ�����ļ�����");
		  scanf("%s", HistorySimulateFilesName);
		  while (getchar() != '\n');
		  strcpy(HistorySimulateFilesPathName, SimulationFilesPath);
		  strcat(HistorySimulateFilesPathName, "//");
		  strcat(HistorySimulateFilesPathName, HistorySimulateFilesName);
		  
		  if (access(HistorySimulateFilesPathName, 0))
		  {
			  printf("No Access File!\n");
			  continue;
		  }

		  InitSimulation();

		  fp = fopen(HistorySimulateFilesPathName, "r");
		  
		  if (fp == NULL)
		  {
			  printf("Can't Open this File!\n");
			  continue;
		  }
		  break;
	  }

	   //������1LoadUserCallArray
	   fscanf(fp, "%d", &usercall_list_len);
	   usercall_list = (USERCALL*)malloc(usercall_list_len * sizeof(USERCALL));
	   if (usercall_list == NULL)
	   {
		   printf("Can't Ollocate Memory!\n\n"); 
		   return;
	   }

	   int item_num = 0;
	   while (item_num < usercall_list_len)
	   {
		   fscanf(fp, "%d,%d,%d"
			   , &usercall_list[item_num].user_floor
			   , &usercall_list[item_num].user_target
			   , &usercall_list[item_num].call_time);

		   if (usercall_list[item_num].user_target > usercall_list[item_num].user_floor)
			   usercall_list[item_num].call_type = 'U';
		   else
			   usercall_list[item_num].call_type = 'D';
		   item_num++;
	   }
	   char temp[200];
	   fscanf(fp, "%s", temp);
	   //������1����

	   //������2LoadParam
	   int param_len;
	   fscanf(fp, "%d", &param_len);
	   int param_num = 0;

	   char param[200];
	   char value[200];

	   while (param_num < param_len)
	   {
		   fscanf(fp, "%s %s", param, value);

		   if (strcmp(param, "ElevatorHeight") == 0)
		   {
			   ElevatorHeight = atoi(value);
		   }
		   if (strcmp(param, "ElevatorSpeed") == 0);
		   {
			   ElevatorSpeed = atoi(value);
		   }
		   if (strcmp(param, "SimulateSpeed") == 0)
		   {
			   SimulateSpeed = atoi(value);
			   //�������ʱ�����Լ����ӵ�
			   //�ļ���û��д��ȫ�ֱ���ElevatorSpeed��ElevatorSpeed
			   Delaytime = SimulateSpeed;
		   }
		   param_num++;
	   }
	   fscanf(fp, "%s", temp);
	   //������2����


	   ShowMovieAndImportHISTORY(HistorySimulateFilesName);

	   return;
	   
}

/*
���������������ú���
���ܣ�
���ȶ�ģ��˵��߼��Ŀ��ƺͶ��û�����������
��������
����ֵ����
*/
void ParamConf()
{
	while (1)
	{
		ShowMenu(1);
		int input;
		scanf("%d", &input);
		while (getchar() != '\n');
		if (input == 1)
		{
			while (1) {
				printf("Current Path:%s\n", UserRequestFilesPath);
				printf("Please input the new path:");
				scanf("%s", UserRequestFilesPath);
				while (getchar() != '\n');
				if (access(UserRequestFilesPath, 0))
				{
					printf("No Access File!\n");
				}
				else break;
			}
		}
		else if (input == 2)
		{
			while (1) {
				printf("Current Path:%s\n", SimulationFilesPath);
				printf("Please input the new path:");
				scanf("%s", SimulationFilesPath);
				while (getchar() != '\n');
				if (access(SimulationFilesPath, 0))
				{
					printf("No Access File!\n");
				}
				else break;
			}
		}
		else if (input == 3)
		{
			while (1) {
				printf("Elevator Height:%d\n", ElevatorHeight);
				printf("Please input the new Elevator Height:");
				scanf("%d", &ElevatorHeight);
				while (getchar() != '\n');
				if (ElevatorHeight <= 0)
				{
					printf("Input illegal!\n");
				}
				else break;
			}
		}
		else if (input == 4)
		{
			while (1) {
				printf("Delay Time:%d\n", Delaytime);
				printf("Please input the new Delaytime:");
				scanf("%d", &Delaytime);
				while (getchar() != '\n');
				if (Delaytime <= 0)
				{
					printf("Input illegal!\n");
				}
				else break;
			}
		}
		else if (input == 0)
		{
			return;
		}
		else
		{
			printf("Input Error!\n");
		}
	}
}




