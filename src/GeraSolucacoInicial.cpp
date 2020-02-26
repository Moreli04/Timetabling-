#include "GeraSolucacoInicial.h"

#include <vector>
#include <stdlib.h>
#include <string.h>

typedef pair<int,int> comparacaoPar;

static bool AulasSaoConflitantes(Problema* p, Aula* a1, Aula* a2){
	return p->SaoDoMesmoCurriculo(a1->disciplina, a2->disciplina) || p->SaoDoMesmoProfessor(a1->disciplina, a2->disciplina);
}

GeraSolucacoInicial::~GeraSolucacoInicial(){
	register int i;
	for (i = 0; i <nCandidatos; i++) delete(candidatos[i]);
	free(candidatos);
}

GeraSolucacoInicial::GeraSolucacoInicial(Problema* p, int qtdAulasNaoAloc) {
    list<Disciplina*>::iterator it;
    list<Aula*>::iterator itAulas;
    register int i;
    threshold = 0.10;
    nCandidatos = qtdAulasNaoAloc;
    candidatos = (Candidato**) malloc ( p->nAulasTotal * sizeof(Candidato*) );
    i = 0;
	for (it = p->disciplinas.begin(); it != p->disciplinas.end(); it++) {
		if(((*it)->nAulasNaoAloc > 0)){
			itAulas = (*it)->aulas.begin();
			while((*it)->nAulasNaoAloc > 0){
				candidatos[i] = new Candidato(*itAulas, p);
				(*it)->nAulasNaoAloc--;
				itAulas++;
				i++;
			}			
		}
	}
}

int GeraSolucacoInicial::possuiAulaNoDia(Disciplina *d, int dia, Individuo *ind){
	for(vector<Alocacao*>::iterator it = ind->aulasAlocadas.begin(); it != ind->aulasAlocadas.end(); it++)
	{
		if((*(it))->aula->disciplina->numeroSequencial == d->numeroSequencial && (*(it))->horario->dia == dia)
		{
			return 2;
		}
	}
	return 0;
}

int GeraSolucacoInicial::CriaIndividuoInicial(Problema* p, Individuo* ind){
	Candidato* c;
	Candidato* aux;
	int n1, n2, step;
	vector<Alocacao*>::iterator it;
	register int i;
	int nExplode = 0;
	int max = 100;

	while ((nCandidatos > 0) && (nExplode <= max)){       // enquanto ha candidatos a alocar
		for( i=0; i<nCandidatos; i++) {
			contaTotalHorariosViaveis(p, candidatos[i], ind);
		}
		ordenaAulasPorDificuldade(p, ind);
		// aula "mais dificil"
		c = candidatos[nCandidatos-1];
        
		if ( c->nHorariosViaveis == 0) {
			nExplode++;
			//Explode individuo
			n1 = nCandidatos;
			explodeTimetable2(p, ind, c);
			n2 = nCandidatos;
			step = n2-n1-1;

			aux = candidatos[nCandidatos - 1];
			candidatos[nCandidatos-1] = candidatos[nCandidatos-2-step];
			candidatos[nCandidatos-2-step] = aux;
		}
		else{
			alocaAula(p, ind, c);
			delete(c);
			nCandidatos--;
		}
	}
    if (nExplode > max)
       return 1;
    return 0;
}

