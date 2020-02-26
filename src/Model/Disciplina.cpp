#include "Disciplina.h"
#include "Professor.h"
#include "Curriculo.h"
#include "Aula.h"
#include <string.h>
#include <stdio.h>


Disciplina::Disciplina(char* piNome, Professor* p, int n, int piNAulas, int piMinDias, int piNAlunos, int piNCurriculos, int piNumAulaSequencial) {
	int i;
	strcpy(nome, piNome);
	strcpy(nomeProfessor, p->nome);
	professor = p;
	nAulas		  = piNAulas;
	nAulasNaoAloc = nAulas;
	nAlunos 	  = piNAlunos;
	minDiasSemana = piMinDias;
	numeroSequencial = n;
	nCurriculos   = piNCurriculos;
	nDisciplinasComMesmoCurriculoOuProfessor = 0;

	for( i=0; i<piNAulas; i++ ) aulas.push_back(new Aula(piNumAulaSequencial+i+1, this));
}

void Disciplina::imprime(){
	list<Curriculo*>::iterator it;
	printf("Disciplina %s:\t", nome);
	printf("Professor: %s \t", nomeProfessor);
	printf("nAulas: %d\tnAlunos: %d\tminDiasSemana: %d\tnumero: %d \t", nAulas, nAlunos, minDiasSemana, numeroSequencial);

	printf("Curriculos: ");
	for( it=curriculos.begin(); it!=curriculos.end(); it++ )
		printf("%s ", (*it)->nome);
	printf("\n");
}

void Disciplina::decremento(){
	nAulasNaoAloc--;	
	//if(nAulasNaoAloc < 0)
	//	printf("ERRO DENTRO DO DECREMENTO:%s\n",nome);	
}	

Disciplina::~Disciplina() {
	Aula* a;
	while( aulas.size() > 0 ) {
		a = aulas.back();
		aulas.pop_back();
		delete(a);
	}
}


