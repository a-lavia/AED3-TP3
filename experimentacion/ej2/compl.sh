echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;

# Corro el test1 de complejidad
for i in {1..5000};
	do
		echo "Corriendo caso $i de test1";
		./exp < Complejidad/testcasouno$i > /dev/null;
	done;
mv salida.csv test1complejidad.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# Corro el test2 de complejidad
for i in {1..5000};
	do
		echo "Corriendo caso $i de test2";
		./exp < Complejidad/testcasodos$i > /dev/null;
	done;
mv salida.csv test2complejidad.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# Corro el test3 de complejidad
for i in {1..5000};
	do
		echo "Corriendo caso $i de test3";
		./exp < Complejidad/testcasotres$i > /dev/null;
	done;
mv salida.csv test3complejidad.csv

echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# Corro el test4 de complejidad
for i in {1..5000};
	do
		echo "Corriendo caso $i de test4";
		./exp < Complejidad/testcasocuatro$i > /dev/null;
	done;
mv salida.csv test4complejidad.csv