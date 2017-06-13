//
//  UI.h
//  Lab4
//
//  Created by Eden on 2017/3/21.
//  Copyright © 2017年 GeniusYangdaYu. All rights reserved.
//

#ifndef UI_h
#define UI_h
int printscreen0(){
    printf("杨宇的实验4程序：\n");
    printf("1.学生信息读入\n");
    printf("2.学生信息输出\n");
    printf("3.学生成绩查询\n");
    printf("0.退出\n");
    printf("请输入您要执行的程序序号：");
    int x;
    scanf("%d",&x);
    fflush(stdin);
    putchar('\n');
    return x;
}
//初始界面
int printscreen1_0(){
    printf("学生信息读入：\n");
    printf("1.读入到结构体数组\n");
    printf("2.读入到指针数组\n");
    printf("3.读入到链表\n");
    printf("0.返回上级菜单\n");
    printf("请输入您要执行的程序序号：");
    int x;
    scanf("%d",&x);
    fflush(stdin);
    putchar('\n');
    return x;
}
//第一个子界面
int printscreen1_1(){
    printf("学生信息输出：\n");
    printf("1.输出到屏幕\n");
    printf("2.输出到文件\n");
    printf("3.输出到二进制文件\n");
    printf("0.返回上级菜单\n");
    printf("请输入您要执行的程序序号：");
    int x;
    scanf("%d",&x);
    fflush(stdin);
    putchar('\n');
    return x;
}
//第二个子界面

int printscreen1_2(){
    printf("学生信息查询：\n");
    printf("1.从结构体中查询\n");
    printf("2.从指针数组中查询\n");
    printf("3.从链表中查询\n");
    printf("0.返回上级菜单\n");
    printf("请输入您要执行的程序序号：");
    int x;
    scanf("%d",&x);
    fflush(stdin);
    putchar('\n');
    return x;
}
SEEK printscreen1_2_0(){
    printf("学生成绩查询：\n");
    int flag = 0;
    SEEK a;
    do {
        if(flag == 1) printf("输入信息不合理请重新输入！\n");
        printf("请输入查询科目、最低分、最高分范围\n");
        scanf("%d%lf%lf",&a.sub,&a.min,&a.max);
        fflush(stdin);
        flag = 1;
        }while(a.min > a.max||a.sub >=3||a.sub <0||a.min > 100||a.max > 100||a.min < 0||a.max < 0);
    return a;
}
//第三个子界面





int interface() {
    CLASSINFOINFILE classinfofile;
    CLASSSCORE classscore;
    CLASSINFOINFILE classinfofilestruct;
    CLASSSCORE classscorestruct;
    CHAININFO chaininfochain;
    CLASSINFOINFILE classinfofilechain;
    NODEHEAD nodehead;
    nodehead.nCount = 0;
    CLASSINFOINFILE classinfofilelist;
    while(1){
        int chose0;
        chose0 = printscreen0();
        while(chose0 == 1)//学生信息读取
        {
            int chose1 = printscreen1_0();
            ReadText("DataForLab4.txt", &classinfofile, &classscore);
            ReWriteText("DataForLab4.dat", &classinfofile, &classscore);
            if(chose1 == 1)//读取到结构体数组
            {
                ReadTextForStructNarr("DataForLab4.dat", &classscorestruct, &classinfofilestruct);
                printf("success\n");
                break;
            }
            else if(chose1 == 2)//读取到指针数组
            {
                ReadTextForChain("DataForLab4.dat", &chaininfochain, &classinfofilechain);
                printf("success\n");
                break;
            }
            else if (chose1 == 3)//读取到链表
            {
                ReadTextForList("DataForLab4.dat", &nodehead, &classinfofilelist);
                printf("success\n");
                break;
            }
            else if (chose1 == 0)//返回上级菜单
            {
                break;
            }
            else
            {
                printf("输入不合理...\n");
            }
        }
        
        
        while(chose0 == 2)//学生信息输出
        {
            int chose2 = printscreen1_1();
            if(chose2 == 1)//输出到屏幕
            {
                PrintStructNarr(&classinfofilestruct, &classscorestruct);
                getchar();
                break;
            }
            else if(chose2 == 2)//输出到文件
            {
                ReWriteTextStruct("OutputForLab4.txt", &classinfofilestruct, &classscorestruct);
                printf("success!\n");
                break;
            }
            else if(chose2 == 3)//输出到二进制文件
            {
                ReWriteText("DataForLab4.dat", &classinfofilestruct, &classscorestruct);
                printf("success!\n");
                break;
            }
            else if(chose2 == 0)
            {
                break;
            }
            else
            {
                printf("输入不合理！\n");
            }
        }
        
        
        while(chose0 == 3)//学生成绩查询
        {
            int chose3 = printscreen1_2();
            SEEK info =  printscreen1_2_0();
            if(chose3 == 1)
            {
                FindStuInfoStruct(&classscorestruct, &info);
            }
            if(chose3 == 2)
            {
                FindStuInfoPoint(&chaininfochain, &info);
            }
            if(chose3 == 3)
            {
                FindStuInfoList(&nodehead,&info);
            }
            if(chose3 == 0)
            {
                break;
            }
            else
            {
                printf("输入不合理！\n");
            }
            
        }
        if(chose0 == 0)
        {
            return 0;
        }
    }
}
#endif /* UI_h */
