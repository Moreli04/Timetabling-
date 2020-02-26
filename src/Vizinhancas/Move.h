#ifndef MOVE_H_
#define MOVE_H_

#include "Movimento.h"

#include "../Model/Individuo.h"
#include "../Model/Problema.h"

class Move : public Movimento{
public:
	Move(Individuo* piInd);
	Move(Individuo* piInd, int piPos1, int piPos2);
	virtual ~Move(){};
	void aplicaMovimento();
	void desfazMovimento();
	void aplicaMoveSemRecalculoFuncaoObjetivo();

private:
	int calculaDeltaFitMove(Problema* p);
};

#endif /* MOVE_H_ */
