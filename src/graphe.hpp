#ifndef GRAPHE_H
#define GRAPHE_H

#include <fstream>
#include <string>
#include <ostream>
#include <iostream>
using namespace std;

////////////////////////////// DATAS

#define vertex int

enum orient { north, south, east, west, self };

typedef struct Graph
{
	unsigned width, height;
	vertex* grid;

} Graph;

////////////////////////////// METHODS

//----
void initGraph(Graph& g, unsigned width, unsigned height);
//----
void loadGraph(string filename, Graph& g);
//----
void pruneGraph(Graph& g);
//----
void setVertex(Graph& g, unsigned i, unsigned j, vertex v);
//----
vertex getVertex(const Graph& g, unsigned i, unsigned j, orient o);
//----
void drawGraph(const Graph& g);

#endif /* GRAPHE_HPP */
