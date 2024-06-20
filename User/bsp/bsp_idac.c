
#include "main.h"


//DAC通道1输出固定电压值
void Dac1_fixed_Init(void)
{  
	GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能DAC时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

	DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Enable ;	//DAC1输出缓存关闭 BOFF1=1
	DAC_Init(DAC_Channel_1,&DAC_InitStructure);	 //初始化DAC通道1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC通道1
  
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
}
//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_fixed_Vol(float vol)
{
	float temp=0.0;
	temp=vol*4.095/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
}


//void DAC_Ch1_NoiseConfig(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	DMA_InitTypeDef   DMA_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//开启DMA1时钟
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能DAC时钟
//	
//	   
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//下拉
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化

//	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;	//选择触发功能，触发源为T6 TEN1=0
//	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_Noise;//不使用波形发生
//	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bits10_0;//屏蔽、幅值设置
//	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
//	DAC_Init(DAC_Channel_1,&DAC_InitStructure);	 //初始化DAC通道1

//	/* DMA1_Stream5 channel7 configuration **************************************/ 
//	//DMA数据5的第7通道，DAC1
//	DMA_DeInit(DMA1_Stream5);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_7; 
//	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1_ADDRESS;
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&Wave_Xnum_U16;
//	DMA_InitStructure.DMA_BufferSize = WAVE_DOT_NUM;											//一个周期内的点数
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;		//传输宽度
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;				//内存地址宽度
//	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;							//传输方向
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//	DMA_Init(DMA1_Stream5, &DMA_InitStructure);    
//	
//	/* Enable DMA1_Stream5 */
//	DMA_Cmd(DMA1_Stream5, ENABLE);
//  
//	/* Enable DAC Channel1 */
//	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC通道1
//	/* Enable DMA for DAC Channel1 */
//	//DAC_DMACmd(DAC_Channel_1, ENABLE);
//	DAC_SetChannel1Data(DAC_Align_12b_L, 0x7FF0);
//}





