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


//��Ҫ�洢�Ĳ���
typedef struct  __attribute__ ((__packed__))		
{												
	int16_t  		Front_Panel_current;			//ǰ������õĵ���ֵ
	
}sMEMData_t;



//�豸����
typedef struct  __attribute__ ((__packed__))		
{	
	char		sn[16];						//���ģ��SN
	
	char  		tool_ssid[128];				//AP��SSID
	char  		tool_password[128];			//AP��¼����
	char		tool_gw_mac[32];			//����MAC��ַ���ɲ�����
	char		tool_gw_ip[32];				//����ip��ַ
	char		tool_gw_port[8];			//���ض˿ں�
	
	char  		ssid[128];		//AP��SSID
	char  		password[128];	//AP��¼����
	char		gw_mac[32];		//����MAC��ַ���ɲ�����
	char		gw_ip[16];		//����ip��ַ
	char		gw_port[8];		//���ض˿ں�
	
	uint8_t		sta_dhcp;		//ģ���Ƿ���dhcp����
	uint8_t		sta_ip[8];		//ģ���ip��ַ�����������dhcp����ip��ַ��������
	
	uint8_t		pss;			//��繦�ʵȼ���0=�ر�,1=5V,2=7.5V,3=9V,4=12V,5=15V,6=nc,7=nc,8=nc,9=nc,f=PID		
}sWifi_Cfg_t;



//���ģ������wifi�˺ţ�����
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

//��Ӧ�����wifi�˺ţ�����
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
