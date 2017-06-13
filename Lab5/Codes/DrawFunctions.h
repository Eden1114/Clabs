#pragma once
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
  �������ѷ���2010��10��25�մ�����ģ�飬email: yflin@bjtu.edu.cn
	�������ѷ���2011��11��07���޸ı�ģ�飬email: yflin@bjtu.edu.cn
	  �������ѷ���2012��11��08���޸ı�ģ�飬����Window������ر�ʾ��Ļ
		������2016��9��20���޸ı�ģ�飬email:shhan@bjtu.edu.cn
\**********************************************************/

		//�˴���ֹ���ظ�����ͷ�ļ����������ظ�����
#ifndef DRAWFUNCTIONS_H_
#define DRAWFUNCTIONS_H_

		//�����еĵ�����ṹ�嶨��
struct MyPoint {
	int x; //������
	int y; //������
};
//ע�������MYPOINT��ԭ����Щ����������VCĳЩ�����Ѿ���POINT�Ķ���
typedef struct MyPoint MYPOINT; //��������MYPOINT

typedef struct ArrayPoint {
	int nRow; //���±�
	int nCol; //���±�
}ARRAYPOINT;

//������νṹ������MYRECT
typedef struct MyRect {
	MYPOINT UpperLeft;//���Ͻ�
	int nWidth;//���
	int nHeight;//�߶�
	char cEdge;//��ʾ�ߵ��ַ�
	char cStuff;//�����������ַ�
}MYRECT;

/*	������Ļ����������WINDOWBUFFER
*	carrContentΪ���洰�����ݵ��ַ��������׵�ַ��ʹ��ʱӦ����һ��[nRows][nCols]�Ķ�ά����
*	��Ļ�ϵ�����������ж�Ӧ��ϵΪ�������е��� = ������ - ��Ļ�ϵ��� - 1
*
*/
typedef struct WindowBuffer {
	char *carrContent;//�Զ�����Ļ�����д�������õĴ洢�ռ�(������)����ʹ��ʱ��Ҫ���俴��һ����ά�ַ�����
	int nRows;//��ά�������������Ӧ���������Y��߶�
	int nCols;//��ά�������������Ӧ���������X�᳤��+1�����һ�й̶����ڴ�Ż��з�
}WINDOWBUFFER;

/*
*	��������
*/
typedef struct Window {
	WINDOWBUFFER Buffer;	//�ô�������Ӧ���ַ�������
	int nOriginColInBuffer;	//ԭ����WINDOWBUFFER�еĶ�Ӧ���к�
	int nOriginRowInBuffer; //ԭ����WINDOWBUFFER�еĶ�Ӧ���к�
							//������ԭ���������½ǣ���ֱ�Ϊ:nOriginColInBufferӦ�����0��
							//nOriginRowInBufferӦ��ΪWindowBuffer.nRows-1
	int nWidth;		//���ڿ�� 
	int nHeight;	//���ڸ߶�
	char szCaption[120]; //���ڱ���

}WINDOW;

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
*/
int InitWindow(WINDOW *pWindow, int nWidth, int nHeight);

/*
*	�������� DestroyWindow
*	���ܣ�
*		���ٴ��ڣ��ͷŴ��ڵ��ַ�������
*	������
*		WINDOW *pWindow
*	����ֵ��
*		��
*/
void DestroyWindow(WINDOW *pWindow);

/*
*	�������� ShowWindow
*	���ܣ�
*		�ڿ���̨�ַ��ն�����ʾ�����е�����
*	������
*		WINDOW *pWindow
*
*	����ֵ��
*		��
*
*/

void ShowWindow(WINDOW *pWindow);
/*
*	��������
*		InitWindowCanvas
*	���ܣ�
*		��ʼ�����ڵĻ���
*		1�������ڵľ������򿴳�һ�Ż������ò����и������ַ�ˢ��������Ż������𵽳�ʼ������
*		2�����ڴ��ڶ�Ӧ�Ķ�ά�ַ������ÿ�к�����ϻ��з�
*	������
*		WINDOW *pWindow //����ָ��
*		char chBrush  //��ʼ��
*
*	����ֵ��
*		��
*
*/
void InitWindowCanvas(WINDOW *pWindow, char chBrush);


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
*
*/
void ClearWindow(WINDOW *pWindow, char chBrush);

/*
*	�������� SetOrigin
*	���ܣ�
*		�Ѵ��ڿ�һ��ƽ����������ʱ���趨����ϵԭ��
*	������
*		WINDOW *pWindow
*		int nCol	//ԭ���Ӧ���к�
*		int nRow	//ԭ���Ӧ���к�
*/
void SetOrigin(WINDOW *pWindow, int nCol, int nRow);

