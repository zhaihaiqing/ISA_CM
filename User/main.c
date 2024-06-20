/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"

sWifi_Cfg_t sWifi_Cfg;

sCM_Requst_Cfg_t sCM_Requst_Cfg;	//充电模块请求配置信息
sCM_Respond_Cfg_t sCM_Respond_Cfg;	//响应配置信息

RCC_ClocksTypeDef RCC_Clocks;

/*******************************************************************************
* Function Name  : Init_Devices function
* Description    : 完成硬件设备、各功能模块初始化
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Init_Devices(void)
{
	//完成基本硬件初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);//中断优先级分组设置
	Init_SysTick();//开启SysTick定时器
	
	get_rccclock_info();
	
	GPIO_Configuration();
	
	UART1_Configuration(115200);
	
	Dac1_fixed_Init();
	//ADC_GPIO_Configuration();
	//i2cb_port_init();
	//EE_Init();
	
	
}

/*******************************************************************************
* Function Name  : main
* Description    : 主函数
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/



int main(void)
{
	
	Init_Devices();
	
	
	scs_thread_init();
	
	
	
	
	
	while (1)	//串口解析
	{
		WDI_FD();
		LED1_ON();
		//LED2_ON();
		rt_thread_mdelay(100);
			
		LED1_OFF();
		//LED2_OFF();
		rt_thread_mdelay(100);
		
		

		
	}
}



#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
