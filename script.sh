#!/bin/bash
reset

cd src
mkdir -p bin
make
cd validator
g++ tabela1.cpp -o tabela1
g++ tabela2.cpp -o tabela2
g++ agruparDadosTabela1.cpp -o agruparDadosTabela1
g++ agruparDadosTabela2.cpp -o agruparDadosTabela2
cd ..
cd ../src

mkdir -p ../results
mkdir -p ../tests
mkdir -p ../arquivosTemporarios
mkdir -p ../tests/summaryperinstance
mkdir -p ../arquivosTemporarios/resumo

seeds=( 1 2 3 4 5 6 7 8 9 10 )
testes=( _BLSI_ _BLCI_ _BPSI_ _BPCI_)
instances=( comp01 comp02 comp03 comp04 comp05 comp06 comp07 comp08 comp09 comp10 comp11 comp12 comp13 comp14 comp15 comp16 comp17 comp18 comp19 comp20 comp21 )

title="$instance"

for teste in ${testes[@]} ; do
	echo "testing $teste"
	#Cria o diretório onde vão ficar os resultados
	mkdir -p ../tests/$teste

	#Executa as instâncias para todas as seeds
	for instance in ${instances[@]} ; do
			echo "Instance $instance"
			instancia=instances/$instance.ctt

			for seed in ${seeds[@]} ; do
				resultado=../results/$teste.$instance.$seed.res
				saida=../tests/$teste/$instance-$seed.dat

				if [ $teste = _BLSI_ ]; then
					./grasp $instancia 0 $saida $resultado > $saida
				elif [ $teste = _BLCI_ ]; then
					./grasp $instancia 1 $saida $resultado > $saida
				elif [ $teste = _BPSI_ ]; then
					./grasp $instancia 2 $saida $resultado > $saida
				elif [ $teste = _BPCI_ ]; then
					./grasp $instancia 3 $saida $resultado > $saida
				else
				  echo "Invalid test ($teste)"
				fi

				
			done
			cat ../tests/$teste/$instance-* > ../tests/summaryperinstance/$teste-$instance.dat
	done
done

echo "parte 2"

for teste in ${testes[@]} ; do
	for instance in ${instances[@]} ; do
			instancia=../src/instances/$instance.ctt
			for seed in ${seeds[@]} ; do
				resultado=../results/$teste.$instance.$seed.res
				saida=../arquivosTemporarios/$teste.$instance.$seed.res
				#echo ./src/validator/validator $instancia $resultado
				./validator/validator $instancia $resultado >> $saida
			done
	done
done


echo "parte 3 -> Encontrar a media de tempo de construcao e a melhor FO de cada uma das 10 execucoes"

for teste in ${testes[@]} ; do
	mkdir -p ../arquivosTemporarios/resumo/$teste
	for instance in ${instances[@]} ; do
			for seed in ${seeds[@]} ; do
				resultado=../tests/$teste/$instance-$seed.dat
				saida=../arquivosTemporarios/resumo/$teste/$instance.dat
				#echo $saida
				#echo $resultado
                ./validator/ObtemDados $resultado >> $saida
			done
	done
done

echo "parte 4 -> Criar arquivo com media de tempo de construcao e de fo para cada teste"

for teste in ${testes[@]} ; do
	mkdir -p ../tabelas/tabela1/$teste
	for instance in ${instances[@]} ; do
		resultado=../arquivosTemporarios/resumo/$teste/$instance.dat
		saida=../tabelas/tabela1/$teste/media.dat
        ./validator/tabela1 $resultado >> $saida	
	done
done


echo "parte 5 -> Criar arquivo com media de tempo de construcao e de fo para cada teste"

for teste in ${testes[@]} ; do
	mkdir -p ../tabelas/tabela2/$teste
	saida=../tabelas/tabela2/$teste/info.dat
	for instance in ${instances[@]} ; do
		resultado=../tests/summaryperinstance/$teste-$instance.dat
        ./validator/tabela2 $resultado >> $saida	
	done
done

echo "parte 6 -> Agrupar dados tabela 1"
saida=../tabelas/tabela1/dados
./validator/agruparDadosTabela1 >> $saida	

echo "parte 7 -> Agrupar dados tabela 2"
saida=../tabelas/tabela2/dados
./validator/agruparDadosTabela2 >> $saida	
