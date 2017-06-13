#include "stdafx.h"

double m = 640;//画布宽
double n = 480;//画布长
USERCALL *usercall_list = NULL;//用户指令数组首地址，数组根据用户指令多少动态生成
int usercall_list_len;//用户指令数组长度，从用户指令文件第一行读出
SYSPARAM param_array[100];//系统参数数组
int param_num = 0;

struct Elevatorstate elevator_a;//用于存放电梯a状态的结构体
struct Elevatorstate elevator_b;//用于存放电梯b状态的结构体
RESPONSELISTHEADNODE *response_list = NULL;// 电梯响应指令队列，用于指示当前响应的电梯指令

char UserRequestFilesPath[150] = ".\\UserRequestFiles";//存放用户指令文件的目录
char SimulationFilesPath[150] = ".\\SimlationFiles";//存放用户历史仿真文件的目录

char user_file_name[100];//用户存放‘用户指令文件’名称的数组

char simulate_file_name_input[100];//用户存放用于输入‘历史仿真文件’名称的数组

char simulate_file_name_output[100];//用户存放用于输出‘历史仿真文件’名称的数组

int finish_call_num;//用于记录当前已响应完成的用户指令个数
int time;//用于记录当前仿真时刻
int status_change_flag;//用于记录下一时刻相较于当前状态是否改变，1变，0不变

int ElevatorHeight = 20;//电梯总层数，默认20
int Delaytime = 1000; //动画展示每个状态仿真的延迟时间，单位ms，默认1000
int ElevatorSpeed = 1;//
int SimulateSpeed = 1000;//可能是Delaytime


/*
void main()
{
	
}
*/

//调试用
int main() {
	SystemInit();
	while (1) {
		ShowMenu(1);
		int input;
		scanf("%d", &input);
		while (getchar() != '\n');
		if (input == 1)
		{
			SilenceSimulate();
		}
		else if (input == 2)
		{
			MovieSimulate();
		}
		else if (input == 3)
		{
			FullSimulate();
		}
		else if (input == 4)
		{
			HistorySimulate();
		}
		else if (input == 5)
		{
			ParamConf();
		}
		else if (input == 0)
		{
			return 0;
		}
		else
		{
			printf("Input Error!\n");
		}
	}
	return 0;
}
