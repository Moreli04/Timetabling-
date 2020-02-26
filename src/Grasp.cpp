#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Grasp.h"
#include "GeraSolucacoInicial.h"
#include "Model/Problema.h"
#include "BuscaLocal/SimulatedAnnealing.h"
#include <math.h>
#include <string.h>
#define MIN(X,Y) ((X < Y) ? (X) : (Y))
#define MAXIMO(X,Y) ((X > Y) ? (X) : (Y))
#define TEMPO 220

Grasp::Grasp(Problema* p) {
	ordem = p->nSalas*p->nDias*p->nPerDias + p->nDisciplinas+2;
	sumidouro = ordem -1;
	lin = p->preencherMatriz(ordem);
	embaralharMatriz2(p->nDisciplinas);
	criarMatrizDisciplinaSala(p->nDisciplinas,p->nSalas);
	ordenarSalas1(p);
	if(p->nDisciplinas >= 500){
		printf("Tem vetor com tamanho fixo de 500, essa instancia tem %d, vai dar falha de segmentacao\n",p->nDisciplinas);
		exit(0);
	}
	nSalas = p->nSalas;
	nDiasXnPeriodos = p->nDias*p->nPerDias;
	criarMatrizFluxoPassado(p->nDisciplinas+1);
}

Individuo* Grasp::executaDfsAle(Problema* p,char *arq) {
	SimulatedAnnealing* sa = new SimulatedAnnealing();
	Individuo *ind, *bestInd,*indConstrucao;
	bestInd = new Individuo(p); bestInd->fitness = 9999999;
	GeraSolucacoInicial* geraSolucaoI;

	int nTentativas = 1,contAulasNaoAloc = 0, nIteracoes = 0,fitness = 0;
	float tempo_construcao, tempo_busca_local, t,tempoExecucao;
	clock_t hi;
	tempoExecucao = clock() / CLOCKS_PER_SEC;
	
	 do{
	 	hi = clock();
	 	nIteracoes++;

		indConstrucao = new Individuo(p);
		contAulasNaoAloc = fluxoMaximoEmRedesDfs(indConstrucao);
		geraSolucaoI = new GeraSolucacoInicial(p,contAulasNaoAloc);
		
		nTentativas = 1;
		while(geraSolucaoI->CriaIndividuoInicial(p, indConstrucao)){

			delete(indConstrucao);
			p->restaurarAulasNaoAlocadas();	
			
		  	indConstrucao = new Individuo(p);
		  	contAulasNaoAloc = fluxoMaximoEmRedesDfs(indConstrucao);

			delete(geraSolucaoI);
			geraSolucaoI = new GeraSolucacoInicial(p,contAulasNaoAloc);

			nTentativas++;
		}
		t = clock();
		tempo_construcao = (t - hi)/CLOCKS_PER_SEC;
		delete(geraSolucaoI);

		p->restaurarAulasNaoAlocadas();
		p->CalculaFuncaoObjetivo(indConstrucao);
		
		fitness = indConstrucao->fitness;
		t = clock();
		ind = sa->executa(indConstrucao);
		ind->fitness = 99999999;
		tempo_busca_local = (clock() - t) / CLOCKS_PER_SEC;
		p->CalculaFuncaoObjetivo(ind);
		gerarResultados(contAulasNaoAloc,nTentativas,p->nAulasTotal,tempo_construcao,tempo_busca_local,fitness,ind->fitness,arq);
			
		if (ind->fitness < bestInd->fitness) {
			delete (bestInd);
			bestInd = ind;
		}else
			delete (ind);
	}while(((clock() / CLOCKS_PER_SEC) - tempoExecucao) < TEMPO);
	desalocarMemoria();
	desalocarMatrizDisciplinaSala(p->nSalas);
	delete(sa);
	return bestInd;
}

