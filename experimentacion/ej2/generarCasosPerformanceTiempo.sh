# Este archivo tiene que estar en la carpeta gen_instancias


# Creo una carpeta en donde voy a poner los tests
# mkdir CasosPerformanceTiempo


# Test 1
# Genero instancias con cantidad de gimnasios crecientes 
# 		hasta la cantidad de paradas (p).
# p oscila entre 1 y 7.
# g va desde 1 a p
# mochila fija = 6
# posiciones aleatorias
# dificultad 50
# x = 30, y = 30
# mkdir CasosPerformanceTiempo/Caso1
echo "Generar Test Caso 1"
for ((i = 1; i <= 7; i++))
do
	for ((j = 1; j <= $i; j++))
	do
		../gen_instancias/gen 30 30 $j $i 6 50 $j
		mv mapa CasosPerformanceTiempo/Caso1/caso1-p$i-g$j
	done
done


# Test 2
# Genero instancias con cantidad de paradas crecientes 
# 		hasta la cantidad de gimnasios (g).
# g oscila entre 1 y 7.
# p va desde 1 a g
# mochila fija = 6
# posiciones aleatorias
# dificultad 50
# x = 30, y = 30
# mkdir CasosPerformanceTiempo/Caso2
echo "Generar Test Caso 2"
for ((i = 1; i <= 7; i++))
do
	for ((j = 1; j <= $i; j++))
	do
		../gen_instancias/gen 30 30 $i $j 6 50 $j
		mv mapa CasosPerformanceTiempo/Caso2/caso2-g$i-p$j
	done
done


# Test 3
# En una instancia fija de 14 nodos, aumento gimnasios y
# 		disminuyo paradas
# mochila fija = 6
# posiciones aleatorias
# dificultad 50
# x = 30, y = 30
# mkdir CasosPerformanceTiempo/Caso3
echo "Generar Test Caso 3"
for i in {1..13}; do
	../gen_instancias/gen 30 30 $i $((14 - i)) 6 50 $i;
	mv mapa CasosPerformanceTiempo/Caso3/caso3-$i;
done;


# Test 4
# Subimos de a uno la cantidad de gimnasios y paradas
# 		hasta 7 cada una
# mochila fija = 6
# posiciones aleatorias
# dificultad 50
# x = 30, y = 30
# mkdir CasosPerformanceTiempo/Caso4
echo "Generar Test Caso 4"
for i in {1..7}; do
	../gen_instancias/gen 30 30 $i $i 6 50 $i;
	mv mapa CasosPerformanceTiempo/Caso4/caso4-$i;
done;


# Test 5
# Aumento dificultad de 0 a 100
# Instancia fija de 10 nodos. 
# g = 5; p = 5
# mochila fija = 6
# posiciones aleatorias
# x = 30, y = 30
# mkdir CasosPerformanceTiempo/Caso5
echo "Generar Test Caso 5"
for i in {1..100}; do
	../gen_instancias/gen 30 30 5 5 6 $i $i;
	mv mapa CasosPerformanceTiempo/Caso5/caso5-$i;
done;