#include <stdlib.h>
#include <math.h>

#include "SimulatedAnnealing.h"
#include "../Model/Problema.h"
#include "../Vizinhancas/Movimento.h"
#include "../Vizinhancas/Move.h"
#include "../Vizinhancas/Swap.h"
#include "../Vizinhancas/LectureMove3.h"

#define temperaturaInicial 17.3
#define	nMaxIterSemMelhora 2000
#define	temperaturaFinal 0.03
#define taxaDecaimentoTemperatura 0.9999

SimulatedAnnealing::SimulatedAnnealing() {
}

SimulatedAnnealing::~SimulatedAnnealing() { }


Individuo* SimulatedAnnealing::executa(Individuo* bestInd){
	Movimento *vizinho;
	Individuo *melhorInd, *solucaoAtual;

	long N, i;
	double tAtual = temperaturaInicial;

	solucaoAtual = bestInd;
	melhorInd = new Individuo(solucaoAtual);

	int nIteracoesExecutadas = 0;
	do {
		N = 500;
		i = 0;
		do {
			vizinho = new LectureMove3(solucaoAtual);

			if( vizinho->deltaFit <= 0 ){// função objetivo decresceu
				vizinho->aplicaMovimento();
		
				if (solucaoAtual->fitness < melhorInd->fitness) {
					delete(melhorInd);
					melhorInd = new Individuo(solucaoAtual);
				}
			} else if( vizinho->deltaFit < 3000 ){
				i++;
				// calcula probabilidade de aceitação
				if(((float) rand() / RAND_MAX) <= pow(M_E, -vizinho->deltaFit / tAtual)){
					vizinho->aplicaMovimento();
				}
			}
			delete(vizinho);
			N--;
			nIteracoesExecutadas++;

			if( i >= nMaxIterSemMelhora ) break;
		} while( N > 0 );

		if( i >= nMaxIterSemMelhora ) break;
		tAtual *= taxaDecaimentoTemperatura;
	} while (tAtual > temperaturaFinal);

	delete(solucaoAtual);
	return melhorInd;
}

Individuo* SimulatedAnnealing::executa1(Individuo *solucaoAtual){
	LectureMove3 *vizinho;
	Individuo *melhorInd;
	int i;
	double tAtual = temperaturaInicial;
	melhorInd = new Individuo(solucaoAtual);
	//usar i < 300 da bons resultados
	do{
		for(i = 0; i < 500; i++){
			vizinho = new LectureMove3(solucaoAtual);
			
			if( vizinho->deltaFit <= 0 ){// função objetivo decresceu
				vizinho->aplicaMovimento();
		
				if (solucaoAtual->fitness < melhorInd->fitness) {
					delete(melhorInd);
					melhorInd = new Individuo(solucaoAtual);
				}
			}else{
				if( vizinho->deltaFit < 3000 ){
					if(((float) rand() /RAND_MAX) <= pow(M_E, -vizinho->deltaFit / tAtual)){
						vizinho->aplicaMovimento();
					}
				} 
			}
			delete(vizinho);	
		}
		tAtual *= taxaDecaimentoTemperatura;

	}while(tAtual > temperaturaFinal);
	delete(solucaoAtual);
	return melhorInd;
}