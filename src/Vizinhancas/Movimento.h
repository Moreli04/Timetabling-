#ifndef MOVIMENTO_H_
#define MOVIMENTO_H_

#include <stdlib.h>

class Individuo;
class Alocacao;

class Movimento {
public:
	Individuo* ind;
	Alocacao* a1;
	Alocacao* a2;
	int deltaFit;
	int deltaHard, deltaSoft1, deltaSoft2, deltaSoft3, deltaSoft4;
	unsigned int tipoMovimento;

	Movimento(){ ind = NULL; deltaFit = deltaHard = deltaSoft1 = deltaSoft2 = deltaSoft3 = deltaSoft4 = 0;tipoMovimento = 0; a1 = a2 = NULL;};
	virtual void aplicaMovimento(){};
	virtual void desfazMovimento(){};

	virtual ~Movimento(){};
};

#endif /* MOVIMENTO_H_ */
