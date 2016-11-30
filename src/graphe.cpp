#include "graphe.hpp"
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> split(string str, char delimiter)
{
	vector<string> internal;
	stringstream ss(str); // Turn the string into a stream.
	string tok;

	while(getline(ss, tok, delimiter))
	{
		internal.push_back(tok);
	}

	return internal;
}
//////////////////////////////// METHODS

void initGraph(Graph& g, unsigned width, unsigned height)
{
	g.width = width;
	g.height = height;
	g.grid = new vertex[width * height];
}
//----
void loadGraph(string filename, Graph& g)
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
			vector<string> parts = split(line, ' ');

			int jW = atoi(parts.at(0).c_str());
			int iH = atoi(parts.at(1).c_str());

			if(lineCount == 0)
			{
				initGraph(g, jW, iH);
			}
			else
			{
				vertex v = atoi(parts.at(2).c_str());			
				setVertex(g, iH, jW, v);
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
			cout << g.grid[j * g.width + i] << " ";
		cout << endl;
	}
}

