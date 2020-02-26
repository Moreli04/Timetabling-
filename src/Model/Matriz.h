#ifndef MATRIZ_H_
#define MATRIZ_H_

#include "MeuTimeslot.h"
#include "Disciplina.h"
#define TAM_MATRIZ 1000


typedef struct coluna{
	MeuTimeslot *timeslot;
	int capacidade;
}Coluna;

typedef struct linha{
	Coluna *coluna;
	Disciplina *disc;
}Linha;

#endif 
