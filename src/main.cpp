#include "graphe.hpp"

int main()
{
	string filename = "exemple.grd";
	Graph g;

	loadGraph(filename,g);

	drawGraph(g);

	return 0;
}
