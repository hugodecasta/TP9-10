#ifndef "GRAPHE_H"
#define "GRAPHE_H"

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

typedef struct Grid
{
	
	unsigned width, height;
	vertex* graphe;

}Grid;

////////////////////////////// METHODS

//----
void initGrid(Grid& g, unsigned width, unsigned height);
//----
void pruneGrid(Grid& g);
//----
void setVertex(Grid& g, unsigned i, unsigned j, vertex v);
//----
vertex getVertex(const Grid& g, unsigned i, unsigned j, orient o);
//----
void drawGrid(const Grid& g);

#endif
