#ifndef AULA_H_
#define AULA_H_

class Disciplina;

class Aula {
public:
	int numero;
	Disciplina* disciplina; //Ponteiro para a disciplina que ele pertence

	Aula(int i, Disciplina* d);
	void imprime();
};

#endif /* AULA_H_ */
