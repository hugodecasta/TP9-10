#ifndef GRAPHE_H
#define GRAPHE_H

#include <fstream>
#include <string>
#include <ostream>
#include <iostream>
#include <vector>
using namespace std;

////////////////////////////// DATAS

typedef int vertex;
typedef struct Pos {
    unsigned i, j;
} Pos;

typedef struct dijkstraNode {
	Pos position;
	Pos last;
	int distance;
	
} dijkstraNode;

typedef struct Graph {
	unsigned width, height;
	vertex* grid;

} Graph;

enum orient {north, south, east, west, self};

enum color {white, grey, black};
typedef vector<color> v_status;
typedef vector<dijkstraNode> dijkstra_map;

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

void initGraph(Graph& g, unsigned width, unsigned height);
bool loadGraph(string filename, Graph& g);
void pruneGraph(Graph& g);

void setVertex(Graph& g, unsigned i, unsigned j, vertex v);
vertex getVertex(const Graph& g, unsigned i, unsigned j, orient o); // Le vertex que l'on veut retourner est dans le graphe

void drawGraph(const Graph& g);

////////////////////////////// PARCOURS

void initVectorStatus(const Graph& g, v_status& v);
void setVectorStatus(v_status& vect, unsigned i, unsigned j, unsigned width, color c);
void drawVectorStatus(const Graph& g, const v_status& vect);

void Dijkstra(appParameters parameters, const Graph& g, unsigned iStart, unsigned jStart);
void Largeur(appParameters parameters,const Graph& g, unsigned iStart, unsigned jStart);
void Profondeur(appParameters parameters,const Graph& g, unsigned iStart, unsigned jStart);

#endif /* GRAPHE_HPP */
