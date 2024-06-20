#include "main.h"

/*
1：测试命令		AT+<命令名称>=?
2：查询命令		AT+<命令名称>?
3：设置命令		AT+<命令名称>=<...>
4：执行命令		AT+<命令名称>
*/

/*
基础AT命令集

AT					测试AT
AT+HELP				查看AT指令集
AT+RST				模块重启
AT+RESTORE			回复出厂设置
ATE1				打开回显
ATE0				关闭回显
AT+GMR				查询版本信息
AT+SLEEP			睡眠模式
AT+UARTCFG			串口设置
AT+OTA				在线升级
*/

/*
WIFI AT命令集

AT+WMODE			WIFI工作模式
AT+WSCAN			扫描WIFI列表
AT+WSDHCP			STA模式下DHCP参数
AT+WJAP				连接AP
AT+WDISCONNECT		断开当前的AP连接
AT+WAUTOCONN		上电自动连接WIFI
AT+WAPDHCP			AP模式下DHCP参数
AT+WAP				AP模式WIFI参数
AT+PING				进行Ping操作
AT+CIPSTAMAC_DEF	WIFI station MAC地址
AT+WCOUNTRY			WIFI国家代码
AT+WCONFIG			手机配网
AT+WSACNOPT			筛选WIFI扫描信息显示
AT+WRSSI			WIFI连接信号强度
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
*	wifi模块电源控制
*	0=关闭电源，1=开启电源，并等待模块就绪
*********************************************************************/
void WIFI_POWER_Ctrl(uint8_t parameter)
{
	uint8_t retry_count = 3;
	UART1_RBUF_ST *p = &uart1_rbuf;
	char *ret;
	
	if(parameter == 0)	//关闭wifi模块电源
	{
		WIFI_POW_EN_OFF();
		WIFI_RST_LOW();
	}
	else			//wifi模块上电，如果失败重试3次
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
*	wifi模块AT指令测试
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
*	wifi模块AT指令回显控制
*	0=关闭回显，1=开启回显
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
*	wifi扫描
*	打印扫描的结果
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
*	设置wifi模块的工作模式
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
*	设置wifi模块的DHCP模式
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
*	wifi模块连接AP
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
*	wifi模块断开与AP的连接
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
*	查询wifi模式、联网信息
*	
*********************************************************************/
void WIFI_Query_WIFI(void)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	Wifi_SendAT("AT+CWMODE?\r\n");		//查询wifi模式
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
	
	Wifi_SendAT("AT+CWSTATE?\r\n");		//查询wifi信息
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
	
	Wifi_SendAT("AT+CIPSTA?\r\n");		//查询联网信息
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
*	TCP连接模式设置，单连接、多连接
*	
*********************************************************************/
void WIFI_Set_Mux(uint8_t mode)	//TCP连接模式设置
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	
	if(mode == 0)
	{
		Wifi_SendAT("AT+CIPMUX=0\r\n");	//设置单连接模式
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
	else if(mode == 1)	//设置为多连接模式
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
*	创建TCP连接
*	
*********************************************************************/
void WIFI_Creat_Socket(void)	//客户端采用单连接模式
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
*	wifi 发送函数，输入要发送的数据类型、字符串和长度
*	
*********************************************************************/
void WIFI_Socket_Send(uint8_t send_type ,char *ss,uint16_t dat_len)
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	char tx_buf[64] = {0};
	
	sprintf(tx_buf,"AT+CIPSEND=%d\r\n",dat_len);
	Wifi_SendAT(tx_buf);			//A:进入数据发送模式，并设置发送长度
	
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
	
	if(send_type == 0)					//如果类型为0，则发送的是字符串，否则，则发送的是数据
	{
		Wifi_SendAT(ss);				//B:发送特定长度的数据
	}
	else								//如果类型为1，则发送的是数据					
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
*	wifi 数据接收函数
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
*	设置接收模式，主动接收和被动接收
*	
*********************************************************************/
void WIFI_Set_RecvType(void)	//设置数据接收模式为手动模式
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

void WIFI_Recv_Dat(void)//被动接受模式，数据接受，避免突发事件导致的乱序
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
			//接受数据长度成功
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
//				ptr = strchr((const char *)p->rx_buf, ch);//寻找\r出现的位置
//				tt =  ptr - p->rx_buf + 1;	//计算\r的下标
//				
//				for(ix = 0; ix<tt-s_p-1 ; ix++)			//将=和\r之间的数字复制到缓冲区，并将其转换为数字
//					s_buf[ix] = p->rx_buf[ix+s_p];
//				
//				Scoket_ConID = strtol((const char *)s_buf , NULL , 10);	//获取ConID
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



//wifi工具，默认账号密码
char WIFI_CFG_SSID[128] = "WIFI_TOOL";
char WIFI_CFG_PASS[128] = "12345678";

//配置的账号密码
uint8_t	wifi_ssid_len = 	0;
uint8_t wifi_ssid[128] = 	{0};
uint8_t wifi_pass_len = 	0;
uint8_t wifi_pass[128] = 	{0};

uint16_t MI_V	= 0;
uint16_t BAT_V	= 0;
uint16_t BAT_I	= 0;
int16_t  TEMP	= 0;

//wifi模块获取配置信息，并解析
uint8_t wifi_get_cfg(uint8_t type)	//0：获取配置信息，1：获取数据
{
	UART1_RBUF_ST *p = &uart1_rbuf;
	uint8_t tx_buf_array[256] = {0};
	uint8_t rx_buf_array[256] = {0};
	uint8_t	rx_pow_sn[6]	={0};
	uint8_t	rx_isa_sn[6]	={0};
	uint8_t ix = 0;
	uint16_t tcp_rx_len = 0;
	uint8_t tcp_order_type = 0;
	uint8_t sta	=	0;	//返回值
	
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
	if(p->rx_flag == 1 )	//收到模块发送的数据，在这里，只处理异常情况、例如断联等
	{
		//1：将收到的数据复制到数组中，
		//2：解析命令码，判断数据类型	
		if(strstr((const char *)p->rx_buf,wifi_tcp_read_stack))	//查找字符串中时候有+IPD，有则说明收到了数据
		{
			tcp_rx_len = (p->rx_buf[14]<<8 | p->rx_buf[15]) + 7;			//获取数据长度
			tcp_order_type = p->rx_buf[22];									//获取指令类型
			log_info("333rx_data...........,tcp_rx_len:%d，tcp_order_type:0x%x\r\n",tcp_rx_len,tcp_order_type);
			
			//帧头帧尾判断，证明数据传输无误
			if( (p->rx_buf[10] == 0xa5) && (p->rx_buf[11] == 0xa5)  && (p->rx_buf[12] == 0xa5) && (p->rx_buf[p->rx_len-3] == 0x5a)  )
			{
				memcpy(rx_buf_array,&p->rx_buf[10],tcp_rx_len);	//帧头帧尾判断成功，将数据cpy到缓存中
				for(ix=0;ix<tcp_rx_len;ix++)
				{
					log_info("rx_data[%d]:0x%x\r\n",ix,rx_buf_array[ix]);
				}
				
				if( tcp_order_type == 0x15 )	////数据解析	收到的是配置信息	账号密码解析	
				{
					memcpy(rx_isa_sn,&rx_buf_array[18],6);
					memcpy(rx_pow_sn,&rx_buf_array[24],6);
					
					//判断收到的SN码，rx_pow_sn
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
				else if( tcp_order_type == 0x11 )	////数据解析	收到的是数据信息	数据解析，数据解析成功后，发送信号量
				{
					memcpy(rx_isa_sn,&rx_buf_array[18],6);
					memcpy(rx_pow_sn,&rx_buf_array[24],6);
					
					//判断收到的SN码，rx_pow_sn
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
					sta = 4;	//错误码,代表收到的数据指令类型错误
				}	
			}
			else
			{
				sta = 3;	//错误码,代表数据校验错误
				log_info("error,Frame error......\r\n");
			}	
		}
		else
		{
			sta = 2;	//错误码,代表串口数据中没有+IPD字符，无数据
		}
		USART1_ClearRxBuf_Flag();
	}
	else
	{
		sta = 1;	//错误码,代表串口没收到数据，
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
	
	WIFI_POWER_Ctrl(1);						//1：打开wifi模块电源
	WIFI_AT_Test();							//2：测试AT指令
	//WIFI_ATE_Ctrl(0);						//关闭AT回显
	WIFI_Set_Mode(1,1);						//3：设置模块工作模式为客户端模式
	WIFI_Set_DHCP(1,0);						//4：设置DHCP模式
	WIFI_Scan();							//5：扫描wifi，或者扫描指定的wifi	
	
	if(1)//读取配置值，如果需要配置，则执行配置任务，否则直接跳过,从存储器中读取配置的SSID
	{
		WIFI_Join_AP(WIFI_CFG_SSID,WIFI_CFG_PASS);	//6：wifi模块连接到AP
		WIFI_Query_WIFI();							//7：查询wifi模块IP信息、联网信息等
		WIFI_Set_Mux(0);							//8：设置为单连接模式
		WIFI_Creat_Socket();						//9：模块创建并连接Socket
		
		while(wifi_get_cfg(0))			//等待获取配置信息
		{
			rt_thread_mdelay(5000);
		}
		
		//将配置信息保存到存储器中
		WIFI_Disconnect_AP();			
		WIFI_Join_AP((char *)wifi_ssid,(char *)wifi_pass);	//连接新的wifi		
		WIFI_Set_Mux(0);	//
		WIFI_Creat_Socket();
	}
	else
	{
		//从存储器中读取配置信息
		WIFI_Join_AP((char *)wifi_ssid,(char *)wifi_pass);	//6：wifi模块连接到AP
		WIFI_Query_WIFI();							//7：查询wifi模块IP信息、联网信息等
		WIFI_Set_Mux(0);							//8：设置为单连接模式
		WIFI_Creat_Socket();						//9：模块创建并连接Socket
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
		
		/*****	A:账号密码解析	*******************************************************************************************************/
		WIFI_Socket_Send(1,(char *)tx_buf_array,sizeof(sCM_Requst_Cfg));
		rt_thread_mdelay(3000);
		if(p->rx_flag == 1 )	//收到模块发送的数据，在这里，只处理异常情况、例如断联等
		{
			uint8_t ix = 0;
			
//			log_info("22wifi_rx data:len=%d\r\n",p->rx_len);		//打印串口接收到的所有数据
//			for(ix=0;ix<p->rx_len;ix++)
//			{
//				log_info("rx_data[%d]:0x%x\r\n",ix,p->rx_buf[ix]);
//			}
//			log_info("\r\n");
//			
			
			if(strstr((const char *)p->rx_buf,wifi_tcp_read_stack))	//查找字符串中时候有+IPD，有则说明收到了数据
			{
				uint16_t tcp_rx_len = 0;
				uint8_t tcp_order_type = 0;
				tcp_rx_len = (p->rx_buf[14]<<8 | p->rx_buf[15]) + 7;			//获取数据长度
				tcp_order_type = p->rx_buf[22];									//获取指令类型
				log_info("333rx_data...........,tcp_rx_len:%d，tcp_order_type:0x%x\r\n",tcp_rx_len,tcp_order_type);
				
				//帧头帧尾判断，证明数据传输无误
				
				if( (p->rx_buf[10] == 0xa5) && (p->rx_buf[11] == 0xa5)  && (p->rx_buf[12] == 0xa5) && (p->rx_buf[p->rx_len-3] == 0x5a)  )
				{
					//帧头帧尾判断成功，将数据cpy到缓存中
					memcpy(rx_buf_array,&p->rx_buf[10],tcp_rx_len);
					for(ix=0;ix<tcp_rx_len;ix++)
					{
						log_info("rx_data[%d]:0x%x\r\n",ix,rx_buf_array[ix]);
					}
					
					//数据解析
					if( tcp_order_type == 0x15 )	//收到的是配置信息
					{
						//判断收到的SN码，rx_pow_sn
						
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
						WIFI_Set_Mux(0);	//设置为单连接
						WIFI_Creat_Socket();
						
						while(1)
						{
							rt_thread_mdelay(200);
						}
						
						//连接新的wifi
						//断开TCP
						//断开wifi
						//连接新的wifi
						//连接新的TCP	
					}
					
					if( tcp_order_type == 0x11 )	//收到的是网关发送的数据
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


