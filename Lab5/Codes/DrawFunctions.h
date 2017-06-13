#pragma once
/****************************************************\
作者信息：
姓名：林友芳
版权声明：
版权由北京交通大学计算机与信息技术学院高级语言设计训练课题组拥有
模块名称:
DrawFunctions.h DrawFunctions.cpp配合使用
摘要:
用于高级程序设计训练课程教学
其它说明:
　　无
  模块历史:
  　　林友芳于2010年10月25日创建本模块，email: yflin@bjtu.edu.cn
	　　林友芳于2011年11月07日修改本模块，email: yflin@bjtu.edu.cn
	  　　林友芳于2012年11月08日修改本模块，换用Window来抽象地表示屏幕
		韩升于2016年9月20日修改本模块，email:shhan@bjtu.edu.cn
\**********************************************************/

		//此处防止因重复包含头文件引的类型重复定义
#ifndef DRAWFUNCTIONS_H_
#define DRAWFUNCTIONS_H_

		//窗口中的点坐标结构体定义
struct MyPoint {
	int x; //行坐标
	int y; //列坐标
};
//注：定义成MYPOINT的原因，有些开发环境如VC某些包中已经有POINT的定义
typedef struct MyPoint MYPOINT; //定义类型MYPOINT

typedef struct ArrayPoint {
	int nRow; //行下标
	int nCol; //列下标
}ARRAYPOINT;

//定义矩形结构体类型MYRECT
typedef struct MyRect {
	MYPOINT UpperLeft;//左上角
	int nWidth;//宽度
	int nHeight;//高度
	char cEdge;//表示边的字符
	char cStuff;//向矩形内填充字符
}MYRECT;

/*	定义屏幕缓冲区类型WINDOWBUFFER
*	carrContent为保存窗口内容的字符缓冲区首地址，使用时应看成一个[nRows][nCols]的二维数组
*	屏幕上的行与数组的行对应关系为：数组中的行 = 总行数 - 屏幕上的行 - 1
*
*/
typedef struct WindowBuffer {
	char *carrContent;//自定义屏幕窗口中存放内容用的存储空间(缓冲区)，在使用时需要将其看成一个二维字符数组
	int nRows;//二维数组的行数，对应于坐标轴的Y轴高度
	int nCols;//二维数组的列数，对应于坐标轴的X轴长度+1，最后一列固定用于存放换行符
}WINDOWBUFFER;

/*
*	窗口类型
*/
typedef struct Window {
	WINDOWBUFFER Buffer;	//该窗口所对应的字符缓冲区
	int nOriginColInBuffer;	//原点在WINDOWBUFFER中的对应的列号
	int nOriginRowInBuffer; //原点在WINDOWBUFFER中的对应的行号
							//例：若原点设在左下角，则分别为:nOriginColInBuffer应该设成0，
							//nOriginRowInBuffer应设为WindowBuffer.nRows-1
	int nWidth;		//窗口宽度 
	int nHeight;	//窗口高度
	char szCaption[120]; //窗口标题

}WINDOW;

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
*/
int InitWindow(WINDOW *pWindow, int nWidth, int nHeight);

/*
*	函数名： DestroyWindow
*	功能：
*		销毁窗口，释放窗口的字符缓冲区
*	参数：
*		WINDOW *pWindow
*	返回值：
*		无
*/
void DestroyWindow(WINDOW *pWindow);

/*
*	函数名： ShowWindow
*	功能：
*		在控制台字符终端上显示窗口中的内容
*	参数：
*		WINDOW *pWindow
*
*	返回值：
*		无
*
*/

void ShowWindow(WINDOW *pWindow);
/*
*	函数名：
*		InitWindowCanvas
*	功能：
*		初始化窗口的画布
*		1）将窗口的矩形区域看成一张画布，用参数中给定的字符刷子填充整张画布，起到初始化作用
*		2）并在窗口对应的二维字符数组的每行后面加上换行符
*	参数：
*		WINDOW *pWindow //窗口指针
*		char chBrush  //初始化
*
*	返回值：
*		无
*
*/
void InitWindowCanvas(WINDOW *pWindow, char chBrush);


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
*
*/
void ClearWindow(WINDOW *pWindow, char chBrush);

/*
*	函数名： SetOrigin
*	功能：
*		把窗口看一个平面坐标区域时，设定坐标系原点
*	参数：
*		WINDOW *pWindow
*		int nCol	//原点对应的列号
*		int nRow	//原点对应的行号
*/
void SetOrigin(WINDOW *pWindow, int nCol, int nRow);

