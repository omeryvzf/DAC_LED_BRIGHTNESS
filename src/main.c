#include "stm32f4xx.h"
#include "stm32f4xx_dac.h"
void gpioConfig(){
	GPIO_InitTypeDef	GPIOInitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIOInitStructure.GPIO_Mode=GPIO_Mode_AN;
	GPIOInitStructure.GPIO_OType=GPIO_OType_PP;
	GPIOInitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIOInitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIOInitStructure.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIOInitStructure);
}
void dac2Config(){
	DAC_InitTypeDef	DACInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC,ENABLE);
	DACInitStructure.DAC_LFSRUnmask_TriangleAmplitude=DISABLE;
	DACInitStructure.DAC_OutputBuffer=ENABLE;
	DACInitStructure.DAC_Trigger=DAC_Trigger_None;
	DACInitStructure.DAC_WaveGeneration=DAC_WaveGeneration_None;

	DAC_Init(DAC_Channel_2,&DACInitStructure);
	DAC_Cmd(DAC_Channel_2,ENABLE);
}
void delay(uint32_t time){
	while(time--);
}

int main(void){
  gpioConfig();
  dac2Config();

  while (1){
	  for(int i=0;i<=255;i++){
		  DAC_SetChannel2Data(DAC_Align_8b_R,i);
		  //DAC_SetDualChannelData(DAC_Align_12b_R,i,i); çift dac için
		  delay(36000);

	  }
	  for(int i=254;i<0;i--){
		  DAC_SetChannel2Data(DAC_Align_8b_R,i);
		  delay(36000);
	  }

  }
}
