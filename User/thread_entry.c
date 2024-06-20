#include "main.h"

static struct rt_timer timer1;
static void timeout1(void* parameter);
int timer_static_sample(void);


//�������������
static struct rt_thread wifi_thread;				//�߳̿��ƿ�
static char wifi_thread_stack[2048];				//�̶߳�ջ
#define WIFI_THREAD_PRIORITY         8				//�߳����ȼ���
#define WIFI_THREAD_TIMESLICE        100			//�̵߳�ʱ��Ƭ��С


//�������������
static struct rt_thread key_thread;				//�߳̿��ƿ�
static char key_thread_stack[1024];				//�̶߳�ջ
#define KEY_THREAD_PRIORITY         9				//�߳����ȼ���
#define KEY_THREAD_TIMESLICE        100			//�̵߳�ʱ��Ƭ��С


//LED��ͷ��������
static struct rt_thread mled_thread;				//�߳̿��ƿ�
static char mled_thread_stack[1024];				//�̶߳�ջ
#define MLED_THREAD_PRIORITY         10				//�߳����ȼ���
#define MLED_THREAD_TIMESLICE        100			//�̵߳�ʱ��Ƭ��СS


//PLED��ͷ��⣨�������¶ȡ���ǿ��
static struct rt_thread pled_monitor_thread;			//�߳̿��ƿ�
static char pled_monitor_thread_stack[1024];			//�̶߳�ջ
#define PLED_MONITOR_THREAD_PRIORITY         11		//�߳����ȼ���
#define PLED_MONITOR_THREAD_TIMESLICE        100		//�̵߳�ʱ��Ƭ��С



//�����źż������
static struct rt_thread sw_thread;					//�߳̿��ƿ�
static char sw_thread_stack[1024];					//�̶߳�ջ
#define SW_THREAD_PRIORITY         12				//�߳����ȼ���
#define SW_THREAD_TIMESLICE        100				//�̵߳�ʱ��Ƭ��С



//OLED��ʾ
static struct rt_thread oled_thread;				//�߳̿��ƿ�
static char oled_thread_stack[1024];				//�̶߳�ջ
#define OLED_THREAD_PRIORITY         13				//�߳����ȼ���
#define OLED_THREAD_TIMESLICE        100			//�̵߳�ʱ��Ƭ��С



//Ƭ��ADC���ݻ�ȡ
static struct rt_thread adc_thread;					//�߳̿��ƿ�
static char adc_thread_stack[1024];					//�̶߳�ջ
#define ADC_THREAD_PRIORITY         14				//�߳����ȼ���
#define ADC_THREAD_TIMESLICE        100				//�̵߳�ʱ��Ƭ��С



//�����¶Ȼ�ȡ�̣߳���
static struct rt_thread board_temp_thread;			//�߳̿��ƿ�
static char board_temp_thread_stack[1024];			//�̶߳�ջ
#define BOARD_TEMP_THREAD_PRIORITY         16		//�߳����ȼ���
#define BOARD_TEMP_THREAD_TIMESLICE        100		//�̵߳�ʱ��Ƭ��С



//ָʾ���߳�
static struct rt_thread led_thread;					//�߳̿��ƿ�
static char led_thread_stack[1024];					//�̶߳�ջ
#define LED_THREAD_PRIORITY         17				//�߳����ȼ���
#define LED_THREAD_TIMESLICE        100				//�̵߳�ʱ��Ƭ��С


