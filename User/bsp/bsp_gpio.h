
#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

#define LED1   0x01
#define LED2   0x02
#define LED3   0x04
#define LED4   0x08

#define LED_RUN1   0x11
#define LED_RUN2   0x12

#define CFG_RST_GPIO_Pin	GPIO_Pin_8		//wifi重新配置按键
#define CFG_RST_GPIO_Port	GPIOB

#define LED1_GPIO_Pin		GPIO_Pin_12		//板级指示灯，LED1
#define LED1_GPIO_Port		GPIOB

#define LED2_GPIO_Pin		GPIO_Pin_14		//板级指示灯，LED2
#define LED2_GPIO_Port		GPIOB

#define LED3_GPIO_Pin		GPIO_Pin_15		//板级指示灯，LED3
#define LED3_GPIO_Port		GPIOB

#define LED4_GPIO_Pin		GPIO_Pin_8		//板级指示灯，LED4
#define LED4_GPIO_Port		GPIOC

#define LED_RUN1_GPIO_Pin	GPIO_Pin_9		//板级指示灯，LED_RUN1
#define LED_RUN1_GPIO_Port	GPIOC

#define LED_RUN2_GPIO_Pin	GPIO_Pin_8		//板级指示灯，LED_RUN2
#define LED_RUN2_GPIO_Port	GPIOA



#define WDI_GPIO_Pin			GPIO_Pin_13		//喂狗信号，WDI
#define WDI_GPIO_Port			GPIOC


#define POWEN_GPIO_Pin			GPIO_Pin_13		//PPS电源使能信号
#define POWEN_GPIO_Port			GPIOB

#define WLPEN_GPIO_Pin			GPIO_Pin_0		//PPS电源使能信号
#define WLPEN_GPIO_Port			GPIOC

#define WIFI_POWEN_GPIO_Pin		GPIO_Pin_12		//WIFI电源使能信号
#define WIFI_POWEN_GPIO_Port	GPIOA

#define WIFI_RST_GPIO_Pin		GPIO_Pin_11		//WIFI使能信号
#define WIFI_RST_GPIO_Port		GPIOA



#define READ_CFGRST_SW()		GPIO_ReadInputDataBit(CFG_RST_GPIO_Port,CFG_RST_GPIO_Pin)	




#define LED1_ON()				GPIO_ResetBits(LED1_GPIO_Port,LED1_GPIO_Pin)
#define LED1_OFF()				GPIO_SetBits(LED1_GPIO_Port,LED1_GPIO_Pin)

#define LED2_ON()				GPIO_ResetBits(LED2_GPIO_Port,LED2_GPIO_Pin)
#define LED2_OFF()				GPIO_SetBits(LED2_GPIO_Port,LED2_GPIO_Pin)

#define LED3_ON()				GPIO_ResetBits(LED3_GPIO_Port,LED3_GPIO_Pin)
#define LED3_OFF()				GPIO_SetBits(LED3_GPIO_Port,LED3_GPIO_Pin)

#define LED4_ON()				GPIO_ResetBits(LED4_GPIO_Port,LED4_GPIO_Pin)
#define LED4_OFF()				GPIO_SetBits(LED4_GPIO_Port,LED4_GPIO_Pin)

#define LED_RUN1_ON()			GPIO_ResetBits(LED_RUN1_GPIO_Port,LED_RUN1_GPIO_Pin)
#define LED_RUN1_OFF()			GPIO_SetBits(LED_RUN1_GPIO_Port,LED_RUN1_GPIO_Pin)

#define LED_RUN2_ON()			GPIO_ResetBits(LED_RUN2_GPIO_Port,LED_RUN2_GPIO_Pin)
#define LED_RUN2_OFF()			GPIO_SetBits(LED_RUN2_GPIO_Port,LED_RUN2_GPIO_Pin)


#define WDI_FD()				GPIO_ToggleBits(WDI_GPIO_Port,WDI_GPIO_Pin)

#define POW_EN_ON()				GPIO_SetBits(POWEN_GPIO_Port,POWEN_GPIO_Pin)
#define POW_EN_OFF()			GPIO_ResetBits(POWEN_GPIO_Port,POWEN_GPIO_Pin)

#define WLP_EN_ON()				GPIO_SetBits(WLPEN_GPIO_Port,WLPEN_GPIO_Pin)
#define WLP_EN_OFF()			GPIO_ResetBits(WLPEN_GPIO_Port,WLPEN_GPIO_Pin)


#define WIFI_POW_EN_ON()		GPIO_SetBits(WIFI_POWEN_GPIO_Port,WIFI_POWEN_GPIO_Pin)
#define WIFI_POW_EN_OFF()		GPIO_ResetBits(WIFI_POWEN_GPIO_Port,WIFI_POWEN_GPIO_Pin)

#define WIFI_RST_HIGH()			GPIO_SetBits(WIFI_RST_GPIO_Port,WIFI_RST_GPIO_Pin)
#define WIFI_RST_LOW()			GPIO_ResetBits(WIFI_RST_GPIO_Port,WIFI_RST_GPIO_Pin)






void key_Init(void);
void GPIO_Configuration(void);
void DIGIN_Iint(void);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