Individuo* Grasp::executaDfsAleSemIf(Problema* p,char *arq) {
	SimulatedAnnealing* sa = new SimulatedAnnealing();
	Individuo *ind, *bestInd,*indConstrucao;
	bestInd = new Individuo(p); bestInd->fitness = 9999999;
	GeraSolucacoInicial* geraSolucaoI;

	int nTentativas = 1,contAulasNaoAloc = 0, nIteracoes = 0,fitness = 0;
	float tempo_construcao, tempo_busca_local, t,tempoExecucao;
	clock_t hi;
	tempoExecucao = clock() / CLOCKS_PER_SEC;
	
	 do{
	 	hi = clock();
	 	nIteracoes++;

		indConstrucao = new Individuo(p);
		contAulasNaoAloc = fluxoMaximoEmRedesDfsSemIf(indConstrucao);
		geraSolucaoI = new GeraSolucacoInicial(p,contAulasNaoAloc);
		
		nTentativas = 1;
		while(geraSolucaoI->CriaIndividuoInicial(p, indConstrucao)){

			delete(indConstrucao);
			p->restaurarAulasNaoAlocadas();	
			
		  	indConstrucao = new Individuo(p);
		  	contAulasNaoAloc = fluxoMaximoEmRedesDfsSemIf(indConstrucao);

			delete(geraSolucaoI);
			geraSolucaoI = new GeraSolucacoInicial(p,contAulasNaoAloc);

			nTentativas++;
		}
		t = clock();
		tempo_construcao = (t - hi)/CLOCKS_PER_SEC;
		delete(geraSolucaoI);

		p->restaurarAulasNaoAlocadas();
		p->CalculaFuncaoObjetivo(indConstrucao);
		
		fitness = indConstrucao->fitness;
		t = clock();
		ind = sa->executa(indConstrucao);
		ind->fitness = 99999999;
		tempo_busca_local = (clock() - t) / CLOCKS_PER_SEC;
		p->CalculaFuncaoObjetivo(ind);
		gerarResultados(contAulasNaoAloc,nTentativas,p->nAulasTotal,tempo_construcao,tempo_busca_local,fitness,ind->fitness,arq);

		if (ind->fitness < bestInd->fitness) {
			delete (bestInd);
			bestInd = ind;
		}else
			delete (ind);
	}while(((clock() / CLOCKS_PER_SEC) - tempoExecucao) < TEMPO);
	desalocarMemoria();
	desalocarMatrizDisciplinaSala(p->nSalas);
	delete(sa);
	return bestInd;
}


Individuo* Grasp::executaBfsAle(Problema* p,char *arq) {
	SimulatedAnnealing* sa = new SimulatedAnnealing();
	Individuo *ind, *bestInd,*indConstrucao;
	bestInd = new Individuo(p); bestInd->fitness = 9999999;
	GeraSolucacoInicial* geraSolucaoI;

	int nTentativas = 1,contAulasNaoAloc = 0, nIteracoes = 0, fitness = 0;
	float tempo_construcao, tempo_busca_local, t,tempoExecucao;
	clock_t hi;
	tempoExecucao = clock() / CLOCKS_PER_SEC;
	
	 do{
	 	hi = clock();
	 	nIteracoes++;

		indConstrucao = new Individuo(p);
		contAulasNaoAloc = fluxoMaximoEmRedesBfs(indConstrucao);
		geraSolucaoI = new GeraSolucacoInicial(p,contAulasNaoAloc);
		
		nTentativas = 1;
		while(geraSolucaoI->CriaIndividuoInicial(p, indConstrucao)){

			delete(indConstrucao);
			p->restaurarAulasNaoAlocadas();	
			
		  	indConstrucao = new Individuo(p);
		  	contAulasNaoAloc = fluxoMaximoEmRedesBfs(indConstrucao);

			delete(geraSolucaoI);
			geraSolucaoI = new GeraSolucacoInicial(p,contAulasNaoAloc);

			nTentativas++;
		}
		t = clock();
		tempo_construcao = (t - hi)/CLOCKS_PER_SEC;
		delete(geraSolucaoI);

		p->restaurarAulasNaoAlocadas();
		p->CalculaFuncaoObjetivo(indConstrucao);
		

		fitness = indConstrucao->fitness;
		t = clock();
		ind = sa->executa(indConstrucao);
		tempo_busca_local = (clock() - t) / CLOCKS_PER_SEC;
		p->CalculaFuncaoObjetivo(ind);
		gerarResultados(contAulasNaoAloc,nTentativas,p->nAulasTotal,tempo_construcao,tempo_busca_local,fitness,ind->fitness,arq);
				
		if (ind->fitness < bestInd->fitness) {
			delete (bestInd);
			bestInd = ind;
		}else
			delete (ind);
		
	}while(((clock() / CLOCKS_PER_SEC) - tempoExecucao) < TEMPO);
	desalocarMemoria();
	desalocarMatrizDisciplinaSala(p->nSalas);
	delete(sa);
	return bestInd;
}

