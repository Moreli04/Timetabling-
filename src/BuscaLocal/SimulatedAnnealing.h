#ifndef SIMULATEDANNEALING_H_
#define SIMULATEDANNEALING_H_

class Individuo;
class SimulatedAnnealing{
public:

	SimulatedAnnealing();
	~SimulatedAnnealing();

	Individuo* executa(Individuo* bestInd);
	Individuo* executa1(Individuo* bestInd);
};

#endif /* SIMULATEDANNEALING_H_ */
