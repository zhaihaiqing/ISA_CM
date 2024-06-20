#include "main.h"

/*
1����������		AT+<��������>=?
2����ѯ����		AT+<��������>?
3����������		AT+<��������>=<...>
4��ִ������		AT+<��������>
*/

/*
����AT���

AT					����AT
AT+HELP				�鿴ATָ�
AT+RST				ģ������
AT+RESTORE			�ظ���������
ATE1				�򿪻���
ATE0				�رջ���
AT+GMR				��ѯ�汾��Ϣ
AT+SLEEP			˯��ģʽ
AT+UARTCFG			��������
AT+OTA				��������
*/

/*
WIFI AT���

AT+WMODE			WIFI����ģʽ
AT+WSCAN			ɨ��WIFI�б�
AT+WSDHCP			STAģʽ��DHCP����
AT+WJAP				����AP
AT+WDISCONNECT		�Ͽ���ǰ��AP����
AT+WAUTOCONN		�ϵ��Զ�����WIFI
AT+WAPDHCP			APģʽ��DHCP����
AT+WAP				APģʽWIFI����
AT+PING				����Ping����
AT+CIPSTAMAC_DEF	WIFI station MAC��ַ
AT+WCOUNTRY			WIFI���Ҵ���
AT+WCONFIG			�ֻ�����
AT+WSACNOPT			ɸѡWIFIɨ����Ϣ��ʾ
AT+WRSSI			WIFI�����ź�ǿ��
*/


void Wifi_SendAT(char *p_at)
{
	USART_PutS(USART1,p_at);
}

void Wifi_SendAT_Dat(uint8_t *p_at,uint16_t len)
{
	USART_PutData(USART1,p_at,len);
}



const char wifi_ready_stack[10] = "ready";
const char wifi_ok_stack[10] = "OK";
const char wifi_error_stack[10] = "ERROR";
const char wifi_tcp_read_stack[10] = "+IPD";
const char wifi_socketok_stack[32] = "connect success ConID=";
const char wifi_disconnect_stack[32] = "WIFI DISCONNECT";


uint8_t Is_Wifi_Power_On 	= 0;
uint8_t Is_AT_OK 			= 0;


/*********************************************************************
*	wifiģ���Դ����
*	0=�رյ�Դ��1=������Դ�����ȴ�ģ�����
*********************************************************************/
void WIFI_POWER_Ctrl(uint8_t parameter)
{
	uint8_t retry_count = 3;
	UART1_RBUF_ST *p = &uart1_rbuf;
	char *ret;
	
	if(parameter == 0)	//�ر�wifiģ���Դ
	{
		WIFI_POW_EN_OFF();
		WIFI_RST_LOW();
	}
	else			//wifiģ���ϵ磬���ʧ������3��
	{
		while(1)
		{
			WIFI_RST_HIGH();
			WIFI_POW_EN_ON();
			rt_thread_mdelay(2000);
			if(p->rx_flag == 1)
			{
				log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,&p->rx_buf[3]);
				if(strstr((const char *)&p->rx_buf[3],wifi_ready_stack))
				{
					log_info("WIFI Module POWER ON OK\r\n");
					Is_Wifi_Power_On = 1;
					USART1_ClearRxBuf_Flag();
					break;
				}
				else
				{
					WIFI_POW_EN_OFF();
					WIFI_RST_LOW();
					rt_thread_mdelay(3000);
					USART1_ClearRxBuf_Flag();
				}
			}
		}
	}
}

/*********************************************************************
*	wifiģ��ATָ�����
*	
*********************************************************************/
void WIFI_AT_Test(void)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	log_info("WIFI_AT_Test\r\n");
	Wifi_SendAT("AT\r\n");
	while(!p->rx_flag)
	{
		rt_thread_mdelay(100);
	}
	//rt_thread_mdelay(1000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("AT Command test OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