Individuo* Grasp::executaBfsAleSemIf(Problema* p,char *arq) {
	SimulatedAnnealing* sa = new SimulatedAnnealing();
	Individuo *ind, *bestInd,*indConstrucao;
	bestInd = new Individuo(p); bestInd->fitness = 9999999;
	GeraSolucacoInicial* geraSolucaoI;

	int nTentativas = 1,contAulasNaoAloc = 0, nIteracoes = 0, fitness = 0;
	float tempo_construcao, tempo_busca_local, t,tempoExecucao;
	clock_t hi;
	tempoExecucao = clock() / CLOCKS_PER_SEC;
	
	 do{
	 	hi = clock();
	 	nIteracoes++;

		indConstrucao = new Individuo(p);
		contAulasNaoAloc = fluxoMaximoEmRedesBfsSemIf(indConstrucao);
		geraSolucaoI = new GeraSolucacoInicial(p,contAulasNaoAloc);
		
		nTentativas = 1;
		while(geraSolucaoI->CriaIndividuoInicial(p, indConstrucao)){

			delete(indConstrucao);
			p->restaurarAulasNaoAlocadas();	
			
		  	indConstrucao = new Individuo(p);
		  	contAulasNaoAloc = fluxoMaximoEmRedesBfsSemIf(indConstrucao);

			delete(geraSolucaoI);
			geraSolucaoI = new GeraSolucacoInicial(p,contAulasNaoAloc);

			nTentativas++;
		}
		t = clock();
		tempo_construcao = (t - hi)/CLOCKS_PER_SEC;
		delete(geraSolucaoI);

		p->restaurarAulasNaoAlocadas();
		p->CalculaFuncaoObjetivo(indConstrucao);
		

		fitness = indConstrucao->fitness;
		t = clock();
		ind = sa->executa(indConstrucao);
		tempo_busca_local = (clock() - t) / CLOCKS_PER_SEC;
		p->CalculaFuncaoObjetivo(ind);
		gerarResultados(contAulasNaoAloc,nTentativas,p->nAulasTotal,tempo_construcao,tempo_busca_local,fitness,ind->fitness,arq);
				
		if (ind->fitness < bestInd->fitness) {
			delete (bestInd);
			bestInd = ind;
		}else
			delete (ind);
		
	}while(((clock() / CLOCKS_PER_SEC) - tempoExecucao) < TEMPO);
	desalocarMemoria();
	desalocarMatrizDisciplinaSala(p->nSalas);
	delete(sa);
	return bestInd;
}

void Grasp::gerarResultados(int contAulasNaoAloc,int nTentativas,int nAulasTotal,float tempo_construcao,float tempo_busca_local,int icf, int ibf, char*arq){
    char a;
    if(contAulasNaoAloc > 0)
    	a = 'N';
    else
    	a = 'S';

    printf("%d;%c;%d;%d;%f;%d;%f\n",seed,a,nTentativas,icf,tempo_construcao,ibf,tempo_busca_local);
}

void Grasp::criarMatrizDisciplinaSala(int nDisciplinas, int nSalas){
	int i;

	disciplinaSala = (int**) malloc(nSalas * sizeof(int*));
	
	for(i = 0; i < nSalas; i++)
		disciplinaSala[i] = (int*) malloc(nDisciplinas * sizeof(int));
}

void Grasp::desalocarMatrizDisciplinaSala(int nSalas){
	int i;

	for(i = 0; i < nSalas; i++)
		free(disciplinaSala[i]);

	free(disciplinaSala);
}

void Grasp::embaralharMatriz(int nDisciplinas){
	register int j = 0;
	int nDisNoVetor = nDisciplinas;
	int vetDisc[500];
	int qtd,linha1,linha2,capacidade;
	int aux1,aux2,i;
	Linha aux;
	qtd = (int)MAXIMO(0.4*(nDisciplinas),1);

	for(j = 1; j <= nDisciplinas; j++)
		vetDisc[j] = j;

	for (j = 0; j < qtd; j++){
		do{
		    linha1  = 1 + rand() %  (nDisNoVetor);
			linha2 	= 1 + rand() %  (nDisNoVetor);
		}while(linha1 == linha2);

		aux1 = vetDisc[linha1];
		aux2 = vetDisc[linha2];

		i = nDisNoVetor;
		while((vetDisc[i] == aux1) || (vetDisc[i] == aux2))
			i--;

		vetDisc[linha1] = vetDisc[i];
		nDisNoVetor--;

		i = nDisNoVetor;
		while((vetDisc[i] == aux1) || (vetDisc[i] == aux2))
			i--;
		vetDisc[linha2] = vetDisc[i];

		nDisNoVetor--;

		aux = lin[aux1];
		lin[aux1] = lin[aux2];
		lin[aux2] = aux;	

		capacidade = lin[0].coluna[aux1].capacidade;
		lin[0].coluna[aux1].capacidade = lin[0].coluna[aux2].capacidade;
		lin[0].coluna[aux2].capacidade = capacidade;	
	}

}

