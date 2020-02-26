#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define LIN 21
#define COL 20

int preencherArq1(float matriz[LIN][COL]){
	char dir1[] = "../tabelas/tabela2/_BLCI_/info.dat";
	int i = 0; 
	int cont = 0;
	FILE *f;
    f = fopen(dir1, "r");

    if (f == NULL) {
        printf("Erro de abertura do arquivo %s\n",dir1);
        exit(1);
    }
    while(fscanf(f,"%f;%f;%f;%f;%f\n",&matriz[i][0],&matriz[i][1],&matriz[i][2],&matriz[i][3],&matriz[i][4]) != EOF){
		//printf("lendo %f e %f\n",matriz[i][0],matriz[i][1] );
		i++;
		cont++;
	}
	fclose(f);
	return cont;
}

void preencherArq2(float matriz[LIN][COL]){
	char dir2[] = "../tabelas/tabela2/_BLSI_/info.dat";
	int i = 0; 
	FILE *f;
    f = fopen(dir2, "r");

    if (f == NULL) {
        printf("Erro de abertura do arquivo %s\n",dir2);
        exit(1);
    }
    while(fscanf(f,"%f;%f;%f;%f;%f\n",&matriz[i][5],&matriz[i][6],&matriz[i][7],&matriz[i][8],&matriz[i][9]) != EOF){
		//printf("lendo %f e %f\n",matriz[i][0],matriz[i][1] );
		i++;
	}
	fclose(f);
}

void preencherArq3(float matriz[LIN][COL]){
	char dir3[] = "../tabelas/tabela2/_BPCI_/info.dat";
	int i = 0; 
	FILE *f;
    f = fopen(dir3, "r");

    if (f == NULL) {
        printf("Erro de abertura do arquivo %s\n",dir3);
        exit(1);
    }
    while(fscanf(f,"%f;%f;%f;%f;%f\n",&matriz[i][10],&matriz[i][11],&matriz[i][12],&matriz[i][13],&matriz[i][14]) != EOF){
		//printf("lendo %f e %f\n",matriz[i][0],matriz[i][1] );
		i++;
	}
	fclose(f);
}

void preencherArq4(float matriz[LIN][COL]){
	char dir4[] = "../tabelas/tabela2/_BPSI_/info.dat";
	int i = 0; 
	FILE *f;
    f = fopen(dir4, "r");

    if (f == NULL) {
        printf("Erro de abertura do arquivo %s\n",dir4);
        exit(1);
    }
    while(fscanf(f,"%f;%f;%f;%f;%f\n",&matriz[i][15],&matriz[i][16],&matriz[i][17],&matriz[i][18],&matriz[i][19]) != EOF){
		//printf("lendo %f e %f\n",matriz[i][0],matriz[i][1] );
		i++;
	}
	fclose(f);
}

int main(int argc, char** argv) {
	float matriz[LIN][COL];
	int i, cont;
	cont = preencherArq1(matriz);
	preencherArq2(matriz);
	preencherArq3(matriz);
	preencherArq4(matriz);

	for(i = 0; i < cont; i++)
		printf("%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f;%f\n", matriz[i][0], matriz[i][1], matriz[i][2], matriz[i][3], matriz[i][4],matriz[i][5],matriz[i][6],matriz[i][7],matriz[i][8],matriz[i][9],matriz[i][10],matriz[i][11],matriz[i][12],matriz[i][13],matriz[i][14],matriz[i][15],matriz[i][16],matriz[i][17],matriz[i][18],matriz[i][19]);
	return 0;
}
