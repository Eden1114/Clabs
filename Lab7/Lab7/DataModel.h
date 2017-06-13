/*
TODO:
	用于数据结构体的声明
修改：
	在servelist结点中添加了n，标记servelist中第n个响应
	
*/
#pragma once
#ifndef DATAMODEL_H_
#define DATAMODEL_H_

/*
USERCALL 用于存储用户指令的结构体
int user_floor：用户所在楼层
int user_target：用户目标楼层
int call_time：用户请求时刻
char call_type：用户指令类型‘U’表示上行，‘D'表示下行
*/
struct UserCall {
	int user_floor;//用户所在楼层
	int user_target;//用户目标楼层
	int call_time;//用户请求时刻
	char call_type;//用户指令类型‘U’表示上行，‘D'表示下行
};
typedef struct UserCall USERCALL;


//保存命令的数组的最大长度
const int MAX_PARAM_NAME_LEN = 100;
const int MAX_PARAM_VALUE_LEN = 100;
/*
系统参数数据
MAX_PARAM_NAME_LEN：表示存放参数名最大存储字符个数
MAX_PARAM_VALUE_LEN：参数值的字符数组最大存储字符个数
*/
struct SysParam {
	char param_name[MAX_PARAM_NAME_LEN];
	char param_value[MAX_PARAM_VALUE_LEN];
};
typedef struct SysParam SYSPARAM;


/*
char serve_state：电梯服务状态
USERCALL *user_call：电梯当前响应用户指令时，指向数组的某个元素
struct ServeListNode *next_node：存储下一个结点的地址

TODO:
为user_call指针分配空间
*/
struct ServeListNode {
	char serve_state;//电梯服务状态
	USERCALL *user_call;//电梯当前响应用户指令时，指向数组的某个元素
	struct ServeListNode *next_node;//存储下一个结点的地址
};
typedef ServeListNode SERVELISTNODE;


/*
int current_floor：电梯当前所处的楼层
char run_state：电梯运行状态
SERVELISTNODE *serve_list：电梯响应的用户指令队列
*/
struct Elevatorstate {
	int current_floor;//电梯当前所处的楼层
	char run_state;//电梯运行状态
	SERVELISTNODE *serve_list;//电梯响应的用户指令队列
};
typedef struct Elevatorstate ELEVATORSTATE;


/*
int usercall_index：用户指令在指令数组中对应的序号
struct ResponseListNode *next_node：存储下一个结点的地址
*/
struct ResponseListNode {
	int usercall_index;//用户指令在指令数组中对应的序号
	struct ResponseListNode *next_node;//存储下一个结点的地址
};
typedef struct ResponseListNode RESPONSELISTNODE;


/*
//int list_num：待响应的用户链表中数据结点的个数
//struct ResponseListHeadNode *head：链表中第一个数据结点的指针
//struct ResponseListHeadNode *tail：链表中最后一个数据结点的指针
*/
struct ResponseListHeadNode {
	int list_num;//待响应的用户链表中数据结点的个数
	struct ResponseListNode *head;//链表中第一个数据结点的指针
	struct ResponseListNode *tail;//链表中最后一个数据结点的指针
	int Responsed_num;
};
typedef struct ResponseListHeadNode RESPONSELISTHEADNODE;


#endif // !DATAMODEL_H_