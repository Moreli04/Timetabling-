#ifndef DISS_VETOR_GERASOLUCACOINICIAL_H_
#define DISS_VETOR_GERASOLUCACOINICIAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <list>
using namespace std;

#include "Model/Problema.h"

class GeraSolucacoInicial {
public:
	GeraSolucacoInicial(Problema* p,int qtdAulasNaoAloc);
	void CriaIndividuoInicialEspecial(Problema* p, Individuo* ind);
	int CriaIndividuoInicial(Problema* p, Individuo* ind);
	~GeraSolucacoInicial();

private:
    class Candidato{
    public:
    	Aula* aula;
    	int* horariosViaveis;
    	int nTamVetorHorariosViaveis;
    	int nHorariosViaveis;
    	int nHorariosSalaViaveis;
			int d1; // Quantidade de horarios disponíveis nos dias que a disciplina não possui aula alocada;
			int d2; // Quantidade de horarios disponíveis nos dias que a disciplina possui aula alocada;
    	Candidato(Aula* a, Problema* p){
    		if( a == NULL ){
    			fprintf(stderr, "Erro ao tentar criar um candidato com aula NULA.\n\n");
    			exit(0);
    		}
    		aula = a;
    		horariosViaveis = (int*) malloc ( p->nHorarios * sizeof(int) );
    		nHorariosSalaViaveis = nHorariosViaveis = d1 = d2 = 0;
    		nTamVetorHorariosViaveis = p->nHorarios;
    	};
    	~Candidato(){ free(horariosViaveis); };
    	void imprime(){aula->imprime();};
    };
    class Possibilidade{
    public:
    	Aula* aula;
    	int posAulaNaListaHorariosVazios;
    	Alocacao* horario;
    	int custoAlocacao;
    	int nAulasParaIndisponibilizar;
    	int custoTotal;
    	Possibilidade(Aula* au, Alocacao* aloc, Problema* p, Individuo* ind, int pos){
    		aula = au; horario = aloc;
    		posAulaNaListaHorariosVazios = pos;
    		aloc->aula = aula;
    		custoAlocacao = p->calculaCustoNovaAlocacao(ind, aloc);
    		nAulasParaIndisponibilizar = 0;
    		custoTotal = 0;
//    		printf("Alocar a aula %s no horario %d/%d custa %d\n", aula->disciplina->nome, aloc->horario->dia, aloc->horario->periodo, custoAlocacao);
    		aloc->aula = NULL;
    	};
    };

	Candidato** candidatos;
	int nCandidatos;
	float threshold;

	bool my_compare (Possibilidade* a, Possibilidade* b){
	    return a->custoAlocacao < b->custoAlocacao;
	}

	void explodeTimetable2(Problema* p, Individuo* ind, Candidato* cand);
	int comparaAulas(Problema* p, Individuo* ind, Candidato* c1, Candidato* c2);
	void ordenaAulasPorDificuldade(Problema* p, Individuo* ind);
	int contaTotalHorariosViaveis(Problema* p, Candidato* cand, Individuo* ind);
	int contaTotalHorariosViaveis2(Problema* p, Candidato* cand, Individuo* ind);
	int possuiAulaNoDia(Disciplina *d, int dia, Individuo *ind);
	void alocaAula(Problema* p, Individuo* ind, Candidato* cand);
	void alocaAula2(Problema* p, Individuo* ind, Candidato* cand);

//	bool my_compare (Possibilidade* a, Possibilidade* b);
};

#endif /* DISS_VETOR_GERASOLUCACOINICIAL_H_ */