//�Ӽ����϶���������������һ��MYPOINT�ṹ�ĵ㷵��
MYPOINT GetPoint();

/*
*	�������� CoordinateToArrayPoint
*	���ܣ�����Ļ�ϵ�����ת�����������꣬ת����ʽ��
*	������
*		WINDOW *pWindow ����ָ��
*		MYPOINT point ����������ϵ�ϵĵ�
*	����ֵ��
*		���ڻ����е�carrContent�е��ַ������е����꣨�кţ��кţ�
*/
ARRAYPOINT CoordinateToArrayPoint(WINDOW *pWindow, MYPOINT Point);

/*	�������� IsValidPoint
*	���ܣ�
*		�ж������ĵ��Ƿ��Ǵ����еĺϷ���
*	������
*		WINDOW *pWindow
*		MYPOINT Point
*	����ֵ��
*		1 �ǺϷ���
*		0 �ǺϷ���
*/
int IsValidPoint(WINDOW *pWindow, MYPOINT Point);


/*
*	�������� DrawAt
*	���ܣ�
*		�ڸ����ĵ��û��ʻ�
*	������
*		MYPOINT Point��������
*		char chBrush�����ʻ�ˢ�ӣ������뱳����ͬ
*	����ֵ��
*		��
*/
void DrawAt(WINDOW *pWindow, MYPOINT Point, char chBrush);

/***********************************************\
��������:
DrawVertiLine
��������:
���ַ������ʾ�Ľ���������һ����ֱ��
ֻ֧���������»�
��������:
SCREENBUFFER *pScreenBuffer ��Ļ������ָ��
MYPOINT StartPoint //���
int nHeight //�߸�
char chBrush //�������ַ�
����ֵ:
��
ģ����ʷ:
������2010.10.10, by ���ѷ�
�޸�:2011.11.07 ��������任
�޸�:2012.11.08 �����°�ӿ�
\**********************************************/
void DrawVertiLine(WINDOW *pWindow,
	MYPOINT StartPoint, int nHeight, char chBrush);


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
�޸�:2012.11.08 �����°�ӿ�
\**********************************************/
void DrawHoriLine(WINDOW *pWindow,
	MYPOINT StartPoint, int nWidth, char chBrush);


/***********************************************\
��������:
DrawRect
����������
�ڴ���������һ������
����������
WINDOW *pWindow //��Ļ������ָ��
MYRECT rect	 //���νṹ��
����ֵ����
ģ����ʷ��
������2010.10.10, by ���ѷ�
\**********************************************/
void DrawRect(WINDOW *pWindow, MYRECT rect);



void TestOfDrawingRect();//���Գ���

						 //���ڴ˺���Ӵ���

struct duobianxin
{
	int number = 0;     //����εĶ������
	MYPOINT * points;   //���ڶ�̬�洢����ζ��������
};
typedef struct duobianxin DBX;
//�����˶���εĽṹ��



/***********************************************\
��������:
DrawLine
����������
�ڴ���������һ��ֱ�߶�
����������
WINDOW *pWindow //��Ļ������ָ��
MYPOINT a //�߶εĶ˵�a
MYPOINT b //�߶εĶ˵�b
����ֵ����
ģ����ʷ��
������2017.4.12��by ����
\**********************************************/
void DrawLine(WINDOW* pWindow, 
	     MYPOINT a, MYPOINT b, char chBrush);



/***********************************************\
��������:
Initduobianxin
����������
��ʼ�������a,���ö���ζ������
����������
DBX* a //��Ҫ��ʼ���Ķ���εĵ�ַ
int n  //��ʼ���Ķ���εĶ������
����ֵ�������ʼ���ɹ������ض������������ʼ��ʧ�ܣ�����0
ģ����ʷ��
������2017.4.12��by ����
\**********************************************/
int Initduobianxin(DBX* a, int n);



/***********************************************\
��������:
Routeduobianxin
����������
��ת�����a
����������
DBX* a //��Ҫ��ת�Ķ���εĵ�ַ
double //��Ҫ��ת�ĽǶ�
����ֵ����ת�ɹ���Ķ���νṹ��
ģ����ʷ��
������2017.4.12��by ����
\**********************************************/
DBX Routeduobianxin(DBX* a, double angle);



/***********************************************\
��������:
Drawduobianxin
����������
�ڴ���������һ�������
����������
WINDOW *pWindow //��Ļ������ָ��
DBX* a //��Ҫ��ת�Ķ���εĵ�ַ
char chBrush //�������ַ�
ģ����ʷ��
������2017.4.12��by ����
\**********************************************/
void Drawduobianxin(WINDOW *pWindow, DBX* a, char chBrush);



#endif