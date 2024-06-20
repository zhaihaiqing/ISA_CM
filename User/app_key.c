#include "main.h"

struct rt_semaphore key_sem;  //����һ���ź���

void key_thread_entry(void *par)
{
	uint16_t count=0;
	rt_sem_init(&key_sem, "key_sem", 0, RT_IPC_FLAG_FIFO); //�����ź���
	
	key_Init();

	while(1)
	{
		count = 0;
		rt_sem_control(&key_sem, RT_IPC_CMD_RESET, RT_NULL); 	//�ȴ�ǰ�����ź�������ֹ�����
		rt_sem_take(&key_sem, RT_WAITING_FOREVER);			//�����ȴ��ź���
		
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
		
		
		rt_thread_mdelay(1);		//ˢ���� 100hz
	}
}
























