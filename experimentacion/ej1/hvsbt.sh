# echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# # TEST 1a
# echo "TEST 1a";
# for i in {1..3};
# 	do
# 	./ej1Exp.out < ../ej2/HvsBT/test1a_$i > /dev/null;
# done;
# echo "TEST 1a completo";
# mv salida.csv ../ej2/HvsBT/test1aBT.csv;


echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# TEST 1b
echo "TEST 1b";
for i in {1..10};
	do
	./ej1Exp.out < ../ej2/HvsBT/test1b_$i > /dev/null; 
done;
echo "TEST 1b completo";
mv salida.csv ../ej2/HvsBT/test1bBT.csv;


# echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# # TEST 2a
# echo "TEST 2a";
# for i in {1..3};
# 	do
# 	./ej1Exp.out < ../ej2/HvsBT/test2a_$i > /dev/null; 
# done;
# echo "TEST 2a completo";
# mv salida.csv ../ej2/HvsBT/test2aBT.csv;


# echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# # TEST 2b
# echo "TEST 2b";
# for i in {3..15};
# 	do 
# 	./ej1Exp.out < ../ej2/HvsBT/test2b_$i > /dev/null; 
# done;
# echo "TEST 2b completo";
# mv salida.csv ../ej2/HvsBT/test2bBT.csv;


# echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# # TEST 3a y 3b
# echo "TEST 3a y 3b";
# ./ej1Exp.out < ../ej2/HvsBT/test3a > /dev/null;
# mv salida.csv ../ej2/HvsBT/test3aBT.csv;


# echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# ./ej1Exp.out < ../ej2/HvsBT/test3b > /dev/null;
# echo "TEST 3a y 3b completos";
# mv salida.csv ../ej2/HvsBT/test3bBT.csv;


# echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# # TEST 4
# echo "TEST 4";
# for i in {0..99}; 
# 	do
# 	./ej1Exp.out < ../ej2/HvsBT/test4_$i > /dev/null;
# done;
# echo "TEST 4 completo";
# mv salida.csv ../ej2/HvsBT/test4BT.csv;

# echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# # TEST 5
# echo "TEST 5";
# ./ej1Exp.out < ../ej2/HvsBT/test5 > /dev/null;
# echo "TEST 5 completo";
# mv salida.csv ../ej2/HvsBT/test5BT.csv;


# echo "gimnasios,paradas,mochila,distancia,cantciclos" >> salida.csv;
# # TEST 6
# # Creo los test con el siguiente codigo en gen_instancias
# # for x in {1..10}; do ./gen 30 30 $x $((10 - x)) 5 100 $x; mv mapa test6_$x; done
# echo "TEST 6";
# for i in {1..9};
# 	do
# 	./ej1Exp.out < ../ej2/HvsBT/test6_$i > /dev/null;
# done;
# echo "TEST 6 completo";
# mv salida.csv ../ej2/HvsBT/test6BT.csv;