void GeraSolucacoInicial::alocaAula(Problema* p, Individuo* ind, Candidato* cand){
	register int i;
	Aula* aula = cand->aula;
	list<Possibilidade*> possibilidades;
    list<Possibilidade*>::iterator itPos;
    list<Possibilidade*>::iterator itPos2;
    list<Possibilidade*>::iterator itPosProximo2;
    int it;
    list<Curriculo*>::iterator itCurr;
    list<Disciplina*>::iterator itDisc;

    Possibilidade* possibilidade;
    Alocacao* aloc;
    int cMin = 999999, cMax = 0;
    float maxC;

	int nrPossibilidades = 0;
	// cria "Alocacao" marcando (horario,sala) que estao disponiveis
	for( it = 0; it < (int)ind->horariosVazios.size(); it++ ){
		if( cand->horariosViaveis[ind->horariosVazios[it]->horario->horario] == 0 ){
			possibilidade = new Possibilidade(aula, ind->horariosVazios[it], p, ind, it);
			possibilidades.push_back( possibilidade );
			for( i=0; i<nCandidatos; i++) {
				if( candidatos[i]->horariosViaveis[possibilidade->horario->horario->horario] == 0) possibilidade->nAulasParaIndisponibilizar++;
			}
			possibilidade->custoTotal = (0.5 * possibilidade->custoAlocacao);// + possibilidade->nAulasParaIndisponibilizar;
			if( (nrPossibilidades == 0) || (possibilidade->custoTotal > cMax) ) cMax = possibilidade->custoTotal;
			if( (nrPossibilidades == 0) || (possibilidade->custoTotal < cMin) ) cMin = possibilidade->custoTotal;
			nrPossibilidades++;
		}
	}

	maxC = cMin + threshold * (cMax - cMin);
	for( itPos=possibilidades.begin(); itPos!=possibilidades.end();  ){
		if( (*itPos)->custoTotal > maxC ){
			possibilidade = *itPos;
			itPos++;
			possibilidades.remove(possibilidade);
			delete(possibilidade);
			nrPossibilidades--;
		}
		else {
			itPos++;
		}
	}

	// escohe uma possibilidade e aloca a aula
	int escolha = rand() % nrPossibilidades;
	possibilidade = NULL;
	for( itPos=possibilidades.begin(), i=0; itPos!=possibilidades.end(), i<=escolha; itPos++, i++ ) {
		possibilidade = (*itPos);
		aloc = (*itPos)->horario;
	}

	aloc->aula = aula;
	ind->aulasAlocadas.push_back(aloc);
	//printf("%d aulas alocadas\n", (int)ind->aulasAlocadas.size());
	ind->horariosVazios.erase(ind->horariosVazios.begin()+possibilidade->posAulaNaListaHorariosVazios);

	ind->Alocacao_dias_utilizados[aloc->aula->disciplina->numeroSequencial][aloc->horario->dia]++;
	ind->Alocacao_salas_utilizadas[aloc->aula->disciplina->numeroSequencial][aloc->sala->numeroSequencial]++;
	ind->matrizProfessorHorarioQntd[aloc->aula->disciplina->professor->numeroSequencial][aloc->horario->horario]++;
	ind->matrizProfessorHorario[aloc->aula->disciplina->professor->numeroSequencial][aloc->horario->horario] = aloc;
	for( itCurr = aula->disciplina->curriculos.begin(); itCurr!=aula->disciplina->curriculos.end(); itCurr++){
		ind->Alocacao_horarios_utilizados_por_curriculo[(*itCurr)->numeroSequencial][aloc->horario->horario]++;
		ind->matrizAlocacaoCurriculoDiasPeriodos[(*itCurr)->numeroSequencial][aloc->horario->dia][aloc->horario->periodo] = aloc;
	}

	while( possibilidades.size() > 0 ) {
		possibilidade = possibilidades.back();
		possibilidades.pop_back();
		delete(possibilidade);
	}

}


int GeraSolucacoInicial::contaTotalHorariosViaveis(Problema* p, Candidato* cand, Individuo* ind){
	register int i;
	Disciplina *discPos;
	Timeslot* horarioPos;
	vector<Alocacao*>::iterator it;
	Disciplina* discCand = cand->aula->disciplina;
	int horarioVisitado[p->nHorarios];

	for (i = 0; i < p->nHorarios; i++) {
		horarioVisitado[i]       = 0;
		cand->horariosViaveis[i] = p->HorarioIndisponivelDisciplina(discCand, i);
	}

	for( it = ind->aulasAlocadas.begin(); it != ind->aulasAlocadas.end(); it++ ){
		discPos    = (*it)->aula->disciplina;
		horarioPos = (*it)->horario;
		if ( p->SaoDoMesmoProfessor(discCand, discPos) || p->SaoDoMesmoCurriculo(discCand, discPos) ) {
			cand->horariosViaveis[horarioPos->horario] = 1;
		}
	}

	cand->nHorariosViaveis     = 0;
	cand->nHorariosSalaViaveis = 0;
	for( it = ind->horariosVazios.begin(); it != ind->horariosVazios.end(); it++ ){
		if(  cand->horariosViaveis[(*it)->horario->horario] == 0 ) {
			cand->nHorariosSalaViaveis++;
			if( horarioVisitado[(*it)->horario->horario] == 0 ){
				horarioVisitado[(*it)->horario->horario] = 1;
				cand->nHorariosViaveis++;
			}
		}
	}
	
	return cand->nHorariosViaveis;
}


int GeraSolucacoInicial::comparaAulas(Problema* p, Individuo* ind, Candidato* c1, Candidato* c2) {
	int horariosDisp1, horariosDisp2;
	int horariosSalaDisp1, horariosSalaDisp2;
	Disciplina* d1 = c1->aula->disciplina;
	Disciplina* d2 = c2->aula->disciplina;

	if ( d1 == d2 ) return 0; //Mesma disciplina

	// calcula os horarios disponiveis para cada aula
	horariosDisp1 = c1->nHorariosViaveis;
	horariosDisp2 = c2->nHorariosViaveis;
	horariosSalaDisp1 = c1->nHorariosSalaViaveis;
	horariosSalaDisp2 = c2->nHorariosSalaViaveis;

	if (horariosDisp1 > horariosDisp2) {
		return -1;
	} else if (horariosDisp1 < horariosDisp2) {
		return 1;
	} else if (horariosSalaDisp1 > horariosSalaDisp2) {
		return -1;
	} else if (horariosSalaDisp1 < horariosSalaDisp2) {
		return 1;
	} else if (d1->nCurriculos < d2->nCurriculos) {
		return -1;
	} else if (d1->nCurriculos > d2->nCurriculos) {
		return 1;
	} else {
		return 0;
	}
}

