/****************************************************\
 作者信息：
 姓名：林友芳
 版权声明：
 版权由北京交通大学计算机与信息技术学院高级程序设计训练课程组拥有
 模块名称:
 ClassInfo.h
 摘要:
 用于实验3教学
 其它说明:
 　　无
 模块历史:
 　　林友芳于2010年11月29日创建本模块，email: yflin@bjtu.edu.cn
	林友芳于2011年12月5日修改
	林友芳于2012年12月6日修改
	韩升于2017年2月15日修改，email：shhan@bjtu.edu.cn
    杨宇于2017年3月21日修改，email:16281237@bjtu.edu.cn
 
 **********************************************************/
//此处防止因重复包含头文件引的类型重复定义
#ifndef CLASSINFO_H_

#define CLASSINFO_H_
//班级信息结构体类型
typedef struct sClassInfo{
    int nClassNO;                          //班级代码
    char szClassName[20];                  //班级名称
    int nStudentNumber;                    //学生人数
}CLASSINFO;

//班级信息二进制文件（学号_姓名_Lab9.dat）的文件头结构
typedef struct sClassInfoInFile{
    CLASSINFO Class;                       //班级信息
    int nStudentInfoOffset;                //学生信息存储位置相对于文件起始位置的偏移量 >0
    char carrPreserved[512];               //预留512字节，用于扩展
}CLASSINFOINFILE;

//学生信息结构体类型
typedef struct sStudentInfo{
    char szID[9];                          //以\0结尾的学号
    char szName[21];                       //以\0结尾的姓名
    double darrScores[3];                  //某三门课的成绩
}STUDENTINFO;


//请从此往后添加新的类型说明，或新建头文件声明类型


//结构体数组保存学生信息的头
typedef struct sClassScore{
    STUDENTINFO *data;                     //学生信息结构体首地址
    int nCount;                            //学生人数（数组元素个数）
}CLASSSCORE;

//指针数组保存学生信息的头
typedef struct sChainInfo{
    int nCount;                            //学生人数（结构体数组的长度）
    STUDENTINFO **data;                    //用于动态分配结构体指针数组的指针
}CHAININFO;


//查询信息结构体
typedef struct sSeek{
    int sub;                               //查询的学科
    double max;                            //最大值
    double min;                            //最小值
}SEEK;

//定义保存信息的链表结点
typedef struct sNode{
    STUDENTINFO stu;                       //学生信息结构体
    struct sNode *next = NULL;             //指向下一个结构体的指针
}NODE;

//定义保存信息的链表头
typedef struct sNodeHead{
    int nCount = 0;                        //学生人数（链表长度）
    struct sNode *head = NULL;                    //链表头
    struct sNode *tail = NULL;                    //链表尾
}NODEHEAD;
void PrintInfo(STUDENTINFO *aStu){
    printf("%s %s ",aStu->szID,aStu->szName);
    for(int i = 0;i < 3;i++){
        if(i == 0)
        {
            printf("%.1lf",aStu->darrScores[i]);
        }
        else
        {
            printf(" %.1lf",aStu->darrScores[i]);
        }
    }
    putchar('\n');
}

/*
 函数描述：输出单个学生的信息
 函数参数：aStu:要输出的学生信息结构体STUDENTINFO的地址
 */

void fPrintInfo(STUDENTINFO *aStu,FILE* fp){
    fprintf(fp,"%s %s ",aStu->szID,aStu->szName);
    for(int i = 0;i < 3;i++){
        if(i == 0)
        {
            fprintf(fp,"%.1lf",aStu->darrScores[i]);
        }
        else
        {
            fprintf(fp," %.1lf",aStu->darrScores[i]);
        }
    }
    fputc('\n', fp);
}
/*
 函数描述：通过文件输出单个学生的信息
 函数参数：aStu:要输出的学生信息结构体STUDENTINFO的地址 fp:文件指针
 */

