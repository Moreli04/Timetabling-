#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//------------------------------------------------------------------------------
int main(int argc, char *argv[]){
  int fo;
  float somaFo;
  float tempo;
  float somaTempo;

  somaTempo = 0.0;
  somaFo = 0.0;

  FILE *f;
  // Abre Arquivo
  f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Erro de abertura do arquivo %s\n", argv[1]);
    exit(1);
  }

  while(fscanf(f,"%d %f\n",&fo,&tempo) != EOF){
    somaTempo+= tempo;
    somaFo += fo;
  }

  printf("%f;%f\n", ((float)somaFo)*0.1, somaTempo*0.1);

  fclose(f);
  return 0;
}
