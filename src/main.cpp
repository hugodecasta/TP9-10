#include "graphe.hpp"
#include <stdlib.h>

/*
void fillGraph(Graph& g)
{
	cout << g.width << " " << g.height << endl;
	for(unsigned i = 0; i < g.height; ++i)
		for(unsigned j = 0; j < g.width; ++j)
		{
			vertex v = rand()%100;
			cout << j << " " << i << " " << v << endl;
		}
}
*/

int main()
{
	string filename = "exemple.grd";
	Graph g;

	loadGraph(filename,g);

	drawGraph(g);

	return 0;
}