void Grasp::embaralharMatriz2(int nDisciplinas){
	register int j = 0;
	int nDisNoVetor = nDisciplinas;
	int vetDisc[500];
	int qtd,linha1,linha2,capacidade;
	int aux1,aux2,i;
	Linha aux;
	qtd = (int)MAXIMO(0.5*(nDisciplinas),1);

	for(j = 1; j <= nDisciplinas; j++)
		vetDisc[j] = j;
	
	for (j = 0; j < qtd; j++){
		do{
		    linha1  = 1 + rand() %  (nDisNoVetor);
			linha2 	= 1 + rand() %  (nDisNoVetor);
		}while(linha1 == linha2);

		aux1 = vetDisc[linha1];
		aux2 = vetDisc[linha2];

		i = nDisNoVetor;
		while((vetDisc[i] == aux1) || (vetDisc[i] == aux2))
			i--;

		vetDisc[linha1] = vetDisc[i];
		nDisNoVetor--;

		i = nDisNoVetor;
		while((vetDisc[i] == aux1) || (vetDisc[i] == aux2))
			i--;
		vetDisc[linha2] = vetDisc[i];

		nDisNoVetor--;

		aux = lin[aux1];
		lin[aux1] = lin[aux2];
		lin[aux2] = aux;	

		capacidade = lin[0].coluna[aux1].capacidade;
		lin[0].coluna[aux1].capacidade = lin[0].coluna[aux2].capacidade;
		lin[0].coluna[aux2].capacidade = capacidade;	
	}

}

void Grasp::ordenarVetoresDecrescente(int qtd,int vet[], Problema *p){
	int maior = 0,posMaior = 0,achouMaior = 0;
	int i,j,aux;
	
	for(i = 0; i < qtd-1; i++){
		maior = p->getCapacidadeSala(vet[i]);
		achouMaior = 0;
		for(j = i+1; j < qtd; j++){
			if(maior < p->getCapacidadeSala(vet[j])){
				maior = p->getCapacidadeSala(vet[j]);
				posMaior = j;
				achouMaior = 1;
			}
		}
		if(achouMaior){
			aux = vet[i];
			vet[i] = vet[posMaior];
			vet[posMaior] = aux;
		}	
	}

}

void Grasp::ordenarVetoresCrescente(int qtd,int vet[], Problema *p){
	int maior = 0,posMaior = 0,achouMaior = 0;
	int i,j,aux;
	
	for(i = 0; i < qtd-1; i++){
		maior = p->getCapacidadeSala(vet[i]);
		achouMaior = 0;
		for(j = i+1; j < qtd; j++){
			if(maior > p->getCapacidadeSala(vet[j])){
				maior = p->getCapacidadeSala(vet[j]);
				posMaior = j;
				achouMaior = 1;
			}
		}
		if(achouMaior){
			aux = vet[i];
			vet[i] = vet[posMaior];
			vet[posMaior] = aux;
		}	
	}
}


void Grasp::criarMatrizFluxoPassado(int nDisciplinas){
	pais = (int*)malloc(ordem* sizeof(int));
	fluxoPassado = (int*) malloc((nDisciplinas)* sizeof(int*));
	limparFluxo_e_Pais(nDisciplinas);
}


void Grasp::imprimirMatriz(int nDisciplinas){
	int i;
	
	printf("fluxoPassado ficou assim:\n");
	for(i = 0; i < ordem; i++){
		printf("%d\t ",fluxoPassado[i]);
	}
	printf("\n");

	///*
	printf("Pais\n");
	for(i = 0; i < ordem; i++)
		printf("%d ",pais[i]);
	printf("\n");
	//*/
}

