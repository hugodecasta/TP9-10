#include "graphe.hpp"

int main()
{
	string filename = "exemple.grille";
	Graph g;

	loadGraph(filename,g);

	drawGraph(g);

	return 0;
}
