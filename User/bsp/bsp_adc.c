
#include "main.h"


void ADC_GPIO_Configuration(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	//NVIC_InitTypeDef   NVIC_InitStructure;
	//EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);				//��ʼ���ö˿�
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ���ö˿�
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		//��ͨ���ģʽ
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOD, &GPIO_InitStructure);				//��ʼ���ö˿�
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		//��ͨ���ģʽ
	//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
	GPIO_Init(GPIOB, &GPIO_InitStructure);				//��ʼ���ö˿�
	
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource13);//
//	
//	/* ����EXTI_Line0 */
//	EXTI_InitStructure.EXTI_Line = EXTI_Line13;//LINE13
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;//�ж��¼�
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�����ش���һ�� 
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;//ʹ��LINE13
//	EXTI_Init(&EXTI_InitStructure);//����
//	
//	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;//�ⲿ�ж�0
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;//��ռ���ȼ�2
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;//�����ȼ�2
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
//	NVIC_Init(&NVIC_InitStructure);//����
	
}





//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI->PR & (1 << 13))	//��⵽PB13�ж�
//	{
//		log_info("123\r\n");

//		EXTI->PR |= 1 << 13;
//	}
//}


//����ADCת��
void Start_ADC_ConV(void)
{	
	GPIO_SetBits(GPIOE,GPIO_Pin_13);
	__nop();__nop();
	__nop();__nop();
	__nop();__nop();
	__nop();__nop();
//		__nop();
//		__nop();
//		__nop();
//		__nop();
	//Delay_us(2);
	GPIO_ResetBits(GPIOE,GPIO_Pin_13);

	//GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);	//����������ת��
}

//����ADC����ģʽ
void ADC_Config(void)
{
	//������Ӳ������ģʽ
	//��λADC
	//���ù�����Χ
	
	//GPIO_SetBits(GPIOE,GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);//��λ�����У�����ת������
	
	ADC_CONV_H();
	rt_thread_mdelay(10);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_11);	//
	rt_thread_mdelay(100);
	GPIO_ResetBits(GPIOE,GPIO_Pin_11);	
	rt_thread_mdelay(100);
	
	SET_ADC_RANGE_HIGH();
	rt_thread_mdelay(10);
	
	ADC_CONV_L();
	rt_thread_mdelay(10);
	
	ADC_CONV_H();
	rt_thread_mdelay(10);
	
	ADC_CONV_L();
	rt_thread_mdelay(10);	
}






