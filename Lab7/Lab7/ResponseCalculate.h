/*
TODO:
���ڴ洢������Ӧ����ģ�����ع��ܺͺ���Դ���롣
*/
#pragma once
#ifndef RESPONSECALCULATE_H_
#define RESPONSECALCULATE_H_
#include "extern.h"

/*
��������GetNextTimeStatus
���ܣ����������һʱ��״̬�ĺ���
������
ELEVATORSTATE  *elevator
����ֵ����
*/
void  GetNextTimeStatus(ELEVATORSTATE  *elevator);




/*
��������FindUserCallCanServe
���ܣ�����ǰ�����Ƿ����ͬʱ��Ӧ�����û�ָ��ĺ���
������
ELEVATORSTATE  *elevator
char r_state
����ֵ����
*/
void  FindUserCallCanServe(ELEVATORSTATE  *elevator, char r_state);


/*
��������GetElevatorDirection
���ܣ������ڷ�������д���ֹͣ״̬ʱ�ж���������״̬�ĺ���
������
ELEVATORSTATE *elevator
����ֵ��
*/
char  GetElevatorDirection(ELEVATORSTATE  *elevator);


/*
��������SetElevatorState
���ܣ�������״̬�޸�Ϊ��һʱ��״̬�ĺ���
������
ELEVATORSTATE *elevator
����ֵ����
*/
void  SetElevatorState(ELEVATORSTATE  *elevator);

#endif // !RESPONSECALCULATE_H_
