#include "Move.h"
#include "../Model/Alocacao.h"
#include "../Model/Aula.h"
#include "../Model/Disciplina.h"

Move::Move(Individuo* piInd) {
	ind = piInd;
	tipoMovimento = 1;
//	printf("Move: \n");
	a1 = piInd->aulasAlocadas[rand() % piInd->aulasAlocadas.size()];
	a2 = piInd->horariosVazios[rand() % piInd->horariosVazios.size()];

	deltaFit = calculaDeltaFitMove(piInd->p);
}

Move::Move(Individuo* piInd, int piPos1, int piPos2){
	ind = piInd;
	tipoMovimento = 1;
	a1 = piInd->aulasAlocadas[piPos1];
	a2 = piInd->horariosVazios[piPos2];
	deltaFit = calculaDeltaFitMove(piInd->p);
}

void Move::aplicaMovimento(){
	aplicaMoveSemRecalculoFuncaoObjetivo();

	ind->fitness += deltaFit;
	ind->hard  += deltaHard;
	ind->soft1 += deltaSoft1;
	ind->soft2 += deltaSoft2;
	ind->soft3 += deltaSoft3;
	ind->soft4 += deltaSoft4;
}

void Move::desfazMovimento(){
  aplicaMoveSemRecalculoFuncaoObjetivo();

  ind->fitness -= deltaFit;
  ind->hard  -= deltaHard;
  ind->soft1 -= deltaSoft1;
  ind->soft2 -= deltaSoft2;
  ind->soft3 -= deltaSoft3;
  ind->soft4 -= deltaSoft4;
}

int Move::calculaDeltaFitMove(Problema* p){
	list<Restricao*>::iterator it;
	int deltaFitness;
	int violaRestricaoHard;
	deltaFitness  = -p->CalculaCustoAulaAlocada(ind, a1, this);
	deltaHard  = 0;
	deltaSoft1 = -deltaSoft1;
	deltaSoft2 = -deltaSoft2;
	deltaSoft3 = -deltaSoft3;
	deltaSoft4 = -deltaSoft4;
	deltaFitness = deltaSoft1 + deltaSoft2 + deltaSoft3 + deltaSoft4;
	aplicaMoveSemRecalculoFuncaoObjetivo();
	violaRestricaoHard = p->violaRestricaoGrave(ind, this);
	if( ! violaRestricaoHard ){
		deltaFitness += p->CalculaCustoAulaAlocada(ind, a1, this);
	}
	else {deltaFitness = 99999; deltaHard  = 99999;}
	aplicaMoveSemRecalculoFuncaoObjetivo();

	return deltaFitness;
}

void Move::aplicaMoveSemRecalculoFuncaoObjetivo(){
  list<Curriculo*>::iterator itCurr;
	Timeslot* temp_hora;
	Sala* temp_sala;
	int aula1;
	aula1 = a1->aula->disciplina->numeroSequencial;
	ind->Alocacao_dias_utilizados[aula1][a1->horario->dia]--;
	ind->Alocacao_salas_utilizadas[aula1][a1->sala->numeroSequencial]--;
	for( itCurr = a1->aula->disciplina->curriculos.begin(); itCurr!=a1->aula->disciplina->curriculos.end(); itCurr++){
		ind->Alocacao_horarios_utilizados_por_curriculo[(*itCurr)->numeroSequencial][a1->horario->horario]--;
		if( ind->Alocacao_horarios_utilizados_por_curriculo[(*itCurr)->numeroSequencial][a1->horario->horario] == 0)
			ind->matrizAlocacaoCurriculoDiasPeriodos[(*itCurr)->numeroSequencial][a1->horario->dia][a1->horario->periodo] = NULL;
	}
	ind->matrizProfessorHorarioQntd[a1->aula->disciplina->professor->numeroSequencial][a1->horario->horario]--;
	if( ind->matrizProfessorHorario[a1->aula->disciplina->professor->numeroSequencial][a1->horario->horario] == a1)
		ind->matrizProfessorHorario[a1->aula->disciplina->professor->numeroSequencial][a1->horario->horario] = NULL;
//		a1->aula->disciplina->professor->restricaoHorario[a1->horario->horario] = NULL;

	temp_hora = a1->horario;
	a1->horario = a2->horario;
	a2->horario= temp_hora;
	temp_sala = a1->sala;
	a1->sala = a2->sala;
	a2->sala = temp_sala;

	ind->matrizProfessorHorarioQntd[a1->aula->disciplina->professor->numeroSequencial][a1->horario->horario]++;
	if( ind->matrizProfessorHorario[a1->aula->disciplina->professor->numeroSequencial][a1->horario->horario] == NULL)
		ind->matrizProfessorHorario[a1->aula->disciplina->professor->numeroSequencial][a1->horario->horario] = a1;
//		a1->aula->disciplina->professor->restricaoHorario[a1->horario->horario] = a1;

	ind->Alocacao_dias_utilizados[aula1][a1->horario->dia]++;
	ind->Alocacao_salas_utilizadas[aula1][a1->sala->numeroSequencial]++;
	for( itCurr = a1->aula->disciplina->curriculos.begin(); itCurr!=a1->aula->disciplina->curriculos.end(); itCurr++){
		ind->Alocacao_horarios_utilizados_por_curriculo[(*itCurr)->numeroSequencial][a1->horario->horario]++;
		if( ind->matrizAlocacaoCurriculoDiasPeriodos[(*itCurr)->numeroSequencial][a1->horario->dia][a1->horario->periodo] == NULL )
			ind->matrizAlocacaoCurriculoDiasPeriodos[(*itCurr)->numeroSequencial][a1->horario->dia][a1->horario->periodo] = a1;
	}

}
