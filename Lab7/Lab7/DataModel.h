/*
TODO:
	�������ݽṹ�������
�޸ģ�
	��servelist����������n�����servelist�е�n����Ӧ
	
*/
#pragma once
#ifndef DATAMODEL_H_
#define DATAMODEL_H_

/*
USERCALL ���ڴ洢�û�ָ��Ľṹ��
int user_floor���û�����¥��
int user_target���û�Ŀ��¥��
int call_time���û�����ʱ��
char call_type���û�ָ�����͡�U����ʾ���У���D'��ʾ����
*/
struct UserCall {
	int user_floor;//�û�����¥��
	int user_target;//�û�Ŀ��¥��
	int call_time;//�û�����ʱ��
	char call_type;//�û�ָ�����͡�U����ʾ���У���D'��ʾ����
};
typedef struct UserCall USERCALL;


//����������������󳤶�
const int MAX_PARAM_NAME_LEN = 100;
const int MAX_PARAM_VALUE_LEN = 100;
/*
ϵͳ��������
MAX_PARAM_NAME_LEN����ʾ��Ų��������洢�ַ�����
MAX_PARAM_VALUE_LEN������ֵ���ַ��������洢�ַ�����
*/
struct SysParam {
	char param_name[MAX_PARAM_NAME_LEN];
	char param_value[MAX_PARAM_VALUE_LEN];
};
typedef struct SysParam SYSPARAM;


/*
char serve_state�����ݷ���״̬
USERCALL *user_call�����ݵ�ǰ��Ӧ�û�ָ��ʱ��ָ�������ĳ��Ԫ��
struct ServeListNode *next_node���洢��һ�����ĵ�ַ

TODO:
Ϊuser_callָ�����ռ�
*/
struct ServeListNode {
	char serve_state;//���ݷ���״̬
	USERCALL *user_call;//���ݵ�ǰ��Ӧ�û�ָ��ʱ��ָ�������ĳ��Ԫ��
	struct ServeListNode *next_node;//�洢��һ�����ĵ�ַ
};
typedef ServeListNode SERVELISTNODE;


/*
int current_floor�����ݵ�ǰ������¥��
char run_state����������״̬
SERVELISTNODE *serve_list��������Ӧ���û�ָ�����
*/
struct Elevatorstate {
	int current_floor;//���ݵ�ǰ������¥��
	char run_state;//��������״̬
	SERVELISTNODE *serve_list;//������Ӧ���û�ָ�����
};
typedef struct Elevatorstate ELEVATORSTATE;


/*
int usercall_index���û�ָ����ָ�������ж�Ӧ�����
struct ResponseListNode *next_node���洢��һ�����ĵ�ַ
*/
struct ResponseListNode {
	int usercall_index;//�û�ָ����ָ�������ж�Ӧ�����
	struct ResponseListNode *next_node;//�洢��һ�����ĵ�ַ
};
typedef struct ResponseListNode RESPONSELISTNODE;


/*
//int list_num������Ӧ���û����������ݽ��ĸ���
//struct ResponseListHeadNode *head�������е�һ�����ݽ���ָ��
//struct ResponseListHeadNode *tail�����������һ�����ݽ���ָ��
*/
struct ResponseListHeadNode {
	int list_num;//����Ӧ���û����������ݽ��ĸ���
	struct ResponseListNode *head;//�����е�һ�����ݽ���ָ��
	struct ResponseListNode *tail;//���������һ�����ݽ���ָ��
	int Responsed_num;
};
typedef struct ResponseListHeadNode RESPONSELISTHEADNODE;


#endif // !DATAMODEL_H_