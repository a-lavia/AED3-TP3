# # Este archivo hay que ponerlo en la carpeta gen_instancias y luego ejecutar.

# mkdir ../ej2/Complejidad;

# # Casos con gym moviendose entre 1 y 250
# # Paradas fijas = 250
# # Mochila fija = 6
# echo "generar testcasouno";
# for i in {1..250};
# 	do
# 	./gen 500 500 $i 250 6 50 $i;
# 	mv mapa ../ej2/Complejidad/testcasouno$i;
# 	done;
# echo "testcasouno terminados";


# echo "generar testcasodos";
# # Caso con paradas variables cambiando entre 1 y 250
# # Gimnasios fijos = 250
# # Mochila fija  = 6
# for i  in {1..250};
# 	do
# 	./gen 500 500 250 $i 6 50 $i;
# 	mv mapa ../ej2/Complejidad/testcasodos$i;
# 	done;
# echo "testcasodos terminado";


# echo "testcasotres generar";
# # Instancia fija de 500 nodos aumentando y disminuyendo variables
# # Mochila fija = 6
# for i in {1..499};
# 	do
# 	./gen 500 500 $i $((500 - i)) 6 50 $i;
# 	mv mapa ../ej2/Complejidad/testcasotres$i;
# 	done;
# echo "testcasotres terminado";


# echo "testcasocuatro generar";
# # Caso aumento de nodos y paradas al mismo tiempo
# for i in {1..250};
# 	do
# 	./gen 500 500 $i $i 6 50 $i;
# 	mv mapa ../ej2/Complejidad/testcasocuatro$i;
# 	done;
# echo "testcasocuatro terminado";

echo "testcasocinco generar";
# Caso aumento de nodos y paradas al mismo tiempo
for i in {1..100};
	do
	./gen 500 500 100 100 18 $i $i;
	mv mapa ../ej2/Complejidad/testcasocinco$i;
	done;
echo "testcasocinco terminado";