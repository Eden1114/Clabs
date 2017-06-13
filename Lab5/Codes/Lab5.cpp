// Lab5.cpp : 定义控制台应用程序的入口点。
//

/****************************************************\
作者信息：
姓名：林友芳
版权声明：
版权由北京交通大学计算机与信息技术学院高级程序设计训练课题组拥有
模块名称:
DrawFunctions.h DrawFunctions.cpp配合使用
摘要:
用于高级程序设计训练课程教学
其它说明:
　　无
  模块历史:
  　林友芳于2010年10月25日创建本模块，email: yflin@bjtu.edu.cn
	林友芳于2012年11月08日修改本模块
	韩升于2016年9月20日修改本模块，email：shhan@bjtu.edu.cn
**********************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "DrawFunctions.h"

#include "ctype.h"

	/*
	*	函数名： InitWindow
	*	功能：
	*		初始化一个窗口，根据窗口尺寸为窗口申请字符缓冲区
	*	参数：
	*		WINDOW *pWindow
	*		int nWidth			//窗口宽度，度量单位：字符数
	*		int nHeight			//窗口高度，度量单位：字符数
	*	返回值：
	*		若成功，返回1
	*		否则，返回0
	*  模块历史:
	* 		创建于2012.11.8, by 林友芳
	*/
int InitWindow(WINDOW *pWindow, int nWidth, int nHeight)
{

	if (pWindow == NULL)
		return 0;
	pWindow->nWidth = nWidth;
	pWindow->nHeight = nHeight;

	pWindow->Buffer.nCols = nWidth + 1; //记下缓冲区二维字符数组的列数
	pWindow->Buffer.nRows = nHeight;	//记下缓冲区二维字符数组的行数

										//申请缓冲区所对应的二维字符数组所需的存储空间
	pWindow->Buffer.carrContent = (char *)malloc(pWindow->Buffer.nCols * pWindow->Buffer.nRows);
	if (pWindow->Buffer.carrContent == NULL)
		return 0; //内存不足
	SetOrigin(pWindow, 0, nHeight - 1); //将坐标原点默认置成左下角，自己可以根据需要重设

	sprintf(pWindow->szCaption, "\tThis is my window.");

	return 1;
}
/*
*	函数名： DestroyWindow
*	功能：
*		销毁窗口，释放窗口的字符缓冲区
*	参数：
*		WINDOW *pWindow
*	返回值：
*		无
*  模块历史:
* 		创建于2012.11.8, by 林友芳
*/
void DestroyWindow(WINDOW *pWindow)
{
	free(pWindow->Buffer.carrContent);
}

/*
*	函数名： ShowWindow
*	功能：
*		在控制台字符终端上显示窗口中的内容
*	参数：
*		WINDOW *pWindow
*
*	返回值：
*		无
*  模块历史:
* 		创建于2012.11.8, by 林友芳
*/

void ShowWindow(WINDOW *pWindow)
{
	int nCol, nRow;//循环变量，代表行与列

	printf(pWindow->szCaption);
	putchar('\n');
	for (nRow = 0; nRow < pWindow->Buffer.nRows; nRow++)//逐行输出字符数组中的内容
	{
		for (nCol = 0; nCol < pWindow->Buffer.nCols; nCol++)
		{
			putchar(pWindow->Buffer.carrContent[nRow * pWindow->Buffer.nCols + nCol]);
		}
	}
	//也可以用如下代码，思考一下为什么?
	//如果换用的话，应将上面的代码注掉，否则会发生重复输出
	/*
	int i;
	//字符缓冲区长度变量，用一个变量空间换时间（想想为什么？）
	int nBufferLen = pWindow->Buffer.nRows * pWindow->Buffer.nCols;

	for (i = 0; i < nBufferLen; ++i )
	putchar(pWindow->Buffer.carrContent[i]);
	*/
	return;
}
/*
*	函数名：
*		InitWindowCanvas
*	功能：
*		初始化窗口的画布
*		1）将窗口的矩形区域看成一张画布，用参数中给定的字符刷子填充整张画布，起到初始化作用
*		2）并在窗口对应的二维字符数组的每行后面加上换行符
*	参数：
*		WINDOW *pWindow
*		char chBrush  //初始化
*
*	返回值：
*		无
*  模块历史:
* 		创建于2012.11.8, by 林友芳
*/
void InitWindowCanvas(WINDOW *pWindow, char chBrush)
{
	int nCol, nRow; //循环变量，代表行与列

					//逐行初始成由刷子参数指定的字符并在行尾加换行符
	for (nRow = 0; nRow < pWindow->Buffer.nRows; nRow++)
	{
		//对当前行的每列初始化
		for (nCol = 0; nCol < pWindow->Buffer.nCols - 1; nCol++)
		{
			//用刷子刷当前点
			pWindow->Buffer.carrContent[nRow * pWindow->Buffer.nCols + nCol] = chBrush;
		}
		//行尾加换行符
		pWindow->Buffer.carrContent[nRow * pWindow->Buffer.nCols + nCol] = '\n';
	}
	return;
}

