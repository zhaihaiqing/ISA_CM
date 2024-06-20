#include "main.h"

struct rt_semaphore key_sem;  //创建一个信号量

void key_thread_entry(void *par)
{
	uint16_t count=0;
	rt_sem_init(&key_sem, "key_sem", 0, RT_IPC_FLAG_FIFO); //创建信号量
	
	key_Init();

	while(1)
	{
		count = 0;
		rt_sem_control(&key_sem, RT_IPC_CMD_RESET, RT_NULL); 	//等待前清零信号量，防止误操作
		rt_sem_take(&key_sem, RT_WAITING_FOREVER);			//持续等待信号量
		
		while(!READ_CFGRST_SW())
		{
			count++;
			rt_thread_mdelay(10);
			if(count>=300)
			{
				break;
			}
		}
		
		if(count>=300)
		{
			log_info("enter Cfg mode\r\n");
		}
		
		
		rt_thread_mdelay(1);		//刷新率 100hz
	}
}
























