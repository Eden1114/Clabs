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
 　　用于读取Datalab3.txt,存入结构体，并重新写入到16281237
 _杨宇_Lab3.dat文件中
 模块历史:
 　　杨宇于2017年3月9日创建本模块，email: 16281237@bjtu.edu.cn
 \*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "ClassInfo.h"

int main(int argc, const char * argv[]){
CLASSINFOINFILE classinfofile1;
    CLASSSCORE classscore1;
    ReadText("DataForLab3.txt", &classinfofile1, &classscore1);
    ReWriteText("16281237_杨宇_Lab3.dat", &classinfofile1, &classscore1);
    return 0;
}
