
#include "main.h"



//��ʼ��ADC															   
void  Adc1_Init(void)
{   	
	GPIO_InitTypeDef  		GPIO_InitStructure;
	ADC_CommonInitTypeDef 	ADC_CommonInitStructure;
	ADC_InitTypeDef       	ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��

	//�ȳ�ʼ��ADC1ͨ��0 IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//PA0 ͨ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  	//ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);	//��λ����	 
 
	
	ADC_StructInit(&ADC_InitStructure);	
	
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
	
	
	ADC_RegularChannelConfig(ADC1, 0, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��	
	
	ADC_Cmd(ADC1, ENABLE);//����ADת����	
}				  
//���ADCֵ
//ch: @ref ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_Channel_0~ADC_Channel_16
//����ֵ:ת�����
unsigned short Get_Adc1()   
{
	ADC_SoftwareStartConv(ADC1);	//ʹ��ָ����ADC1�����ת����������	
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}


float get_pow_in_val()
{
	float val=0.0;
	
	val=5.22*Get_Adc1()*3.300/0xfff;

	return val;
	
}



void  Adc2_Init(void)
{    
	GPIO_InitTypeDef  		GPIO_InitStructure;
	ADC_CommonInitTypeDef 	ADC_CommonInitStructure;
	ADC_InitTypeDef       	ADC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //ʹ��ADC2ʱ��

	//�ȳ�ʼ��ADC2ͨ��1 IO��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PA0 ͨ��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��  
 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,ENABLE);	  	//ADC2��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2,DISABLE);	//��λ����	 
 
	
	ADC_StructInit(&ADC_InitStructure);	
	
	
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMAʧ��
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC2, &ADC_InitStructure);//ADC��ʼ��
	
	
	ADC_RegularChannelConfig(ADC2, 1, 1, ADC_SampleTime_480Cycles );	//ADC1,ADCͨ��,480������,��߲���ʱ�������߾�ȷ��	
	
	ADC_Cmd(ADC2, ENABLE);//����ADת����	
}

unsigned short Get_Adc2()   
{
	ADC_SoftwareStartConv(ADC2);	//ʹ��ָ����ADC1�����ת����������	
	while(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC2);	//�������һ��ADC1�������ת�����
}

float get_pow_out_val()
{
	float val=0.0;
	
	val=5.22*Get_Adc2()*3.300/0xfff;

	return val;
	
}


