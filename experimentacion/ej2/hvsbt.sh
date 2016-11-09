echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 1a
echo "TEST 1a";
for i in {1..3};
	do
	./exp < HvsBT/test1a_$i > /dev/null;
	./exp2 < HvsBT/test1a_$i > /dev/null;
done;
echo "TEST 1a completo";
mv salida.csv HvsBT/test1aH.csv;
mv salidaOtraH.csv HvsBT/test1aOtraH.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 1b
echo "TEST 1b";
for i in {3..15};
	do
	./exp < HvsBT/test1b_$i > /dev/null;
	./exp2 < HvsBT/test1b_$i > /dev/null;
done;
echo "TEST 1b completo";
mv salida.csv HvsBT/test1bH.csv;
mv salidaOtraH.csv HvsBT/test1bOtraH.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 2a
echo "TEST 2a";
for i in {1..3};
	do
	./exp < HvsBT/test2a_$i > /dev/null;
	./exp2 < HvsBT/test2a_$i > /dev/null;
done;
echo "TEST 2a completo";
mv salida.csv HvsBT/test2aH.csv;
mv salidaOtraH.csv HvsBT/test2aOtraH.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 2b
echo "TEST 2b";
for i in {3..15};
	do 
	./exp < HvsBT/test2b_$i > /dev/null;
	./exp2 < HvsBT/test2b_$i > /dev/null;
done;
echo "TEST 2b completo";
mv salida.csv HvsBT/test2bH.csv;
mv salidaOtraH.csv HvsBT/test2bOtraH.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 3a y 3b
echo "TEST 3a y 3b";
./exp < HvsBT/test3a > /dev/null;
./exp2 < HvsBT/test3a > /dev/null;
mv salida.csv HvsBT/test3aH.csv;
mv salidaOtraH.csv HvsBT/test3aOtraH.csv;

echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
./exp < HvsBT/test3b > /dev/null;
./exp2 < HvsBT/test3b > /dev/null;
echo "TEST 3a y 3b completos";
mv salida.csv HvsBT/test3bH.csv;
mv salidaOtraH.csv HvsBT/test3bOtraH.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 4a
echo "TEST 4a";
for i in {3..15}; 
	do
	./exp < HvsBT/test4a_$i > /dev/null;
	./exp2 < HvsBT/test4a_$i > /dev/null;
done;
echo "TEST 4a completo";
mv salida.csv HvsBT/test4aH.csv;
mv salidaOtraH.csv HvsBT/test4aOtraH.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 4b
echo "TEST 4b";
./exp < HvsBT/test4b > /dev/null;
./exp2 < HvsBT/test4b > /dev/null;
echo "TEST 4b completo";
mv salida.csv HvsBT/test4bH.csv;
mv salidaOtraH.csv HvsBT/test4bOtraH.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 5
echo "TEST 5";
./exp < HvsBT/test5 > /dev/null;
./exp2 < HvsBT/test5 > /dev/null;
echo "TEST 5 completo";
mv salida.csv HvsBT/test5H.csv;
mv salidaOtraH.csv HvsBT/test5OtraH.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salidaOtraH.csv;
# TEST 6
# Creo los test con el siguiente codigo en gen_instancias
# for x in {1..10}; do ./gen 30 30 $x $((10 - x)) 5 100 $x; mv mapa test6_$x; done
echo "TEST 6";
for i in {1..10};
	do
	./exp < HvsBT/test6_$i > /dev/null;
	./exp2 < HvsBT/test6_$i > /dev/null;
done;
echo "TEST 6 completo";
mv salida.csv HvsBT/test6H.csv;
mv salidaOtraH.csv HvsBT/test6OtraH.csv;
