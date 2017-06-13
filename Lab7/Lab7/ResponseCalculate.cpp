/*
TODO:
用于存储电梯响应计算模块的相关功能和函数源代码。
*/
#include "stdafx.h"
#include "extern.h"

/*
函数名：GetNextTimeStatus
功能：计算电梯下一时刻状态的函数
参数：
ELEVATORSTATE  *elevator
返回值：无
*/
void  GetNextTimeStatus(ELEVATORSTATE  *elevator)
{
	/*
	待响应列表为空，需要把usercall_list中，calltime可以响应的添加到 responselist
	待响应列表不为空，需要把user call list中calltime可以添加的响应添加到response list
	*/
	if (response_list->head == NULL)
	{
		int index = response_list->Responsed_num;
		if (index >= usercall_list_len) goto loop;
		if (usercall_list[index].call_time <= time)
		{
			RESPONSELISTNODE *p = (RESPONSELISTNODE*)malloc(sizeof(RESPONSELISTNODE));
			p->usercall_index = index;
			p->next_node = NULL;
			response_list->head = p;
			response_list->tail = p;
			response_list->list_num = 1;
			response_list->Responsed_num++;
			printf("Responsed_num:%d  time:%d\n", response_list->Responsed_num, time);
			status_change_flag = 1;
		}
		goto loop;
	}
	else
	{
		int index = response_list->Responsed_num;
		while (index < usercall_list_len)
		{
			if (usercall_list[index].call_time <= time)
			{
				RESPONSELISTNODE *p = (RESPONSELISTNODE*)malloc(sizeof(RESPONSELISTNODE));
				p->usercall_index = index;
				p->next_node = NULL;
				response_list->tail->next_node = p;
				response_list->tail = p;
				response_list->list_num++;

				response_list->Responsed_num++;
				printf("Responsed_num:%d   time:%d\n", response_list->Responsed_num, time);
				status_change_flag = 1;
				index = response_list->Responsed_num;
				//添加合适的指令到用户指令到response_list.
			}
			else
			{
				goto loop;
			}
		}
	}



	//从response list 中把可以给serve_list的任务分走
loop:do {
	//电梯没有任务
	if (elevator->serve_list == NULL)
	{
		//任务列表也为空
		if (response_list->head == NULL)
		{
			SetElevatorState(elevator);
			return;
		}
		//电梯没有任务，任务列表有，需要把任务列表中的任务添加到serve_list并在response_list删除
		else {
			elevator->serve_list = (SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
			if (elevator->serve_list == NULL) 	printf("Can't Ollocate Memory!\n");
			//为电梯serve_list分配空间

			elevator->serve_list->user_call =
				&usercall_list[response_list->head->usercall_index];
			printf("第%d个指令到了serve_list？time:%d\n", response_list->head->usercall_index, time);
			elevator->serve_list->next_node = NULL;
			status_change_flag = 1;

			//电梯到达了用户所在的楼层，状态 E进入服务状态
			if (elevator->current_floor == elevator->serve_list->user_call->user_floor)
				elevator->serve_list->serve_state = 'E';
			//电梯未到达用户所在的楼层，状态 P进入服务前状态
			else
				elevator->serve_list->serve_state = 'P';


			//把交给电梯后的任务从responselist中删除
			if (response_list->head == response_list->tail)
			{
				free(response_list->head);
				response_list->head = NULL;
				response_list->tail = NULL;
				response_list->list_num = 0;
			}
			else
			{
				ResponseListNode *q = response_list->head;
				response_list->head = response_list->head->next_node;
				response_list->list_num--;
				free(q);
				q = NULL;
			}

			FindUserCallCanServe(elevator, GetElevatorDirection(elevator));//添加可以同时响应的任务
			SetElevatorState(elevator);//设置电梯状态
			return;
		}
	}

	//电梯有任务
	else
	{
		if (elevator->run_state == 'S')//电梯有任务，而且停了，用户到了
		{
			char nextdirect = GetElevatorDirection(elevator);//求停了以后下个状态去哪
			if (nextdirect != 'S' && nextdirect != ' ')
			{
				FindUserCallCanServe(elevator, nextdirect);
			}
			else
			{
				//下个状态尴尬了？有任务停下来干嘛?
				//这个时候要不要回去？
				putchar(nextdirect);
				printf("会不会尴尬呢。。。\n");
			}
			SetElevatorState(elevator);
			return;
		}
		else//电梯没停
		{
			FindUserCallCanServe(elevator, elevator->run_state);
			SetElevatorState(elevator);
			return;
		}


	}
} while (0);
}



/*
函数名：FindUserCallCanServe(应该正常)
功能：处理当前电梯是否可以同时响应其它用户指令的函数
参数：
ELEVATORSTATE  *elevator
char r_state
返回值：无
*/
void  FindUserCallCanServe(ELEVATORSTATE  *elevator, char r_state)
{
	//r_state是否指的就是 elevator->run_state...
	int uf = elevator->serve_list->user_call->user_floor;
	char us = elevator->serve_list->user_call->call_type;//正在响应的'U','D'
	int ue = elevator->run_state;

	if (response_list->head == NULL) return;//没有可以同时响应的。。

	RESPONSELISTNODE *r = response_list->head, *k = r, *p = r;
	//r->>>>>>>>>>>>>responselist->head
	//
	//
	int m = elevator->current_floor;//当前楼层
	while (1)
	{
		int i = p->usercall_index;//待添加的usercall的序号
		int f = usercall_list[i].user_floor;
		int t = usercall_list[i].user_target;
		int s = usercall_list[i].call_type;

		int flag = 0;//判断是否可以顺带响应的标志变量
		if (us == r_state)
		{
			if (r_state == 'U' && s == 'U' && f > m)
			{
				flag = 1;
			}
			else if (r_state == 'D' && s == 'D' && f < m)
			{
				flag = 1;
			}
			else if (ue == 'S' && f == m)
			{
				flag = 1;
			}
		}
		else
		{
			if (r_state == 'U' && s == 'U' && f >= m && t <= uf)
			{
				flag = 1;
			}
			else if (r_state == 'D' && s == 'D' && f <= m && t >= uf)
			{
				flag = 1;
			}
			else if (ue == 'S' && f == m && r_state == 'U' && t <= uf)
			{
				flag = 1;
			}
			else if (ue == 'S' && f == m && r_state == 'D' && t >= uf)
			{
				flag = 1;
			}
		}

		//可以顺带响应
		if (flag == 1)
		{
			SERVELISTNODE *q = (SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
			q->user_call = &usercall_list[i];
			printf("第%d个指令到了serve_list？time:%d(顺带响应)\n", response_list->head->usercall_index, time);
			q->next_node = NULL;
			if (f == m)
			{
				q->serve_state = 'E';
			}
			else
			{
				q->serve_state = 'P';
			}
			//把顺带响应的指令添加到serve_list的尾部
			SERVELISTNODE *balabala = elevator->serve_list;
			while (balabala->next_node != NULL) balabala = balabala->next_node;
			balabala->next_node = q;
			status_change_flag = 1;

			//删掉response list 中的p
			if (p->next_node == NULL)//p是尾
			{
				//p是头
				if (p == response_list->head)
				{
					response_list->head = NULL;
					response_list->tail = NULL;
					response_list->list_num = 0;
					free(p);
					p = NULL;
				}
				//p是尾，但不是头
				else
				{
					response_list->tail = r;//把链表头赋值给链表尾？
					r->next_node = NULL;//链表头下一个结点设置为空
					response_list->list_num--;
					free(p);
					p = NULL;
					/*ResponseListNode *q = response_list->head;
					while (q->next_node != p)
					{
					q = q->next_node;
					}
					response_list->tail = q;
					response_list->list_num--;
					free(p);
					p = NULL;*/
				}
				return;
			}

			else//p不是尾结点
			{
				if (p == response_list->head)//p是头结点
				{
					response_list->head = p->next_node;
					free(p);
					p = response_list->head;
					k = p;
					r = k;
					response_list->list_num--;
				}
				else//p是中间的一个结点
				{
					r->next_node = k;
					free(p);
					p = k;
					k = k->next_node;
					response_list->list_num--;
				}
				if (p == NULL) return;
				else continue;
			}
		}
		//没有可以顺带响应的指令
		else
		{
			if (p->next_node == NULL) return;//第i个结点不行，也没有下一个结点了

			if (p == response_list->head)//p是待响应列表中的第一个
			{
				p = p->next_node;
				k = p->next_node;
			}
			else//p不是待响应列表的第一个
			{
				r = p;
				p = k;
				k = p->next_node;
			}

			if (p == NULL) return;
			else continue;
		}
	}
}

/*
函数名：GetElevatorDirection(调试正常)
功能：电梯在服务过程中处于停止状态时判断其上下行状态的函数
参数：
ELEVATORSTATE *elevator
返回值：
char e_status
*/
char  GetElevatorDirection(ELEVATORSTATE  *elevator)
{
	char e_status = ' ';
	if (elevator->serve_list == NULL)
	{
		e_status = 'S';
		return e_status;
	}
	SERVELISTNODE* p = elevator->serve_list;
	int m = elevator->current_floor;
	if (p->serve_state == 'P')
	{
		int f = p->user_call->user_floor;
		if (f > m)
		{
			e_status = 'U';
			return e_status;
		}
		else
		{
			e_status = 'D';
			return e_status;
		}
	}
	else if (p->serve_state == 'E')
	{
		int t = p->user_call->user_target;
		if (t > m)
		{
			e_status = 'U';
			return e_status;
		}
		else
		{
			e_status = 'D';
			return e_status;
		}
	}
	else return e_status;
}


/*
函数名：SetElevatorState(调试正常)
功能：将电梯状态修改为下一时刻状态的函数
参数：
ELEVATORSTATE *elevator
返回值：无
*/
void  SetElevatorState(ELEVATORSTATE  *elevator)
{
	int m = elevator->current_floor;
	char e_rs = elevator->run_state;
	int step_flag = 0;

	if (elevator->serve_list == NULL)
	{
		elevator->current_floor = elevator->current_floor + step_flag;
		return;
	}
	

	SERVELISTNODE *r = elevator->serve_list;
	SERVELISTNODE *p = r;
	SERVELISTNODE *k = p;

	while (1) {
		int f = p->user_call->user_floor;
		int t = p->user_call->user_target;
		char s = p->serve_state;


		if (e_rs == 'U') {//电梯运行处于上升状态
			step_flag = 1;

			if (s == 'E' && t == m + 1) {
				elevator->run_state = 'S';
				status_change_flag = 1;
				if (p->next_node == NULL) {
					if (p == elevator->serve_list) {
						elevator->serve_list = NULL;
						free(p);
						r = NULL;
						k = NULL;
						p = NULL;
					}
					else {
						r->next_node = NULL;
						free(p);
						k = NULL;
						p = NULL;
					}
				}
				else {
					if (p == elevator->serve_list) {
						elevator->serve_list = p->next_node;
						free(p);
						r = elevator->serve_list;
						k = r;
						p = r;
					}
					else {
						r->next_node = k;
						free(p);
						p = k;
						k = k->next_node;
					}
				}
				finish_call_num++;
			}
			else if (s == 'P' && f == m + 1)
			{
				elevator->run_state = 'S';
				p->serve_state = 'E';
				status_change_flag = 1;
				p = p->next_node;
			}
			else {
				if (p->next_node == NULL)
				{
					elevator->current_floor = elevator->current_floor + step_flag;
					return;
				}
				else {
					p = p->next_node;//分析下一个结点来判断
					continue;
				}
			}
		}
		else if (e_rs == 'D') {//电梯运行处于下降状态
			step_flag = -1;
			if (s == 'E' && t == m - 1)//电梯处于服务中状态，且目标楼层就在楼下
			{
				elevator->run_state = 'S';
				status_change_flag = 1;
				if (p->next_node == NULL) {

					if (p == elevator->serve_list) 
					{
						elevator->serve_list = NULL;
						free(p);
						r = NULL;
						k = NULL;
						p = NULL;
					}
					else {
						r->next_node = NULL;
						free(p);
						k = NULL;
						p = NULL;
						r = NULL;///////////////////
					}
				}
				else {
					if (p == elevator->serve_list) {
						elevator->serve_list = p->next_node;
						free(p);
						r = elevator->serve_list;
						k = r;
						p = r;
					}
					else {
						r->next_node = k;
						free(p);
						p = k;
						k = k->next_node;
					}
				}
				finish_call_num++;
			}
			else if (s == 'P' && f == m - 1)//电梯处于服务前状态，且用户所在楼层在楼下
			{
				elevator->run_state = 'S';
				p->serve_state = 'E';
				status_change_flag = 1;
				p = p->next_node;
			}
			else//电梯处于服务状态
			{
				if (p->next_node == NULL)
				{
					elevator->current_floor = elevator->current_floor + step_flag;
					return;
				}
				else {
					p = p->next_node;//分析下一个结点
					continue;
				}
			}
		}
		else {
			if (s == 'P')
			{
				if (f > m)
				{
					elevator->run_state = 'U';
				}
				else
				{
					elevator->run_state = 'D';

				}
				status_change_flag = 1;
				elevator->current_floor = elevator->current_floor + step_flag;
				return;
			}
			else if (s == 'E')
			{
				if (t > m)
				{
					elevator->run_state = 'U';
				}
				else
				{
					elevator->run_state = 'D';
				}
				status_change_flag = 1;
				elevator->current_floor = elevator->current_floor + step_flag;
				return;
			}
		}

		if (p == NULL)
		{
			elevator->current_floor = elevator->current_floor + step_flag;
			return;
		}
	}
}
