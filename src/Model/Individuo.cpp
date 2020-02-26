#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Problema.h"
#include "Individuo.h"
#include "Disciplina.h"
#include "Alocacao.h"


Individuo::Individuo(Problema* p) {
	list<Timeslot*>::iterator itHora;
	list<Sala*>::iterator itSala;
	Alocacao* aloc;
	int i, j, k;

	aulasAlocadas.reserve(p->nSalas * p->nHorarios);
	horariosVazios.reserve(p->nSalas * p->nHorarios);
	TodosHorarios.reserve(p->nSalas * p->nHorarios);

	i = 0;
	for( itSala=p->salas.begin(); itSala!=p->salas.end(); itSala++ ) {
		for( itHora=p->horarios.begin(); itHora!=p->horarios.end(); itHora++ ) {
			aloc = new Alocacao(i);
			aloc->aula 	  = NULL;
			aloc->horario = *itHora;
			aloc->sala	  = *itSala;
			horariosVazios.push_back(aloc);
			TodosHorarios.push_back(aloc);
			i++;
		}
	}
	
	
	this->p = p;
	hard = 0;
	soft1 = 0;
	soft2 = 0;
	soft3 = 0; 
	soft4 = 0;
	fitness = 0;

	Alocacao_salas_utilizadas = (int**) malloc( p->nDisciplinas * sizeof(int*) );
	Alocacao_dias_utilizados  = (int**) malloc( p->nDisciplinas * sizeof(int*) );
	for( j=0; j<p->nDisciplinas; j++ ) {
		Alocacao_salas_utilizadas[j] = (int*) malloc( p->nSalas * sizeof(int) );
		Alocacao_dias_utilizados[j]  = (int*) malloc( p->nDias * sizeof(int) );
		for( i=0; i<p->nSalas; i++ ) Alocacao_salas_utilizadas[j][i] = 0;
		for( i=0; i<p->nDias; i++ ) Alocacao_dias_utilizados[j][i] = 0;
	}

	Alocacao_horarios_utilizados_por_curriculo = (int**) malloc( p->nCurriculos * sizeof(int*) );
	for( j=0; j<p->nCurriculos; j++ ) {
		Alocacao_horarios_utilizados_por_curriculo[j] = (int*) malloc( p->nHorarios * sizeof(int) );
		for( i=0; i<p->nHorarios; i++ )
			Alocacao_horarios_utilizados_por_curriculo[j][i] = 0;
	}

	matrizAlocacaoCurriculoDiasPeriodos = (Alocacao****) malloc( p->nCurriculos * sizeof(Alocacao***) );
	for( j=0; j<p->nCurriculos; j++ ) {
		matrizAlocacaoCurriculoDiasPeriodos[j] = (Alocacao***) malloc( p->nDias * sizeof(Alocacao**) );
		for( i=0; i<p->nDias; i++ ){
			matrizAlocacaoCurriculoDiasPeriodos[j][i] = (Alocacao**) malloc( p->nPerDias * sizeof(Alocacao*) );
			for( k=0; k<p->nPerDias; k++ ){
				matrizAlocacaoCurriculoDiasPeriodos[j][i][k] = NULL;
			}
		}
	}

	matrizProfessorHorario = (Alocacao***) malloc( ((int) p->professores.size()) * sizeof(Alocacao**) );
	matrizProfessorHorarioQntd = (int**) malloc( ((int) p->professores.size()) * sizeof(int*) );
	for( j=0; j<(int) p->professores.size(); j++ ) {
		matrizProfessorHorario[j] = (Alocacao**) malloc( p->nHorarios * sizeof(Alocacao*) );
		matrizProfessorHorarioQntd[j] = (int*) malloc( p->nHorarios * sizeof(int) );
		for( i=0; i<p->nHorarios; i++ ){
			matrizProfessorHorario[j][i] = NULL;
			matrizProfessorHorarioQntd[j][i] = 0;
		}
	}
	
}

