echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 1a
echo "TEST 1a";
for i in {1..3};
	do
	./exp < HvsBT/test1a_$i;
	../ej1/exp < HvsBT/test1a_$i;
done;
echo "TEST 1a completo";
mv salida.csv HvsBT/test1aH.csv
mv ../ej1/salida.csv HvsBT/test1aBT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 1b
echo "TEST 1b";
for i in {3..15};
	do
	./exp < HvsBT/test1b_$i; 
	../ej1/exp < HvsBT/test1b_$i;
done;
echo "TEST 1b completo";
mv salida.csv HvsBT/test1bH.csv
mv ../ej1/salida.csv HvsBT/test1bBT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 2a
echo "TEST 2a";
for i in {1..3};
	do
	./exp < HvsBT/test2a_$i; 
	../ej1/exp < HvsBT/test2a_$i;
done;
echo "TEST 2a completo";
mv salida.csv HvsBT/test2aH.csv
mv ../ej1/salida.csv HvsBT/test2aBT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 2b
echo "TEST 2b";
for i in {3..15};
	do 
	./exp < HvsBT/test2b_$i; 
	../ej1/exp < HvsBT/test2b_$i;
done;
echo "TEST 2b completo";
mv salida.csv HvsBT/test2bH.csv
mv ../ej1/salida.csv HvsBT/test2bBT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 3a y 3b
echo "TEST 3a y 3b";
./exp < HvsBT/test3a;
../ej1/exp < HvsBT/test3a;
mv salida.csv HvsBT/test3aH.csv
mv ../ej1/salida.csv HvsBT/test3aBT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
./exp < HvsBT/test3b;
../ej1/exp < HvsBT/test3b;
echo "TEST 3a y 3b completos";
mv salida.csv HvsBT/test3bH.csv
mv ../ej1/salida.csv HvsBT/test3bBT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 4a
echo "TEST 4a";
for i in {3..15}; 
	do
	./exp < HvsBT/test4a_$i; 
	../ej1/exp < HvsBT/test4a_$i;
done;
echo "TEST 4a completo";
mv salida.csv HvsBT/test4aH.csv
mv ../ej1/salida.csv HvsBT/test4aBT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 4b
echo "TEST 4b";
./exp < HvsBT/test4b;
../ej1/exp < HvsBT/test4b;
echo "TEST 4b completo";
mv salida.csv HvsBT/test4bH.csv
mv ../ej1/salida.csv HvsBT/test4bBT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 5
echo "TEST 5";
./exp < HvsBT/test5;
../ej1/exp < HvsBT/test5;
echo "TEST 5 completo";
mv salida.csv HvsBT/test5H.csv
mv ../ej1/salida.csv HvsBT/test5BT.csv


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> ../ej1/salida.csv
# TEST 6
# Creo los test con el siguiente codigo en gen_instancias
# for x in {1..10}; do ./gen 30 30 $x $((10 - x)) 5 100 $x; mv mapa test6_$x; done
echo "TEST 6";
for i in {1..10};
	do
	./exp < HvsBT/test6_$i; 
	../ej1/exp < HvsBT/test6_$i;
done;
echo "TEST 6 completo";
mv salida.csv HvsBT/test6H.csv
mv ../ej1/salida.csv HvsBT/test6BT.csv