#ifndef INDIVIDUO_H_
#define INDIVIDUO_H_

#include <list>
#include <vector>
#include <stdio.h>

#include "Alocacao.h"
class Problema;
using namespace std;

class Individuo {
public:
	vector<Alocacao*> aulasAlocadas;
	vector<Alocacao*> horariosVazios;
	vector<Alocacao*> TodosHorarios;
	int fitness;
	int hard;
	int soft1, soft2, soft3, soft4;

	Problema* p;
	int** Alocacao_salas_utilizadas;
	int** Alocacao_dias_utilizados;
	int** Alocacao_horarios_utilizados_por_curriculo;
	Alocacao* ***matrizAlocacaoCurriculoDiasPeriodos;
	Alocacao* **matrizProfessorHorario;
	int **matrizProfessorHorarioQntd;

	Individuo(Problema* p);
	Individuo(Individuo* i);
	void ImprimeIndividuo();
	void ImprimeInstancia(char *arq);
	~Individuo();

	Alocacao* ObtemAlocacao(int horario, int numSala);

	int restricaoForte(Disciplina *d,int dia, int periodo);
	void escreverNoArquivoTeste();
	void gerarResultadosContrucao(int contAulasNaoAloc,int nIteracoes,float tempo_construcao);
	void gerarResultadosBuscaLocal(float tempo_busca_local);
};

#endif /* INDIVIDUO_H_ */
