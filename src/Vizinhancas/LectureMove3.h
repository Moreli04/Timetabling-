#ifndef LectureMove3_H_
#define LectureMove3_H_

#include "Movimento.h"
#include "Swap.h"
#include "Move.h"
#include "../Model/Individuo.h"
#include "../Model/Problema.h"

class LectureMove3 : public Movimento{
public:
	LectureMove3(Individuo* piInd);
	void aplicaMovimento();
	~LectureMove3();

private:
	Movimento* m;
	int pos1,pos2;
};

#endif /* LectureMove3_H_ */
