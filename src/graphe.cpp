#include "graphe.hpp"

//////////////////////////////// METHODS


//----
void initGrid(Grid& g, unsigned width, unsigned height)
{
	
}
//----
void loadGrid(string filename, Grid& g)
{
	// file reading tools init
	int lineCount = 0;
	string line;
	ifstream myfile (filename);

	// check file
	if(myfile.is_open())
	{
		// reading file
		while(getline(myfile,line))
		{
			int iW = stoi(line.substr(0, line.find(" ")));
			int jH = stoi(line.substr(1, line.find(" ")));
			if(lineCount == 0)
			{
				initGrid(g, iW, jH);
			}
			else
			{
				vertex v = stoi(line.substr(2, line.find(" ")));
				setVertex(g, iW, jH, v);
			}
			++lineCount;
		}
		myfile.close();
	}
	else
	{
		cerr << "Unable to read file \"" << filename << "\"" << endl;
	}

}
//----
void pruneGrid(Grid& g)
{
	
}
//----
void setVertex(Grid& g, unsigned i, unsigned j, vertex v)
{
	
}
//----
vertex getVertex(const Grid& g, unsigned i, unsigned j, orient o)
{
	return 0;
}
//----
void drawGrid(const Grid& g)
{
	
}

