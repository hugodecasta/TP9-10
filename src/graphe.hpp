#ifndef GRAPHE_HPP
#define GRAPHE_HPP

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
void pruneGraph(Graph& g);
//----
void setVertex(Graph& g, unsigned i, unsigned j, vertex v);
//----
vertex getVertex(const Graph& g, unsigned i, unsigned j, orient o);
//----
void drawGraph(const Graph& g);

#endif /* GRAPHE_HPP */
