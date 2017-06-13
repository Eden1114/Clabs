/*
TODO:
用于存储电梯响应展示模块的相关功能和函数源代码
*/
#pragma once
#ifndef SCREENSIMLATION_H_
#define SCREENSIMLATION_H_

#include"extern.h"



/*
函数名：ShowMovieAndImport
功能：显示动画仿真过程并输出结果文件的函数
参数：无
返回值：无
*/
int ShowMovieAndImport();

/*
函数名：ShowMoive
功能：显示动作仿真过程函数
参数：
返回值：无
*/
void ShowMoive();


/*
函数名：PaintPicture
功能：将当前时刻电梯绘制成图形的函数
参数：
返回值：无
*/
void PaintPicture();


/*
函数名：ShowMovieAndImportHISTORY
功能：通过历史仿真文件显示动画仿真过程并输出结果文件的函数
参数：char HistorySimulateFilesName[]
返回值：
1成功
0 失败
*/
int ShowMovieAndImportHISTORY(char HistorySimulateFilesName[]);

#endif// !SCREENSIMLATION_H_