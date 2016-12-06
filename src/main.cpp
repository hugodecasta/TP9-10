#include "graphe.hpp"

void drawUsage()
{
    system("cat usage.txt");
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
		string tem = "-t";
		bool waitForTime = false;
		for(int i=3; i<argc;++i)
		{
			string option = argv[i];
			if(waitForTime)
			{
				aParams.delay = stof(option);
				waitForTime = false;
				continue;
			}
			else if (option.compare(col) == 0)
				aParams.useColor = true;
			else if (option.compare(mem) == 0)
				aParams.drawMemory = true;
			else if (option.compare(inp) == 0)
				aParams.useInput = true;
			else if (option.compare(tem) == 0)
				waitForTime = true;
		}
	}
	
	return true;
}
////////////////////////////////////////////////////////////
// MAIN
int main(int argc, char* argv[])
{
	// --- parsing des paramètres
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
	
	// --- initialisation du Graphe
	Graph g;
	if(!loadGraph(aParams.filename,g))
	{
		return 1;
	}

	// --- execution de l'algorithme de parcours
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
