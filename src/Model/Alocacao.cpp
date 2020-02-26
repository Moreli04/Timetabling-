#include <stdlib.h>
#include <stdio.h>

#include "Alocacao.h"

#include "Disciplina.h"
#include "Curriculo.h"

Alocacao::Alocacao(int piId){
	id = piId;
	aula = NULL;
	sala = NULL;
	horario = NULL;
}

Alocacao::Alocacao(Alocacao* a){
	id = a->id;
	aula = a->aula;
	sala = a->sala;
	horario = a->horario;
}

void Alocacao::imprime(){
    list<Curriculo*>::iterator itCurr;

    if(aula != NULL){
			printf("Aula %d/%s ( ", aula->disciplina->numeroSequencial, aula->disciplina->nome);
			for( itCurr = aula->disciplina->curriculos.begin(); itCurr!=aula->disciplina->curriculos.end(); itCurr++){
				printf("%d ", (*itCurr)->numeroSequencial);
		}
		printf("): ");
    }
	printf("sala %d no horario %d/%d (%d)\n", sala->numeroSequencial, horario->dia, horario->periodo, horario->horario);
}

Alocacao::~Alocacao(){
}
