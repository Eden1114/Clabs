/*
TODO:
用于存储电梯响应计算模块的相关功能和函数源代码。
*/
#pragma once
#ifndef RESPONSECALCULATE_H_
#define RESPONSECALCULATE_H_
#include "extern.h"

/*
函数名：GetNextTimeStatus
功能：计算电梯下一时刻状态的函数
参数：
ELEVATORSTATE  *elevator
返回值：无
*/
void  GetNextTimeStatus(ELEVATORSTATE  *elevator);




/*
函数名：FindUserCallCanServe
功能：处理当前电梯是否可以同时响应其它用户指令的函数
参数：
ELEVATORSTATE  *elevator
char r_state
返回值：无
*/
void  FindUserCallCanServe(ELEVATORSTATE  *elevator, char r_state);


/*
函数名：GetElevatorDirection
功能：电梯在服务过程中处于停止状态时判断其上下行状态的函数
参数：
ELEVATORSTATE *elevator
返回值：
*/
char  GetElevatorDirection(ELEVATORSTATE  *elevator);


/*
函数名：SetElevatorState
功能：将电梯状态修改为下一时刻状态的函数
参数：
ELEVATORSTATE *elevator
返回值：无
*/
void  SetElevatorState(ELEVATORSTATE  *elevator);

#endif // !RESPONSECALCULATE_H_
