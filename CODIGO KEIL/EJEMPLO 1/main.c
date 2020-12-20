#include "arm_math.h"
#include "stm32f4xx_hal.h"
#include "signal.h"
#include "main.h"
#include "fir_lowP.h"

#define LOW_PASS

/*VARIABLES GLOBALES*/
float32_t inputSample;
float32_t outputSample;
uint32_t freq;
uint32_t k;


float32_t y[SIGNAL_LENGTH];

#ifdef LOW_PASS

#define BLOCKSIZE		32
uint32_t numBlocks 	= SIGNAL_LENGTH / BLOCKSIZE;
//variables para realizar el filtrado

float32_t firStateF32[BLOCKSIZE + N -1];
arm_fir_instance_f32	S;

#endif /*LOW_PASS*/
/*POTOTIPO DE FUNCIONES*/

void plot_signal(void);

int main(void){
	
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	/*inicializacion del filtro
	* S: instancia que contiene los coeff, dimension, cantidad de datos de muestra
	* firStateF32: para las operaciones intermedias
	*/
	arm_fir_init_f32(&S, N, (float32_t*)fir_lowP, firStateF32, BLOCKSIZE);
	/* realizacion del filtro por bloques*/
	int i;
	for ( i= 0;i<numBlocks ;i++){
	  arm_fir_f32(&S, &singal_1K_5k_10k_15kHz[0]+(i*BLOCKSIZE), &y[0]+ (i*BLOCKSIZE), BLOCKSIZE);
  }
	
	plot_signal();
	
	/*gpio*/
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER |= 1U<<2*12 | 1U<<2*13 | 1U<<2*14 | 1U<<2*15;
	while(1){
		GPIOD->ODR ^= 0xF<<12;
		HAL_Delay(100);
	}
}
/*definicion de funciones*/
void plot_signal(void){
	uint32_t i;
	for(i = 0;i<SIGNAL_LENGTH ;i++){
		inputSample = singal_1K_5k_10k_15kHz[i];
		outputSample = y[i];
		HAL_Delay(1);
	}
	
}



void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
