#include "graphe.hpp"

int main()
{
	string filename = "exemple.grd";
	Graph g;

	loadGraph(filename,g);

	//Largeur(g, 5, 5);
	Profondeur(g, 5, 5);

	return 0;
}
