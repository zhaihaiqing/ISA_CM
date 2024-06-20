#include "main.h"

//#define PID_KP	20
//#define PID_KI	2
//#define PID_KD	0

//#define PID_KP	30
//#define PID_KI	2
//#define PID_KD	1

//��ǰһֱ���õ�һ������
//#define PID_KP	50
//#define PID_KI	5
//#define PID_KD	1

#define PID_KP	200
#define PID_KI	20
#define PID_KD	2



sPID_t PID1 				= 	{0};
sPID_t PID2 				= 	{0};



#define PID_ADJ_REDUNDANCY_VALUE	0.001	//�������С�ڸ�ֵ������ҪPID���е���


/*			PID���ù���

1������PID����
2����ʼ��PID����
3������PID����ʱ��
4������PID����
5����PID��������ݷ��ظ����ƺ���

*/


//��ʼ��PID����
void PID_Parm_init(void)
{
	PID1.err = 0;//���ֵ
	PID1.err_n1 = 0;			//n-1���ֵ
	PID1.err_n2 = 0;			//n-2���ֵ
	PID1.Kp = PID_KP;
	PID1.Ki = PID_KI;
	PID1.Kd = PID_KD;
	PID1.Incerr = 0;
	PID1.UK = 0;
	
	PID2.err = 0;//���ֵ
	PID2.err_n1 = 0;			//n-1���ֵ
	PID2.err_n2 = 0;			//n-2���ֵ
	PID2.Kp = PID_KP;
	PID2.Ki = PID_KI;
	PID2.Kd = PID_KD;
	PID2.Incerr = 0;
	PID2.UK = 0;
}

/*			PID
�˿ڲ�����Ŀ��ֵ ʵ�ʲ���ֵ
������ɢPID��ʽ��PWM += Kp[ e(k) - e(k-1)] + Ki*e(k) + Kd[e(k) -2e(k-1)+e(k-2)]
e(k)���������
e(k-1)������һ��ƫ��
e(k-2)

���룺Ŀ��ֵ��ʵ�ʲ���ֵ
�����PID.UK������ֵ
*/

float PID1_Cal(float target_Current,float Actual_current)
{ 
	PID1.err = target_Current - Actual_current;
	PID1.Incerr = PID1.Kp*(PID1.err - PID1.err_n1) + PID1.Ki*PID1.err + PID1.Kd*(PID1.err - 2*PID1.err_n1 + PID1.err_n2);
	PID1.UK += PID1.Incerr;
	PID1.err_n2 = PID1.err_n1;
	PID1.err_n1 = PID1.err;
	
	if(PID1.UK < PIDDUTYMIN)PID1.UK = PIDDUTYMIN;			//������Сֵ
	//else if(PID1.UK > PIDDUTYMAX) PID1.UK = PIDDUTYMAX;	//�������ֵ
	
	return PID1.UK;
}

float PID2_Cal(float target_Current,float Actual_current)
{ 
	PID2.err = target_Current - Actual_current;
	PID2.Incerr = PID2.Kp*(PID2.err - PID2.err_n1) + PID2.Ki*PID2.err + PID2.Kd*(PID2.err - 2*PID2.err_n1 + PID2.err_n2);
	PID2.UK += PID2.Incerr;
	PID2.err_n2 = PID2.err_n1;
	PID2.err_n1 = PID2.err;
	
	if(PID2.UK < PIDDUTYMIN)PID2.UK = PIDDUTYMIN;			//������Сֵ
	//else if(PID2.UK > PIDDUTYMAX) PID2.UK = PIDDUTYMAX;		//�������ֵ
	
	return PID2.UK;
}












void mled_thread_entry(void *par)
{
	//����LED�Ƶ�������
	//���ȿ���
	//�¶ȿ���
	

	
	while(1)
	{
		rt_thread_mdelay(50);
	}
}

	
	



















