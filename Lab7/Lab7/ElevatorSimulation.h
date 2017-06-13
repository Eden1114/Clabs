/*
TODO:
用于存储系统主控模块的相关功能和函数源代码
包括，系统主函数，自检函数，裁剪逻辑等
*/
#pragma once
#ifndef ELEVATORSIMLATION_H_
#define ELEVATORSIMLATION_H_
#include"extern.h"

/*
函数名：SystemInit
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
int SystemInit();


/*
函数名：ShowMenu
功能：主要负责将系统菜单使用printf函数打印输出到界面上
展示给用户
使得用户可通过系统菜单了解到系统功能及调用相应功能的方法
参数：
menu_flag 所选择的菜单号（1-6）
返回值：无
*/
void ShowMenu(int menu_flag);

/*
函数名：SilenceSimulate
功能：用于实现静默仿真模块功能，
	函数为用户打印模块菜单
	接收用户输入
	计算仿真结果并直接将结果输出为历史仿真文件
参数：
返回值：
*/
void SilenceSimulate();

/*
函数名：MovieSimulate
功能：用于实现静默仿真模块功能，
	函数为用户打印模块菜单
	接收用户输入
	计算仿真结果并直接将结果输出为历史仿真文件
参数：
返回值：无
*/
void MovieSimulate();


/*
函数名：FullSimulate
功能：用户实现全面仿真模块功能
	采用动画进行仿真过程展示的同时将仿真结果保存到结果文件中去
参数：
返回值：无
*/
void FullSimulate();

/*
函数名：HistorySimlate
功能：用于实现历史仿真回放模块功能，读入用户历史仿真文件，用动画的方式将电梯服务过程展示出来
参数：无
返回值：无
*/
void HistorySimulate();




/*
函数名：InitSimulation
功能：初始化仿真变量函数
参数：无
返回值：无
*/
void InitSimulation();

/*
函数名：InitElevator
功能：初始化电梯状态变量函数
参数：
ELEVATORSTATE *elevator
返回值：无
*/
void InitElevator(ELEVATORSTATE *elevator);

/*
函数名：LoadUserCallArray
功能：用户指令数组加载数据函数
参数：
FILE *fp
返回值：
*/
int LoadUserCallArray(FILE *fp);



/*
函数名：ImportUserCall
功能：将用户指令写入仿真结果文件的函数
参数：
FILE *fp
返回值：无
*/
void ImportUserCall(FILE *fp);

/*
函数名：ImportSimulateParam
功能：将仿真参数写入仿真结果文件的函数
参数：
FILE *fp;
返回值：无
*/
void ImportSimulateParam(FILE *fp);



/*
函数名：参数配置函数
功能：
事先对模块菜单逻辑的控制和对用户参数的配置
参数：无
返回值：无
*/
void ParamConf();



#endif