// Lab5.cpp : �������̨Ӧ�ó������ڵ㡣
//

/****************************************************\
������Ϣ��
���������ѷ�
��Ȩ������
��Ȩ�ɱ�����ͨ��ѧ���������Ϣ����ѧԺ�߼��������ѵ��������ӵ��
ģ������:
DrawFunctions.h DrawFunctions.cpp���ʹ��
ժҪ:
���ڸ߼��������ѵ���γ̽�ѧ
����˵��:
������
  ģ����ʷ:
  �����ѷ���2010��10��25�մ�����ģ�飬email: yflin@bjtu.edu.cn
	���ѷ���2012��11��08���޸ı�ģ��
	������2016��9��20���޸ı�ģ�飬email��shhan@bjtu.edu.cn
**********************************************************/

#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "DrawFunctions.h"

#include "ctype.h"

	/*
	*	�������� InitWindow
	*	���ܣ�
	*		��ʼ��һ�����ڣ����ݴ��ڳߴ�Ϊ���������ַ�������
	*	������
	*		WINDOW *pWindow
	*		int nWidth			//���ڿ�ȣ�������λ���ַ���
	*		int nHeight			//���ڸ߶ȣ�������λ���ַ���
	*	����ֵ��
	*		���ɹ�������1
	*		���򣬷���0
	*  ģ����ʷ:
	* 		������2012.11.8, by ���ѷ�
	*/
int InitWindow(WINDOW *pWindow, int nWidth, int nHeight)
{

	if (pWindow == NULL)
		return 0;
	pWindow->nWidth = nWidth;
	pWindow->nHeight = nHeight;

	pWindow->Buffer.nCols = nWidth + 1; //���»�������ά�ַ����������
	pWindow->Buffer.nRows = nHeight;	//���»�������ά�ַ����������

										//���뻺��������Ӧ�Ķ�ά�ַ���������Ĵ洢�ռ�
	pWindow->Buffer.carrContent = (char *)malloc(pWindow->Buffer.nCols * pWindow->Buffer.nRows);
	if (pWindow->Buffer.carrContent == NULL)
		return 0; //�ڴ治��
	SetOrigin(pWindow, 0, nHeight - 1); //������ԭ��Ĭ���ó����½ǣ��Լ����Ը�����Ҫ����

	sprintf(pWindow->szCaption, "\tThis is my window.");

	return 1;
}
/*
*	�������� DestroyWindow
*	���ܣ�
*		���ٴ��ڣ��ͷŴ��ڵ��ַ�������
*	������
*		WINDOW *pWindow
*	����ֵ��
*		��
*  ģ����ʷ:
* 		������2012.11.8, by ���ѷ�
*/
void DestroyWindow(WINDOW *pWindow)
{
	free(pWindow->Buffer.carrContent);
}

/*
*	�������� ShowWindow
*	���ܣ�
*		�ڿ���̨�ַ��ն�����ʾ�����е�����
*	������
*		WINDOW *pWindow
*
*	����ֵ��
*		��
*  ģ����ʷ:
* 		������2012.11.8, by ���ѷ�
*/

void ShowWindow(WINDOW *pWindow)
{
	int nCol, nRow;//ѭ������������������

	printf(pWindow->szCaption);
	putchar('\n');
	for (nRow = 0; nRow < pWindow->Buffer.nRows; nRow++)//��������ַ������е�����
	{
		for (nCol = 0; nCol < pWindow->Buffer.nCols; nCol++)
		{
			putchar(pWindow->Buffer.carrContent[nRow * pWindow->Buffer.nCols + nCol]);
		}
	}
	//Ҳ���������´��룬˼��һ��Ϊʲô?
	//������õĻ���Ӧ������Ĵ���ע��������ᷢ���ظ����
	/*
	int i;
	//�ַ����������ȱ�������һ�������ռ任ʱ�䣨����Ϊʲô����
	int nBufferLen = pWindow->Buffer.nRows * pWindow->Buffer.nCols;

	for (i = 0; i < nBufferLen; ++i )
	putchar(pWindow->Buffer.carrContent[i]);
	*/
	return;
}
/*
*	��������
*		InitWindowCanvas
*	���ܣ�
*		��ʼ�����ڵĻ���
*		1�������ڵľ������򿴳�һ�Ż������ò����и������ַ�ˢ��������Ż������𵽳�ʼ������
*		2�����ڴ��ڶ�Ӧ�Ķ�ά�ַ������ÿ�к�����ϻ��з�
*	������
*		WINDOW *pWindow
*		char chBrush  //��ʼ��
*
*	����ֵ��
*		��
*  ģ����ʷ:
* 		������2012.11.8, by ���ѷ�
*/
void InitWindowCanvas(WINDOW *pWindow, char chBrush)
{
	int nCol, nRow; //ѭ������������������

					//���г�ʼ����ˢ�Ӳ���ָ�����ַ�������β�ӻ��з�
	for (nRow = 0; nRow < pWindow->Buffer.nRows; nRow++)
	{
		//�Ե�ǰ�е�ÿ�г�ʼ��
		for (nCol = 0; nCol < pWindow->Buffer.nCols - 1; nCol++)
		{
			//��ˢ��ˢ��ǰ��
			pWindow->Buffer.carrContent[nRow * pWindow->Buffer.nCols + nCol] = chBrush;
		}
		//��β�ӻ��з�
		pWindow->Buffer.carrContent[nRow * pWindow->Buffer.nCols + nCol] = '\n';
	}
	return;
}