void Grasp::ordenarSalas1(Problema *p){
	list<Sala*>::iterator itSala;
	list<Disciplina*>::iterator itDisc;
	int maiores[500],menores[500];
	int cont1, cont2, i, j;
	int numeroSequencial;

	for(itDisc = p->disciplinas.begin();itDisc != p->disciplinas.end(); itDisc++){
		cont1 = 0; cont2 = 0;
		memset(maiores,1000,sizeof(maiores));
		memset(menores,0,sizeof(menores));
		for(itSala = p->salas.begin();itSala != p->salas.end(); itSala++){
			if((*itSala)->capacidade >= (*itDisc)->nAlunos){
				maiores[cont1] = (*itSala)->numeroSequencial;
				cont1++;
			}else{
				menores[cont2] = (*itSala)->numeroSequencial;
				cont2++;
			}
		}
		ordenarVetoresCrescente(cont1,maiores,p);
		ordenarVetoresDecrescente(cont2,menores,p);
		numeroSequencial = (*itDisc)->numeroSequencial;
		for(i = 0; i < cont1; i++){
			disciplinaSala[i][numeroSequencial] = maiores[i];	
		}
		for(j = 0; j < cont2; j++){
			disciplinaSala[cont1+j][numeroSequencial] = menores[j];	
		}

	}

}

void Grasp::ordenarSalas2(Problema *p){
	list<Sala*>::iterator itSala;
	list<Disciplina*>::iterator itDisc;
	int vet[500];
	int i,j,aux,maior = 0,posMaior = 0,achouMaior = 0,pos;

	for(itDisc = p->disciplinas.begin();itDisc != p->disciplinas.end(); itDisc++){
		pos = 0;
		memset(vet,0,sizeof(vet));
		for(itSala = p->salas.begin();itSala != p->salas.end(); itSala++){
			vet[pos] = (*itSala)->numeroSequencial;
			pos++;
		}

		for(i = 0; i < p->nSalas-1; i++){
			maior = abs(p->getCapacidadeSala(vet[i]) - (*itDisc)->nAlunos);
			achouMaior = 0;
			for(j = i+1; j < p->nSalas; j++){
				if(maior > abs(p->getCapacidadeSala(vet[j]) - (*itDisc)->nAlunos)){
					maior = abs(p->getCapacidadeSala(vet[j]) - (*itDisc)->nAlunos);
					posMaior = j;
					achouMaior = 1;
				}else if(maior == abs(p->getCapacidadeSala(vet[j]) - (*itDisc)->nAlunos)){
					if(maior < (p->getCapacidadeSala(vet[j]) - (*itDisc)->nAlunos)){
						posMaior = j;
						achouMaior = 1;
					}
				}
			}
			if(achouMaior){
				aux = vet[i];
				vet[i] = vet[posMaior];
				vet[posMaior] = aux;
			}	
		}

		for(i = 0; i < p->nSalas; i++){
			disciplinaSala[(*itDisc)->numeroSequencial][i] = vet[i];	
		}

	}
}

void Grasp::desalocarMemoria(){
	int i;

	for(i = 0; i < ordem; i++)
		free(lin[i].coluna);

	free(pais);
	free(fluxoPassado);
	free(lin);
}

void Grasp::limparFluxo_e_Pais(int nDisciplinas){
	register int i;

	for(i = 0; i < nDisciplinas; i++)
		fluxoPassado[i] = 0;

	for(; i < ordem; i++)
		pais[i] = -1;
}


