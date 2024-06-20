 /* Includes ------------------------------------------------------------------*/
#include "main.h"


#define UART_FLAG_TimeOut  0x50000   //��ʱ����

UART1_RBUF_ST	uart1_rbuf	=	{ 0, 0, 0, 0, 0, 0, 0, 0 };

unsigned char Uart2Flag;
UART2_RBUF_ST	uart2_rbuf	=	{ 0, 0, };

unsigned char Uart3Flag;
UART3_RBUF_ST	uart3_rbuf	=	{ 0, 0, };

#ifdef	USE_UART7
unsigned char Uart7Flag=0;
unsigned short uart7_rx_len=0;
UART7_RBUF_ST	uart7_rbuf	=	{ 0, 0, };
#endif


/**********************************************************************************
* Function Name  : UART1_Configuration
* ����1��ʼ��
* ��ڲ���
* baudrate:������
**********************************************************************************/
void UART1_Configuration(unsigned int baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Enable the USART1 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	//��GPIO��USART2��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//����7��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUART1
	
	/* ��UART1_Tx��GPIO����Ϊ���츴��ģʽ */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;     
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;		
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = baudrate;//���ò�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//��������λΪ8
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//����ֹͣλΪ1
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������λ
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//���ͺͽ���
	USART_Init(USART1, &USART_InitStructure);
	
	
	
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);  //���� USART1 ���߿����ж�
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	USART_ClearFlag(USART1, USART_FLAG_TC);     /* �巢�ͱ�־��Transmission Complete flag */
	USART_ClearFlag(USART1, USART_FLAG_IDLE); //���������IDLE�жϣ������һֱ��IDLE�ж�
	
	//ʹ��
	USART_Cmd(USART1, ENABLE);
	
	

}

/**********************************************************************************
* Function Name  : USART_PutChar
* ���ڷ���һ���ַ�
* ��ڲ���
* USARTx:���ں�
* ch:����
**********************************************************************************/
void USART_PutChar(USART_TypeDef* USARTx,char  ch)
{
  unsigned int timeout = 0;
  USART_SendData(USARTx, (uint8_t)  ch);
  while( ((USARTx->SR&0X40) == RESET) && (timeout++ < UART_FLAG_TimeOut));
  //while((USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET) && (timeout++ < UART_FLAG_TimeOut));
}
/**********************************************************************************
* Function Name  : USART_PutData
* ���ڷ������ɸ��ַ�
* ��ڲ���
* USARTx:���ں�
* ch:����
* len:���ݳ���
**********************************************************************************/
void USART_PutData(USART_TypeDef* USARTx,unsigned char *dat,unsigned short int len)
{
	unsigned short int i;
	for(i = 0;i < len;i++)USART_PutChar(USARTx,(uint8_t)* (dat++));
}
/**********************************************************************************
* Function Name  : USART_PutS
* ���ڷ����ַ���
* ��ڲ���
* USARTx:���ں�
* *s:����ָ��
**********************************************************************************/
void USART_PutS(USART_TypeDef* USARTx,char *s)
{
	while(*s != '\0')USART_PutChar(USARTx,*(s++));
}




/**********************************************************************************
* ����1�����ַ�����������ģʽ�����ջ���������ȡ��
**********************************************************************************/
uint16_t USART1_GetCharBlock(uint16_t timeout)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	uint16_t to = timeout;	
	while(p->out == p->in)if(!(--to))return TIMEOUT;
	return (p->rx_buf [(p->out++) & (UART1_RBUF_SIZE - 1)]);
}

/**********************************************************************************
* ����1�����ַ�������������ģʽ�����ջ���������ȡ��
**********************************************************************************/
uint16_t USART1_GetChar(void)
{
	UART1_RBUF_ST *p = &uart1_rbuf;			
	if(p->out == p->in) //������������
		return EMPTY;
	return USART1_GetCharBlock(1000);
}






/**********************************************************************************
* ����2�����ַ�����������ģʽ�����ջ���������ȡ��
**********************************************************************************/
uint16_t USART2_GetCharBlock(uint16_t timeout)
{
	UART2_RBUF_ST *p = &uart2_rbuf;
	uint16_t to = timeout;	
	while(p->out == p->in)if(!(--to))return TIMEOUT;
	return (p->buf [(p->out++) & (UART2_RBUF_SIZE - 1)]);
}

/**********************************************************************************
* ����2�����ַ�������������ģʽ�����ջ���������ȡ��
**********************************************************************************/
uint16_t USART2_GetChar(void)
{
	UART2_RBUF_ST *p = &uart2_rbuf;			
	if(p->out == p->in) //������������
		return EMPTY;
	return USART2_GetCharBlock(1000);
}

/**********************************************************************************
* ����3�����ַ�����������ģʽ�����ջ���������ȡ��
**********************************************************************************/
uint16_t USART3_GetCharBlock(uint16_t timeout)
{
	UART3_RBUF_ST *p = &uart3_rbuf;
	uint16_t to = timeout;
	while(((p->out - p->in)& (UART3_RBUF_SIZE - 1)) == 0)if(!(--to))return TIMEOUT;
	return (p->buf [(p->out++) & (UART3_RBUF_SIZE - 1)]);
}

/**********************************************************************************
* ����3�����ַ�������������ģʽ�����ջ���������ȡ��
**********************************************************************************/
uint16_t USART3_GetChar(void)
{
	UART3_RBUF_ST *p = &uart3_rbuf;		
	if(((p->out - p->in) & (UART3_RBUF_SIZE - 1)) == 0) //������������
		return EMPTY;
	return USART3_GetCharBlock(1000);
}



/**********************************************************************************
�������1���ձ�־λ����֡����
**********************************************************************************/
void USART1_ClearRxBuf_Flag(void)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	p->out = 0;
	p->in = 0;
	p->rx_len = 0;
	p->rx_flag = 0;
	
	memset(p->rx_buf,0,UART1_RBUF_SIZE);
}

/**********************************************************************************
�������2���ձ�־λ����֡����
**********************************************************************************/
void USART2_ClearBuf_Flag(void)
{
	UART2_RBUF_ST *p = &uart2_rbuf;
	p->out = 0;
	p->in = 0;
	
	//Uart2Flag = 0;
	//USART2_RX_Len = 0;
	//ModbusDataPackage.DataFlag=0;
	//ModbusDataPackage.DataLen=0;
}

/**********************************************************************************
�������3���ձ�־λ����֡����
**********************************************************************************/
void USART3_ClearBuf_Flag(void)
{
	UART3_RBUF_ST *p = &uart3_rbuf;
	p->out = 0;
	p->in = 0;
	
	//Uart3Flag = 0;
	//USART3_RX_Len = 0;
}







/*******************************************************************************
* Function Name  : USART1_IRQHandler function
* Description    : debug�����ж�
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USART1_IRQHandler(void)
{
	unsigned char Uart_Get_Data=0;
	
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)	//���ڽ����ж�
	{
		Uart_Get_Data = USART_ReceiveData(USART1);
		
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		
		if((p->in - p->out)<UART1_RBUF_SIZE)
		{
			p->rx_buf [p->in & (UART1_RBUF_SIZE-1)] = Uart_Get_Data;	
			p->in++;
		}
		p->rx_len = (p->in - p->out) & (UART1_RBUF_SIZE - 1);//��ȡ���ݳ���
	}
	
	else if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)	//���ڿ����ж�
	{
		Uart_Get_Data = USART1->SR;
		Uart_Get_Data = USART1->DR;
		p->rx_flag = 1;
	}			
}