/*
*	�������� ClearWindow
*	���ܣ�
*		1�����ó�ʼ�������Ĺ��ܣ����ַ�ˢ��������������е�����
*		2����ʾ����
*	������
*		WINDOW *pWindow
*		char chBrush
*
*	����ֵ��
*		��
*  ģ����ʷ:
* 		������2012.11.8, by ���ѷ�*
*/
void ClearWindow(WINDOW *pWindow, char chBrush)
{
	InitWindowCanvas(pWindow, chBrush);
	ShowWindow(pWindow);
}

/*
*	�������� SetOrigin
*	���ܣ�
*		�Ѵ��ڿ�һ��ƽ����������ʱ���趨����ϵԭ��
*	������
*		WINDOW *pWindow
*		int nCol	//ԭ���Ӧ���к�
*		int nRow	//ԭ���Ӧ���к�
*  ģ����ʷ:
* 		������2012.11.8, by ���ѷ�*
*/
void SetOrigin(WINDOW *pWindow, int nCol, int nRow)
{
	pWindow->nOriginColInBuffer = nCol;
	pWindow->nOriginRowInBuffer = nRow;

	return;
}

/*
*	�������� CoordinateToArrayPoint
*	���ܣ��������ϵ�����ת������������
*	������
*		WINDOW *pWindow ����ָ��
*		MYPOINT point ����������ϵ�ϵĵ�
*	����ֵ��
*		���ڻ����е�carrContent�е��ַ������е����꣨�кţ��кţ�
*  ģ����ʷ:
* 		������2012.11.8, by ���ѷ�
*
*/
ARRAYPOINT CoordinateToArrayPoint(WINDOW *pWindow, MYPOINT Point)
{
	ARRAYPOINT arrPoint;

	arrPoint.nRow = pWindow->nOriginRowInBuffer - Point.y;
	arrPoint.nCol = Point.x + pWindow->nOriginColInBuffer;

	return arrPoint;
}

/*	�������� IsValidPoint
*	���ܣ�
*		�ж������ĵ��Ƿ��Ǵ����еĺϷ���
�ж���׼Ϊͬʱ����������������
1. ��ĺ������Ƿ���[0,pScreenBuffer->nCols-2]֮�䣬���һ�����ڴ�'\n'������
2. ����������Ƿ���[0,pScreenBuffer->nRows-1]
*	������
*		WINDOW *pWindow
*		MYPOINT Point
*	����ֵ��
*		1 �ǺϷ���
*		0 �ǺϷ���
*  ģ����ʷ:
* 		������2012.11.8, by ���ѷ�
*/
int IsValidPoint(WINDOW *pWindow, MYPOINT Point)
{
	ARRAYPOINT arrPoint;

	//����ת��
	arrPoint = CoordinateToArrayPoint(pWindow, Point);

	//����Խ���ж�
	if (arrPoint.nRow < 0 || arrPoint.nRow >= pWindow->Buffer.nRows)
		return 0;
	//����Խ���ж�
	if (arrPoint.nCol < 0 || arrPoint.nCol >= pWindow->Buffer.nCols - 1)
		return 0;

	return 1;
}

/*
*	�������� DrawAt
*	���ܣ�
*		�ڸ����ĵ��û��ʻ�
*	������
*		WINDOW *pWindow
*		MYPOINT Point��������
*		char chBrush�����ʻ�ˢ�ӣ������뱳����ͬ
*	����ֵ��
*		��
*  ģ����ʷ:
* 		������2012.11.8, by ���ѷ�
*/
void DrawAt(WINDOW *pWindow, MYPOINT Point, char chBrush)
{
	ARRAYPOINT arrPoint;

	//����ת��
	arrPoint = CoordinateToArrayPoint(pWindow, Point);

	//��
	pWindow->Buffer.carrContent
		[   //����ά�������������ӳ���һά��������
			arrPoint.nRow * pWindow->Buffer.nCols +
			arrPoint.nCol
		]
	= chBrush;
	return;
}