void fWriteInfoBin(STUDENTINFO* aStu,FILE* fp){
    fwrite(aStu->szID,sizeof(char),sizeof(aStu->szID),fp);
    fwrite(aStu->szName, sizeof(char), sizeof(aStu->szName), fp);
    for(int i = 0; i < 3;i++)
    {
        fwrite(&aStu->darrScores[i],sizeof(double),1,fp);
    }
}
/*
 函数描述：通过二进制文件写入输出单个学生的信息
 函数参数：aStu:要输出的学生信息结构体STUDENTINFO的地址 fp:文件指针
 */

void fReadInfoBin(STUDENTINFO* aStu,FILE* fp){
    fread(aStu->szID,sizeof(char),sizeof(aStu->szID),fp);
    fread(aStu->szName, sizeof(char), sizeof(aStu->szName), fp);
    for(int i = 0; i < 3;i++)
    {
        fread(&aStu->darrScores[i],sizeof(double),1,fp);
    }
}
/*
 函数描述：通过二进制文件读取单个学生的信息
 函数参数：a:读取后存入的学生结构体地址 fp:文件指针
 */

int ReadText(const char *FileName,CLASSINFOINFILE *pClassInfoHead,CLASSSCORE *Classmate){
    FILE* fp = NULL;
    if((fp = fopen(FileName,"r")) == NULL)
    {
        printf("Can't open this file!\n");
        exit(-1);
    }
    fscanf(fp,"%d %s %d",&pClassInfoHead->Class.nClassNO,pClassInfoHead->Class.szClassName,&pClassInfoHead->Class.nStudentNumber);
    Classmate->nCount = pClassInfoHead->Class.nStudentNumber;
    //读取班级的头信息，设置Classnote里的nCount
    
    if((Classmate->data = (STUDENTINFO*)malloc(Classmate->nCount*sizeof(STUDENTINFO)))== NULL)
    {
        printf("No Memery!\n");
        exit(-1);
    }
    //为学生信息分配空间
    
    for(int i = 0;i < Classmate->nCount;i++)
    {
        fscanf(fp,"%s %s", Classmate->data[i].szID, Classmate->data[i].szName);
        for(int j = 0; j < 3;j++)
        {
            fscanf(fp,"%lf",&Classmate->data[i].darrScores[j]);
        }
    }
    //依次读取学生信息，存储到分配的空间
    
    fclose(fp);
    return 0;
}
/*
 函数描述：读入文本文件中的信息并保存到结构体中
 函数参数：Filename:要打开的文件名 pClassInfoHead:存储班级信息结构体的地址 Classmate:存储学生信息的头结构体地址
 */
int ReWriteTextStruct(const char *FileName,CLASSINFOINFILE *pClassInfoHead,CLASSSCORE *Classmate)
{
    FILE* fp;
    if((fp = fopen(FileName,"w")) == NULL)
    {
        printf("Can't write this file!\n");
        exit(-1);
    }
    
    fprintf(fp,"%d ",pClassInfoHead->Class.nClassNO);
    fprintf(fp,"%s ",pClassInfoHead->Class.szClassName);
    fprintf(fp,"%d\n",pClassInfoHead->Class.nStudentNumber);
    for(int i = 0;i < pClassInfoHead->Class.nStudentNumber;i++)
        fPrintInfo(&Classmate->data[i], fp);
    return 0;
}

