#ifndef SWAP_H_
#define SWAP_H_

#include "Movimento.h"

#include "../Model/Individuo.h"
#include "../Model/Problema.h"

class Swap : public Movimento{
public:
	Swap(Individuo* piInd);
	Swap(Individuo* piInd, int piPos1, int piPos2);
	virtual ~Swap();
	void aplicaMovimento();
	void desfazMovimento();
	void aplicaMoveSemRecalculoFuncaoObjetivo();

private:
	int calculaDeltaFitSwap(Problema* p);
};

#endif /* SWAP_H_ */
