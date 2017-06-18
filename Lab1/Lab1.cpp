/***************************************\
 *文件名：lab1.c
 *作者信息：
 *		姓名：杨宇
 *		班级：1608
 *		学号：16281237
 *		Email：16281237@bjtu.edu.cn
 *		电话：18800107072
 *文件信息：
 *		创建时间：2017年03月01日16:07:41
 *		最后一次修改：2017年03月02日17:08:01
 *版权信息：
 *		遵守GPL协议
 *摘要：
 *		参数为1
 *		从data.txt中读取一批实数，并求出平均值。
 *		参数为2
 *		打开text.txt,统计其中a-z出现的次数，并将结果输出到result.txt中。
 *		如果为其他参数
 *		退出程序
 *		如果没有参数
 *		从键盘输入一批整数，并输出所成坐标点连线与x轴围成的面积
 \**************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 1100
//参数为1时，读取的最大实数个数为MAXSIZE

typedef struct darray{
	double *pdata;
	int len;
	int maxlen;
} DARRAY;
//用于记录读取实数的保存情况

int main (int argc,char *argv[])
{
	if (argc == 1)
	{	
		int x;
		int last = 0;
		double s = 0;
		while (scanf("%d",&x) == 1)
		{
			if (x == 0) break;
			if (last != 0)
				s += (last + x);
			last = x;
		}
		printf("%lf",s / 2);
		return 0;
	}
	//如果没有其他参数

	else if (!strcmp(argv[1],"1"))
	{
		if (freopen("data.txt","r",stdin) == NULL)
		{
			printf("Not find the file!\n");
			exit(1);
		}
		//输入重定向
		DARRAY data;
		data.pdata = (double*) malloc(MAXSIZE*sizeof(double));
		data.len = 0;
		data.maxlen = MAXSIZE;
		//结构体初始化
		double average = 0;
		
		
		/*
		while (~scanf("%lf", &data.pdata[data.len]))
		{
			if(data.len >=  data.maxlen - 1) return -1;
			//printf("%lf\n",data.pdata[data.len]);		
			average += data.pdata[data.len];
			data.len++;
		}
		数据没有用逗号隔开时的读取代码
		*/
		 
		//
		scanf("%lf",&data.pdata[data.len]);
		average += data.pdata[data.len];
		data.len++;
		
		char comma;
		while((  comma = getchar()   ) == ',' ){
			scanf("%lf",&data.pdata[data.len]);
			average += data.pdata[data.len];
			data.len++;
		}
		//数据有用逗号隔开时的读取代码
		
		average /= data.len;
		printf ("%lf\n",average);
		return 0;
	}
//如果参数为1

	else if (!strcmp(argv[1],"2"))
	{
		freopen("text.txt","r",stdin);
		freopen("result.txt","w",stdout);
		//重定向
		char c;
		int times[26];
		memset(times,0,26*sizeof(int));	
		
		while ( scanf("%c",&c) != EOF){
			if(c >= 'a' && c<= 'z')
			{
				int temp = c - 'a';
				times[temp] ++;
			}
			else if(c >= 'A' || c <= 'Z')
			{	
				int temp = c - 'A';
				times[temp] ++;
			}
		}
		//计数模块
		char x = 'A';
		for(int i = 0;i < 26;i++)
		{
			printf("%c:%d\n",x,times[i]);
			x++;
		}
		//输出
		return 0;
	}
//如果参数为2
	
	else return 0;
//如果没有参数
}