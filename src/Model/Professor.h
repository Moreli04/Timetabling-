#ifndef PROFESSOR_H_
#define PROFESSOR_H_

class Alocacao;
class Professor {
public:
	int numeroSequencial;
	char nome[30];

	int nHorarios, nSalas;

	Professor(int piNHorarios, int piNSalas, int i, char* piNome);
	virtual ~Professor();
};

#endif /* PROFESSOR_H_ */
