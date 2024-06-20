
#include "main.h"


//DACͨ��1����̶���ѹֵ
void Dac1_fixed_Init(void)
{  
	GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//ʹ��DACʱ��
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��

	DAC_InitStructure.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Enable ;	//DAC1�������ر� BOFF1=1
	DAC_Init(DAC_Channel_1,&DAC_InitStructure);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DACͨ��1
  
	DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ
}
//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac1_Set_fixed_Vol(float vol)
{
	float temp=0.0;
	temp=vol*4.095/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}


//void DAC_Ch1_NoiseConfig(void)
//{
//	GPIO_InitTypeDef  GPIO_InitStructure;
//	DMA_InitTypeDef   DMA_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//����DMA1ʱ��
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//ʹ��DACʱ��
//	
//	   
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//����
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��

//	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO;	//ѡ�񴥷����ܣ�����ԴΪT6 TEN1=0
//	DAC_InitStructure.DAC_WaveGeneration=DAC_WaveGeneration_Noise;//��ʹ�ò��η���
//	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bits10_0;//���Ρ���ֵ����
//	DAC_InitStructure.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
//	DAC_Init(DAC_Channel_1,&DAC_InitStructure);	 //��ʼ��DACͨ��1

//	/* DMA1_Stream5 channel7 configuration **************************************/ 
//	//DMA����5�ĵ�7ͨ����DAC1
//	DMA_DeInit(DMA1_Stream5);
//	DMA_InitStructure.DMA_Channel = DMA_Channel_7; 
//	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1_ADDRESS;
//	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&Wave_Xnum_U16;
//	DMA_InitStructure.DMA_BufferSize = WAVE_DOT_NUM;											//һ�������ڵĵ���
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;		//������
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;				//�ڴ��ַ���
//	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;							//���䷽��
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
//	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DACͨ��1
//	/* Enable DMA for DAC Channel1 */
//	//DAC_DMACmd(DAC_Channel_1, ENABLE);
//	DAC_SetChannel1Data(DAC_Align_12b_L, 0x7FF0);
//}





