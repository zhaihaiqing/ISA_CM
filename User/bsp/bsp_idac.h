
#ifndef __BSP_IDAC_H
#define __BSP_IDAC_H


void Dac1_fixed_Init(void);	//初始化DAC，默认电压值为0V
void Dac1_Set_fixed_Vol(float vol);//设置DAC输出电压值，单位mV


#endif 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
