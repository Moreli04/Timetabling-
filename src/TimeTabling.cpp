#include "Model/Problema.h"
#include "Model/Individuo.h"
#include "Grasp.h"
#include <stdio.h>

int main(int argc, char** argv) {
	Problema* p;
	Individuo* best = NULL;
	Grasp* grasp;
	int tipoExecucao;

	if(argc != 5){

		printf("Erro na quantidade de parametros informados \n");
		exit(0);

	}else{

		p = new Problema(argv[1]);
	    grasp = new Grasp(p);
	 	grasp->seed = (unsigned)time(NULL);
		srand(grasp->seed);
		tipoExecucao = *argv[2] - '0';

		if(tipoExecucao == 0)
			best = grasp->executaBfsAleSemIf(p,argv[3]);
		if(tipoExecucao == 1)
			best = grasp->executaBfsAle(p,argv[3]);
		if(tipoExecucao == 2)
			best = grasp->executaDfsAleSemIf(p,argv[3]);
		else if(tipoExecucao == 3)
			best = grasp->executaDfsAle(p,argv[3]);

		best->ImprimeInstancia(argv[4]);

		delete(grasp);
		delete(best);
		delete(p);
		return 0;
	}
}
