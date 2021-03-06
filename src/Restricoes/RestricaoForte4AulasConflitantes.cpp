#include "RestricaoForte4AulasConflitantes.h"
#include <stdlib.h>

#include "../Model/Problema.h"
#include "../Model/Aula.h"

double RestricaoForte4AulasConflitantes::contaViolacaoRestricao(Individuo* ind, Problema* p){
	int count = 0;
	list<Curriculo*>::iterator it;

	for(it = p->curriculos.begin(); it != p->curriculos.end(); it++){
		count += contaViolacaoRestricaoCurriculo(ind, (*it), p);
	}
	count += contaViolacaoRestricaoProfessor(ind, p);

	return peso * count;
}


double RestricaoForte4AulasConflitantes::contaViolacaoRestricaoCurriculo(Individuo* ind, Curriculo* c, Problema* p){
	int contaViolacao = 0;
	list<Alocacao*>::iterator it;
	int i;

	for( i=0; i<p->nHorarios; i++ ) {
		if( ind->Alocacao_horarios_utilizados_por_curriculo[c->numeroSequencial][i] > 1 ){
			contaViolacao += ind->Alocacao_horarios_utilizados_por_curriculo[c->numeroSequencial][i]-1;
		}
	}
	return contaViolacao;
}

double RestricaoForte4AulasConflitantes::contaViolacaoRestricaoProfessor(Individuo* ind, Problema* p){
	int contaViolacao = 0;
	unsigned int j;
	int i;


	for( j=0; j < p->professores.size(); j++ ) {
		for( i=0; i<p->nHorarios; i++ ){
			if( ind->matrizProfessorHorarioQntd[j][i] > 1 ) {
				contaViolacao += ind->matrizProfessorHorarioQntd[j][i]-1;
			}
		}
	}
	return contaViolacao;
}



double RestricaoForte4AulasConflitantes::contaViolacaoRestricaoAlocacao(Individuo* ind, Problema* p, Alocacao* a, Movimento* m){
	int count = 0;
	Disciplina* disc = a->aula->disciplina;
	list<Curriculo*>::iterator it;

	list<Alocacao*>::iterator itAloc;
	int i;

	for(it = disc->curriculos.begin(); it != disc->curriculos.end(); it++){
		for( i=0; i<p->nHorarios; i++ ) {
			if( ind->Alocacao_horarios_utilizados_por_curriculo[(*it)->numeroSequencial][i] > 1 ){
				count += ind->Alocacao_horarios_utilizados_por_curriculo[(*it)->numeroSequencial][i]-1;
			}
		}
	}
	if( ind->matrizProfessorHorario[disc->professor->numeroSequencial][a->horario->horario] != NULL ) count++;

	if( m != NULL) m->deltaHard+=peso*count;
	return peso * count;
}

double RestricaoForte4AulasConflitantes::restricaoViolada(Individuo* ind, Problema* p, Movimento* m){
	list<Curriculo*>::iterator it;
	Disciplina* disc;
	Aula *aula1, *aula2;
	int horario1, horario2;

	aula1 = m->a1->aula;
	aula2 = m->a2->aula;
	horario1 = m->a1->horario->horario;
	horario2 = m->a2->horario->horario;

	if( (aula1 != NULL) &&
		(ind->matrizProfessorHorario[aula1->disciplina->professor->numeroSequencial][horario1] != NULL &&
		 ind->matrizProfessorHorario[aula1->disciplina->professor->numeroSequencial][horario1] != m->a1		)){
		return 1;
	}
	if( (aula2 != NULL) &&
		(ind->matrizProfessorHorario[aula2->disciplina->professor->numeroSequencial][horario2] != NULL &&
		 ind->matrizProfessorHorario[aula2->disciplina->professor->numeroSequencial][horario2] != m->a2) ){
		return 1;
	}
	if( (aula1 != NULL) && (ind->matrizProfessorHorarioQntd[aula1->disciplina->professor->numeroSequencial][horario1] > 1) )
		return 1;
	if( (aula2 != NULL) && (ind->matrizProfessorHorarioQntd[aula2->disciplina->professor->numeroSequencial][horario2] > 1) )
		return 1;


	if( aula1 != NULL ){
		disc = aula1->disciplina;
		for(it = disc->curriculos.begin(); it != disc->curriculos.end(); it++){
			if( ind->Alocacao_horarios_utilizados_por_curriculo[(*it)->numeroSequencial][horario1] > 1 ) {
				return 1;
			}
		}
	}
	if( aula2 != NULL ){
		disc = aula2->disciplina;
		for(it = disc->curriculos.begin(); it != disc->curriculos.end(); it++){
			if( ind->Alocacao_horarios_utilizados_por_curriculo[(*it)->numeroSequencial][horario2] > 1 ) {
				return 1;
			}
		}
	}

	return 0;
}

int RestricaoForte4AulasConflitantes::horarioEhDisponivel(Individuo* ind, Disciplina* d, int iHorarios){
	list<Curriculo*>::iterator it;

	for(it = d->curriculos.begin(); it != d->curriculos.end(); it++){
		if( ind->Alocacao_horarios_utilizados_por_curriculo[(*it)->numeroSequencial][iHorarios] > 1 ) {
			return 1;
		}
	}

	return 0;
}
