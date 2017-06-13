/*
TODO:
���ڴ洢������Ӧ����ģ�����ع��ܺͺ���Դ���롣
*/
#include "stdafx.h"
#include "extern.h"

/*
��������GetNextTimeStatus
���ܣ����������һʱ��״̬�ĺ���
������
ELEVATORSTATE  *elevator
����ֵ����
*/
void  GetNextTimeStatus(ELEVATORSTATE  *elevator)
{
	/*
	����Ӧ�б�Ϊ�գ���Ҫ��usercall_list�У�calltime������Ӧ����ӵ� responselist
	����Ӧ�б�Ϊ�գ���Ҫ��user call list��calltime������ӵ���Ӧ��ӵ�response list
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
				//��Ӻ��ʵ�ָ��û�ָ�response_list.
			}
			else
			{
				goto loop;
			}
		}
	}



	//��response list �аѿ��Ը�serve_list���������
loop:do {
	//����û������
	if (elevator->serve_list == NULL)
	{
		//�����б�ҲΪ��
		if (response_list->head == NULL)
		{
			SetElevatorState(elevator);
			return;
		}
		//����û�����������б��У���Ҫ�������б��е�������ӵ�serve_list����response_listɾ��
		else {
			elevator->serve_list = (SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
			if (elevator->serve_list == NULL) 	printf("Can't Ollocate Memory!\n");
			//Ϊ����serve_list����ռ�

			elevator->serve_list->user_call =
				&usercall_list[response_list->head->usercall_index];
			printf("��%d��ָ���serve_list��time:%d\n", response_list->head->usercall_index, time);
			elevator->serve_list->next_node = NULL;
			status_change_flag = 1;

			//���ݵ������û����ڵ�¥�㣬״̬ E�������״̬
			if (elevator->current_floor == elevator->serve_list->user_call->user_floor)
				elevator->serve_list->serve_state = 'E';
			//����δ�����û����ڵ�¥�㣬״̬ P�������ǰ״̬
			else
				elevator->serve_list->serve_state = 'P';


			//�ѽ������ݺ�������responselist��ɾ��
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

			FindUserCallCanServe(elevator, GetElevatorDirection(elevator));//��ӿ���ͬʱ��Ӧ������
			SetElevatorState(elevator);//���õ���״̬
			return;
		}
	}

	//����������
	else
	{
		if (elevator->run_state == 'S')//���������񣬶���ͣ�ˣ��û�����
		{
			char nextdirect = GetElevatorDirection(elevator);//��ͣ���Ժ��¸�״̬ȥ��
			if (nextdirect != 'S' && nextdirect != ' ')
			{
				FindUserCallCanServe(elevator, nextdirect);
			}
			else
			{
				//�¸�״̬�����ˣ�������ͣ��������?
				//���ʱ��Ҫ��Ҫ��ȥ��
				putchar(nextdirect);
				printf("�᲻�������ء�����\n");
			}
			SetElevatorState(elevator);
			return;
		}
		else//����ûͣ
		{
			FindUserCallCanServe(elevator, elevator->run_state);
			SetElevatorState(elevator);
			return;
		}


	}
} while (0);
}



/*
��������FindUserCallCanServe(Ӧ������)
���ܣ�����ǰ�����Ƿ����ͬʱ��Ӧ�����û�ָ��ĺ���
������
ELEVATORSTATE  *elevator
char r_state
����ֵ����
*/
void  FindUserCallCanServe(ELEVATORSTATE  *elevator, char r_state)
{
	//r_state�Ƿ�ָ�ľ��� elevator->run_state...
	int uf = elevator->serve_list->user_call->user_floor;
	char us = elevator->serve_list->user_call->call_type;//������Ӧ��'U','D'
	int ue = elevator->run_state;

	if (response_list->head == NULL) return;//û�п���ͬʱ��Ӧ�ġ���

	RESPONSELISTNODE *r = response_list->head, *k = r, *p = r;
	//r->>>>>>>>>>>>>responselist->head
	//
	//
	int m = elevator->current_floor;//��ǰ¥��
	while (1)
	{
		int i = p->usercall_index;//����ӵ�usercall�����
		int f = usercall_list[i].user_floor;
		int t = usercall_list[i].user_target;
		int s = usercall_list[i].call_type;

		int flag = 0;//�ж��Ƿ����˳����Ӧ�ı�־����
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

		//����˳����Ӧ
		if (flag == 1)
		{
			SERVELISTNODE *q = (SERVELISTNODE*)malloc(sizeof(SERVELISTNODE));
			q->user_call = &usercall_list[i];
			printf("��%d��ָ���serve_list��time:%d(˳����Ӧ)\n", response_list->head->usercall_index, time);
			q->next_node = NULL;
			if (f == m)
			{
				q->serve_state = 'E';
			}
			else
			{
				q->serve_state = 'P';
			}
			//��˳����Ӧ��ָ����ӵ�serve_list��β��
			SERVELISTNODE *balabala = elevator->serve_list;
			while (balabala->next_node != NULL) balabala = balabala->next_node;
			balabala->next_node = q;
			status_change_flag = 1;

			//ɾ��response list �е�p
			if (p->next_node == NULL)//p��β
			{
				//p��ͷ
				if (p == response_list->head)
				{
					response_list->head = NULL;
					response_list->tail = NULL;
					response_list->list_num = 0;
					free(p);
					p = NULL;
				}
				//p��β��������ͷ
				else
				{
					response_list->tail = r;//������ͷ��ֵ������β��
					r->next_node = NULL;//����ͷ��һ���������Ϊ��
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

			else//p����β���
			{
				if (p == response_list->head)//p��ͷ���
				{
					response_list->head = p->next_node;
					free(p);
					p = response_list->head;
					k = p;
					r = k;
					response_list->list_num--;
				}
				else//p���м��һ�����
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
		//û�п���˳����Ӧ��ָ��
		else
		{
			if (p->next_node == NULL) return;//��i����㲻�У�Ҳû����һ�������

			if (p == response_list->head)//p�Ǵ���Ӧ�б��еĵ�һ��
			{
				p = p->next_node;
				k = p->next_node;
			}
			else//p���Ǵ���Ӧ�б�ĵ�һ��
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
��������GetElevatorDirection(��������)
���ܣ������ڷ�������д���ֹͣ״̬ʱ�ж���������״̬�ĺ���
������
ELEVATORSTATE *elevator
����ֵ��
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
��������SetElevatorState(��������)
���ܣ�������״̬�޸�Ϊ��һʱ��״̬�ĺ���
������
ELEVATORSTATE *elevator
����ֵ����
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


		if (e_rs == 'U') {//�������д�������״̬
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
					p = p->next_node;//������һ��������ж�
					continue;
				}
			}
		}
		else if (e_rs == 'D') {//�������д����½�״̬
			step_flag = -1;
			if (s == 'E' && t == m - 1)//���ݴ��ڷ�����״̬����Ŀ��¥�����¥��
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
			else if (s == 'P' && f == m - 1)//���ݴ��ڷ���ǰ״̬�����û�����¥����¥��
			{
				elevator->run_state = 'S';
				p->serve_state = 'E';
				status_change_flag = 1;
				p = p->next_node;
			}
			else//���ݴ��ڷ���״̬
			{
				if (p->next_node == NULL)
				{
					elevator->current_floor = elevator->current_floor + step_flag;
					return;
				}
				else {
					p = p->next_node;//������һ�����
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
