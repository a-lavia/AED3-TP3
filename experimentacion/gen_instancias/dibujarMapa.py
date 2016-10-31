#!/usr/bin/env python

import sys
import matplotlib.pyplot as plt
import networkx as nx

#Constantes
tamNodoInicial = 200
tamNodoGym = 100
tamNodoParada = 60
tamBordeNodo = 0.5

colorGym = "red"
colorParada = "green"

mostrarEtiqueta=True
tamFuente = 4

colorArista = "black"
alphaArista = 0.8
tamArista = 1.2


#Parseamos la entrada
mapaEntrada = open(sys.argv[1])
mapa = mapaEntrada.read().replace('\n', ' ').split(' ')
while '' in mapa: mapa.remove('')

dibujarCamino = len(sys.argv) == 3
if dibujarCamino:
	caminoSalida = open(sys.argv[2])
	camino = caminoSalida.read().replace('\n', ' ').split(' ')
	while '' in camino: camino.remove('')

#Creamos el grafo con sus nodos
mapaGimnasios = int(mapa[0])
mapaPokeParadas = int(mapa[1])
mapaNodos = mapaGimnasios + mapaPokeParadas


G = nx.Graph()
G.add_nodes_from(range(1, mapaNodos+1))

x = 0
nodosTam = []
nodosColor = []
nodosPos = {}
while x < mapaGimnasios:
	nodosTam.append(tamNodoGym)
	nodosColor.append(colorGym)
	nodosPos[x+1] = (int(mapa[3+x*3]), int(mapa[3+x*3+1]))
	x += 1

x = 0
while x < mapaPokeParadas:
	nodosTam.append(tamNodoParada)
	nodosColor.append(colorParada)
	nodosPos[mapaGimnasios+x+1] = (int(mapa[3+mapaGimnasios*3+x*2]), int(mapa[3+mapaGimnasios*3+x*2+1]))
	x += 1

#Agregamos las aristas
#distancia = float(camino[0])
if dibujarCamino:
	nodosRecorridos = int(camino[1])
	nodosTam[int(camino[2])-1] = tamNodoInicial
	x=0
	while x < nodosRecorridos-1:
		G.add_edge(int(camino[x+2]), int(camino[2+x+1]))
		x += 1

#Dibujamos
nx.draw(G, nodosPos, node_color=nodosColor, node_size=nodosTam, linewidths=tamBordeNodo, font_size=tamFuente, with_labels=mostrarEtiqueta, edge_color=colorArista, alpha=alphaArista, width=tamArista)
plt.savefig("mapa.png")
plt.savefig("mapa.pdf")
