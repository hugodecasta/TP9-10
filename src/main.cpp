#include "graphe.hpp"

int main()
{
	string filename = "exemple.grd";
	Graph g;

	loadGraph(filename,g);

	drawGraph(g);

	Dijkstra(g, 5, 5, 0, 0);

	return 0;
}
