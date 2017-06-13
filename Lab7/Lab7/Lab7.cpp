#include "stdafx.h"

double m = 640;//������
double n = 480;//������
USERCALL *usercall_list = NULL;//�û�ָ�������׵�ַ����������û�ָ����ٶ�̬����
int usercall_list_len;//�û�ָ�����鳤�ȣ����û�ָ���ļ���һ�ж���
SYSPARAM param_array[100];//ϵͳ��������
int param_num = 0;

struct Elevatorstate elevator_a;//���ڴ�ŵ���a״̬�Ľṹ��
struct Elevatorstate elevator_b;//���ڴ�ŵ���b״̬�Ľṹ��
RESPONSELISTHEADNODE *response_list = NULL;// ������Ӧָ����У�����ָʾ��ǰ��Ӧ�ĵ���ָ��

char UserRequestFilesPath[150] = ".\\UserRequestFiles";//����û�ָ���ļ���Ŀ¼
char SimulationFilesPath[150] = ".\\SimlationFiles";//����û���ʷ�����ļ���Ŀ¼

char user_file_name[100];//�û���š��û�ָ���ļ������Ƶ�����

char simulate_file_name_input[100];//�û�����������롮��ʷ�����ļ������Ƶ�����

char simulate_file_name_output[100];//�û���������������ʷ�����ļ������Ƶ�����

int finish_call_num;//���ڼ�¼��ǰ����Ӧ��ɵ��û�ָ�����
int time;//���ڼ�¼��ǰ����ʱ��
int status_change_flag;//���ڼ�¼��һʱ������ڵ�ǰ״̬�Ƿ�ı䣬1�䣬0����

int ElevatorHeight = 20;//�����ܲ�����Ĭ��20
int Delaytime = 1000; //����չʾÿ��״̬������ӳ�ʱ�䣬��λms��Ĭ��1000
int ElevatorSpeed = 1;//
int SimulateSpeed = 1000;//������Delaytime


/*
void main()
{
	
}
*/

//������
int main() {
	SystemInit();
	while (1) {
		ShowMenu(1);
		int input;
		scanf("%d", &input);
		while (getchar() != '\n');
		if (input == 1)
		{
			SilenceSimulate();
		}
		else if (input == 2)
		{
			MovieSimulate();
		}
		else if (input == 3)
		{
			FullSimulate();
		}
		else if (input == 4)
		{
			HistorySimulate();
		}
		else if (input == 5)
		{
			ParamConf();
		}
		else if (input == 0)
		{
			return 0;
		}
		else
		{
			printf("Input Error!\n");
		}
	}
	return 0;
}
