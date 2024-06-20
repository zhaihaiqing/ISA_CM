
#include "main.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
//	NVIC_InitTypeDef   NVIC_InitStructure;
//	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	//WDI
	GPIO_InitStructure.GPIO_Pin = WDI_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(WDI_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	//LED1
	GPIO_InitStructure.GPIO_Pin = LED1_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(LED1_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	GPIO_InitStructure.GPIO_Pin = LED2_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(LED2_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	GPIO_InitStructure.GPIO_Pin = LED3_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(LED3_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	GPIO_InitStructure.GPIO_Pin = LED4_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(LED4_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	GPIO_InitStructure.GPIO_Pin = LED_RUN1_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(LED_RUN1_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	GPIO_InitStructure.GPIO_Pin = LED_RUN2_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(LED_RUN2_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	//PPS POW_EN
	GPIO_InitStructure.GPIO_Pin = POWEN_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(POWEN_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	//WLP POW_EN
	GPIO_InitStructure.GPIO_Pin = WLPEN_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;		//����
	GPIO_Init(WLPEN_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	//wifi_pow_EN
	GPIO_InitStructure.GPIO_Pin = WIFI_POWEN_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(WIFI_POWEN_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
	//wifi_rst_EN
	GPIO_InitStructure.GPIO_Pin = WIFI_RST_GPIO_Pin ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(WIFI_RST_GPIO_Port, &GPIO_InitStructure);		//��ʼ���ö˿�
	
//	GPIO_InitStructure.GPIO_Pin = CFG_RST_GPIO_Pin;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		//��ͨ����ģʽ
//	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
//	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
//	GPIO_Init(CFG_RST_GPIO_Port, &GPIO_InitStructure);	//��ʼ���ö˿�
	
	
	LED1_ON();
	LED2_ON();
	LED3_ON();
	LED4_ON();
	LED_RUN1_ON();
	LED_RUN2_ON();
	
	POW_EN_OFF();
	WLP_EN_OFF();
	
	WIFI_POW_EN_OFF();
	WIFI_RST_LOW();
	
}



void key_Init(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	NVIC_InitTypeDef   		NVIC_InitStructure;
	EXTI_InitTypeDef   		EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = CFG_RST_GPIO_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		//��ͨ���ģʽ
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(CFG_RST_GPIO_Port, &GPIO_InitStructure);				//��ʼ���ö˿�
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource8);//
	
	/* ����EXTI_Line */
	EXTI_InitStructure.EXTI_Line = EXTI_Line8;//LINE
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�ش���һ�� 
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE
	EXTI_Init(&EXTI_InitStructure);//����
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;//�ⲿ�ж�0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����
	
	EXTI_ClearITPendingBit(EXTI_Line8);
}



void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line8) != RESET)
	{
		rt_sem_release(&key_sem); //һ�����ݲɼ���ɺ󣬷��Ͳ�����ɲ����ź���
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
}