/*
*	函数名： ClearWindow
*	功能：
*		1）调用初始化画布的功能，用字符刷子清除画布中现有的内容
*		2）显示窗口
*	参数：
*		WINDOW *pWindow
*		char chBrush
*
*	返回值：
*		无
*  模块历史:
* 		创建于2012.11.8, by 林友芳*
*/
void ClearWindow(WINDOW *pWindow, char chBrush)
{
	InitWindowCanvas(pWindow, chBrush);
	ShowWindow(pWindow);
}

/*
*	函数名： SetOrigin
*	功能：
*		把窗口看一个平面坐标区域时，设定坐标系原点
*	参数：
*		WINDOW *pWindow
*		int nCol	//原点对应的列号
*		int nRow	//原点对应的行号
*  模块历史:
* 		创建于2012.11.8, by 林友芳*
*/
void SetOrigin(WINDOW *pWindow, int nCol, int nRow)
{
	pWindow->nOriginColInBuffer = nCol;
	pWindow->nOriginRowInBuffer = nRow;

	return;
}

/*
*	函数名： CoordinateToArrayPoint
*	功能：将窗口上的坐标转换成数组坐标
*	参数：
*		WINDOW *pWindow 窗口指针
*		MYPOINT point 窗口坐标体系上的点
*	返回值：
*		窗口缓冲中的carrContent中的字符数组中的坐标（行号，列号）
*  模块历史:
* 		创建于2012.11.8, by 林友芳
*
*/
ARRAYPOINT CoordinateToArrayPoint(WINDOW *pWindow, MYPOINT Point)
{
	ARRAYPOINT arrPoint;

	arrPoint.nRow = pWindow->nOriginRowInBuffer - Point.y;
	arrPoint.nCol = Point.x + pWindow->nOriginColInBuffer;

	return arrPoint;
}

/*	函数名： IsValidPoint
*	功能：
*		判定给定的点是否是窗口中的合法点
判定标准为同时满足如下两条件：
1. 点的横坐标是否在[0,pScreenBuffer->nCols-2]之间，最后一列用于存'\n'，不算
2. 点的纵坐标是否在[0,pScreenBuffer->nRows-1]
*	参数：
*		WINDOW *pWindow
*		MYPOINT Point
*	返回值：
*		1 是合法点
*		0 非合法点
*  模块历史:
* 		创建于2012.11.8, by 林友芳
*/
int IsValidPoint(WINDOW *pWindow, MYPOINT Point)
{
	ARRAYPOINT arrPoint;

	//坐标转换
	arrPoint = CoordinateToArrayPoint(pWindow, Point);

	//纵向越界判断
	if (arrPoint.nRow < 0 || arrPoint.nRow >= pWindow->Buffer.nRows)
		return 0;
	//横向越界判断
	if (arrPoint.nCol < 0 || arrPoint.nCol >= pWindow->Buffer.nCols - 1)
		return 0;

	return 1;
}

/*
*	函数名： DrawAt
*	功能：
*		在给定的点用画笔画
*	参数：
*		WINDOW *pWindow
*		MYPOINT Point，点坐标
*		char chBrush，画笔或刷子，必须与背景不同
*	返回值：
*		无
*  模块历史:
* 		创建于2012.11.8, by 林友芳
*/
void DrawAt(WINDOW *pWindow, MYPOINT Point, char chBrush)
{
	ARRAYPOINT arrPoint;

	//坐标转换
	arrPoint = CoordinateToArrayPoint(pWindow, Point);

	//画
	pWindow->Buffer.carrContent
		[   //将二维的行列数组序号映射成一维数组的序号
			arrPoint.nRow * pWindow->Buffer.nCols +
			arrPoint.nCol
		]
	= chBrush;
	return;
}

