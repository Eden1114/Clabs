#pragma once
//extern 全局变量
extern double m;//画布宽
extern double n;//画布长
extern USERCALL *usercall_list;//用户指令数组首地址，数组根据用户指令多少动态生成
extern int usercall_list_len;//用户指令数组长度，从用户指令文件第一行读出
extern SYSPARAM param_array[100];//系统参数数组
extern int param_num;
extern struct Elevatorstate elevator_a;//用于存放电梯a状态的结构体
extern struct Elevatorstate elevator_b;//用于存放电梯b状态的结构体
extern RESPONSELISTHEADNODE *response_list;// 电梯响应指令队列，用于指示当前响应的电梯指令


extern char user_file_name[100];//用户存放‘用户指令文件’名称的数组
extern char simulate_file_name[100];//用户存放‘历史仿真文件’名称的数组
extern int finish_call_num;//用于记录当前已响应完成的用户指令个数
extern int time;//用于记录当前仿真时刻
extern int status_change_flag;//用于记录下一时刻相较于当前状态是否改变，1变，0不变

							  //6个系统参数
extern char UserRequestFilesPath[150];//存放用户指令文件的目录，默认*
extern char SimulationFilesPath[150];//存放用户历史仿真文件的目录，默认*
extern int ElevatorHeight;//电梯总层数，默认20
extern int Delaytime; //动画展示每个状态仿真的延迟时间，单位ms，默认1000
extern int ElevatorSpeed;
extern int SimulateSpeed;