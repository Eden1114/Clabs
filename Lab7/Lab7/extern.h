#pragma once
//extern ȫ�ֱ���
extern double m;//������
extern double n;//������
extern USERCALL *usercall_list;//�û�ָ�������׵�ַ����������û�ָ����ٶ�̬����
extern int usercall_list_len;//�û�ָ�����鳤�ȣ����û�ָ���ļ���һ�ж���
extern SYSPARAM param_array[100];//ϵͳ��������
extern int param_num;
extern struct Elevatorstate elevator_a;//���ڴ�ŵ���a״̬�Ľṹ��
extern struct Elevatorstate elevator_b;//���ڴ�ŵ���b״̬�Ľṹ��
extern RESPONSELISTHEADNODE *response_list;// ������Ӧָ����У�����ָʾ��ǰ��Ӧ�ĵ���ָ��


extern char user_file_name[100];//�û���š��û�ָ���ļ������Ƶ�����
extern char simulate_file_name[100];//�û���š���ʷ�����ļ������Ƶ�����
extern int finish_call_num;//���ڼ�¼��ǰ����Ӧ��ɵ��û�ָ�����
extern int time;//���ڼ�¼��ǰ����ʱ��
extern int status_change_flag;//���ڼ�¼��һʱ������ڵ�ǰ״̬�Ƿ�ı䣬1�䣬0����

							  //6��ϵͳ����
extern char UserRequestFilesPath[150];//����û�ָ���ļ���Ŀ¼��Ĭ��*
extern char SimulationFilesPath[150];//����û���ʷ�����ļ���Ŀ¼��Ĭ��*
extern int ElevatorHeight;//�����ܲ�����Ĭ��20
extern int Delaytime; //����չʾÿ��״̬������ӳ�ʱ�䣬��λms��Ĭ��1000
extern int ElevatorSpeed;
extern int SimulateSpeed;