#include "LectureMove3.h"
#include "../Model/Alocacao.h"

LectureMove3::LectureMove3(Individuo* piInd){
	int i;
	tipoMovimento = 10;
 	ind = piInd;
	/* Escolhe randomicamente uma aula alocada */
	pos1 = rand() % ind->aulasAlocadas.size();
	a1 = ind->aulasAlocadas[pos1];

	/* Escolhe um horário aleatório dentre os disponíveis */
	a2 = ind->TodosHorarios[ rand() % ind->TodosHorarios.size() ];

	pos2 = -1;
	if (a2->aula == NULL){
		for(i=0; i<(int)ind->horariosVazios.size(); i++){
			if( ind->horariosVazios[i]->id == a2->id ){
				pos2 = i;
				break;
			}
		}
		m = new Move(ind, pos1, pos2);
	}
	else {
		for(i=0; i<(int)ind->aulasAlocadas.size(); i++){
			if( ind->aulasAlocadas[i]->id == a2->id ){
				pos2 = i;
				break;
			}
		}
		m = new Swap(ind, pos1, pos2);
	}
	deltaFit = m->deltaFit;
 }
 


 void LectureMove3::aplicaMovimento(){
		if (m->tipoMovimento == 1) {
			/* Remove A1 da lista de aulas alocadas */
			ind->aulasAlocadas.erase(ind->aulasAlocadas.begin()+pos1);

			/* Remove a2 da lista de alocações vazias */
			ind->horariosVazios.erase(ind->horariosVazios.begin()+pos2);

			/* Aplica o Movimento */
			m->aplicaMovimento();

			/* Insere A1 na lista de aulas alocadas */
			ind->aulasAlocadas.push_back(a1);

			/* Insere A2 na lista de alocações vazias, de modo ordenado */
			vector<Alocacao*>::iterator it;
			for(it = ind->horariosVazios.begin(); it != ind->horariosVazios.end() && (*it)->sala->numeroSequencial <= a2->sala->numeroSequencial; it++) {
				if ( (*it)->sala->numeroSequencial == a2->sala->numeroSequencial && (*it)->horario->horario > a2->horario->horario ) {
				 break;
				}
			}
			ind->horariosVazios.insert (it, a2);
		} else {
			m->aplicaMovimento();
		}
 }

LectureMove3::~LectureMove3(){
    delete(m);
  }