void Grasp::alocarAulasEncontradasPelofluxoMaximoEmRedes(Individuo* ind,int linha, int coluna){

	list<Curriculo*>::iterator itCurr;
	list<Aula*>::iterator itAula;
	Alocacao* aloc;
	Aula* aula;
	unsigned int iAloc;
    itAula = lin[linha].disc->aulas.begin();
    aula = *itAula;
    itAula++;

	lin[linha].disc->decremento();
    for( iAloc=0; iAloc < ind->horariosVazios.size(); iAloc++ ) {
        if( ind->horariosVazios[iAloc]->sala->numeroSequencial == lin[linha].coluna[coluna].timeslot->sala->numeroSequencial && 
            ind->horariosVazios[iAloc]->horario->dia==lin[linha].coluna[coluna].timeslot->dia && 
            ind->horariosVazios[iAloc]->horario->periodo==lin[linha].coluna[coluna].timeslot->periodo){
            aloc = ind->horariosVazios[iAloc];
            aloc->aula = aula;
            ind->aulasAlocadas.push_back(aloc);
            ind->horariosVazios[iAloc] = ind->horariosVazios[ind->horariosVazios.size()-1];
            ind->horariosVazios.pop_back();
            ind->Alocacao_dias_utilizados[aloc->aula->disciplina->numeroSequencial][aloc->horario->dia]++;
            ind->Alocacao_salas_utilizadas[aloc->aula->disciplina->numeroSequencial][aloc->sala->numeroSequencial]++;
            ind->matrizProfessorHorarioQntd[aloc->aula->disciplina->professor->numeroSequencial][aloc->horario->horario]++;
            ind->matrizProfessorHorario[aloc->aula->disciplina->professor->numeroSequencial][aloc->horario->horario] = aloc;
            for( itCurr = aula->disciplina->curriculos.begin(); itCurr!=aula->disciplina->curriculos.end(); itCurr++){
                ind->Alocacao_horarios_utilizados_por_curriculo[(*itCurr)->numeroSequencial][aloc->horario->horario]++;
                ind->matrizAlocacaoCurriculoDiasPeriodos[(*itCurr)->numeroSequencial][aloc->horario->dia][aloc->horario->periodo] = aloc;
            }
            break;
        }
    }
}


int Grasp::dfs(Individuo *ind,int nDisciplinas, int *posDiscAtual){
	int j,lim,v;

	while(lin[0].coluna[*posDiscAtual].capacidade <= fluxoPassado[*posDiscAtual])
		(*posDiscAtual)++;

	v = *posDiscAtual;
	j = 0;
	
	while(j < nSalas){
		v = nDisciplinas + (nDiasXnPeriodos * disciplinaSala[j][lin[*posDiscAtual].disc->numeroSequencial]);
		lim = v + nDiasXnPeriodos;
		for(; v < lim; v++){
		    if((pais[v] == -1) && (lin[*posDiscAtual].coluna[v].capacidade > 0)){
		        if (ind->restricaoForte(lin[*posDiscAtual].disc,lin[*posDiscAtual].coluna[v].timeslot->dia,lin[*posDiscAtual].coluna[v].timeslot->periodo)){ /* para verificar indisponibilidade*/
		            pais[v] = *posDiscAtual;
		            alocarAulasEncontradasPelofluxoMaximoEmRedes(ind,*posDiscAtual,v);
					return 0;
		       }
		    }    
		}
		j++;
	}

	return 1;
}

int Grasp::dfsSemIf(Individuo *ind,int nDisciplinas, int *posDiscAtual){
	int j,lim,v;

	while(lin[0].coluna[*posDiscAtual].capacidade <= fluxoPassado[*posDiscAtual])
		(*posDiscAtual)++;

	v = *posDiscAtual;
	j = 0;
	
	while(j < nSalas){
		v = nDisciplinas + (nDiasXnPeriodos * disciplinaSala[j][lin[*posDiscAtual].disc->numeroSequencial]);
		lim = v + nDiasXnPeriodos;
		for(; v < lim; v++){
		    if((pais[v] == -1) && (lin[*posDiscAtual].coluna[v].capacidade > 0)){
		        pais[v] = *posDiscAtual;
		        alocarAulasEncontradasPelofluxoMaximoEmRedes(ind,*posDiscAtual,v);
	  			return 0;
		    }    
		}
		j++;
	}

	return 1;
}



int Grasp::bfs(Individuo *ind,int nDisciplinas, int *posDiscAtual){
    int priDisc = -1, priTimes = -1;
    int i,j,v,lim;
   
    for(i = *posDiscAtual; i < nDisciplinas; i++)
    	if((priDisc == -1) && (fluxoPassado[i] < lin[0].coluna[i].capacidade))
    		priDisc = i;

    *posDiscAtual = priDisc;
    j = 0;
    while(j < nSalas){
    	v = nDisciplinas + (nDiasXnPeriodos * disciplinaSala[j][lin[*posDiscAtual].disc->numeroSequencial]);
		lim = v + nDiasXnPeriodos;
		for(; v < lim; v++){
		    if((pais[v] == -1) && (lin[*posDiscAtual].coluna[v].capacidade > 0)){
		        if (ind->restricaoForte(lin[*posDiscAtual].disc,lin[*posDiscAtual].coluna[v].timeslot->dia,lin[*posDiscAtual].coluna[v].timeslot->periodo)){ /* para verificar indisponibilidade*/
		            if(priTimes == -1){
		            	priTimes = v;
		            }
		       }
		    }    
		}
		j++;
    }

    if(priTimes != -1){
		pais[priTimes] = *posDiscAtual;
        alocarAulasEncontradasPelofluxoMaximoEmRedes(ind,*posDiscAtual,priTimes);
		return 0;
	}

	return 1;
}

