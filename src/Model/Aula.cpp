#include "Aula.h"

#include <stdio.h>
#include "Disciplina.h"

Aula::Aula(int i, Disciplina* d) {
	numero = i;
	disciplina = d;
}

void Aula::imprime(){
	printf("Aula %d da disciplina %s\n", numero, disciplina->nome);
};
