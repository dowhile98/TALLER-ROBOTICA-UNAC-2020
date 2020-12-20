#include <stdio.h>
#include <conio.h>
#include <stdint.h>
#include <math.h>
#include "FIR_lpf_coefficients.h"
#include "waveForms.c"
#include "ruido.c"
#define SIGNAL_LENGTH	320
#define W               0.05    //freq señal
float his[K];
/*funcion filtro fir
float input     : nueva entrada de muestreo
float *h        : puntero a los coeficientes del filtro
int n           : numero de coeficientes del filtro
float *history  : para las operaciones intermedias
*/
float fir_filter(float input,float *h, int k, float *history);


int main(int argc,char *argv[]){

    float disturbed, filtered;
    uint32_t i;
    
    //se crean dos archivos
    FILE *s  = fopen("s.dat","w");
    if(s == NULL)
        return -1;

    FILE *y = fopen("y.dat","w");
    if(y == NULL)
        return -1;
    //se genera una señal y se filtra
    for(i = 0; i<SIGNAL_LENGTH ; i++){;
        disturbed = inputSignal_f32_1kHz_15kHz[i];
        filtered = fir_filter(disturbed,h,K,his);
        /*disturbed = sin(2*M_PI*W*(float)i) + 0.2*gaussian();
        filtered = fir_filter(disturbed,h,K,his);*/
        fprintf(s,"%.4f\n",disturbed);
        fprintf(y,"%.4f\n",filtered);
        printf( "singal: %.4f filtered: %.4f\n",disturbed,filtered);
    }
    fclose(s);
    fclose(y);
    return 0;
}

//definicion de la funcion
float fir_filter(float input,float *h, int k, float *history){
   uint32_t i;
   float *hist_ptr, *hist1_ptr, *coef_ptr;
   float output;

   hist_ptr = history;
   hist1_ptr = hist_ptr;    //puntero actualizado
   coef_ptr = h + k - 1;    //puntero a los coeficientes
   /*inicio del algoritmo recursivo*/
   output = *hist_ptr++*(*coef_ptr--);
   for(i = 2; i<k; i++){
       *hist1_ptr++ = *hist_ptr;
       output += (*hist_ptr++)*(*coef_ptr--);
   }
    output += input * (*coef_ptr--);
    *hist1_ptr = input;     //se actualiza el history
    return (output);        //se devuelve la salida
}