int ReWriteText(const char *FileName,CLASSINFOINFILE *pClassInfoHead,CLASSSCORE *Classmate)
{
    FILE* fp;
    if((fp = fopen(FileName,"wb")) == NULL)
    {
        printf("Can't write this file!\n");
        exit(-1);
    }
    
    fwrite(&pClassInfoHead->Class.nClassNO,sizeof(int),1,fp);
    //班级代码
    fwrite(pClassInfoHead->Class.szClassName,sizeof(char),sizeof(pClassInfoHead->Class.szClassName),fp);
    //班级名称
    fwrite(&pClassInfoHead->Class.nStudentNumber,sizeof(int),1,fp);
    Classmate->nCount = pClassInfoHead->Class.nStudentNumber;
    //学生人数
    pClassInfoHead->nStudentInfoOffset = (int)ftell(fp) + sizeof(pClassInfoHead->carrPreserved) * sizeof(char);
    fwrite(&pClassInfoHead->nStudentInfoOffset, sizeof(int), 1, fp);
    //学生信息存储起始位置
    fwrite(pClassInfoHead->carrPreserved,sizeof(char),sizeof(pClassInfoHead->carrPreserved),fp);
    //预留空间
    
    for(int i = 0;i < Classmate->nCount;i++)
    {
        fWriteInfoBin(&Classmate->data[i],fp);
    }
    //所有学生的信息
    fclose(fp);
    return 0;
}
/*
 函数描述：把结构体中的数据写入到二进制文件中
 函数参数：Filename:写入后生成文件的文件名 pClassInfoHead:存储班级信息结构体的地址 Classmate:存储学生信息的头结构体地址
 */


int ReadTextForStructNarr(const char *FileName,CLASSSCORE *classscore,CLASSINFOINFILE *pClassInfoHead){
    FILE *fp = NULL;
    if((fp = fopen(FileName,"rb")) == NULL)
    {
        printf("Can't write this file!\n");
        exit(-1);
    }
    fread(&pClassInfoHead->Class.nClassNO,sizeof(int),1,fp);
    //班级代码
    fread(pClassInfoHead->Class.szClassName,sizeof(char),sizeof(pClassInfoHead->Class.szClassName),fp);
    //班级名称
    fread(&pClassInfoHead->Class.nStudentNumber,sizeof(int),1,fp);
    classscore->nCount = pClassInfoHead->Class.nStudentNumber;
    //学生人数
    fread(&pClassInfoHead->nStudentInfoOffset, sizeof(int), 1, fp);
    //学生信息存储起始位置
    fread(pClassInfoHead->carrPreserved,sizeof(char),sizeof(pClassInfoHead->carrPreserved),fp);
    //预留空间
    
    if((classscore->data = (STUDENTINFO*)malloc(classscore->nCount*sizeof(STUDENTINFO)))== NULL)
    {
        printf("No Memery!\n");
        exit(-1);
    }
    //分配空间

    for(int i = 0;i < pClassInfoHead->Class.nStudentNumber;i++)
        fReadInfoBin(&classscore->data[i],fp);
    //所有学生的信息
    
    fclose(fp);
    return 0;
};
/*
 函数描述：用于读取.dat二进制文件并保存在结构体数组中,需要新定义结构体，再把结构体的地址传入到函数的参数中。
 函数参数：Filename:写入后生成文件的文件名 pClassInfoHead:存储班级信息结构体的地址 Classmate:存储学生信息的头结构体地址
 */

int ReadTextForChain(const char *FileName,CHAININFO *ChainInfo,CLASSINFOINFILE *pClassInfoHead){
    FILE *fp = NULL;
    if((fp = fopen(FileName,"rb")) == NULL)
    {
        printf("Can't write this file!\n");
        exit(-1);
    }
    fread(&pClassInfoHead->Class.nClassNO,sizeof(int),1,fp);
    //班级代码
    fread(pClassInfoHead->Class.szClassName,sizeof(char),sizeof(pClassInfoHead->Class.szClassName),fp);
    //班级名称
    fread(&pClassInfoHead->Class.nStudentNumber,sizeof(int),1,fp);
    ChainInfo->nCount = pClassInfoHead->Class.nStudentNumber;
    //学生人数
    fread(&pClassInfoHead->nStudentInfoOffset, sizeof(int), 1, fp);
    //学生信息存储起始位置
    fread(pClassInfoHead->carrPreserved,sizeof(char),sizeof(pClassInfoHead->carrPreserved),fp);
    //预留空间
    
    if((ChainInfo->data = (STUDENTINFO**)malloc(ChainInfo->nCount*sizeof(STUDENTINFO*)))== NULL)
    {
        printf("No Memery!\n");
        exit(-1);
    }
    //分配空间
    STUDENTINFO *dataspace;
    if((dataspace = (STUDENTINFO*)malloc(ChainInfo->nCount*sizeof(STUDENTINFO)))== NULL)
    {
        printf("No Memery!\n");
        exit(-1);
    }
    
    for (int i = 0; i < ChainInfo->nCount; i++) {
        ChainInfo->data[i] = &dataspace[i];
        fReadInfoBin(ChainInfo->data[i], fp);
    }
    //所有学生的信息
    fclose(fp);
    return 0;
    
}
/*
 函数描述：用于读取.dat二进制文件并保存在结构体指针数组中
 函数参数：Filename:写入后生成文件的文件名 ChainInfo:存储学生信息的指针头结构体地址 pClassInfoHead:存储班级信息结构体的地址
 */


