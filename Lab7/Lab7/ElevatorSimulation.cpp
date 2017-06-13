#include "stdafx.h"
#include "extern.h"

/*
函数名：SystemInit(调试正常)
功能：负责将系统参数配置文件读入系统，并在读入过程中校验文件目录、配置文件、参数及参数值的正确性
参数：无
返回值：
1	自检无误
0	自检找不到SysConf目录
-1	找不到SysConf目录下的SysParam.txt
-2	SysParam.txt打开失败
-3	用户自定义的存放用户指令文件目录不存在
-4	用户自定义的存放历史仿真文件目录不存在
-5	电梯楼层参数有误
-6	电梯动画仿真延迟参数有误
-7	实际读出的系统参数个数与文件第一行申明的参数个数不符
-8	从参数文件中没有找到任何系统定义的参数
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

	int argument_num = 0;//参数个数
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
函数名：ShowMenu（调试正常）
功能：主要负责将系统菜单使用printf函数打印输出到界面上
展示给用户
使得用户可通过系统菜单了解到系统功能及调用相应功能的方法
参数：
menu_flag 所选择的菜单号（1-6）
返回值：无
*/
void ShowMenu(int menu_flag) {
	if (menu_flag == 1)
	{
		printf("本程序为一个电梯仿真程序，仿真两部电梯的联动运行，提供如下功能：\n");
		printf("1. 指定用户指令文件，静默仿真（只输出仿真结果文件）\n");
		printf("2. 指定用户指令文件，动画仿真（不输出仿真结果文件）\n");
		printf("3. 指定用户指令文件，全面仿真（即显示动画，又输出结果文件）\n");
		printf("4.指定历史仿真文件，动画形式回放\n");
		printf("5.修改系统参数\n");
		printf("0. 退出\n");
		printf("请输入您要执行的功能序号：");
	}
	else if (menu_flag == 2)
	{
		printf("您当前处于“静默仿真”模块，请选择要进行的操作：\n");
		printf("1. 输入用户指令文件名称，开始静默仿真\n");
		printf("0. 返回上级菜单\n");
		printf("请输入您需要进行的操作序号：");
	}
	else if (menu_flag == 3)
	{
		printf("您当前处于“动画仿真”模块，请选择要进行的操作：\n");
		printf("1. 输入用户指令文件名称，开始动画仿真\n");
		printf("0. 返回上级菜单\n");
		printf("请输入您需要进行的操作序号：");
	}
	else if (menu_flag == 4)
	{
		printf("您当前处于“全面仿真”模块，请选择要进行的操作：\n");
		printf("1. 输入用户指令文件名称，开始全面仿真\n");
		printf("0. 返回上级菜单\n");
		printf("请输入您需要进行的操作序号：");
	}
	else if (menu_flag == 5)
	{
		printf("您当前处于“历史仿真文件回放”模块，请选择要进行的操作：\n");
		printf("1. 输入历史仿真文件名称，开始仿真回放\n");
		printf("0. 返回上级菜单\n");
		printf("请输入您需要进行的操作序号：");
	}
	else if (menu_flag == 6)
	{
		printf("您当前处于“系统参数配置”模块，请选择要配置的参数：\n");
		printf("1. 配置用户指令文件存放目录\n");
		printf("2. 配置历史仿真文件存放目录\n");
		printf("3. 配置电梯总层数\n");
		printf("4. 配置电梯动画仿真时的延迟系数\n");
		printf("0. 返回上级菜单\n");
		printf("请输入您需要进行的操作序号：");
	}

	else
	{
		printf("Menu Argument error!\n");
	}
}

/*
函数名：SilenceSimulate(正常)
功能：用于实现静默仿真模块功能
函数为用户打印模块菜单
接收用户输入
计算仿真结果并直接将结果输出为历史仿真文件
参数：
返回值：
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
		printf("Please input the name of UserRequestFile：");
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
函数名：InitSimulation(调试正常)
功能：初始化仿真变量函数
参数：无
返回值：无
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
函数名：InitElevator(调试正常)
功能：初始化电梯状态变量函数
参数：
ELEVATORSTATE *elevator
返回值：无
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
函数名：LoadUserCallArray(调试正常)
功能：用户指令数组加载数据函数
参数：
FILE *fp
返回值：
1成功
0失败
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
函数名：MovieSimulate(没毛病)
功能：
用于实现动画仿真模块功能，
动画仿真函数用于采用动画的方式展现电梯仿真过程。
参数：
返回值：无
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
		 printf("Please input the name of UserRequestFile：");
		 scanf("%s", &user_file_name);
		 while (getchar() != '\n');//缓冲区

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
函数名：FullSimulate
功能：用户实现全面仿真模块功能
采用动画进行仿真过程展示的同时将仿真结果保存到结果文件中去
参数：
返回值：无
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
		 printf("Please input the name of UserRequestFile：");
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
函数名：HistorySimulate
功能：用于实现历史仿真回放模块功能，读入用户历史仿真文件，用动画的方式将电梯服务过程展示出来
参数：无
返回值：无
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
	while (getchar() != '\n');//清空缓冲区
	if (input == 0) return;
	if (input == 1) break;
	else printf("Input Error!\n");
}
	  while (1) {
		  printf("请输入历史仿真文件名：");
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

	   //子流程1LoadUserCallArray
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
	   //子流程1结束

	   //子流程2LoadParam
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
			   //下面这句时根据自己理解加的
			   //文件里没有写有全局变量ElevatorSpeed和ElevatorSpeed
			   Delaytime = SimulateSpeed;
		   }
		   param_num++;
	   }
	   fscanf(fp, "%s", temp);
	   //子流程2结束


	   ShowMovieAndImportHISTORY(HistorySimulateFilesName);

	   return;
	   
}

/*
函数名：参数配置函数
功能：
事先对模块菜单逻辑的控制和对用户参数的配置
参数：无
返回值：无
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




