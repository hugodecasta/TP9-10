#include "graphe.hpp"

void drawUsage()
{
	cout << "Usage : filename Algorithm [Options]" << endl;
	cout << endl << " filename:" << endl;
	cout << "\tle fichier *.grd contenant le graphe à utiliser" << endl;
	cout << endl << " Algorithm:" << endl;
	cout << "\t-D : parcours selon l'algorithm de Dijkstra" << endl;
	cout << "\t-P : parcours en profondeur" << endl;
	cout << "\t-L : parcours en largeure" << endl;
	cout << endl << " Options:" << endl;
	cout << "\t-c : afficher la trace avec couleurs" << endl;
	cout << "\t-m : afficher l'objet mémoire utiliser (pile, file ...)" << endl;
	cout << "\t-i : utiliser un input utilisateur entre chaque itération au lieu d'un Delay" << endl;
}


bool parseArgv(int argc, char* argv[], appParameters& aParams)
{
    aParams.filename = argv[1];
	
    string dij = "-D";
    string pro = "-P";
    string lar = "-L";
	string algoUsed = argv[2];
	if (algoUsed.compare(dij) == 0)
		aParams.usedAlgorithm = dijkstra;
	else if (algoUsed.compare(pro) == 0)
		aParams.usedAlgorithm = profondeur;
	else if (algoUsed.compare(lar) == 0)
		aParams.usedAlgorithm = largeur;
	
	if(argc > 3)
	{
		string col = "-c";
		string mem = "-m";
		string inp = "-i";
		for(int i=3; i<argc;++i)
		{
			string option = argv[i];
			if (option.compare(col) == 0)
				aParams.useColor = true;
			else if (option.compare(mem) == 0)
				aParams.drawMemory = true;
			else if (option.compare(inp) == 0)
				aParams.useInput = true;
		}
	}
	
	return true;
}
int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		drawUsage();
		return 1;
	}
	
	appParameters aParams;
	if(!parseArgv(argc, argv,aParams))
	{
		drawUsage();
		return 1;
	}
	
	Graph g;
	if(!loadGraph(aParams.filename,g))
	{
		return 1;
	}

	switch(aParams.usedAlgorithm)
	{
		case dijkstra:
			Dijkstra(aParams, g, 5, 5);
			break;
		case largeur:
			Largeur(aParams, g, 5, 5);
			break;
		case profondeur:
			Profondeur(aParams, g, 5, 5);
			break;
	}

	return 0;
}