//从键盘上读两个整数，生成一个MYPOINT结构的点返回
MYPOINT GetPoint();

/*
*	函数名： CoordinateToArrayPoint
*	功能：将屏幕上的坐标转换成数组坐标，转换公式：
*	参数：
*		WINDOW *pWindow 窗口指针
*		MYPOINT point 窗口坐标体系上的点
*	返回值：
*		窗口缓冲中的carrContent中的字符数组中的坐标（行号，列号）
*/
ARRAYPOINT CoordinateToArrayPoint(WINDOW *pWindow, MYPOINT Point);

/*	函数名： IsValidPoint
*	功能：
*		判定给定的点是否是窗口中的合法点
*	参数：
*		WINDOW *pWindow
*		MYPOINT Point
*	返回值：
*		1 是合法点
*		0 非合法点
*/
int IsValidPoint(WINDOW *pWindow, MYPOINT Point);


/*
*	函数名： DrawAt
*	功能：
*		在给定的点用画笔画
*	参数：
*		MYPOINT Point，点坐标
*		char chBrush，画笔或刷子，必须与背景不同
*	返回值：
*		无
*/
void DrawAt(WINDOW *pWindow, MYPOINT Point, char chBrush);

/***********************************************\
函数名称:
DrawVertiLine
功能描述:
在字符数组表示的界面中生成一条垂直线
只支持自上往下画
函数参数:
SCREENBUFFER *pScreenBuffer 屏幕缓冲区指针
MYPOINT StartPoint //起点
int nHeight //线高
char chBrush //画线用字符
返回值:
无
模块历史:
创建于2010.10.10, by 林友芳
修改:2011.11.07 增加坐标变换
修改:2012.11.08 换用新版接口
\**********************************************/
void DrawVertiLine(WINDOW *pWindow,
	MYPOINT StartPoint, int nHeight, char chBrush);


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
修改:2012.11.08 换用新版接口
\**********************************************/
void DrawHoriLine(WINDOW *pWindow,
	MYPOINT StartPoint, int nWidth, char chBrush);


/***********************************************\
函数名称:
DrawRect
功能描述：
在窗口中生成一个矩形
函数参数：
WINDOW *pWindow //屏幕缓冲区指针
MYRECT rect	 //矩形结构体
返回值：无
模块历史：
创建于2010.10.10, by 林友芳
\**********************************************/
void DrawRect(WINDOW *pWindow, MYRECT rect);



void TestOfDrawingRect();//测试程序

						 //请在此后添加代码

struct duobianxin
{
	int number = 0;     //多边形的顶点个数
	MYPOINT * points;   //用于动态存储多边形顶点的数组
};
typedef struct duobianxin DBX;
//定义了多边形的结构体



/***********************************************\
函数名称:
DrawLine
功能描述：
在窗口中生成一个直线段
函数参数：
WINDOW *pWindow //屏幕缓冲区指针
MYPOINT a //线段的端点a
MYPOINT b //线段的端点b
返回值：无
模块历史：
创建于2017.4.12，by 杨宇
\**********************************************/
void DrawLine(WINDOW* pWindow, 
	     MYPOINT a, MYPOINT b, char chBrush);



/***********************************************\
函数名称:
Initduobianxin
功能描述：
初始化多边形a,设置多边形顶点个数
函数参数：
DBX* a //需要初始化的多边形的地址
int n  //初始化的多边形的顶点个数
返回值：如果初始化成功，返回顶点个数。若初始化失败，返回0
模块历史：
创建于2017.4.12，by 杨宇
\**********************************************/
int Initduobianxin(DBX* a, int n);



/***********************************************\
函数名称:
Routeduobianxin
功能描述：
旋转多边形a
函数参数：
DBX* a //需要旋转的多边形的地址
double //需要旋转的角度
返回值：旋转成功后的多边形结构体
模块历史：
创建于2017.4.12，by 杨宇
\**********************************************/
DBX Routeduobianxin(DBX* a, double angle);



/***********************************************\
函数名称:
Drawduobianxin
功能描述：
在窗口中生成一个多边形
函数参数：
WINDOW *pWindow //屏幕缓冲区指针
DBX* a //需要旋转的多边形的地址
char chBrush //画线用字符
模块历史：
创建于2017.4.12，by 杨宇
\**********************************************/
void Drawduobianxin(WINDOW *pWindow, DBX* a, char chBrush);



#endif