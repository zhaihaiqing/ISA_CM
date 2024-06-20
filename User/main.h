/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.h 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//#include "arm_math.h"

#include "rtthread.h"
#include "thread_entry.h"

#include "sys.h"
#include "debug_uart.h"
#include "bsp_gpio.h"

#include "bsp_uart.h"
#include "bsp_temp.h"
#include "bsp_adc.h"
#include "bsp_iadc.h"
#include "bsp_idac.h"
#include "bsp_i2c.h"
#include "bsp_i2ca_port.h"
#include "bsp_i2cb_port.h"
#include "bsp_i2cc_port.h"
#include "bsp_spi.h"

#include "bsp_oled.h"
#include "bsp_codec.h"
#include "bsp_timer.h"
#include "bsp_eeprom.h"
#include "bsp_ds18b20.h"

#include "app_key.h"
#include "app_codec.h"
#include "app_temp.h"
#include "app_adc.h"
#include "app_led.h"
#include "app_wifi.h"
#include "app_test.h"


//#define __FPU_PRESENT 	1U
//#define __FPU_USED 		1U


//需要存储的参数
typedef struct  __attribute__ ((__packed__))		
{												
	int16_t  		Front_Panel_current;			//前面板设置的电流值
	
}sMEMData_t;



//设备参数
typedef struct  __attribute__ ((__packed__))		
{	
	char		sn[16];						//充电模块SN
	
	char  		tool_ssid[128];				//AP的SSID
	char  		tool_password[128];			//AP登录密码
	char		tool_gw_mac[32];			//网关MAC地址，可不设置
	char		tool_gw_ip[32];				//网关ip地址
	char		tool_gw_port[8];			//网关端口号
	
	char  		ssid[128];		//AP的SSID
	char  		password[128];	//AP登录密码
	char		gw_mac[32];		//网关MAC地址，可不设置
	char		gw_ip[16];		//网关ip地址
	char		gw_port[8];		//网关端口号
	
	uint8_t		sta_dhcp;		//模块是否开启dhcp功能
	uint8_t		sta_ip[8];		//模块的ip地址，如果开启了dhcp，则ip地址不起作用
	
	uint8_t		pss;			//充电功率等级，0=关闭,1=5V,2=7.5V,3=9V,4=12V,5=15V,6=nc,7=nc,8=nc,9=nc,f=PID		
}sWifi_Cfg_t;



//充电模块请求wifi账号，密码
typedef struct  __attribute__ ((__packed__))		
{	
	uint8_t		frame_h[3];						
	uint8_t  	cmd_pow;				//
	uint8_t   	dat_len_h;			//
	uint8_t   	dat_len_l;
	uint8_t		rev[6];			//
	uint8_t		cmd;				//
	uint8_t		time[4];			//
	uint8_t  	err;		//
	uint8_t		charge_sat;
	uint8_t  	isa_sn[6];	//
	uint8_t		pow_sn[6];		//
	uint8_t		frame_end;	
}sCM_Requst_Cfg_t;

//响应请求的wifi账号，密码
typedef struct  __attribute__ ((__packed__))		
{	
	uint8_t		frame_h[3];						
	uint8_t  	cmd_pow;				//
	uint8_t   	dat_len_h;			//
	uint8_t   	dat_len_l;
	uint8_t		rev[6];			//
	uint8_t		cmd;				//
	uint8_t		time[4];			//
	uint8_t  	err;		//
	uint8_t		wifi_ssid_len;
	uint8_t  	ssid[256];	//
	uint8_t		wifi_pass_len;
	uint8_t		pass_word[256];		//
	uint8_t		frame_end;	
}sCM_Respond_Cfg_t;





extern sWifi_Cfg_t 			sWifi_Cfg;	
extern sCM_Requst_Cfg_t 	sCM_Requst_Cfg;
extern sCM_Respond_Cfg_t 	sCM_Respond_Cfg;



/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);



#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
