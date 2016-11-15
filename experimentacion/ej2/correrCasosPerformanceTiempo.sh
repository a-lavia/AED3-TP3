echo "Test 1 Heuristica"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for ((i = 1; i <= 7; i++))
do
	for ((j = 1; j <= $i; j++))
	do
		echo "Caso 1 Heuristica: $i <= 7, $j <= $i"
		./exp < CasosPerformanceTiempo/Caso1/caso1-p$i-g$j
	done
done
mv salida.csv CasosPerformanceTiempo/Caso1/resultadosH.csv
mv camino.csv CasosPerformanceTiempo/Caso1/resCaminosH.csv
echo "Fin Test 1 Heuristica"


echo "Test 1 Backtracking"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for ((i = 1; i <= 7; i++))
do
	for ((j = 1; j <= $i; j++))
	do
		echo "Caso 1 Backtracking: $i <= 7, $j <= $i"
		../ej1/ej1Exp.out < CasosPerformanceTiempo/Caso1/caso1-p$i-g$j
	done
done
mv salida.csv CasosPerformanceTiempo/Caso1/resultadosBT.csv
mv camino.csv CasosPerformanceTiempo/Caso1/resCaminosBT.csv
echo "Fin Test 1 Backtracking"


echo "Test 2 Heuristica"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for ((i = 1; i <= 7; i++))
do
	for ((j = 1; j <= $i; j++))
	do
		echo "Caso 2 Heuristica: $i <= 7, $j <= $i"
		./exp < CasosPerformanceTiempo/Caso2/caso2-g$i-p$j
	done
done
mv salida.csv CasosPerformanceTiempo/Caso2/resultadosH.csv
mv camino.csv CasosPerformanceTiempo/Caso2/resCaminosH.csv
echo "Fin Test 2 Heuristica"


echo "Test 2 Backtracking"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for ((i = 1; i <= 7; i++))
do
	for ((j = 1; j <= $i; j++))
	do
		echo "Caso 2 Backtracking: $i <= 7, $j <= $i"
		../ej1/ej1Exp.out < CasosPerformanceTiempo/Caso2/caso2-g$i-p$j
	done
done
mv salida.csv CasosPerformanceTiempo/Caso2/resultadosBT.csv
mv camino.csv CasosPerformanceTiempo/Caso2/resCaminosBT.csv
echo "Fin Test 2 Backtracking"


echo "Test 3 Heuristica"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for i in {1..13}; do
	echo "Caso 3 Heuristica: $i <= 13"
	./exp < CasosPerformanceTiempo/Caso3/caso3-$i
done;
mv salida.csv CasosPerformanceTiempo/Caso3/resultadosH.csv
mv camino.csv CasosPerformanceTiempo/Caso3/resCaminosH.csv
echo "Fin Test 3 Heuristica"


echo "Test 3 Backtracking"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for i in {1..13}; do
	echo "Caso 3 Backtracking: $i <= 13"
	../ej1/ej1Exp.out < CasosPerformanceTiempo/Caso3/caso3-$i
done;
mv salida.csv CasosPerformanceTiempo/Caso3/resultadosBT.csv
mv camino.csv CasosPerformanceTiempo/Caso3/resCaminosBT.csv
echo "Fin Test 3 Backtracking"


echo "Test 4 Heuristica"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for i in {1..7}; do
	echo "Caso 4 Heuristica: $i <= 7"
	./exp < CasosPerformanceTiempo/Caso4/caso4-$i
done;
mv salida.csv CasosPerformanceTiempo/Caso4/resultadosH.csv
mv camino.csv CasosPerformanceTiempo/Caso4/resCaminosH.csv
echo "Fin Test 4 Heuristica"


echo "Test 4 Backtracking"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for i in {1..7}; do
	echo "Caso 4 Backtracking: $i <= 7"
	../ej1/ej1Exp.out < CasosPerformanceTiempo/Caso4/caso4-$i
done;
mv salida.csv CasosPerformanceTiempo/Caso4/resultadosBT.csv
mv camino.csv CasosPerformanceTiempo/Caso4/resCaminosBT.csv
echo "Fin Test 4 Backtracking"


echo "Test 5 Heuristica"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for i in {1..100}; do
	echo "Caso 5 Heuristica: $i <= 100"
	./exp < CasosPerformanceTiempo/Caso5/caso5-$i;
done;
mv salida.csv CasosPerformanceTiempo/Caso5/resultadosH.csv
mv camino.csv CasosPerformanceTiempo/Caso5/resCaminosH.csv
echo "Fin Test 5 Heuristica"


echo "Test 5 Backtracking"
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
for i in {1..100}; do
	echo "Caso 5 Backtracking: $i <= 100"
	../ej1/ej1Exp.out < CasosPerformanceTiempo/Caso5/caso5-$i;
done;
mv salida.csv CasosPerformanceTiempo/Caso5/resultadosBT.csv
mv camino.csv CasosPerformanceTiempo/Caso5/resCaminosBT.csv
echo "Fin Test 5 Backtracking"