
#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#define DA_CS1_L()	  	GPIO_ResetBits(GPIOF,GPIO_Pin_0)
#define DA_CS1_H()      GPIO_SetBits(GPIOF,GPIO_Pin_0)

#define DA_CS2_L()	  	GPIO_ResetBits(GPIOF,GPIO_Pin_1)
#define DA_CS2_H()      GPIO_SetBits(GPIOF,GPIO_Pin_1)


#define DA_CLR1_L()	  	GPIO_ResetBits(GPIOF,GPIO_Pin_9)
#define DA_CLR1_H()     GPIO_SetBits(GPIOF,GPIO_Pin_9)

#define DA_CLR2_L()	  	GPIO_ResetBits(GPIOF,GPIO_Pin_7)
#define DA_CLR2_H()     GPIO_SetBits(GPIOF,GPIO_Pin_7)

#define DA_LDAC1_L()	GPIO_ResetBits(GPIOF,GPIO_Pin_10)
#define DA_LDAC1_H()    GPIO_SetBits(GPIOF,GPIO_Pin_10)

#define DA_LDAC2_L()	GPIO_ResetBits(GPIOF,GPIO_Pin_8)
#define DA_LDAC2_H()    GPIO_SetBits(GPIOF,GPIO_Pin_8)



void SPI3_Config(void);
unsigned char SPI3_ReadWriteByte(unsigned char byte);
void SPI3_WriteByte(unsigned char byte);

void AD5542_WriteA( float val);
void AD5542_WriteB( float val);

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


