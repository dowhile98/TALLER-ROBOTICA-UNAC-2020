#include <conio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#define N 200
/*
    	r = v1*v1 + v2*v2;
        fac = sqrt(-2*log(r)/r);
        gstore = v1*fac;
        gaus = v2*fac;
*/
/* prototipo de funciones*/
float gaussian(void);

int main(int argc, char *argv[]){
    float g[N];
    uint8_t i;
    //*se crea un archivo
    FILE *fp = fopen("g.dat","w");
    if(fp == NULL)
    	return 0;
    //se genera y se almacena el ruido obtenido en el archivo g.dat
    for(i = 0;i <N; i++){
        g[i] = gaussian();
        fprintf(fp,"%.4f\n",g[i]);
    }
    // se muestra el resultado
    printf("ruido generado\n");
    for (i = 0;i<N ; i++){
        printf("%.4f\n",g[i]);
    }
    fclose(fp); //se cierra el archivo
    getch();
    return 0;
}

/* defincion de funciones*/
float gaussian(void){
    static int ready = 0;
    static float gstore;
    static float rconst1 = (float)(2.0/RAND_MAX);
    static float rconst2 = (float)(RAND_MAX/2.0);

    float v1, v2, r, fac, gaus;
    /* se genera dos numeros si no se tiene nada almacenado*/
    if(ready == 0){
        do{
            v1 = (float)rand() - rconst2;
            v2 = (float)rand() - rconst2;
            v1 *= rconst1;
            v2 *= rconst1;
            r = v1 * v1 + v2 * v2;
        }while(r>1.0f);/*hacer que r>1*/

        fac = sqrt(-2.0f*log(r)/r);
        gstore = v1*fac;
        gaus = v2 * fac;
        ready = 1;
    }
    else{
        ready = 0;
        gaus = gstore;
    }
    return gaus;
}