/***********************************************\
函数名称:
DrawHoriLine
功能描述:
在窗口中界面中生成一条水平线
画线模式，从左至右画，不支持从右至左画
函数参数:
WINDOW *pWindow //屏幕缓冲区指针
MYPOINT StartPoint //起点
int nWidth //线宽
char chBrush//画线用字符
返回值:
无
模块历史:
创建于2010.10.10, by 林友芳
修改:2011.11.07 增加坐标变换
修改:2012.11.08 换用新版
\**********************************************/
void DrawHoriLine(WINDOW *pWindow,
	MYPOINT StartPoint, int nWidth, char chBrush)
{
	int i;
	MYPOINT Point;

	Point.y = StartPoint.y;
	Point.x = StartPoint.x;

	for (i = 0; i < nWidth; ++i) //根据线宽从起点处开始从左向右顺序填充一段内容
	{
		if (IsValidPoint(pWindow, Point))
		{
			DrawAt(pWindow, Point, chBrush);
			++Point.x;
		}
		else
			break;
	}

	return;

}

/***********************************************\
函数名称:
DrawVertiLine
功能描述:
在字符数组表示的界面中生成一条垂直线
函数参数:
WINDOW *pWindow 屏幕缓冲区指针
MYPOINT StartPoint //起点
int nHeight //线高
char ch//画线用字符
返回值:
无
模块历史:
创建于2010.10.10, by 林友芳
修改:2011.11.07 增加坐标变换
修改：2012.11.08 适应新版窗口
\**********************************************/
void DrawVertiLine(WINDOW *pWindow, MYPOINT StartPoint, int nHeight, char chBrush)
{
	int i;
	MYPOINT Point;

	Point.y = StartPoint.y;
	Point.x = StartPoint.x;

	for (i = 0; i < nHeight; ++i)//根据线高从起点处开始从上往下顺序填充一段内容
	{
		if (IsValidPoint(pWindow, Point))
		{
			DrawAt(pWindow, Point, chBrush);
			--Point.y;
		}
		else
			break;
	}
	return;
}
/********************************************************************\
函数名称:
GetPoint
功能描述:
从键盘上读两个整数，生成一个MYPOINT结构的点返回
函数参数:
无
返回值:
MYPOINT，符合此结构的点
模块历史:
创建于2010.10.25, by 林友芳
修改于2012.11.08，增加输入可靠性处理，by 林友芳
\*******************************************************************/
MYPOINT GetPoint()
{
	MYPOINT point;

	while (1) {
		fflush(stdin);
		if (scanf("%d%d", &point.x, &point.y) == 2)
		{
			break;
		}
		printf("Error input, please try again:");
	}

	return point;
}

/*
*	函数名：
*		DrawRect
*	功能：
*		在窗口中生成一个矩形
*	参数：
*		WINDOW *pWindow
*		MYRECT rect	 //矩形结构体
*	返回值：无
*	模块历史:
创建于2010.10.10, by 林友芳
\**********************************************/

void DrawRect(WINDOW *pWindow, MYRECT rect)
{
	int nRow;
	MYPOINT Point = rect.UpperLeft;

	//用画边的字符生成顶边
	DrawHoriLine(pWindow, Point, rect.nWidth, rect.cEdge);

	//生成左边
	DrawVertiLine(pWindow, Point, rect.nHeight, rect.cEdge);

	//生成下边
	Point.y -= rect.nHeight;
	DrawHoriLine(pWindow, Point, rect.nWidth, rect.cEdge);

	//生成右边
	Point.y = rect.UpperLeft.y;
	Point.x += rect.nWidth - 1;
	DrawVertiLine(pWindow, Point, rect.nHeight, rect.cEdge);

	//再用填充字符填充矩形内部，矩形内容由若干条横线组成，也可改成竖线，效果一样
	Point = rect.UpperLeft;
	Point.x++;
	Point.y--;
	for (nRow = 0; nRow < rect.nHeight - 1; nRow++, Point.y--)
	{
		DrawHoriLine(pWindow, Point, rect.nWidth - 2, rect.cStuff);
	}
	return;
}

void ClearRect(WINDOW *pWindow, MYRECT rect,char chBrush)
{
	rect.cEdge = chBrush;
	rect.cStuff = chBrush;
	DrawRect(pWindow, rect);
}