/*********************************************************************
*	wifiģ��ATָ����Կ���
*	0=�رջ��ԣ�1=��������
*********************************************************************/
void WIFI_ATE_Ctrl(uint8_t parameter)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	if(parameter == 0)
	{
		Wifi_SendAT("ATE0\r\n");
		rt_thread_mdelay(1000);
		if(p->rx_flag == 1 )
		{
			log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
			if(strstr((const char *)p->rx_buf,wifi_ok_stack))
			{
				log_info("ATE=0 test OK\r\n");
			}
			USART1_ClearRxBuf_Flag();
		}
	}
	else
	{
		Wifi_SendAT("ATE1\r\n");
		rt_thread_mdelay(1000);
		if(p->rx_flag == 1 )
		{
			log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
			if(strstr((const char *)p->rx_buf,wifi_ok_stack))
			{
				log_info("ATE=1 OK\r\n");
			}
			USART1_ClearRxBuf_Flag();
		}
	}
	
}

/*********************************************************************
*	wifiɨ��
*	��ӡɨ��Ľ��
*********************************************************************/
void WIFI_Scan(void)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	Wifi_SendAT("AT+CWLAP\r\n");
	
	rt_thread_mdelay(5000);
	
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("WSCAN OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
	
}

/*********************************************************************
*	����wifiģ��Ĺ���ģʽ
*	
*********************************************************************/
void WIFI_Set_Mode(uint8_t par1,uint8_t par2)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	Wifi_SendAT("AT+CWMODE=1,1\r\n");
	rt_thread_mdelay(1000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("CWMODE OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

/*********************************************************************
*	����wifiģ���DHCPģʽ
*	
*********************************************************************/
void WIFI_Set_DHCP(uint8_t dhcp_operate,uint8_t dhcp_mode)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	//Wifi_SendAT("AT+WSDHCP=0,192.168.43.166,255.255.255.0,192.168.43.1\r\n");
	Wifi_SendAT("AT+CWDHCP=1,1\r\n");
	rt_thread_mdelay(3000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("CWDHCP OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

/*********************************************************************
*	wifiģ������AP
*	
*********************************************************************/
void WIFI_Join_AP(char *ssid,char *pass)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	uint8_t tx_buf[128] = {0};
	
	sprintf((char *)tx_buf,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,pass);
	
	//Wifi_SendAT("AT+CWJAP=\"ESP32_softAP\",\"1234567890\"\r\n");
	Wifi_SendAT((char *)tx_buf);
	rt_thread_mdelay(5000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("WJAP OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

/*********************************************************************
*	wifiģ��Ͽ���AP������
*	
*********************************************************************/
void WIFI_Disconnect_AP(void)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	
	Wifi_SendAT("AT+CIPCLOSE\r\n");
	rt_thread_mdelay(2000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("CIPCLOSE OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
	
	Wifi_SendAT("AT+CWQAP\r\n");
	rt_thread_mdelay(2000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("CWQAP OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

/*********************************************************************
*	��ѯwifiģʽ��������Ϣ
*	
*********************************************************************/
void WIFI_Query_WIFI(void)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	Wifi_SendAT("AT+CWMODE?\r\n");		//��ѯwifiģʽ
	rt_thread_mdelay(1000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("CWMODE OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
	
	Wifi_SendAT("AT+CWSTATE?\r\n");		//��ѯwifi��Ϣ
	rt_thread_mdelay(1000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("CWSTATE OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
	
	Wifi_SendAT("AT+CIPSTA?\r\n");		//��ѯ������Ϣ
	rt_thread_mdelay(1000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("CIPSTA OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//TCP_IP


uint8_t Scoket_ConID = 0;


//void WIFI_Socket_Senddat(uint8_t ConID,uint8_t dat_len)
//{
//	UART1_RBUF_ST *p = &uart1_rbuf;
//	char Tx_buf[256] = {0};
//	
//	Wifi_SendAT("123\r\n");
//	rt_thread_mdelay(5000);
//	if(p->rx_flag == 1 )
//	{
//		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
//		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
//		{
//			log_info("SOCKET OK\r\n");
//		}
//		USART1_ClearRxBuf_Flag();
//	}
//}

/*********************************************************************
*	TCP����ģʽ���ã������ӡ�������
*	
*********************************************************************/
void WIFI_Set_Mux(uint8_t mode)	//TCP����ģʽ����
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	if(mode == 0)
	{
		Wifi_SendAT("AT+CIPMUX=0\r\n");	//���õ�����ģʽ
		rt_thread_mdelay(1000);
		if(p->rx_flag == 1 )
		{
			log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
			if(strstr((const char *)p->rx_buf,wifi_ok_stack))
			{
				log_info("CIPMUX OK\r\n");
			}
			USART1_ClearRxBuf_Flag();
		}
	}
	else if(mode == 1)	//����Ϊ������ģʽ
	{
		Wifi_SendAT("AT+CIPMUX=1\r\n");	
		rt_thread_mdelay(1000);
		if(p->rx_flag == 1 )
		{
			log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
			if(strstr((const char *)p->rx_buf,wifi_ok_stack))
			{
				log_info("CIPMUX OK\r\n");
			}
			USART1_ClearRxBuf_Flag();
		}
	}
}

/*********************************************************************
*	����TCP����
*	
*********************************************************************/
void WIFI_Creat_Socket(void)	//�ͻ��˲��õ�����ģʽ
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	//Wifi_SendAT("AT+CIPSTART=\"TCP\",\"192.168.4.1\",333\r\n");
	Wifi_SendAT("AT+CIPSTART=\"TCP\",\"192.168.4.1\",8888\r\n");
	rt_thread_mdelay(3000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("Creat_Socket OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

/*********************************************************************
*	wifi ���ͺ���������Ҫ���͵��������͡��ַ����ͳ���
*	
*********************************************************************/
void WIFI_Socket_Send(uint8_t send_type ,char *ss,uint16_t dat_len)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	char tx_buf[64] = {0};
	
	sprintf(tx_buf,"AT+CIPSEND=%d\r\n",dat_len);
	Wifi_SendAT(tx_buf);			//A:�������ݷ���ģʽ�������÷��ͳ���
	
	while(!p->rx_flag)
	{
		rt_thread_mdelay(10);
	}
	//if(p->rx_flag == 1 )
	{
		log_info("00wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("CIPSEND OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
	
	if(send_type == 0)					//�������Ϊ0�����͵����ַ������������͵�������
	{
		Wifi_SendAT(ss);				//B:�����ض����ȵ�����
	}
	else								//�������Ϊ1�����͵�������					
	{
		Wifi_SendAT_Dat((uint8_t *)ss,dat_len);
	}
	
	while(!p->rx_flag)
	{
		rt_thread_mdelay(10);
	}
	
	log_info("11wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
	if(strstr((const char *)p->rx_buf,wifi_ok_stack))
	{
		log_info("SEND OK\r\n");
	}
	USART1_ClearRxBuf_Flag();
	
}

/*********************************************************************
*	wifi ���ݽ��պ���
*	
*********************************************************************/
void WIFI_Socket_Read(uint8_t ConID,uint8_t dat_len)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	char Tx_buf[256] = {0};
	
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_tcp_read_stack))
		{
			log_info("Socket Read OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

/*********************************************************************
*	���ý���ģʽ���������պͱ�������
*	
*********************************************************************/
void WIFI_Set_RecvType(void)	//�������ݽ���ģʽΪ�ֶ�ģʽ
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	//char *pEnd;
	
	Wifi_SendAT("AT+CIPRECVTYPE=1\r\n");
	rt_thread_mdelay(3000);
	if(p->rx_flag == 1 )
	{
		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			log_info("Set_RecvType OK\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

void WIFI_Recv_Dat(void)//��������ģʽ�����ݽ��ܣ�����ͻ���¼����µ�����
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	Wifi_SendAT("AT+CIPRECVLEN?\r\n");
	while(!p->rx_flag)
	{
		rt_thread_mdelay(10);
	}
	//if(p->rx_flag == 1 )
	{
		log_info("00wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
		{
			//�������ݳ��ȳɹ�
			//
			log_info("Get Len\r\n\r\n");
		}
		USART1_ClearRxBuf_Flag();
	}
}

//void WIFI_Creat_Socket(void)
//{
//	UART1_RBUF_ST *p = &uart1_rbuf;
//	//char *pEnd;
//	
//	Wifi_SendAT("AT+CIPSTART=\"TCP\",\"192.168.43.1\",8088\r\n");
//	rt_thread_mdelay(5000);
//	if(p->rx_flag == 1 )
//	{
//		log_info("wifi_rx data:len=%d\r\n%s\r\n",p->rx_len,p->rx_buf);
//		if(strstr((const char *)p->rx_buf,wifi_ok_stack))
//		{
//			log_info("SOCKET OK\r\n");
//			{
//				uint8_t tt;
//				char *ptr;
//				char ch = '\r';
//				char s_buf[10] = {0};
//				uint8_t s_p = 22;
//				uint8_t ix = 0;
//				ptr = strchr((const char *)p->rx_buf, ch);//Ѱ��\r���ֵ�λ��
//				tt =  ptr - p->rx_buf + 1;	//����\r���±�
//				
//				for(ix = 0; ix<tt-s_p-1 ; ix++)			//��=��\r֮������ָ��Ƶ���������������ת��Ϊ����
//					s_buf[ix] = p->rx_buf[ix+s_p];
//				
//				Scoket_ConID = strtol((const char *)s_buf , NULL , 10);	//��ȡConID
//				log_info("Scoket_ConID:%d,%d\r\n",Scoket_ConID,tt);
//			}
//			
//			
//			WIFI_Socket_Send(Scoket_ConID,3);
//			
//		}
//		USART1_ClearRxBuf_Flag();
//	}
//}



//wifi���ߣ�Ĭ���˺�����
char WIFI_CFG_SSID[128] = "WIFI_TOOL";
char WIFI_CFG_PASS[128] = "12345678";

//���õ��˺�����
uint8_t	wifi_ssid_len = 	0;
uint8_t wifi_ssid[128] = 	{0};
uint8_t wifi_pass_len = 	0;
uint8_t wifi_pass[128] = 	{0};

uint16_t MI_V	= 0;
uint16_t BAT_V	= 0;
uint16_t BAT_I	= 0;
int16_t  TEMP	= 0;

//wifiģ���ȡ������Ϣ��������
uint8_t wifi_get_cfg(uint8_t type)	//0����ȡ������Ϣ��1����ȡ����
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	uint8_t tx_buf_array[256] = {0};
	uint8_t rx_buf_array[256] = {0};
	uint8_t	rx_pow_sn[6]	={0};
	uint8_t	rx_isa_sn[6]	={0};
	uint8_t ix = 0;
	uint16_t tcp_rx_len = 0;
	uint8_t tcp_order_type = 0;
	uint8_t sta	=	0;	//����ֵ
	
	sCM_Requst_Cfg.frame_h[0] = 0xA5;
	sCM_Requst_Cfg.frame_h[1] = 0xA5;
	sCM_Requst_Cfg.frame_h[2] = 0xA5;
	sCM_Requst_Cfg.cmd_pow		=	3;
	sCM_Requst_Cfg.dat_len_h	=	0;
	sCM_Requst_Cfg.dat_len_l	=	25;
	sCM_Requst_Cfg.rev[0]		=	0;
	sCM_Requst_Cfg.rev[1]		=	0;
	sCM_Requst_Cfg.rev[2]		=	0;
	sCM_Requst_Cfg.rev[3]		=	0;
	sCM_Requst_Cfg.rev[4]		=	0;
	sCM_Requst_Cfg.rev[5]		=	0;
	
	if(type == 0)
	{
		sCM_Requst_Cfg.cmd			=	0x15;
	}
	else if(type == 1)
	{
		sCM_Requst_Cfg.cmd			=	0x11;
	}
	sCM_Requst_Cfg.time[0]		=	0;
	sCM_Requst_Cfg.time[1]		=	0;
	sCM_Requst_Cfg.time[2]		=	0;
	sCM_Requst_Cfg.time[3]		=	0;
	sCM_Requst_Cfg.err			=	0;
	sCM_Requst_Cfg.charge_sat	=	0;
	sCM_Requst_Cfg.isa_sn[0]	=	0xaf;
	sCM_Requst_Cfg.isa_sn[1]	=	0x36;
	sCM_Requst_Cfg.isa_sn[2]	=	0xc7;
	sCM_Requst_Cfg.isa_sn[3]	=	0x72;
	sCM_Requst_Cfg.isa_sn[4]	=	0x37;
	sCM_Requst_Cfg.isa_sn[5]	=	0xe8;
	sCM_Requst_Cfg.pow_sn[0]	=	0x11;
	sCM_Requst_Cfg.pow_sn[1]	=	0x12;
	sCM_Requst_Cfg.pow_sn[2]	=	0x13;
	sCM_Requst_Cfg.pow_sn[3]	=	0x14;
	sCM_Requst_Cfg.pow_sn[4]	=	0x15;
	sCM_Requst_Cfg.pow_sn[5]	=	0x16;
	sCM_Requst_Cfg.frame_end	=	0x5A;
	
	memset(tx_buf_array,0,sizeof(tx_buf_array));
	memcpy(tx_buf_array,&sCM_Requst_Cfg.frame_h,sizeof(sCM_Requst_Cfg));	
	WIFI_Socket_Send(1,(char *)tx_buf_array,sizeof(sCM_Requst_Cfg));
	
	rt_thread_mdelay(8000);
	if(p->rx_flag == 1 )	//�յ�ģ�鷢�͵����ݣ������ֻ�����쳣��������������
	{
		//1�����յ������ݸ��Ƶ������У�
		//2�����������룬�ж���������	
		if(strstr((const char *)p->rx_buf,wifi_tcp_read_stack))	//�����ַ�����ʱ����+IPD������˵���յ�������
		{
			tcp_rx_len = (p->rx_buf[14]<<8 | p->rx_buf[15]) + 7;			//��ȡ���ݳ���
			tcp_order_type = p->rx_buf[22];									//��ȡָ������
			log_info("333rx_data...........,tcp_rx_len:%d��tcp_order_type:0x%x\r\n",tcp_rx_len,tcp_order_type);
			
			//֡ͷ֡β�жϣ�֤�����ݴ�������
			if( (p->rx_buf[10] == 0xa5) && (p->rx_buf[11] == 0xa5)  && (p->rx_buf[12] == 0xa5) && (p->rx_buf[p->rx_len-3] == 0x5a)  )
			{
				memcpy(rx_buf_array,&p->rx_buf[10],tcp_rx_len);	//֡ͷ֡β�жϳɹ���������cpy��������
				for(ix=0;ix<tcp_rx_len;ix++)
				{
					log_info("rx_data[%d]:0x%x\r\n",ix,rx_buf_array[ix]);
				}
				
				if( tcp_order_type == 0x15 )	////���ݽ���	�յ�����������Ϣ	�˺��������	
				{
					memcpy(rx_isa_sn,&rx_buf_array[18],6);
					memcpy(rx_pow_sn,&rx_buf_array[24],6);
					
					//�ж��յ���SN�룬rx_pow_sn
					wifi_ssid_len = rx_buf_array[30];
					wifi_pass_len = rx_buf_array[31+wifi_ssid_len];
					memset(wifi_ssid,0,128);
					memset(wifi_pass,0,128);
					memcpy(wifi_ssid,&rx_buf_array[31],wifi_ssid_len);
					memcpy(wifi_pass,&rx_buf_array[32+wifi_ssid_len],wifi_pass_len);
					
					log_info("rx_isa_sn:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",rx_isa_sn[0],rx_isa_sn[1],rx_isa_sn[2],rx_isa_sn[3],rx_isa_sn[4],rx_isa_sn[5]);
					log_info("rx_pow_sn:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",rx_pow_sn[0],rx_pow_sn[1],rx_pow_sn[2],rx_pow_sn[3],rx_pow_sn[4],rx_pow_sn[5]);
					log_info("wifi_ssid_len=%d ssid=%s\r\n",wifi_ssid_len,wifi_ssid);
					log_info("wifi_pass_len=%d pass=%s\r\n",wifi_pass_len,wifi_pass);
				}
				else if( tcp_order_type == 0x11 )	////���ݽ���	�յ�����������Ϣ	���ݽ��������ݽ����ɹ��󣬷����ź���
				{
					memcpy(rx_isa_sn,&rx_buf_array[18],6);
					memcpy(rx_pow_sn,&rx_buf_array[24],6);
					
					//�ж��յ���SN�룬rx_pow_sn
					MI_V	= rx_buf_array[30]<<8 | rx_buf_array[31];
					BAT_I	= rx_buf_array[32]<<8 | rx_buf_array[33];
					BAT_V	= rx_buf_array[34]<<8 | rx_buf_array[35];
					TEMP	= rx_buf_array[36]<<8 | rx_buf_array[37];
					
					log_info("rx_isa_sn:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",rx_isa_sn[0],rx_isa_sn[1],rx_isa_sn[2],rx_isa_sn[3],rx_isa_sn[4],rx_isa_sn[5]);
					log_info("rx_pow_sn:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",rx_pow_sn[0],rx_pow_sn[1],rx_pow_sn[2],rx_pow_sn[3],rx_pow_sn[4],rx_pow_sn[5]);
					log_info("MI_V=0x%x BAT_I=0x%x,BAT_V=0x%x,TEMP=0x%x\r\n",MI_V,BAT_I,BAT_V,TEMP);
				}
				else
				{
					sta = 4;	//������,�����յ�������ָ�����ʹ���
				}	
			}
			else
			{
				sta = 3;	//������,��������У�����
				log_info("error,Frame error......\r\n");
			}	
		}
		else
		{
			sta = 2;	//������,������������û��+IPD�ַ���������
		}
		USART1_ClearRxBuf_Flag();
	}
	else
	{
		sta = 1;	//������,������û�յ����ݣ�
	}
	log_info("wifi_get_cfg sta=%d\r\n",sta);
	return sta;
}

void wifi_thread_entry(void *par)
{
	uint8_t retry_count = 3;
	UART1_RBUF_ST *p = &uart1_rbuf;
	char *ret;
	char *tx_buf=NULL;
	uint8_t tx_buf_array[256] = {0};
	uint8_t rx_buf_array[256] = {0};
	uint8_t	rx_pow_sn[6]	={0};
	uint8_t	rx_isa_sn[6]	={0};
	
	WIFI_POWER_Ctrl(1);						//1����wifiģ���Դ
	WIFI_AT_Test();							//2������ATָ��
	//WIFI_ATE_Ctrl(0);						//�ر�AT����
	WIFI_Set_Mode(1,1);						//3������ģ�鹤��ģʽΪ�ͻ���ģʽ
	WIFI_Set_DHCP(1,0);						//4������DHCPģʽ
	WIFI_Scan();							//5��ɨ��wifi������ɨ��ָ����wifi	
	
	if(1)//��ȡ����ֵ�������Ҫ���ã���ִ���������񣬷���ֱ������,�Ӵ洢���ж�ȡ���õ�SSID
	{
		WIFI_Join_AP(WIFI_CFG_SSID,WIFI_CFG_PASS);	//6��wifiģ�����ӵ�AP
		WIFI_Query_WIFI();							//7����ѯwifiģ��IP��Ϣ��������Ϣ��
		WIFI_Set_Mux(0);							//8������Ϊ������ģʽ
		WIFI_Creat_Socket();						//9��ģ�鴴��������Socket
		
		while(wifi_get_cfg(0))			//�ȴ���ȡ������Ϣ
		{
			rt_thread_mdelay(5000);
		}
		
		//��������Ϣ���浽�洢����
		WIFI_Disconnect_AP();			
		WIFI_Join_AP((char *)wifi_ssid,(char *)wifi_pass);	//�����µ�wifi		
		WIFI_Set_Mux(0);	//
		WIFI_Creat_Socket();
	}
	else
	{
		//�Ӵ洢���ж�ȡ������Ϣ
		WIFI_Join_AP((char *)wifi_ssid,(char *)wifi_pass);	//6��wifiģ�����ӵ�AP
		WIFI_Query_WIFI();							//7����ѯwifiģ��IP��Ϣ��������Ϣ��
		WIFI_Set_Mux(0);							//8������Ϊ������ģʽ
		WIFI_Creat_Socket();						//9��ģ�鴴��������Socket
	}
	
	rt_thread_mdelay(3000);
	
	while(1)
	{
		wifi_get_cfg(1);
		rt_thread_mdelay(5000);
	}
	
	
	
	
	memset(tx_buf_array,0,sizeof(tx_buf_array));
	memcpy(tx_buf_array,&sCM_Requst_Cfg.frame_h,sizeof(sCM_Requst_Cfg));	
	
	rt_thread_mdelay(350);
	
	while(1)
	{
		
		/*****	A:�˺��������	*******************************************************************************************************/
		WIFI_Socket_Send(1,(char *)tx_buf_array,sizeof(sCM_Requst_Cfg));
		rt_thread_mdelay(3000);
		if(p->rx_flag == 1 )	//�յ�ģ�鷢�͵����ݣ������ֻ�����쳣��������������
		{
			uint8_t ix = 0;
			
//			log_info("22wifi_rx data:len=%d\r\n",p->rx_len);		//��ӡ���ڽ��յ�����������
//			for(ix=0;ix<p->rx_len;ix++)
//			{
//				log_info("rx_data[%d]:0x%x\r\n",ix,p->rx_buf[ix]);
//			}
//			log_info("\r\n");
//			
			
			if(strstr((const char *)p->rx_buf,wifi_tcp_read_stack))	//�����ַ�����ʱ����+IPD������˵���յ�������
			{
				uint16_t tcp_rx_len = 0;
				uint8_t tcp_order_type = 0;
				tcp_rx_len = (p->rx_buf[14]<<8 | p->rx_buf[15]) + 7;			//��ȡ���ݳ���
				tcp_order_type = p->rx_buf[22];									//��ȡָ������
				log_info("333rx_data...........,tcp_rx_len:%d��tcp_order_type:0x%x\r\n",tcp_rx_len,tcp_order_type);
				
				//֡ͷ֡β�жϣ�֤�����ݴ�������
				
				if( (p->rx_buf[10] == 0xa5) && (p->rx_buf[11] == 0xa5)  && (p->rx_buf[12] == 0xa5) && (p->rx_buf[p->rx_len-3] == 0x5a)  )
				{
					//֡ͷ֡β�жϳɹ���������cpy��������
					memcpy(rx_buf_array,&p->rx_buf[10],tcp_rx_len);
					for(ix=0;ix<tcp_rx_len;ix++)
					{
						log_info("rx_data[%d]:0x%x\r\n",ix,rx_buf_array[ix]);
					}
					
					//���ݽ���
					if( tcp_order_type == 0x15 )	//�յ�����������Ϣ
					{
						//�ж��յ���SN�룬rx_pow_sn
						
						memcpy(rx_isa_sn,&rx_buf_array[18],6);
						memcpy(rx_pow_sn,&rx_buf_array[24],6);
						wifi_ssid_len = rx_buf_array[30];
						wifi_pass_len = rx_buf_array[31+wifi_ssid_len];
						memcpy(wifi_ssid,&rx_buf_array[31],wifi_ssid_len);
						memcpy(wifi_pass,&rx_buf_array[32+wifi_ssid_len],wifi_pass_len);
						
						log_info("rx_isa_sn:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",rx_isa_sn[0],rx_isa_sn[1],rx_isa_sn[2],rx_isa_sn[3],rx_isa_sn[4],rx_isa_sn[5]);
						log_info("rx_pow_sn:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\r\n",rx_pow_sn[0],rx_pow_sn[1],rx_pow_sn[2],rx_pow_sn[3],rx_pow_sn[4],rx_pow_sn[5]);
						log_info("wifi_ssid_len=%d ssid=%s\r\n",wifi_ssid_len,wifi_ssid);
						log_info("wifi_pass_len=%d pass=%s\r\n",wifi_pass_len,wifi_pass);
						
						WIFI_Disconnect_AP();
						
						WIFI_Join_AP((char *)wifi_ssid,(char *)wifi_pass);
						WIFI_Set_Mux(0);	//����Ϊ������
						WIFI_Creat_Socket();
						
						while(1)
						{
							rt_thread_mdelay(200);
						}
						
						//�����µ�wifi
						//�Ͽ�TCP
						//�Ͽ�wifi
						//�����µ�wifi
						//�����µ�TCP	
					}
					
					if( tcp_order_type == 0x11 )	//�յ��������ط��͵�����
					{
						
					}
				}
				else
				{
					log_info("error,Frame error......\r\n");
				}	
			}
			USART1_ClearRxBuf_Flag();
			//WIFI_Recv_Dat();
		}
	}	
}


