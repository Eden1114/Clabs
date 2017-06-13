/*
TODO:
系统数据接入模块
用户指令文件的读取，
历史仿真文件的读取
系统配置文件的读取。
*/
#pragma once
#ifndef DATAIMPORT_H_
#define DATAIMPORT_H_
#include"extern.h"
#include "stdafx.h"





/*
函数名：ImportSimulateResult
功能：将电梯当前时刻状态写入仿真结果文件的函数
参数：
FILE  *fp
返回值：无
*/
void  ImportSimulateResult(FILE  *fp);


/*
函数名：ImportSimulateParam
功能：将仿真参数写入仿真结果文件的函数
参数：
FILE *fp;
返回值：无
*/
void ImportSimulateParam(FILE *fp);


/*
函数名：ImportUserCall
功能：将用户指令写入仿真结果文件的函数
参数：
FILE *fp
返回值：无
*/
void ImportUserCall(FILE *fp);

#endif// !DATAIMPORT_H_