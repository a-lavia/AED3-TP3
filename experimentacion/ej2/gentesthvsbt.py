import random

def posicionestest2(file, poder):
	file.write("2 1 " + str(poder) + "\n")
	file.write("2 3 " + str(poder) + "\n")
	file.write("4 5 " + str(poder) + "\n")
	file.write("6 1 " + str(poder) + "\n")
	file.write("7 3 " + str(poder) + "\n")
	file.write("1 1\n")
	file.write("1 3\n")
	file.write("3 5\n")
	file.write("5 1\n")
	file.write("6 3\n")
	return


def posaleat():
	pos = []
	for i in range(0,10):
		if i < 5:
			pos.append((str(random.randint(0,5)), str(random.randint(0,5))))
		else:
			pos.append((str(random.randint(10,15)), str(random.randint(10,15))))
	return pos


def test1a():
	"""
	Paradas lejos de los gym
	Poder creciente desde 1 hasta 3
	Mochila fija = 3
	10 nodos -> 5 y 5
	"""
	pos = posaleat()
	for i in range(1,4):
		file = open("HvsBT/test1a_" + str(i), "w+")
		file.write("5 5 3\n")
		
		for j in range(5,10):
			file.write(str(pos[j][0]) + " " + str(pos[j][1]) + " " + str(i) + "\n")

		for k in range(0,5):
			file.write(str(pos[k][0]) + " " + str(pos[k][1]) + "\n")
		
		file.close()

	return


def test1b():
	"""
	Paradas lejos de los gym
	Mochila variable de 3 a 15
	Poder gym fijo = 3
	10 nodos -> 5 y 5
	"""
	pos = posaleat()
	for i in range(3,16):
		file = open("HvsBT/test1b_" + str(i), "w+")
		file.write("5 5 " + str(i) + "\n")

		for j in range(5,10):
			file.write(str(pos[j][0]) + " " + str(pos[j][1]) + " 3\n")

		for k in range(0,5):
			file.write(str(pos[k][0]) + " " + str(pos[k][1]) + "\n")

		file.close()

	return


def test2a():
	"""
	Par parada y gym, pares todos dispersos en mapa
	Poder creciente desde 1 hasta 3
	Mochila fija = 3
	10 nodos -> 5 y 5
	"""
	for i in range(1,4):
		file = open("HvsBT/test2a_" + str(i), "w+")
		file.write("5 5 3\n")
		posicionestest2(file, i)
		file.close()

	return


def test2b():
	"""
	Par parada y gym, pares todos dispersos en mapa
	Poder fijo = 2
	Mochila variable = 3 a 15
	10 nodos -> 5 y 5
	"""
	for i in range(3,16):
		file = open("HvsBT/test2b_" + str(i), "w+")
		file.write("5 5 " + str(i) + "\n")
		posicionestest2(file, 2)
		file.close()

	return


def test3a():
	"""
	Solo gimnasios con poder 0. posiciones aleat.
	Mochila = 0 (no importa)
	"""
	file = open("HvsBT/test3a", "w+")
	file.write("5 5 0\n")
	
	for i in range(1,11):
		file.write(str(random.randint(1,20)) + " " + str(random.randint(1,20)) + " " + "0\n")

	file.close()
	return


def test3b():
	"""
	Solo gimnasios con poder 0. En rectangulo
	Mochila = 0 (no importa)
	"""
	file = open("HvsBT/test3b", "w+")
	file.write("5 5 0\n")
	
	for i in range(2,5):
		file.write(str(i) + " 4 0\n")

	for i in range(2,5):
		file.write(str(i) +  " 1 0\n")

	file.write("1 3 0\n")
	file.write("1 2 0\n")
	file.write("5 3 0\n")
	file.write("5 2 0\n")

	file.close()
	return


def test4a():
	"""
	Posiciones aleatorias - 5 gym y 5 paradas
	posiciones con valores entre 1 y 20
	poder gym valor fijo = 3
	Mochila entre 3 y 15
	"""
	for i in range(3,16):
		file = open("HvsBT/test4a_" + str(i), "w+")
		file.write("5 5 " + str(i) +"\n")
		for j in range(0,5):
			file.write(str(random.randint(1,20)) + " " + str(random.randint(1,20)) + " 3\n")
		for k in range(0,5):
			file.write(str(random.randint(1,20)) + " " + str(random.randint(1,20)) + "\n")
		file.close()

	return


def test4b():
	"""
	Posiciones aleatorias - 5 gym y 5 paradas
	posiciones con valores entre 1 y 20
	poder gym aleat entre 1 y 3
	Mochila = 3
	"""
	file = open("HvsBT/test4b", "w+")
	file.write("5 5 3\n")
	for i in range(0,5):
		file.write(str(random.randint(1,20)) + " " +  str(random.randint(1,20)) + " " + str(random.randint(1,3)) + "\n")
	for j in range(0,5):
		file.write(str(random.randint(1,20)) + " " +  str(random.randint(1,20)) + "\n")

	file.close()
	return


def test5():
	"""
	Caso donde tiene solucion pero la heuristica no la encuentra
	"""
	file = open("HvsBT/test5", "w+")
	file.write("5 5 5\n")
	poder = [4,5,3,2,1]
	for i in range(0,5):
		file.write(str(random.randint(1,20)) + " " +  str(random.randint(1,20)) + " " + str(poder[i]) + "\n")
	for j in range(0,5):
		file.write(str(random.randint(1,20)) + " " +  str(random.randint(1,20)) + "\n")

	file.close()
	return


# ************************************************************


test1a()
test1b()
test2a()
test2b()
test3a()
test3b()
test4a()
test4b()
test5()