void PrintStructNarr(CLASSINFOINFILE *aClass,CLASSSCORE *stu){
    printf("%d ",aClass->Class.nClassNO);
    printf("%s ",aClass->Class.szClassName);
    printf("%d\n",aClass->Class.nStudentNumber);
    for(int i = 0;i < stu->nCount;i++)
        PrintInfo(&stu->data[i]);
}
/*
 学生信息输出函数,结构体数组
 */



void PrintPointNarr(CLASSINFOINFILE *aClass,CHAININFO *pstu){
    printf("%d ",aClass->Class.nClassNO);
    printf("%s ",aClass->Class.szClassName);
    printf("%d\n",aClass->Class.nStudentNumber);
    for(int i = 0; i < pstu->nCount;i++)
        PrintInfo(pstu->data[i]);
}
/*
 学生信息输出函数，指针数组
 */

void FindStuInfoStruct(CLASSSCORE *stu,SEEK *seek){
    if(seek->max < seek-> min)
    {
        printf("seek error!\n");
        exit(-1);
        }
    int flag = 0;
    for(int i = 0;i < stu->nCount;i++)
    {
        if(stu->data[i].darrScores[seek->sub] >= seek->min && stu->data[i].darrScores[seek->sub] <= seek->max)
        {
            PrintInfo(&stu->data[i]);
            flag = 1;
        }
    }
    if(flag == 0) printf("Not Found!\n");
}
/*
 成绩查询函数，结构体数组
 */

void FindStuInfoPoint(CHAININFO *pstu,SEEK *seek){
    if(seek->max < seek-> min)
    {
        printf("seek error!\n");
        exit(-1);
    }
    int flag = 0;
    for(int i = 0;i < pstu->nCount;i++)
        if(pstu->data[i]->darrScores[seek->sub] >= seek->min && pstu->data[i]->darrScores[seek->sub] <= seek->max)
        {
            PrintInfo(pstu->data[i]);
            flag = 1;
        }
    if(flag == 0) printf("Not Found!\n");
}
/*
 成绩查询函数，指针数组
 */

/*/Lab4添加

typedef struct sNode{
    STUDENTINFO stu;
    struct sNode *next;
}NODE;
//定义链表的结点

typedef struct sNodeHead{
    int nCount;
    struct sNode *head;
    struct sNode *tail;
}NODEHEAD;

//*///链表头

int AddNodeToListTail(NODEHEAD* nodehead){
    NODE* newnode = NULL;
    newnode = (NODE*) malloc(sizeof(NODE));
    if(nodehead->nCount == 0)
    {
        nodehead->head = newnode;
        nodehead->tail = newnode;
        nodehead->nCount++;
        newnode->next = NULL;
    }
    else 
    {
        if(nodehead->tail != NULL)
            nodehead->tail->next = newnode;
        newnode->next = NULL;
        nodehead->tail = newnode;
    }
    
    
    return nodehead->nCount;
}
/*
 函数描述：添加一个新的结点到链表的尾部
 函数参数：nodehead要添加到的链表的头指针
 */