int scs_thread_init(void)					//������������߳�
{
	rt_thread_init(&wifi_thread,				//�߳̿��ƿ�
                   "wifi_thread",				//�߳̿��ƿ�����
                   wifi_thread_entry,			//�߳���ں���
                   RT_NULL,						//�߳���ں����Ĳ���
                   &wifi_thread_stack[0],		//�߳�ջ��ʼ��ַ
                   sizeof(wifi_thread_stack),	//�߳�ջ��С
                   WIFI_THREAD_PRIORITY, 		//�߳����ȼ�
				   WIFI_THREAD_TIMESLICE);		//�߳�ʱ��Ƭ��С
				   
	rt_thread_init(&key_thread,				//�߳̿��ƿ�
                   "key_thread",				//�߳̿��ƿ�����
                   key_thread_entry,			//�߳���ں���
                   RT_NULL,						//�߳���ں����Ĳ���
                   &key_thread_stack[0],		//�߳�ջ��ʼ��ַ
                   sizeof(key_thread_stack),	//�߳�ջ��С
                   KEY_THREAD_PRIORITY, 		//�߳����ȼ�
				   KEY_THREAD_TIMESLICE);		//�߳�ʱ��Ƭ��С
				   
				   
	rt_thread_init(&adc_thread,					//�߳̿��ƿ�
                   "adc_thread",				//�߳̿��ƿ�����
                   adc_thread_entry,			//�߳���ں���
                   RT_NULL,						//�߳���ں����Ĳ���
                   &adc_thread_stack[0],		//�߳�ջ��ʼ��ַ
                   sizeof(adc_thread_stack),	//�߳�ջ��С
                   ADC_THREAD_PRIORITY, 		//�߳����ȼ�
				   ADC_THREAD_TIMESLICE);		//�߳�ʱ��Ƭ��С
				   

				   
//	rt_thread_init(&pled_monitor_thread,					//�߳̿��ƿ�
//                   "pled_monitor_thread",				//�߳̿��ƿ�����
//                   pled_monitor_thread_entry,			//�߳���ں���
//                   RT_NULL,						//�߳���ں����Ĳ���
//                   &pled_monitor_thread_stack[0],		//�߳�ջ��ʼ��ַ
//                   sizeof(pled_monitor_thread_stack),	//�߳�ջ��С
//                   PLED_MONITOR_THREAD_PRIORITY, 		//�߳����ȼ�
//				   PLED_MONITOR_THREAD_TIMESLICE);		//�߳�ʱ��Ƭ��С
				   
	rt_thread_init(&led_thread,					//�߳̿��ƿ�
                   "led_thread",				//�߳̿��ƿ�����
                   led_thread_entry,			//�߳���ں���
                   RT_NULL,						//�߳���ں����Ĳ���
                   &led_thread_stack[0],		//�߳�ջ��ʼ��ַ
                   sizeof(led_thread_stack),	//�߳�ջ��С
                   LED_THREAD_PRIORITY, 		//�߳����ȼ�
				   LED_THREAD_TIMESLICE);		//�߳�ʱ��Ƭ��С
				   

		
	
	//rt_thread_startup(&codec_thread);
	//rt_thread_startup(&sw_thread);
	//rt_thread_startup(&oled_thread);					   
	//rt_thread_startup(&adc_thread);	
	//rt_thread_startup(&board_temp_thread);	
	rt_thread_startup(&key_thread); 
	rt_thread_startup(&led_thread); 
	rt_thread_startup(&wifi_thread); 

				   

				
	
				   
	return 0;
}




struct rt_semaphore oled_refresh_sem;  //����һ���ź���,
void oled_thread_entry(void *par)
{

	
	while(1)
	{
						//ִ��һ��Լ��ʱ110ms
			rt_thread_mdelay(75);
		
	}
	
}



void led_thread_entry(void *par)
{
	uint16_t vol = 700;
	
	Adc1_Init();
	Adc2_Init();
	POW_EN_ON();
	
	//rt_thread_mdelay(10000);
	
	Dac1_Set_fixed_Vol(vol);
	rt_thread_mdelay(500);
	WLP_EN_ON();
	
	log_info("pow_in:%.2f, dac_val:%dmV, pow_out:%.2f \r\n",get_pow_in_val()+0.005,vol,get_pow_out_val()+0.005);
	
	while(1)
	{
		
		LED2_ON();
		
		LED_RUN1_ON();
		LED_RUN2_OFF();
		rt_thread_mdelay(500);
		
		LED_RUN1_OFF();
		LED_RUN2_ON();
		LED2_OFF();
		//WLP_EN_OFF();
		
		
		//Dac1_Set_fixed_Vol(vol);
		rt_thread_mdelay(500);
		
		//log_info("pow_in:%.2f, dac_val:%dmV, pow_out:%.2f \r\n",get_pow_in_val()+0.005,vol,get_pow_out_val()+0.005);
		
		
		
		//vol = vol+50;
		
		//if(vol>3250)
			//vol = 0;
	}
	
}



static void timeout1(void* parameter)
{
	rt_sem_release(&oled_refresh_sem);
}


int timer_static_sample(void)
{
    /* ��ʼ����ʱ�� */
    rt_timer_init(&timer1, "timer1",  /* ��ʱ�������� timer1 */
                    timeout1, /* ��ʱʱ�ص��Ĵ����� */
                    RT_NULL, /* ��ʱ��������ڲ��� */
                    3000, /* ��ʱ���ȣ��� OS Tick Ϊ��λ���� 10 �� OS Tick */
                    RT_TIMER_FLAG_PERIODIC); /* �����Զ�ʱ�� */

    /* ������ʱ�� */
    rt_timer_start(&timer1);
    return 0;
}




















