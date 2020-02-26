#include "RestricaoFraca3CurriculumCompactness.h"
#include "../Model/Problema.h"

double RestricaoFraca3CurriculumCompactness::contaViolacaoRestricao(Individuo* ind, Problema* p){
	int count = 0;
	list<Curriculo*>::iterator itCurr;

	for(itCurr = p->curriculos.begin(); itCurr != p->curriculos.end(); itCurr++){
		count += contaViolacaoRestricao(ind, (*itCurr), p, NULL);
	}

	ind->soft3 = peso * count;
	return peso * count;
}


double RestricaoFraca3CurriculumCompactness::contaViolacaoRestricao(Individuo* ind, Curriculo* c, Problema* p, Alocacao* piA){
	int contaViolacao = 0;

    for (int d=0;d<p->nDias;d++) {
        for (int s=0;s<p->nPerDias;s++) {
            Alocacao* a = ind->matrizAlocacaoCurriculoDiasPeriodos[c->numeroSequencial][d][s];
			if (a==NULL) continue;
				Alocacao* prev = (s==0?NULL:ind->matrizAlocacaoCurriculoDiasPeriodos[c->numeroSequencial][d][s-1]);
				Alocacao* next = (s+1==p->nPerDias?NULL:ind->matrizAlocacaoCurriculoDiasPeriodos[c->numeroSequencial][d][s+1]);
				if (next==NULL && prev==NULL) {
					contaViolacao++;
				}
        }
    }
	return contaViolacao;
}

double RestricaoFraca3CurriculumCompactness::contaViolacaoRestricaoAlocacao(Individuo* ind, Problema* p, Alocacao* a, Movimento* m){
	int count = 0;
	list<Curriculo*>::iterator itCurr;
	Disciplina* d = a->aula->disciplina;

	for(itCurr = d->curriculos.begin(); itCurr != d->curriculos.end(); itCurr++){
		count += contaViolacaoRestricao(ind, (*itCurr), p, a);
	}

	if( m != NULL) {
		m->deltaSoft3+=peso*count;
	}

	return peso*count;
}

double RestricaoFraca3CurriculumCompactness::contaViolacaoRestricaoListaAlocacao(Individuo* ind, Problema* p, list<Alocacao*> listaAloc, Movimento* m){
	list<Alocacao*>::iterator itAloc;
	int count = 0;

	list<Curriculo*>::iterator itCurr;
	Disciplina* d;

	for( itAloc=listaAloc.begin(); itAloc!=listaAloc.end(); itAloc++ ){
		if( (*itAloc)->aula != NULL ){
			d = (*itAloc)->aula->disciplina;
			for(itCurr = d->curriculos.begin(); itCurr != d->curriculos.end(); itCurr++){
				count += contaViolacaoRestricao(ind, (*itCurr), p, NULL);
			}
		}
	}

	if( m != NULL) m->deltaSoft3+=peso*count;
	return peso*count;
}
