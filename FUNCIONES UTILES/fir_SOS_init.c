#include <stdio.h>
#include <conio.h>


#define NUM_SECTIONS 8

float b[NUM_SECTIONS][3] = { 
{6.47970511E-04, 1.29594102E-03, 6.47970511E-04},
{2.30585582E-03, 4.61171164E-03, 2.30585582E-03},
{3.62055554E-03, 7.24111107E-03, 3.62055554E-03},
{4.67416881E-03, 9.34833761E-03, 4.67416881E-03},
{5.43447959E-03, 1.08689592E-02, 5.43447959E-03},
{5.87559241E-03, 1.17511848E-02, 5.87559241E-03},
{5.98376718E-03, 1.19675344E-02, 5.98376718E-03},
{5.76196835E-03, 1.15239367E-02, 5.76196835E-03} };

float a[NUM_SECTIONS][3] = { 
{1.00000000E+00, -1.95784152E+00, 9.74735618E-01},
{1.00000000E+00, -1.91050124E+00, 9.26986933E-01},
{1.00000000E+00, -1.86795521E+00, 8.84073675E-01},
{1.00000000E+00, -1.83125293E+00, 8.47054720E-01},
{1.00000000E+00, -1.80115640E+00, 8.16698551E-01},
{1.00000000E+00, -1.77819490E+00, 7.93538868E-01},
{1.00000000E+00, -1.76271629E+00, 7.77926683E-01},
{1.00000000E+00, -1.75492859E+00, 7.70071805E-01} };

void fir_coeff_reorder(float b[][3],float a[][3], float h[], int numStage);

int main(void){
	float h[NUM_SECTIONS*5];
	fir_coeff_reorder(b,a,h,NUM_SECTIONS);
	printf("resultado\n");
	int i;
	for(i = 0;i<NUM_SECTIONS*5;i++){
		printf("i %d: %f\n",i,h[i]);
	}
	
	getch();
	return 0;
}

void fir_coeff_reorder(float b[][3],float a[][3], float h[], int numStage){
	int i, j;
	int n = 0;
	for( i = 0; i<numStage; i++){
		for(j = 0; j<3;j++){
			h[n] = b[i][j];
			n++;
		}
		for(j = 1; j<3;j++){
			h[n] = -1 * a[i][j];  //se niega los coeficientes
			n++;
		}
	}
}
