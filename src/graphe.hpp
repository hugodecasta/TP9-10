#ifndef GRAPHE_H
#define GRAPHE_H

#include <fstream>
#include <string>
#include <ostream>
#include <iostream>
using namespace std;

////////////////////////////// DATAS

#define vertex int

enum orient
{
	north,
	south,
	east,
	west,
	self
};

typedef struct Graph
{
	
	unsigned width, height;
	vertex* grid;

} Graph;

////////////////////////////// METHODS

//----
void initGrid(Graph& g, unsigned width, unsigned height);
//----
void loadGrid(string filename, Graph& g);
//----
void pruneGrid(Graph& g);
//----
void setVertex(Graph& g, unsigned i, unsigned j, vertex v);
//----
vertex getVertex(const Graph& g, unsigned i, unsigned j, orient o);
//----
void drawGrid(const Graph& g);

#endif
