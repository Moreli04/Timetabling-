#ifndef DISS_VETOR_GRASP_H_
#define DISS_VETOR_GRASP_H_

#include "Model/Individuo.h"
#include "Model/Matriz.h"
#include<vector>

class Problema;

class Grasp {
public:
	unsigned int seed;
	int *pais;       
	int sumidouro;
	int ordem;
	int nDiasXnPeriodos;
    Linha *lin;
   	int *fluxoPassado;
	Grasp(Problema* p);
	int **disciplinaSala;
	int nSalas;
	Individuo* executaDfsAle(Problema* p,char *arq);
	Individuo* executaBfsAle(Problema* p,char *arq);
	Individuo* executaDfsAleSemIf(Problema* p,char *arq);
	Individuo* executaBfsAleSemIf(Problema* p,char *arq);

private:
	Individuo* executaSimulatedAnnealing(Individuo* indInicial);
	int alocarSolParcial(Problema *p, Individuo *ind);
	void alocarAulasEncontradasPelofluxoMaximoEmRedes(Individuo* ind,int linha, int coluna);
	int mudarDisciplinasDeLugarNaMatriz(int linha, int nDiscAlocadas);
	int lazySearchSeparando(Individuo *ind, int nDisciplinas,  int nDiscAlocadas,  int *posDiscAtual);
	int dfs(Individuo *ind,int nDisciplinas, int *posDiscAtual);
	int dfsSemIf(Individuo *ind,int nDisciplinas, int *posDiscAtual);
	int fluxoMaximoEmRedesDfs(Individuo *ind);
	int fluxoMaximoEmRedesBfs(Individuo *ind);
	int fluxoMaximoEmRedesDfsSemIf(Individuo *ind);
	int fluxoMaximoEmRedesBfsSemIf(Individuo *ind);
	void embaralharMatriz(int nDisciplinas);
	void embaralharMatriz2(int nDisciplinas);
	void criarMatrizFluxoPassado(int nDisciplinas);
	void alocarMemoriaParaMatrizDisciplinaSala(int nDisciplinas, int nSalas);
	void desalocarMemoria();
	void limparFluxo_e_Pais(int nDisciplinas);
	void gerarResultados(int contAulasNaoAloc,int nTentativas,int nAulasTotal,float tempo_construcao,float tempo_busca_local,int icf,int ibf,char *arq);
	void ordenarVetoresCrescente(int qtd,int vet[], Problema *p);
	void ordenarVetoresDecrescente(int qtd,int vet[], Problema *p);
	void ordenarSalas1(Problema *p);
	void ordenarSalas2(Problema *p);
	int bfs(Individuo *ind,int nDisciplinas, int *posDiscAtual);
	int bfsSemIf(Individuo *ind,int nDisciplinas, int *posDiscAtual);
	void criarMatrizDisciplinaSala(int nDisciplinas, int nSalas);
	void desalocarMatrizDisciplinaSala(int nSalas);
	void imprimirMatriz(int nDisciplinas);
};

#endif /* DISS_VETOR_GRASP_H_ */
