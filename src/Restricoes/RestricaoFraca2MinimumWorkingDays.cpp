#include "RestricaoFraca2MinimumWorkingDays.h"
#include "../Model/Problema.h"

double RestricaoFraca2MinimumWorkingDays::contaViolacaoRestricao(Individuo* ind, Problema* p){
	int count = 0;
	list<Disciplina*>::iterator it;

	for(it = p->disciplinas.begin(); it != p->disciplinas.end(); it++){
		count += contaViolacaoRestricao(ind, (*it), p->nDias);
	}
	ind->soft2 = peso * count;
	return peso * count;
}

double RestricaoFraca2MinimumWorkingDays::contaViolacaoRestricaoAlocacao(Individuo* ind, Problema* p, Alocacao* a, Movimento* m){
	int count = peso * contaViolacaoRestricao(ind, a->aula->disciplina, p->nDias);
	if( m != NULL) m->deltaSoft2+=count;
	return count;
}

double RestricaoFraca2MinimumWorkingDays::contaViolacaoRestricao(Individuo* ind, Disciplina* d, int nDiasSemana){
	int contaDiasSemana = 0;
	int i;

	for( i=0; i<nDiasSemana; i++ ) {
		if( ind->Alocacao_dias_utilizados[d->numeroSequencial][i] > 0 )
			contaDiasSemana++;
	}

	if( contaDiasSemana >= d->minDiasSemana ) return 0;
	return d->minDiasSemana - contaDiasSemana;
}

double RestricaoFraca2MinimumWorkingDays::contaViolacaoRestricaoListaAlocacao(Individuo* ind, Problema* p, list<Alocacao*> listaAloc, Movimento* m){
	list<Alocacao*>::iterator itAloc;
	int count = 0;

	for( itAloc=listaAloc.begin(); itAloc!=listaAloc.end(); itAloc++ ){
		if( (*itAloc)->aula != NULL ){
			count += peso * contaViolacaoRestricao(ind, (*itAloc)->aula->disciplina, p->nDias);
		}
	}

	if( m != NULL) m->deltaSoft2+=count;
	return count;
}