Individuo::Individuo(Individuo* i) {
	vector<Alocacao*>::iterator it;
	Alocacao* copiaAloc;
	int k, j, s;

	p = i->p;

	aulasAlocadas.reserve(p->nSalas * p->nHorarios);
	horariosVazios.reserve(p->nSalas * p->nHorarios);
	TodosHorarios.reserve(p->nSalas * p->nHorarios);

	for( it=i->TodosHorarios.begin(); it!=i->TodosHorarios.end(); it++ ) {
		copiaAloc = new Alocacao(*it);
		TodosHorarios.push_back( copiaAloc );
		//if( copiaAloc->aula == NULL )
	}
	for( it=i->horariosVazios.begin(); it!=i->horariosVazios.end(); it++ ) {
		copiaAloc = this->ObtemAlocacao((*it)->horario->horario, (*it)->sala->numeroSequencial);
		
		horariosVazios.push_back( copiaAloc );
	}
	for( it=i->aulasAlocadas.begin(); it!=i->aulasAlocadas.end(); it++ ) {
		copiaAloc = this->ObtemAlocacao((*it)->horario->horario, (*it)->sala->numeroSequencial);
		
		aulasAlocadas.push_back( copiaAloc );
	}

	hard  = i->hard;
	soft1 = i->soft1;
	soft2 = i->soft2;
	soft3 = i->soft3;
	soft4 = i->soft4;
	fitness = i->fitness;
	p = i->p;
	Alocacao_salas_utilizadas = (int**) malloc( p->nDisciplinas * sizeof(int*) );
	Alocacao_dias_utilizados  = (int**) malloc( p->nDisciplinas * sizeof(int*) );
	Alocacao_horarios_utilizados_por_curriculo = (int**) malloc( p->nCurriculos * sizeof(int*) );
	for( j=0; j<p->nDisciplinas; j++ ) {
		Alocacao_salas_utilizadas[j] = (int*) malloc( p->nSalas * sizeof(int) );
		Alocacao_dias_utilizados[j]  = (int*) malloc( p->nDias * sizeof(int) );
		for( k=0; k<p->nSalas; k++ ) Alocacao_salas_utilizadas[j][k] = i->Alocacao_salas_utilizadas[j][k];
		for( k=0; k<p->nDias ; k++ ) Alocacao_dias_utilizados[j][k] = i->Alocacao_dias_utilizados[j][k];
	}
	for( j=0; j<p->nCurriculos; j++ ) {
		Alocacao_horarios_utilizados_por_curriculo[j] = (int*) malloc( p->nHorarios * sizeof(int) );
		for( k=0; k<p->nHorarios; k++ )
			Alocacao_horarios_utilizados_por_curriculo[j][k] = i->Alocacao_horarios_utilizados_por_curriculo[j][k];
	}
	matrizAlocacaoCurriculoDiasPeriodos = (Alocacao****) malloc( p->nCurriculos * sizeof(Alocacao***) );
	for( j=0; j<p->nCurriculos; j++ ) {
		matrizAlocacaoCurriculoDiasPeriodos[j] = (Alocacao***) malloc( p->nDias * sizeof(Alocacao**) );
		for( s=0; s<p->nDias; s++ ){
			matrizAlocacaoCurriculoDiasPeriodos[j][s] = (Alocacao**) malloc( p->nPerDias * sizeof(Alocacao*) );
			for( k=0; k<p->nPerDias; k++ ){
				matrizAlocacaoCurriculoDiasPeriodos[j][s][k] = i->matrizAlocacaoCurriculoDiasPeriodos[j][s][k];
			}
		}
	}
	matrizProfessorHorario = (Alocacao***) malloc( ((int) p->professores.size()) * sizeof(Alocacao**) );
	matrizProfessorHorarioQntd = (int**) malloc( ((int) p->professores.size()) * sizeof(int*) );
	for( j=0; j<(int) p->professores.size(); j++ ) {
		matrizProfessorHorario[j] = (Alocacao**) malloc( p->nHorarios * sizeof(Alocacao*) );
		matrizProfessorHorarioQntd[j] = (int*) malloc( p->nHorarios * sizeof(int) );
		for( s=0; s<p->nHorarios; s++ ){
			if( i->matrizProfessorHorario[j][s] != NULL ){
				copiaAloc = this->ObtemAlocacao(i->matrizProfessorHorario[j][s]->horario->horario, i->matrizProfessorHorario[j][s]->sala->numeroSequencial);
				
			}
			else copiaAloc = NULL;
			matrizProfessorHorario[j][s] = copiaAloc;
			matrizProfessorHorarioQntd[j][s] = i->matrizProfessorHorarioQntd[j][s];
		}
	}
}


