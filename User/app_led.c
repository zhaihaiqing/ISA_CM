#include "main.h"

//#define PID_KP	20
//#define PID_KI	2
//#define PID_KD	0

//#define PID_KP	30
//#define PID_KI	2
//#define PID_KD	1

//此前一直在用的一组数据
//#define PID_KP	50
//#define PID_KI	5
//#define PID_KD	1

#define PID_KP	200
#define PID_KI	20
#define PID_KD	2



sPID_t PID1 				= 	{0};
sPID_t PID2 				= 	{0};



#define PID_ADJ_REDUNDANCY_VALUE	0.001	//电流误差小于该值，不需要PID进行调节


/*			PID设置过程

1：设置PID参数
2：初始化PID变量
3：配置PID采样时间
4：进行PID调节
5：将PID输出的数据返回给控制函数

*/


//初始化PID参数
void PID_Parm_init(void)
{
	PID1.err = 0;//误差值
	PID1.err_n1 = 0;			//n-1误差值
	PID1.err_n2 = 0;			//n-2误差值
	PID1.Kp = PID_KP;
	PID1.Ki = PID_KI;
	PID1.Kd = PID_KD;
	PID1.Incerr = 0;
	PID1.UK = 0;
	
	PID2.err = 0;//误差值
	PID2.err_n1 = 0;			//n-1误差值
	PID2.err_n2 = 0;			//n-2误差值
	PID2.Kp = PID_KP;
	PID2.Ki = PID_KI;
	PID2.Kd = PID_KD;
	PID2.Incerr = 0;
	PID2.UK = 0;
}

/*			PID
人口参数：目标值 实际测量值
根据离散PID公式：PWM += Kp[ e(k) - e(k-1)] + Ki*e(k) + Kd[e(k) -2e(k-1)+e(k-2)]
e(k)代表本次误差
e(k-1)代表上一次偏差
e(k-2)

输入：目标值，实际测量值
输出：PID.UK，增量值
*/

float PID1_Cal(float target_Current,float Actual_current)
{ 
	PID1.err = target_Current - Actual_current;
	PID1.Incerr = PID1.Kp*(PID1.err - PID1.err_n1) + PID1.Ki*PID1.err + PID1.Kd*(PID1.err - 2*PID1.err_n1 + PID1.err_n2);
	PID1.UK += PID1.Incerr;
	PID1.err_n2 = PID1.err_n1;
	PID1.err_n1 = PID1.err;
	
	if(PID1.UK < PIDDUTYMIN)PID1.UK = PIDDUTYMIN;			//设置最小值
	//else if(PID1.UK > PIDDUTYMAX) PID1.UK = PIDDUTYMAX;	//设置最大值
	
	return PID1.UK;
}

float PID2_Cal(float target_Current,float Actual_current)
{ 
	PID2.err = target_Current - Actual_current;
	PID2.Incerr = PID2.Kp*(PID2.err - PID2.err_n1) + PID2.Ki*PID2.err + PID2.Kd*(PID2.err - 2*PID2.err_n1 + PID2.err_n2);
	PID2.UK += PID2.Incerr;
	PID2.err_n2 = PID2.err_n1;
	PID2.err_n1 = PID2.err;
	
	if(PID2.UK < PIDDUTYMIN)PID2.UK = PIDDUTYMIN;			//设置最小值
	//else if(PID2.UK > PIDDUTYMAX) PID2.UK = PIDDUTYMAX;		//设置最大值
	
	return PID2.UK;
}












void mled_thread_entry(void *par)
{
	//包含LED灯电流控制
	//亮度控制
	//温度控制
	

	
	while(1)
	{
		rt_thread_mdelay(50);
	}
}

	
	



















