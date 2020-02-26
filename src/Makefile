all: GRASP Model Restricoes BuscaLocal Movimentos
	g++ -g -O3 -o grasp bin/*.o -lm -Wall
	
GRASP: bin/GeraSolucacoInicial.o bin/Grasp.o bin/TimeTabling.o 
bin/GeraSolucacoInicial.o: GeraSolucacoInicial.cpp
	g++ -Wall -g -O3 -c GeraSolucacoInicial.cpp -o bin/GeraSolucacoInicial.o
bin/Grasp.o: Grasp.cpp
	g++ -Wall -g -O3 -c Grasp.cpp -o bin/Grasp.o
bin/TimeTabling.o: TimeTabling.cpp
	g++ -Wall -g -O3 -c TimeTabling.cpp -o bin/TimeTabling.o
	
Model: bin/MeuTimeslot.o bin/Alocacao.o bin/Individuo.o bin/Disciplina.o bin/Professor.o bin/Restricao.h.gch bin/Timeslot.o bin/Aula.o bin/Curriculo.o bin/Problema.o bin/Sala.o
bin/MeuTimeslot.o: Model/MeuTimeslot.cpp
	g++ -Wall -g -O3 -c Model/MeuTimeslot.cpp -o bin/MeuTimeslot.o
bin/Alocacao.o: Model/Alocacao.cpp 
	g++ -Wall -g -O3 -c Model/Alocacao.cpp -o bin/Alocacao.o
bin/Individuo.o: Model/Individuo.cpp 
	g++ -Wall -g -O3 -c Model/Individuo.cpp -o bin/Individuo.o
bin/Disciplina.o: Model/Disciplina.cpp 
	g++ -Wall -g -O3 -c Model/Disciplina.cpp -o bin/Disciplina.o
bin/Professor.o: Model/Professor.cpp 
	g++ -Wall -g -O3 -c Model/Professor.cpp -o bin/Professor.o
bin/Restricao.h.gch: Restricoes/Restricao.h 
	g++ -Wall -g -O3 -c Restricoes/Restricao.h -o bin/Restricao.h.gch
bin/Timeslot.o: Model/Timeslot.cpp 
	g++ -Wall -g -O3 -c Model/Timeslot.cpp -o bin/Timeslot.o
bin/Aula.o: Model/Aula.cpp
	g++ -Wall -g -O3 -c Model/Aula.cpp -o bin/Aula.o
bin/Curriculo.o: Model/Curriculo.cpp
	g++ -Wall -g -O3 -c Model/Curriculo.cpp -o bin/Curriculo.o
bin/Problema.o: Model/Problema.cpp
	g++ -Wall -g -O3 -c Model/Problema.cpp -o bin/Problema.o
bin/Sala.o: Model/Sala.cpp
	g++ -Wall -g -O3 -c Model/Sala.cpp -o bin/Sala.o
	
Restricoes: bin/RestricaoForte3Indisponibilidade.o bin/RestricaoForte4AulasConflitantes.o bin/RestricaoFraca1RoomCapacity.h.gch bin/RestricaoFraca2MinimumWorkingDays.o bin/RestricaoFraca3CurriculumCompactness.o bin/RestricaoFraca4RoomStability.o
bin/RestricaoForte3Indisponibilidade.o: Restricoes/RestricaoForte3Indisponibilidade.cpp 
	g++ -Wall -g -O3 -c Restricoes/RestricaoForte3Indisponibilidade.cpp -o bin/RestricaoForte3Indisponibilidade.o
bin/RestricaoForte4AulasConflitantes.o: Restricoes/RestricaoForte4AulasConflitantes.cpp
	g++ -Wall -g -O3 -c Restricoes/RestricaoForte4AulasConflitantes.cpp -o bin/RestricaoForte4AulasConflitantes.o
bin/RestricaoFraca1RoomCapacity.h.gch: Restricoes/RestricaoFraca1RoomCapacity.h
	g++ -Wall -g -O3 -c Restricoes/RestricaoFraca1RoomCapacity.h -o bin/RestricaoFraca1RoomCapacity.h.gch
bin/RestricaoFraca2MinimumWorkingDays.o: Restricoes/RestricaoFraca2MinimumWorkingDays.cpp
	g++ -Wall -g -O3 -c Restricoes/RestricaoFraca2MinimumWorkingDays.cpp -o bin/RestricaoFraca2MinimumWorkingDays.o
bin/RestricaoFraca3CurriculumCompactness.o: Restricoes/RestricaoFraca3CurriculumCompactness.cpp
	g++ -Wall -g -O3 -c Restricoes/RestricaoFraca3CurriculumCompactness.cpp -o bin/RestricaoFraca3CurriculumCompactness.o
bin/RestricaoFraca4RoomStability.o: Restricoes/RestricaoFraca4RoomStability.cpp
	g++ -Wall -g -O3 -c Restricoes/RestricaoFraca4RoomStability.cpp -o bin/RestricaoFraca4RoomStability.o
		
Movimentos: bin/Movimento.h.gch bin/Move.o bin/Swap.o bin/LectureMove3.o 
bin/Movimento.h.gch: Vizinhancas/Movimento.h 
	g++ -Wall -g -O3 -c Vizinhancas/Movimento.h -o bin/Movimento.h.gch
bin/Move.o: Vizinhancas/Move.cpp 
	g++ -Wall -g -O3 -c Vizinhancas/Move.cpp -o bin/Move.o
bin/Swap.o: Vizinhancas/Swap.cpp 
	g++ -Wall -g -O3 -c Vizinhancas/Swap.cpp -o bin/Swap.o
bin/LectureMove3.o: Vizinhancas/LectureMove3.cpp
	g++ -Wall -g -O3 -c Vizinhancas/LectureMove3.cpp -o bin/LectureMove3.o

BuscaLocal: bin/SimulatedAnnealing.o
bin/SimulatedAnnealing.o: BuscaLocal/SimulatedAnnealing.cpp
	g++ -Wall -g -O3 -c BuscaLocal/SimulatedAnnealing.cpp -o bin/SimulatedAnnealing.o
	
clean:
	rm bin/*
	
