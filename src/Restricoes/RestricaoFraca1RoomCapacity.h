#ifndef RESTRICAOFRACA1ROOMCAPACITY_H_
#define RESTRICAOFRACA1ROOMCAPACITY_H_

#include <list>
#include <vector>
using namespace std;

#include "Restricao.h"
#include "../Model/Disciplina.h"

class RestricaoFraca1RoomCapacity: public Restricao{
public:
	RestricaoFraca1RoomCapacity(){};
	~RestricaoFraca1RoomCapacity(){};
	double contaViolacaoRestricao(Individuo* ind, Problema* p){
		int count = 0;
		vector<Alocacao*>::iterator it;

		for(it = ind->aulasAlocadas.begin(); it != ind->aulasAlocadas.end(); it++){
			if( (*it)->aula->disciplina->nAlunos > (*it)->sala->capacidade )
				count += (*it)->aula->disciplina->nAlunos - (*it)->sala->capacidade;
		}
		ind->soft1 = count;
		return count;
	}
	double contaViolacaoRestricaoAlocacao(Individuo* ind, Problema* p, Alocacao* a, Movimento* m){
		int count = 0;

		if( a->aula->disciplina->nAlunos > a->sala->capacidade )
			count = a->aula->disciplina->nAlunos - a->sala->capacidade;

		if( m != NULL) m->deltaSoft1+=count;
		return count;
	}
	double contaViolacaoRestricaoListaAlocacao(Individuo* ind, Problema* p, list<Alocacao*> listaAloc, Movimento* m){
		int count = 0;
		list<Alocacao*>::iterator it;
		Alocacao* a;

		for(it = listaAloc.begin(); it != listaAloc.end(); it++){
			a = (*it);
			if( a->aula->disciplina->nAlunos > a->sala->capacidade )
				count += a->aula->disciplina->nAlunos - a->sala->capacidade;
		}

		if( m != NULL) m->deltaSoft1+=count;
		return count;
	};
};

#endif /* RESTRICAOFRACA1ROOMCAPACITY_H_ */
