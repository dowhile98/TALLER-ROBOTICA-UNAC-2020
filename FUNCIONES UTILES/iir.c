#include <stdio.h>
#include <conio.h>
#include <stdint.h>
#include "waveForms.c"
/*IMPLEMENTACION DEL FILTRO IRR -> FORMA DIRECTA II
-se requiere arrays para los coeficientes y las operaciones intermedias
-La longitud (n) del filtro especifica el número de secciones
-el tamaño de la matriz de historial es 2 * n
-el tamaño de la matriz de coeficientes es 4 * n +1 porque los 
  primeros coeficientes son el factor de escala general para el filtro.
- devuelve una muestra de salida para cada muestra de entrada
*/
float iir_filter(float input,float *coef, int n, float *history);


int main(int argc, char* argv[]){
    //implementar test
    return 0;
}

float iir_filter(float input,float *coef, int n, float *history){
    uint32_t i;
    float *hist1_ptr,*hist2_ptr, *coef_ptr;
    float output, new_hist, history1, history2;

    coef_ptr = coef;

    hist1_ptr = history;
    hist2_ptr = hist1_ptr + 1;

    output = input * (*coef_ptr++);

    for(i = 0; i< n; i++){
        history1 = *hist1_ptr;
        history2 = *hist2_ptr;

        output = output - history1 * (*coef_ptr++);
        new_hist = output - history2 * (*coef_ptr++);

        output = new_hist + history1 * (*coef_ptr++);
        output = output + history2 * (*coef_ptr++);

        *hist2_ptr++ = *hist1_ptr;
        *hist1_ptr++ = new_hist;

        hist1_ptr++;
        hist2_ptr++;
    }
    return output;
}