/***********************************************\
函数名称:
TestOfDrawingRect
功能描述:
用于测试本模块中提供各个函数功能是否正确的
该测试程序测试生成一个可由用户定制的矩形
函数参数:
无
返回值:
无
模块历史:
创建于2010.10.10, by 林友芳
注1：可以参照老师的做法测试你新加的功能是否正确
注2：请勿照抄本函数全部代码，要学习本函数的思想。本测试只画一个矩形，
你的程序中需要输入的参数和功能的流程取决于你要画的形状

\**********************************************/
void TestOfDrawingRect()
{
	MYRECT rect;//定义一个矩形结构体
	WINDOW MyWindow;//定义一个窗口

					//定义测试用的窗口，大小25行，共100列
	InitWindow(&MyWindow, 100, 25);

	//用空格初始化画布
	InitWindowCanvas(&MyWindow, ' ');

	//将坐标原点设在(50, 13)，第50列，13行
	SetOrigin(&MyWindow, 50, 13);

	//提示用户输入矩形的左上角
	printf("Please input left upper point of the rect(x y):");

	while (1)
	{
		rect.UpperLeft = GetPoint();
		//判断输入的点是否合法
		if (IsValidPoint(&MyWindow, rect.UpperLeft))
			break;
		printf("Error input, please re-enter left upper point of the rect(x y):");
	}

	//提示用户输入用于画边的字符
	printf("Please input a char used to paint egdes:");
	fflush(stdin);
	rect.cEdge = '*';

	//提示用户输入用于填充的矩形的字符
	printf("Please input a char used to stuff the rect:");
	fflush(stdin);
	rect.cStuff = '+';

	//提示用户输入矩形的高和宽
	printf("Please input the height and width of the rect(height, width):");

	while (scanf("%d%d", &rect.nHeight, &rect.nWidth) < 2)
	{
		fflush(stdin);
		printf("Error input, please try again:");
	}

	//在字符缓冲区生成矩形
	DrawRect(&MyWindow, rect);

	//将生成结果输出到屏幕上
	ShowWindow(&MyWindow);

	DestroyWindow(&MyWindow);
	return;
}


//同学们请在此后增加你自己的代码
//也可以自己新建一个CPP模块
void DrawLine(WINDOW* pWindow, MYPOINT a, MYPOINT b,char chBrush)
{
	if (IsValidPoint(pWindow, a) == 0 || IsValidPoint(pWindow, b) == 0)
	{
		return;
	}
	
	if (a.x > b.x)
	{
		MYPOINT temp = a;
		a = b;
		b = temp;
	}

	if (b.x == a.x)
	{
		if (a.y < b.y)
		{
			int temp = a.y;
			a.y = b.y;
			b.y = temp;
		}
		DrawVertiLine(pWindow,a,a.y - b.y,chBrush);

	}
	else
	{
		double k = (b.y - a.y)*1.0 / (b.x - a.x);
		MYPOINT l;
		l.x = a.x;
		l.y = a.y;
		double fy = l.y;

		while (l.x <= b.x)
		{
			l.y = (int)(fy + 0.5);
			DrawAt(pWindow, l, chBrush);
			fy = fy + k;
			l.x++;
		}

	}

}




int Initduobianxin(DBX* a,int n) {
	a->number = n;
	
	a->points = (MYPOINT*)malloc(n*sizeof(MYPOINT));
	if (a->points == NULL)
		return 0;
	
	//没有读入点，只是分配了空间

	return n;
}

DBX Routeduobianxin(DBX* a, double angle)
{
	DBX result;
	double center_x = 0, center_y = 0;

	for (int i = 0; i < a->number; i++)
	{
		center_x += a->points[i].x;
		center_y += a->points[i].y;
	}
	center_x /= a->number;
	center_y /= a->number;

	Initduobianxin(&result, a->number);

	for (int i = 0; i < result.number; i++)
	{
		result.points[i].x = (int)((a->points[i].x - center_x) * cos(angle) - (a->points[i].y - center_y) *sin(angle) + center_x + 0.5);
		result.points[i].y = (int)((a->points[i].x - center_x) * sin(angle) + (a->points[i].y - center_y) *cos(angle) + center_y +0.5);
	}
	//旋转以后的坐标

	return result;
}

void Drawduobianxin(WINDOW *pWindow,DBX* a,char chBrush) {
	DrawLine(pWindow,a->points[0],a->points[a->number - 1],chBrush);
	for (int i = 0; i < a->number - 1; i++)
	{
		DrawLine(pWindow,a->points[i],a->points[i+1],chBrush);
	}
}

int main() {
	WINDOW MyWindow;
	InitWindow(&MyWindow,50,50);
	InitWindowCanvas(&MyWindow, '|');
	//SetOrigin();//默认的原点在左下角
	MYPOINT origin;
	origin.x = 0;
	origin.y = 0;
	
	DBX a;
	Initduobianxin(&a,3);

	a.points[0].x = 10; a.points[0].y = 10;
	a.points[1].x = 10; a.points[1].y = 20;
	a.points[2].x = 30; a.points[2].y = 20;
	
	Drawduobianxin(&MyWindow,&a,'%');
	DBX b = Routeduobianxin(&a,3.14/2);

	Drawduobianxin(&MyWindow, &b, '*');

	ShowWindow(&MyWindow);
	DestroyWindow(&MyWindow);
	system("pause");
	return 0;
}