void GeraSolucacoInicial::ordenaAulasPorDificuldade(Problema* p, Individuo* ind){
	register int i, j;
	Candidato* chave;
	for (j = 1; j < nCandidatos; j++) {
		chave = candidatos[j];
		i = j - 1;
		while (i >= 0
				&& comparaAulas(p, ind, candidatos[i], chave) > 0) {
			candidatos[i + 1] = candidatos[i];
			i--;
		}
		candidatos[i + 1] = chave;
	}

}

void GeraSolucacoInicial::explodeTimetable2(Problema* p, Individuo* ind, Candidato* cand) {
	Disciplina *disc;
    vector<Alocacao*>::iterator it;
    list<Curriculo*>::iterator itCurr;
    list<Disciplina*>::iterator itDisc;
	register int i, j;
	int posMin;

	int explodiuPorConflito = 0;
	int nConflitantes = 0;
	Alocacao* aulaConflitante;
	int nAulas = p->nSalas;

	posMin = rand() % p->nHorarios;
	disc = cand->aula->disciplina;

	while( p->HorarioIndisponivelDisciplina(disc, posMin) ) {
		posMin++;
		if (posMin == p->nHorarios) posMin = 0; // volta ao primeiro horario
	}

	i  = 0;
	while( i < (int)ind->aulasAlocadas.size() ) {
	    it = ind->aulasAlocadas.begin();
	    advance(it,i);

		if( (*it)->horario->horario == posMin ){
			if ( AulasSaoConflitantes(p, cand->aula, (*it)->aula) ) {
			
				aulaConflitante = (*it);
					
				candidatos[nCandidatos] = new Candidato(aulaConflitante->aula, p);
				nCandidatos++; 
				
				ind->Alocacao_dias_utilizados[(*it)->aula->disciplina->numeroSequencial][(*it)->horario->dia]--;
				ind->Alocacao_salas_utilizadas[(*it)->aula->disciplina->numeroSequencial][(*it)->sala->numeroSequencial]--;
				ind->matrizProfessorHorarioQntd[(*it)->aula->disciplina->professor->numeroSequencial][(*it)->horario->horario]--;
				ind->matrizProfessorHorario[(*it)->aula->disciplina->professor->numeroSequencial][(*it)->horario->horario] = NULL;

				for( itCurr = (*it)->aula->disciplina->curriculos.begin(); itCurr!=(*it)->aula->disciplina->curriculos.end(); itCurr++){
					ind->Alocacao_horarios_utilizados_por_curriculo[(*itCurr)->numeroSequencial][(*it)->horario->horario]--;
					ind->matrizAlocacaoCurriculoDiasPeriodos[(*itCurr)->numeroSequencial][(*it)->horario->dia][(*it)->horario->periodo] = NULL;
				}
				ind->horariosVazios.push_back((*it));
				ind->aulasAlocadas.erase(it);

				explodiuPorConflito++;
				i--;
			} else{
				 nConflitantes++;
			}
		}else {
			nAulas--;
		}
		i++;   
	}

	if (explodiuPorConflito) return;

	j = rand() % ind->aulasAlocadas.size();
	aulaConflitante = ind->aulasAlocadas[j];

	candidatos[nCandidatos] = new Candidato(aulaConflitante->aula, p); // aula volta a ser candidato
	nCandidatos++; // conflitante voltou a ser um candidato

	ind->Alocacao_dias_utilizados[aulaConflitante->aula->disciplina->numeroSequencial][aulaConflitante->horario->dia]--;
	ind->Alocacao_salas_utilizadas[aulaConflitante->aula->disciplina->numeroSequencial][aulaConflitante->sala->numeroSequencial]--;
	ind->matrizProfessorHorarioQntd[aulaConflitante->aula->disciplina->professor->numeroSequencial][aulaConflitante->horario->horario]--;
	ind->matrizProfessorHorario[aulaConflitante->aula->disciplina->professor->numeroSequencial][aulaConflitante->horario->horario] = NULL;
	for( itCurr = aulaConflitante->aula->disciplina->curriculos.begin(); itCurr!=aulaConflitante->aula->disciplina->curriculos.end(); itCurr++){
		ind->Alocacao_horarios_utilizados_por_curriculo[(*itCurr)->numeroSequencial][aulaConflitante->horario->horario]--;
		ind->matrizAlocacaoCurriculoDiasPeriodos[(*itCurr)->numeroSequencial][aulaConflitante->horario->dia][aulaConflitante->horario->periodo] = NULL;
	}
	//ind->aulasAlocadas.remove(aulaConflitante);
	ind->aulasAlocadas.erase(ind->aulasAlocadas.begin()+j);
	ind->horariosVazios.push_back(aulaConflitante);

	aulaConflitante->aula = NULL; // coloca horario vago na posicao
}
