#include "Curriculo.h"

#include <string.h>

Curriculo::Curriculo(char* piNome, int i, int pNumDisc) {
	numeroSequencial = i;
	strcpy(nome, piNome);
	numeroDisciplinas = pNumDisc;
}

Curriculo::~Curriculo() {
	// TODO Auto-generated destructor stub
}

