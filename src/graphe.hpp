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
typedef struct Graph
{
	unsigned width, height;
	vertex* grid;

} Graph;

enum orient {north, south, east, west, self};

enum color {white, grey, black};
typedef vector<color> v_status;

////////////////////////////// METHODS

void initGraph(Graph& g, unsigned width, unsigned height);
void loadGraph(string filename, Graph& g);
void pruneGraph(Graph& g);

void setVertex(Graph& g, unsigned i, unsigned j, vertex v);
vertex getVertex(const Graph& g, unsigned i, unsigned j, orient o); // Le vertex que l'on veut retourner est dans le graphe

void drawGraph(const Graph& g);

////////////////////////////// PARCOURS

void initVectorStatus(const Graph& g, v_status& v);
void setVectorStatus(v_status& vect, unsigned i, unsigned j, unsigned width, color c);
void drawVectorStatus(const Graph& g, const v_status& vect);

void Dijkstra(const Graph& g, unsigned iStart, unsigned jStart, unsigned iEnd, unsigned jEnd);

#endif /* GRAPHE_HPP */
