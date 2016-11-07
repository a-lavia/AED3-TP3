# Este archivo hay que ponerlo en la carpeta gen_instancias y luego ejecutar.


# Casos con gym moviendose entre 1 y 5000
# Paradas fijas = 5000
# Mochila fija = 6
echo "generar testcasouno";
for i in {1..5000};
	do
	./gen 1000 1000 $i 5000 6 100 $i;
	mv mapa ../ej2/Complejidad/testcasouno$i;
	done;
echo "testcasouno terminados";


echo "generar testcasodos";
# Caso con paradas variables cambiando entre 1 y 5000
# Gimnasios fijos = 5000
# Mochila fija  = 6
for i  in {1..5000};
	do
	./gen 1000 1000 5000 $i 6 100 $i;
	mv mapa ../ej2/Complejidad/testcasodos$i;
	done;
echo "testcasodos terminado";


echo "testcasotres generar";
# Instancia fija de 10000 nodos aumentando y disminuyendo variables
# Mochila fija = 6
for i in {1..5000};
	do
	./gen 1000 1000 $i $((5000 - i)) 100 $i;
	mv mapa ../ej2/Complejidad/testcasotres$i;
	done;
echo "testcasotres terminado";


echo "testcasocuatro generar";
# Caso aumento de nodos y paradas al mismo tiempo
for i in {1..5000};
	do
	./gen 1000 1000 $i $i 100 $i;
	mv mapa ../ej2/Complejidad/testcasocuatro$i;
	done;
echo "testcasocuatro terminado";
