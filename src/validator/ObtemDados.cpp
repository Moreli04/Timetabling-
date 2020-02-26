#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//------------------------------------------------------------------------------
int main(int argc, char *argv[]){

  int menor = 9999999;
  int p1,p3,p4,p6;
  float p5,p7;
  char p2;
  float soma = 0.0;
  int cont = 0;

  FILE *f;
  // Abre Arquivo
  f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Erro de abertura do arquivo %s\n", argv[1]);
    exit(1);
  }

  while(fscanf(f,"%d;%c;%d;%d;%f;%d;%f\n",&p1,&p2,&p3,&p4,&p5,&p6,&p7) != EOF){
    if (p6 < menor){
      menor = p6;
    }
    soma =+ p5;
    cont++;
  }

  if(cont > 0){
     printf("%d %f\n",menor, soma/cont);
  }

  fclose(f);
  return 0;
}
