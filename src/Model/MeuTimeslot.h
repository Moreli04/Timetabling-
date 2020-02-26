
#ifndef MEUTIMESLOT_H_
#define MEUTIMESLOT_H_

#include <string>
#include "Sala.h"

using namespace std;

class MeuTimeslot {
public:
	int dia;
	int periodo;
	Sala *sala;
	MeuTimeslot(int d, int p,Sala *s);

	int getDia();
};

#endif /* MEUTIMESLOT_H_ */