int Grasp::bfsSemIf(Individuo *ind,int nDisciplinas, int *posDiscAtual){
    int priDisc = -1, priTimes = -1;
    int i,j,v,lim;
   
    for(i = *posDiscAtual; i < nDisciplinas; i++)
    	if((priDisc == -1) && (fluxoPassado[i] < lin[0].coluna[i].capacidade))
    		priDisc = i;

    *posDiscAtual = priDisc;
    j = 0;
    while(j < nSalas){
    	v = nDisciplinas + (nDiasXnPeriodos * disciplinaSala[j][lin[*posDiscAtual].disc->numeroSequencial]);
		lim = v + nDiasXnPeriodos;
		for(; v < lim; v++){
		    if((pais[v] == -1) && (lin[*posDiscAtual].coluna[v].capacidade > 0)){
		            if(priTimes == -1){
		            	priTimes = v;
		            }
		    }    
		}
		j++;
    }

    if(priTimes != -1){
		pais[priTimes] = *posDiscAtual;
        alocarAulasEncontradasPelofluxoMaximoEmRedes(ind,*posDiscAtual,priTimes);
		return 0;
	}

	return 1;
}

int Grasp::fluxoMaximoEmRedesBfs(Individuo *ind){
    int posDiscAtual = 1;
   	int nAulasVerificadas = 0;
	int nAulasNaoAlocadas = 0;
	int nDisciplinas = (ind->p->nDisciplinas + 1);

    while(nAulasVerificadas < ind->p->nAulasTotal){
       	nAulasNaoAlocadas+= bfs(ind,nDisciplinas,&posDiscAtual);	
       	fluxoPassado[posDiscAtual]++;
        nAulasVerificadas++;
    }
   
    embaralharMatriz(ind->p->nDisciplinas);
    limparFluxo_e_Pais(nDisciplinas);
    
    return nAulasNaoAlocadas;
}

int Grasp::fluxoMaximoEmRedesBfsSemIf(Individuo *ind){
    int posDiscAtual = 1;
   	int nAulasVerificadas = 0;
	int nAulasNaoAlocadas = 0;
	int nDisciplinas = (ind->p->nDisciplinas + 1);

    while(nAulasVerificadas < ind->p->nAulasTotal){
       	nAulasNaoAlocadas+= bfsSemIf(ind,nDisciplinas,&posDiscAtual);	
       	fluxoPassado[posDiscAtual]++;
        nAulasVerificadas++;
    }
   
    embaralharMatriz(ind->p->nDisciplinas);
    limparFluxo_e_Pais(nDisciplinas);
    
    return nAulasNaoAlocadas;
}

int Grasp::fluxoMaximoEmRedesDfs(Individuo *ind){
    int posDiscAtual = 1;
   	int nAulasVerificadas = 0;
	int nAulasNaoAlocadas = 0;
	int nDisciplinas = (ind->p->nDisciplinas + 1);

   
    while(nAulasVerificadas < ind->p->nAulasTotal){
       	nAulasNaoAlocadas+= dfs(ind,nDisciplinas,&posDiscAtual);	
       	fluxoPassado[posDiscAtual]++;
        nAulasVerificadas++;
    }
   
    embaralharMatriz(ind->p->nDisciplinas);
    limparFluxo_e_Pais(nDisciplinas);
    
    return nAulasNaoAlocadas;
}

int Grasp::fluxoMaximoEmRedesDfsSemIf(Individuo *ind){
    int posDiscAtual = 1;
   	int nAulasVerificadas = 0;
	int nAulasNaoAlocadas = 0;
	int nDisciplinas = (ind->p->nDisciplinas + 1);

   
    while(nAulasVerificadas < ind->p->nAulasTotal){
       	nAulasNaoAlocadas+= dfsSemIf(ind,nDisciplinas,&posDiscAtual);	
       	fluxoPassado[posDiscAtual]++;
        nAulasVerificadas++;
    }
   
    embaralharMatriz(ind->p->nDisciplinas);
    limparFluxo_e_Pais(nDisciplinas);
    
    return nAulasNaoAlocadas;
}
