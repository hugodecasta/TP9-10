#ifndef GRAPHE_H
#define GRAPHE_H

#include <fstream>
#include <string>
#include <ostream>
#include <iostream>
#include <vector>

using namespace std;

////////////////////////////// DATA & TYPE DEFINITIONS

typedef int vertex;
typedef struct Graph {
	unsigned width, height;
	vertex* grid;

} Graph;

typedef struct Pos {
    unsigned i, j;
} Pos;

typedef struct dijkstraNode {
	Pos position;
	Pos last;
	unsigned distance;
	
} dijkstraNode;
typedef vector<dijkstraNode> dijkstra_map;

enum orient {north, south, east, west, self};

enum color {white, grey, black};
typedef vector<color> v_status;

enum algorithm {dijkstra, profondeur, largeur};
typedef struct appParameters
{
	string filename;
	algorithm usedAlgorithm;
	bool useColor;
	bool drawMemory;
	bool useInput;
	float delay;
	
} appParameters;


////////////////////////////// METHODS

////GRAPHE
void initGraph(Graph& g, unsigned width, unsigned height);
bool loadGraph(string filename, Graph& g);
void pruneGraph(Graph& g);
void drawGraph(const Graph& g);

void setVertex(Graph& g, unsigned i, unsigned j, vertex v);
vertex getVertex(const Graph& g, unsigned i, unsigned j, orient o); // Le vertex que l'on veut retourner est dans le graphe

////VECTOR D'ÉTAT (STOCKAGE DES COULEURS)
void initVectorStatus(const Graph& g, v_status& v);
void setVectorStatus(v_status& vect, unsigned i, unsigned j, unsigned width, color c);
color getVectorStatus(const v_status& vect, unsigned i, unsigned j, unsigned width);
void drawVectorStatus(const Graph& g, const v_status& vect, bool useColor);

////DIJKSTRA
void initDijkstraMap(const Graph& g, dijkstra_map& dMap);
void setDijkstraMapDistance(dijkstra_map& dMap, unsigned i, unsigned j, unsigned width, unsigned distance);
void setDijkstraMapLast(dijkstra_map& dMap, unsigned i, unsigned j, unsigned width, unsigned i1, unsigned j1);
dijkstraNode getDijkstraMapNode(const dijkstra_map& dMap, unsigned i, unsigned j, unsigned width);
unsigned getDijkstraMapDistance(const dijkstra_map& dMap, unsigned i, unsigned j, unsigned width);
Pos getDijkstraMapLast(const dijkstra_map& dMap, unsigned i, unsigned j, unsigned width);
void drawDijkstraMap(const Graph& g, const dijkstra_map& dMap, const v_status& vect, bool useColor);

////PARCOURS
void Dijkstra(appParameters parameters, const Graph& g, unsigned iStart, unsigned jStart);
void Largeur(appParameters parameters, const Graph& g, unsigned iStart, unsigned jStart);
void Profondeur(appParameters parameters, const Graph& g, unsigned iStart, unsigned jStart);

#endif /* GRAPHE_HPP */
