#include "arm_math.h"
#include "main.h"
#include "signal.h"
#include "IIR_lowPassD2T.h"
#include "time.h"

#define GAIN		5
#define SYS_FREQ 168000000UL


uint32_t freq;


float32_t inputSample;
float32_t outputSample;
uint32_t freq;
float32_t time;
uint32_t cycle;

void iir_coeff_reorder(float b[][3],float a[][3], float h[], int numStage);
void plot_signal(void);


/*VARIABLES Y INSTANCIAS PARA REALIZAR EL FILTRADO*/
arm_biquad_cascade_df2T_instance_f32 S;
float32_t iirDF1F32[numStages*4];			//para los operaciones intermedias
float32_t h[5*numStages];							//bueffer para almacenar los coefficientes
float32_t y[SIGNAL_LENGTH];						//Salida del filtro


int main(void){
	/*configuracion de perifericos*/
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	/*configuracion del filtro*/
	iir_coeff_reorder(b,a,h,numStages); //se reordena los coeficientes del filtro iir

	arm_biquad_cascade_df2T_init_f32(&S,numStages,h,iirDF1F32);
	
	startTiming();
	
	arm_biquad_cascade_df2T_f32(&S,singal_1K_5k_10k_15kHz,y,SIGNAL_LENGTH);

	cycle = StopTiming();
	time = 1000 * calculateTime(cycle,SYS_FREQ);		//TIEMPO EN MILISEGUNDOS
	arm_scale_f32(y, GAIN, y, SIGNAL_LENGTH);
	//se muestra el resulado
	plot_signal();
	while(1){
		
	}
}


/*funcion que reordena los coeficientes del filtro IIR*/
void iir_coeff_reorder(float32_t b[][3],float32_t a[][3], float32_t h[], int numStage){
	uint32_t i, j;
	uint32_t n = 0;
	//reordena los coeficientes bn0, bn1,b2
	for( i = 0; i<numStage; i++){
		for(j = 0; j<3;j++){
			h[n] = b[i][j];
			n++;
		}
		//reordena los coeficientes an1,an2   -> se obvia an0
		for(j = 1; j<3;j++){
			h[n] = -1 * a[i][j];  //se niega los coeficientes
			n++;
		}
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