#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

//------------------------------------------------------------------------------
int main(int argc, char *argv[]){

  int p1,p3,p4,p6;
  float p5,p7;
  char p2;
  float somaTs = 0.0;
  float somaFs = 0.0;
  int contS = 0;
  float somaTn = 0.0;
  float somaFn = 0.0;
  int contN = 0;
  float porcentagemSucesso = 0.0;

  FILE *f;
  // Abre Arquivo
  f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Erro de abertura do arquivo %s\n", argv[1]);
    exit(1);
  }

  while(fscanf(f,"%d;%c;%d;%d;%f;%d;%f\n",&p1,&p2,&p3,&p4,&p5,&p6,&p7) != EOF){
    if (p2 == 'S'){
      contS++;
      somaTs += p5;
      somaFs += p4;
    }else{
      contN++;
      somaTn += p5;
      somaFn += p4;
    }
  }

  porcentagemSucesso = (((float)contS)/(contS+contN))*100.0;
  //printf("printando para %s contS = %d e contN = %d e porcentagemSucesso = %f\n ", argv[1],contS,contN,porcentagemSucesso);
  if((contS > 0) && (contN > 0))
    printf("%f;%f;%f;%f;%f\n",(float)somaFs/contS, (float)somaTs/contS, (float)somaFn/contN, (float)somaTn/contN, porcentagemSucesso);  
  else if((contS > 0) && (contN == 0))
    printf("%f;%f;%f;%f;%f\n",(float)somaFs/contS, (float)somaTs/contS, 0.0, 0.0, porcentagemSucesso);  
  else if((contS == 0) && (contN > 0))
    printf("%f;%f;%f;%f;%f\n",0.0, 0.0, (float)somaFn/contN, (float)somaTn/contN, (float)porcentagemSucesso);  
  fclose(f);
  return 0;
}
