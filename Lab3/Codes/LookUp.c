/****************************************************\
 作者信息：
 姓名：杨宇
 版权声明：
 版权由北京交通大学计算机与信息技术学院1608班杨宇拥有
 项目名称:
 lab3
 摘要:
 实验3
 其它说明:
 　　无
 模块历史:
 　　杨宇于2017年3月9日创建本模块，email: 16281237@bjtu.edu.cn
 \*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "ClassInfo.h"

int main(int argc, char *argv[]) {
    //结构体
    CLASSINFOINFILE classinfofile1,classinfofile2,classinfofile3;
    CLASSSCORE classscore1,classscore2;
    ReadText("DataForLab3.txt", &classinfofile1, &classscore1);
    ReWriteText("16281237_杨宇_Lab3.dat", &classinfofile1, &classscore1);
    PrintStructNarr(&classinfofile1, &classscore1);
    ReadTextForStructNarr("16281237_杨宇_Lab3.dat",&classscore2,&classinfofile2);
	
    FindStuInfoStruct(&classscore2,&info);
    putchar('\n');
    //指针数组
    SEEK info;
    info.sub = 0;
    info.max = 90.0;
    info.min = 70;
    CHAININFO x;
    ReadTextForChain("16281237_杨宇_Lab3.dat",&x,&classinfofile3);
    PrintPointNarr(&classinfofile3,&x);
    putchar('\n');
    FindStuInfoPoint(&x,&info);
    return 0;
}