void Individuo::ImprimeIndividuo(){
	vector<Alocacao*>::iterator it;

	printf("\nIndividuo: ");
	printf("fitness: %d\n", fitness);
	printf("hard: %3d\tsoft1: %3d\tsoft2: %3d\tsoft3: %3d\tsoft4: %3d\n", hard, soft1, soft2, soft3, soft4);

	//checar possiveis erros
	for(it = aulasAlocadas.begin(); it != aulasAlocadas.end(); it++){
		if( (*it)->aula == NULL  ){
			printf("Aula alocada eh nula\n");
			exit(0);
		}
	}
	for(it = horariosVazios.begin(); it != horariosVazios.end(); it++){
		if( (*it)->aula != NULL  ){
			printf("Horario vazio nao eh nulo\n");
			exit(0);
		}
	}

	printf("\n\n");
}

void Individuo::ImprimeInstancia(char *arq){
	vector<Alocacao*>::iterator it;
    Timeslot* ts;
    FILE *f;

	// abre arquivo
    f = fopen(arq, "w");
    if (f == NULL) {
        printf("Erro de abertura do arquivo %s\n",arq);
        exit(1);
    }

	for( it=aulasAlocadas.begin(); it!=aulasAlocadas.end(); it++ ) {
		ts = (*it)->horario;
		fprintf(f, "%s %s %d %d\n", (*it)->aula->disciplina->nome, (*it)->sala->idSala, ts->dia, ts->periodo);
    }
	fclose(f);
		
}


Alocacao* Individuo::ObtemAlocacao(int horario, int numSala){
	vector<Alocacao*>::iterator it;
	for( it=TodosHorarios.begin(); it!=TodosHorarios.end(); it++ ) {
		if( ((*it)->horario->horario == horario) &&
			((*it)->sala->numeroSequencial == numSala) )
			return (*it);
	}
	fprintf(stderr, "ERRO em Individuo.cpp: horario %d e sala %d nao existente no individuo.\n\n", horario, numSala);
	exit(-1);
}


int Individuo::restricaoForte(Disciplina *disc,int dia, int periodo){
	
	vector<Alocacao*>::iterator itAulasAlocadas;
	
	for(itAulasAlocadas = aulasAlocadas.begin(); itAulasAlocadas!=aulasAlocadas.end(); itAulasAlocadas++ ) {
		if(((*itAulasAlocadas)->horario->dia == dia) && ((*itAulasAlocadas)->horario->periodo == periodo)){
			
			if((p->SaoDoMesmoCurriculo((*itAulasAlocadas)->aula->disciplina, disc))
				||((*itAulasAlocadas)->aula->disciplina->professor->numeroSequencial == disc->professor->numeroSequencial)
				||((*itAulasAlocadas)->aula->disciplina->numeroSequencial == disc->numeroSequencial)){
				return 0;	
			}		
		}
	}
	return 1;
}


Individuo::~Individuo(){
	Alocacao* aloc;
	int i, s;

	while( TodosHorarios.size() > 0 ) {
		aloc = TodosHorarios.back();
		TodosHorarios.pop_back();
		delete(aloc);
	}

	for( i=0; i!=p->nDisciplinas; i++ ) {
		free(Alocacao_dias_utilizados[i]);
		free(Alocacao_salas_utilizadas[i]);
	}
	free(Alocacao_salas_utilizadas);
	free(Alocacao_dias_utilizados);

	for( i=0; i!=p->nCurriculos; i++ ) {
		free(Alocacao_horarios_utilizados_por_curriculo[i]);
		for( s=0; s<p->nDias; s++ ){
			free(matrizAlocacaoCurriculoDiasPeriodos[i][s]);
		}
		free(matrizAlocacaoCurriculoDiasPeriodos[i]);
	}
	free(Alocacao_horarios_utilizados_por_curriculo);
	free(matrizAlocacaoCurriculoDiasPeriodos);
	for( i=0; i!=(int) p->professores.size(); i++ ) {
		free(matrizProfessorHorario[i]);
		free(matrizProfessorHorarioQntd[i]);
	}
	free(matrizProfessorHorario);
	free(matrizProfessorHorarioQntd);
}
