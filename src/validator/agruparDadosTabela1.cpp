#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv) {
	float matriz[21][4];
	char dir1[] = "../tabelas/tabela1/_BLCI_/media.dat";
	char dir2[] = "../tabelas/tabela1/_BPCI_/media.dat";
	int i;
	FILE *f;
	i = 0;
	int cont = 0;
    f = fopen(dir1, "r");

    if (f == NULL) {
        printf("Erro de abertura do arquivo %s\n",dir1);
        exit(1);
    }
    while(fscanf(f,"%f;%f\n",&matriz[i][0],&matriz[i][1]) != EOF){
		//printf("lendo %f e %f\n",matriz[i][0],matriz[i][1] );
		i++;
		cont++;
	}
	fclose(f);

	i = 0;
	f = fopen(dir2, "r");
	if (f == NULL) {
        printf("Erro de abertura do arquivo %s\n",dir2);
        exit(1);
    }

	while(fscanf(f,"%f;%f\n",&matriz[i][2],&matriz[i][3]) != EOF){
		i++;
	}
	
	fclose(f);

	for(i = 0; i < cont; i++)
		printf("%f;%f;%f;%f;\n", matriz[i][0], matriz[i][1], matriz[i][2], matriz[i][3]);
		
	return 0;
}
