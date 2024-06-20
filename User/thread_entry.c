#include "main.h"

static struct rt_timer timer1;
static void timeout1(void* parameter);
int timer_static_sample(void);


//编码器检测任务
static struct rt_thread wifi_thread;				//线程控制块
static char wifi_thread_stack[2048];				//线程堆栈
#define WIFI_THREAD_PRIORITY         8				//线程优先级，
#define WIFI_THREAD_TIMESLICE        100			//线程的时间片大小


//编码器检测任务
static struct rt_thread key_thread;				//线程控制块
static char key_thread_stack[1024];				//线程堆栈
#define KEY_THREAD_PRIORITY         9				//线程优先级，
#define KEY_THREAD_TIMESLICE        100			//线程的时间片大小


//LED灯头控制任务
static struct rt_thread mled_thread;				//线程控制块
static char mled_thread_stack[1024];				//线程堆栈
#define MLED_THREAD_PRIORITY         10				//线程优先级，
#define MLED_THREAD_TIMESLICE        100			//线程的时间片大小S


//PLED灯头监测（电流、温度、光强）
static struct rt_thread pled_monitor_thread;			//线程控制块
static char pled_monitor_thread_stack[1024];			//线程堆栈
#define PLED_MONITOR_THREAD_PRIORITY         11		//线程优先级，
#define PLED_MONITOR_THREAD_TIMESLICE        100		//线程的时间片大小



//开关信号检测任务
static struct rt_thread sw_thread;					//线程控制块
static char sw_thread_stack[1024];					//线程堆栈
#define SW_THREAD_PRIORITY         12				//线程优先级，
#define SW_THREAD_TIMESLICE        100				//线程的时间片大小



//OLED显示
static struct rt_thread oled_thread;				//线程控制块
static char oled_thread_stack[1024];				//线程堆栈
#define OLED_THREAD_PRIORITY         13				//线程优先级，
#define OLED_THREAD_TIMESLICE        100			//线程的时间片大小



//片外ADC数据获取
static struct rt_thread adc_thread;					//线程控制块
static char adc_thread_stack[1024];					//线程堆栈
#define ADC_THREAD_PRIORITY         14				//线程优先级，
#define ADC_THREAD_TIMESLICE        100				//线程的时间片大小



//主板温度获取线程（）
static struct rt_thread board_temp_thread;			//线程控制块
static char board_temp_thread_stack[1024];			//线程堆栈
#define BOARD_TEMP_THREAD_PRIORITY         16		//线程优先级，
#define BOARD_TEMP_THREAD_TIMESLICE        100		//线程的时间片大小



//指示灯线程
static struct rt_thread led_thread;					//线程控制块
static char led_thread_stack[1024];					//线程堆栈
#define LED_THREAD_PRIORITY         17				//线程优先级，
#define LED_THREAD_TIMESLICE        100				//线程的时间片大小


int scs_thread_init(void)					//创建开机检测线程
{
	rt_thread_init(&wifi_thread,				//线程控制块
                   "wifi_thread",				//线程控制块名字
                   wifi_thread_entry,			//线程入口函数
                   RT_NULL,						//线程入口函数的参数
                   &wifi_thread_stack[0],		//线程栈起始地址
                   sizeof(wifi_thread_stack),	//线程栈大小
                   WIFI_THREAD_PRIORITY, 		//线程优先级
				   WIFI_THREAD_TIMESLICE);		//线程时间片大小
				   
	rt_thread_init(&key_thread,				//线程控制块
                   "key_thread",				//线程控制块名字
                   key_thread_entry,			//线程入口函数
                   RT_NULL,						//线程入口函数的参数
                   &key_thread_stack[0],		//线程栈起始地址
                   sizeof(key_thread_stack),	//线程栈大小
                   KEY_THREAD_PRIORITY, 		//线程优先级
				   KEY_THREAD_TIMESLICE);		//线程时间片大小
				   
				   
	rt_thread_init(&adc_thread,					//线程控制块
                   "adc_thread",				//线程控制块名字
                   adc_thread_entry,			//线程入口函数
                   RT_NULL,						//线程入口函数的参数
                   &adc_thread_stack[0],		//线程栈起始地址
                   sizeof(adc_thread_stack),	//线程栈大小
                   ADC_THREAD_PRIORITY, 		//线程优先级
				   ADC_THREAD_TIMESLICE);		//线程时间片大小
				   

				   
//	rt_thread_init(&pled_monitor_thread,					//线程控制块
//                   "pled_monitor_thread",				//线程控制块名字
//                   pled_monitor_thread_entry,			//线程入口函数
//                   RT_NULL,						//线程入口函数的参数
//                   &pled_monitor_thread_stack[0],		//线程栈起始地址
//                   sizeof(pled_monitor_thread_stack),	//线程栈大小
//                   PLED_MONITOR_THREAD_PRIORITY, 		//线程优先级
//				   PLED_MONITOR_THREAD_TIMESLICE);		//线程时间片大小
				   
	rt_thread_init(&led_thread,					//线程控制块
                   "led_thread",				//线程控制块名字
                   led_thread_entry,			//线程入口函数
                   RT_NULL,						//线程入口函数的参数
                   &led_thread_stack[0],		//线程栈起始地址
                   sizeof(led_thread_stack),	//线程栈大小
                   LED_THREAD_PRIORITY, 		//线程优先级
				   LED_THREAD_TIMESLICE);		//线程时间片大小
				   

		
	
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




struct rt_semaphore oled_refresh_sem;  //创建一个信号量,
void oled_thread_entry(void *par)
{

	
	while(1)
	{
						//执行一次约用时110ms
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
    /* 初始化定时器 */
    rt_timer_init(&timer1, "timer1",  /* 定时器名字是 timer1 */
                    timeout1, /* 超时时回调的处理函数 */
                    RT_NULL, /* 超时函数的入口参数 */
                    3000, /* 定时长度，以 OS Tick 为单位，即 10 个 OS Tick */
                    RT_TIMER_FLAG_PERIODIC); /* 周期性定时器 */

    /* 启动定时器 */
    rt_timer_start(&timer1);
    return 0;
}




