/***********************************************\
��������:
DrawHoriLine
��������:
�ڴ����н���������һ��ˮƽ��
����ģʽ���������һ�����֧�ִ�������
��������:
WINDOW *pWindow //��Ļ������ָ��
MYPOINT StartPoint //���
int nWidth //�߿�
char chBrush//�������ַ�
����ֵ:
��
ģ����ʷ:
������2010.10.10, by ���ѷ�
�޸�:2011.11.07 ��������任
�޸�:2012.11.08 �����°�
\**********************************************/
void DrawHoriLine(WINDOW *pWindow,
	MYPOINT StartPoint, int nWidth, char chBrush)
{
	int i;
	MYPOINT Point;

	Point.y = StartPoint.y;
	Point.x = StartPoint.x;

	for (i = 0; i < nWidth; ++i) //�����߿����㴦��ʼ��������˳�����һ������
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
��������:
DrawVertiLine
��������:
���ַ������ʾ�Ľ���������һ����ֱ��
��������:
WINDOW *pWindow ��Ļ������ָ��
MYPOINT StartPoint //���
int nHeight //�߸�
char ch//�������ַ�
����ֵ:
��
ģ����ʷ:
������2010.10.10, by ���ѷ�
�޸�:2011.11.07 ��������任
�޸ģ�2012.11.08 ��Ӧ�°洰��
\**********************************************/
void DrawVertiLine(WINDOW *pWindow, MYPOINT StartPoint, int nHeight, char chBrush)
{
	int i;
	MYPOINT Point;

	Point.y = StartPoint.y;
	Point.x = StartPoint.x;

	for (i = 0; i < nHeight; ++i)//�����߸ߴ���㴦��ʼ��������˳�����һ������
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
��������:
GetPoint
��������:
�Ӽ����϶���������������һ��MYPOINT�ṹ�ĵ㷵��
��������:
��
����ֵ:
MYPOINT�����ϴ˽ṹ�ĵ�
ģ����ʷ:
������2010.10.25, by ���ѷ�
�޸���2012.11.08����������ɿ��Դ���by ���ѷ�
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
*	��������
*		DrawRect
*	���ܣ�
*		�ڴ���������һ������
*	������
*		WINDOW *pWindow
*		MYRECT rect	 //���νṹ��
*	����ֵ����
*	ģ����ʷ:
������2010.10.10, by ���ѷ�
\**********************************************/

void DrawRect(WINDOW *pWindow, MYRECT rect)
{
	int nRow;
	MYPOINT Point = rect.UpperLeft;

	//�û��ߵ��ַ����ɶ���
	DrawHoriLine(pWindow, Point, rect.nWidth, rect.cEdge);

	//�������
	DrawVertiLine(pWindow, Point, rect.nHeight, rect.cEdge);

	//�����±�
	Point.y -= rect.nHeight;
	DrawHoriLine(pWindow, Point, rect.nWidth, rect.cEdge);

	//�����ұ�
	Point.y = rect.UpperLeft.y;
	Point.x += rect.nWidth - 1;
	DrawVertiLine(pWindow, Point, rect.nHeight, rect.cEdge);

	//��������ַ��������ڲ�������������������������ɣ�Ҳ�ɸĳ����ߣ�Ч��һ��
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
��������:
TestOfDrawingRect
��������:
���ڲ��Ա�ģ�����ṩ�������������Ƿ���ȷ��
�ò��Գ����������һ�������û����Ƶľ���
��������:
��
����ֵ:
��
ģ����ʷ:
������2010.10.10, by ���ѷ�
ע1�����Բ�����ʦ�������������¼ӵĹ����Ƿ���ȷ
ע2�������ճ�������ȫ�����룬Ҫѧϰ��������˼�롣������ֻ��һ�����Σ�
��ĳ�������Ҫ����Ĳ����͹��ܵ�����ȡ������Ҫ������״

\**********************************************/
void TestOfDrawingRect()
{
	MYRECT rect;//����һ�����νṹ��
	WINDOW MyWindow;//����һ������

					//��������õĴ��ڣ���С25�У���100��
	InitWindow(&MyWindow, 100, 25);

	//�ÿո��ʼ������
	InitWindowCanvas(&MyWindow, ' ');

	//������ԭ������(50, 13)����50�У�13��
	SetOrigin(&MyWindow, 50, 13);

	//��ʾ�û�������ε����Ͻ�
	printf("Please input left upper point of the rect(x y):");

	while (1)
	{
		rect.UpperLeft = GetPoint();
		//�ж�����ĵ��Ƿ�Ϸ�
		if (IsValidPoint(&MyWindow, rect.UpperLeft))
			break;
		printf("Error input, please re-enter left upper point of the rect(x y):");
	}

	//��ʾ�û��������ڻ��ߵ��ַ�
	printf("Please input a char used to paint egdes:");
	fflush(stdin);
	rect.cEdge = '*';

	//��ʾ�û������������ľ��ε��ַ�
	printf("Please input a char used to stuff the rect:");
	fflush(stdin);
	rect.cStuff = '+';

	//��ʾ�û�������εĸߺͿ�
	printf("Please input the height and width of the rect(height, width):");

	while (scanf("%d%d", &rect.nHeight, &rect.nWidth) < 2)
	{
		fflush(stdin);
		printf("Error input, please try again:");
	}

	//���ַ����������ɾ���
	DrawRect(&MyWindow, rect);

	//�����ɽ���������Ļ��
	ShowWindow(&MyWindow);

	DestroyWindow(&MyWindow);
	return;
}


//ͬѧ�����ڴ˺��������Լ��Ĵ���
//Ҳ�����Լ��½�һ��CPPģ��
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
	
	//û�ж���㣬ֻ�Ƿ����˿ռ�

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
	//��ת�Ժ������

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
	//SetOrigin();//Ĭ�ϵ�ԭ�������½�
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