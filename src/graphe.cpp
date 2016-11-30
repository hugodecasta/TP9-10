#include "graphe.hpp"
#include <iostream>

using namespace std;

//////////////////////////////// METHODS

void initGraph(Graph& g, unsigned width, unsigned height)
{
	g.width = width;
	g.height = height;
	g.grid = new vertex[width * height];
}
//----
void loadGraph(string filename, Grid& g)
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

void pruneGraph(Graph& g)
{
	delete g.grid;
	g.height = 0;
	g.width = 0;
}

void setVertex(Graph& g, unsigned i, unsigned j, vertex v)
{
	g.grid[i * g.width + j] = v;
}

vertex getVertex(const Graph& g, unsigned i, unsigned j, orient o)
{
	switch (o) {
		case north:
			i++;
			break;
		case south:
			i--;
			break;
		case east:
			j++;
			break;
		case west:
			j--;
			break;
		default:
			break;
	}

	return g.grid[i * g.width + j];
}

void drawGraph(const Graph& g)
{
	for (unsigned j = 0; j < g.height; j++) {
		for (unsigned i = 0; i < g.width; i++)
			cout << g.grid[i * g.width + j] << " ";
		cout << endl;
	}
}