int ReadTextForList(const char *FileName,NODEHEAD *nodehead,CLASSINFOINFILE *pClassInfoHead){
    FILE *fp = NULL;
    if((fp = fopen(FileName,"rb")) == NULL)
    {
        printf("Can't write this file!\n");
        exit(-1);
    }
    fread(&pClassInfoHead->Class.nClassNO,sizeof(int),1,fp);
    //班级代码
    fread(pClassInfoHead->Class.szClassName,sizeof(char),sizeof(pClassInfoHead->Class.szClassName),fp);
    //班级名称
    fread(&pClassInfoHead->Class.nStudentNumber,sizeof(int),1,fp);
    nodehead->nCount = 0;
    //学生人数
    fread(&pClassInfoHead->nStudentInfoOffset, sizeof(int), 1, fp);
    //学生信息存储起始位置
    fread(pClassInfoHead->carrPreserved,sizeof(char),sizeof(pClassInfoHead->carrPreserved),fp);
    //预留空间
    
    
    for(int i = 0;i < pClassInfoHead->Class.nStudentNumber;i++)
    {
        AddNodeToListTail(nodehead);
    }
    //分配空间
    
    NODE* i;
    for(i = nodehead->head;i != NULL;i = i->next)
    {
        fReadInfoBin(&i->stu,fp);
    }
    //所有学生的信息
    fclose(fp);
    return 0;
}
//读取函数-链表


void PrintListNarr(CLASSINFOINFILE *aClass,NODEHEAD*nodehead)
{
    printf("%d ",aClass->Class.nClassNO);
    printf("%s ",aClass->Class.szClassName);
    printf("%d\n",aClass->Class.nStudentNumber);
    for(NODE* i = nodehead->head;i != NULL;i = i->next)
    {
        PrintInfo(&i->stu);
    }
}
//输出函数-链表


void FindStuInfoList(NODEHEAD *nodehead,SEEK *seek){
    if(seek->max < seek-> min)
    {
        printf("seek error!\n");
        exit(-1);
    }
    int flag = 0;
    for(NODE* i = nodehead->head;i->next != NULL;i = i->next)
    {
        if(i->stu.darrScores[seek->sub]>seek->min &&  i->stu.darrScores[seek->sub]<seek->max)
        {
            PrintInfo(&i->stu);
        }
    }
    if(flag == 0) printf("Not Found!\n");
}
//查询函数-链表

int SortStuInfoList2(NODEHEAD *nodehead,int lesson){
    if(lesson > 2 ||lesson < 0)
        exit(-1);
    NODE *p = nodehead->head,*p_next = p->next;
    for(int i = 0;i < nodehead->nCount;i++)
    {
        for(int k = 0;k< i;k++)
        {
            p = p->next;
        }
        p_next =p->next;
        for(int j = 0; j < nodehead->nCount - i;j++)
            if(p->stu.darrScores[lesson] > p_next->stu.darrScores[lesson])
            {
                STUDENTINFO temp = p->stu;
                p->stu = p_next -> stu;
                p-> stu = temp;
            }
    }
    return 0;
}
//排序函数-链表

void StuInfoFileList(const char *filename,CLASSINFOINFILE *aClass ,NODEHEAD *nodehead){
    FILE *fp = NULL;
    if((fp = fopen(filename,"w")) == NULL)
    {
        printf("Can't write this file!\n");
        exit(-1);
    }
    fprintf(fp,"%d ",aClass->Class.nClassNO);
    fprintf(fp,"%s ",aClass->Class.szClassName);
    fprintf(fp,"%d\n",aClass->Class.nStudentNumber);
    for(NODE * i = nodehead->head;i->next != NULL;i = i->next)
    {
        fPrintInfo(&i->stu, fp);
    }
    fclose(fp);
}
//输出文本文件
#endif
