#include "graphe.hpp"
#include <fstream>
#include <string>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <queue>
#include <stack>
#include <math.h> 

#define INFINI 100000

using namespace std;

vector<string> split(string str, char delimiter)
{
    vector<string> internal;
    stringstream ss(str);
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

bool loadGraph(string filename, Graph& g)
{
    // file reading tools init
    int lineCount = 0;
    string line;
    ifstream myfile (filename);

    // file check
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
		return false;
    }
	return true;
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
            i--;
            break;
        case south:
            i++;
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

////////////////////////////////////////////////////////////////////////////
// VECTOR STATUS USES
////// init
void initVectorStatus(const Graph& g, v_status& vect)
{
    for (unsigned j = 0; j < g.height; j++) {
        for (unsigned i = 0; i < g.width; i++)
            vect.push_back(white);
    }
}
////// get/set
void setVectorStatus(v_status& vect, unsigned i, unsigned j, unsigned width, color c)
{
    vect[i * width + j] = c;
}
color getVectorStatus(const v_status& vect, unsigned i, unsigned j, unsigned width)
{
    return vect[i * width + j];
}
////// draw
void drawVectorStatus(const Graph& g, const v_status& vect, bool useColor)
{
    for (unsigned i = 0; i < g.height; i++) {
        for (unsigned j = 0; j < g.width; j++) {
            switch (vect[i * g.width + j]) {
                case white:
					if(useColor)
						cout << "\033[31;1m" << setfill('0') << setw(2) << g.grid[i * g.width + j] << "\033[0m";
					else
						cout << "B";
                    break;
                case grey:
					if(useColor)
						cout << "\033[34;1m" << setfill('0') << setw(2) << g.grid[i * g.width + j] << "\033[0m";
					else
						cout << "G";
                    break;
                case black:
					if(useColor)
						cout << "\033[32;1m" << setfill('0') << setw(2) << g.grid[i * g.width + j] << "\033[0m";
					else
						cout << "N";
                    break;
                default:
                    break;
            }
            cout << " ";
        }
        cout << endl << endl;
    }
}
////////////////////////////////////////////////////////////////////////////
// DIJKSTRA MAP USES
////// init
void initDijkstraMap(const Graph& g, dijkstra_map& dMap)
{
	for (unsigned i = 0; i < g.height; i++) {
        for (unsigned j = 0; j < g.width; j++) {
			dMap.push_back({{i,j},{i,j},INFINI});
		}
	}
}
////// get/set
void setDijkstraMapDistance(dijkstra_map& dMap, unsigned i, unsigned j, unsigned width, unsigned distance)
{
	dMap[i * width + j].distance = distance;
}
void setDijkstraMapLast(dijkstra_map& dMap, unsigned i, unsigned j, unsigned width, unsigned i1, unsigned j1)
{
	dMap[i * width + j].last = {i1, j1};
}
unsigned getDijkstraMapDistance(const dijkstra_map& dMap, unsigned i, unsigned j, unsigned width)
{
	return dMap[i * width + j].distance;
}
Pos getDijkstraMapLast(const dijkstra_map& dMap, unsigned i, unsigned j, unsigned width)
{
	return dMap[i * width + j].last;
}
dijkstraNode getDijkstraMapNode(const dijkstra_map& dMap, unsigned i, unsigned j, unsigned width)
{
	return dMap[i * width + j];
}
////// draw
void drawDijkstraMap(const Graph& g, const dijkstra_map& dMap, const v_status& vect, bool useColor)
{
    for (unsigned i = 0; i < g.height; i++) {
        for (unsigned j = 0; j < g.width; j++) {
			
			unsigned dist = getDijkstraMapDistance(dMap,i,j,g.width);
			string toDraw = " ● ";
			if(dist < INFINI)
				toDraw = to_string(dist);
			
            switch (getVectorStatus(vect,i,j,g.width)) {
                case white:
					if(useColor)
						cout << "\033[31;1m" << setfill('0') << setw(3) << toDraw << "\033[0m";
					else
						cout << "(B)";
                    break;
                case grey:
					if(useColor)
						cout << "\033[34;1m" << setfill('0') << setw(3) << toDraw << "\033[0m";
					else
						cout << "(G)";
                    break;
                case black:
					if(useColor)
						cout << "\033[32;1m" << setfill('0') << setw(3) << toDraw << "\033[0m";
					else
						cout << "(N)";
                    break;
                default:
                    break;
            }			
			Pos last = getDijkstraMapLast(dMap,i,j,g.width);
			if(last.i == i && last.j == j+1)
				cout << "← ";
			else if(j<g.width)
			{
				Pos last2 = getDijkstraMapLast(dMap,i,j+1,g.width);
				if(last2.i == i && last2.j == j)
					cout << "→ ";
				else
					cout << "  ";
			}
        }
		cout << endl;
		for (unsigned j = 0; j < g.width; j++)
		{
			Pos last = getDijkstraMapLast(dMap,i,j,g.width);
			if(last.i == i+1 && last.j == j)
				cout << " ↑";
			else if(i<g.height)
			{
				Pos last2 = getDijkstraMapLast(dMap,i+1,j,g.width);
				if(last2.i == i && last2.j == j)
					cout << " ↓";
				else
					cout << "  ";
			}
			cout << "   ";
		}
		cout << endl;
    }
}
////////////////////////////////////////////////////////////////////////////
// OPERATOR OVERLOADS
ostream& operator<<(ostream& stream, const Pos& position)
{
	stream << "{" << position.i << "," << position.j << "}";
	return stream;
}
ostream& operator<<(ostream& stream, const dijkstraNode& n2)
{
	stream << n2.position << n2.last << "-" << n2.distance;
	return stream;
}
// Implémentation du l'opérateur LESS pour la file de priorité
// utilisant les dijkstraNode
bool operator<(const dijkstraNode& n1, const dijkstraNode& n2)
{
	return n1.distance > n2.distance;
}
////////////////////////////////////////////////////////////////////////////
// DIJKSTRA
void Dijkstra(appParameters parameters, const Graph& g, unsigned iStart, unsigned jStart)
{
	//------------------------- datas
    v_status status;
	dijkstra_map dMap;
	
	priority_queue<dijkstraNode> file;
	dijkstraNode pos_actuelle;
	
	//------------------------- inits
    initVectorStatus(g, status);
	initDijkstraMap(g, dMap);
	
	//------------------------- execution inits
	setDijkstraMapDistance(dMap,iStart,jStart,g.width,0);
    setVectorStatus(status, iStart, jStart, g.width, grey);
	file.push(getDijkstraMapNode(dMap,iStart,jStart,g.width));
	
	//------------------------- execute
	
	while(!file.empty()) 
	{
		system("clear");
		// --- récupérer le noeud actuel
        pos_actuelle = file.top();
		unsigned i = pos_actuelle.position.i;
		unsigned j = pos_actuelle.position.j;
		// --- colorer en noir
        setVectorStatus(status, i, j, g.width, black);
		
		// --- travailler sur ses voisins
		Pos voisins[4] = {{i-1,j},{i,j+1},{i+1,j},{i,j-1}};
		for(int k=0;k<4;++k)
		{
			unsigned i1 = voisins[k].i;
			unsigned j1 = voisins[k].j;
			
			// --- vérifier que le voisin existe et qu'il puisse fournir de nouveaux noeuds
			if ((i1 >= 0 && i1 < g.height) && (j1 >= 0 && j1 < g.width) && (getVectorStatus(status,i1,j1,g.width) != black))
			{
				// --- calcule de sa distance avec le noeud actuel
				unsigned localDistanceToIt = sqrt(1 + pow(getVertex(g,i,j,self) - getVertex(g,i1,j1,self),2));
				unsigned globalDistanceToIt = getDijkstraMapDistance(dMap,i,j,g.width) + localDistanceToIt;
				
				// --- mise à jour de la distance du noeud avec son prédécesseur
				if(getDijkstraMapDistance(dMap,i1,j1,g.width) > globalDistanceToIt)
				{
					setDijkstraMapDistance(dMap,i1,j1,g.width,globalDistanceToIt);
					setDijkstraMapLast(dMap,i1,j1,g.width,i, j);
				}
				// --- coloration du noeud
				if(getVectorStatus(status,i1,j1,g.width) == white)
				{
					setVectorStatus(status, i1, j1, g.width, grey);
					file.push(getDijkstraMapNode(dMap,i1,j1,g.width));
				}
			}
		}		
		
		// --- mise à jour de la file de priorité et affichage de fin d'itération
        file.pop();
		
        drawDijkstraMap(g, dMap, status, parameters.useColor);
		if(parameters.drawMemory)
		{
			priority_queue<dijkstraNode> file2(file);
			unsigned size = file2.size();
			for(unsigned i=0;i<size;++i)
			{
				cout << file2.top() << endl;
				file2.pop();
			}
		}
		if(parameters.useInput)
			getchar();
		else
		{
			string sleeper = "sleep " + to_string(parameters.delay);
			system(sleeper.c_str());
		}
	}
}
////////////////////////////////////////////////////////////////////////////
// LARGEUR
void Largeur(appParameters parameters, const Graph& g, unsigned iStart, unsigned jStart)
{
    v_status status;
    initVectorStatus(g, status);
    setVectorStatus(status, iStart, jStart, g.width, grey);

    queue<Pos> file;
    file.push({iStart, jStart});

    Pos pos_actuelle;

    while(!file.empty()) {
        pos_actuelle = file.front();

        if (((int) pos_actuelle.i - 1 >= 0) && (status[(pos_actuelle.i - 1) * g.width + pos_actuelle.j] == white)) {
            setVectorStatus(status, pos_actuelle.i - 1, pos_actuelle.j, g.width, grey);
            file.push({pos_actuelle.i - 1, pos_actuelle.j});
        }

        if ((pos_actuelle.i + 1 < g.height) && (status[(pos_actuelle.i + 1) * g.width + pos_actuelle.j] == white)) {
            setVectorStatus(status, pos_actuelle.i + 1, pos_actuelle.j, g.width, grey);
            file.push({pos_actuelle.i + 1, pos_actuelle.j});
        }
        if (((int) pos_actuelle.j - 1 >= 0) && (status[pos_actuelle.i * g.width + (pos_actuelle.j - 1)] == white)) {
            setVectorStatus(status, pos_actuelle.i, pos_actuelle.j - 1, g.width, grey);
            file.push({pos_actuelle.i, pos_actuelle.j - 1});
        }
        if ((pos_actuelle.j + 1 < g.width) && (status[pos_actuelle.i * g.width + (pos_actuelle.j + 1)] == white)) {
            setVectorStatus(status, pos_actuelle.i, pos_actuelle.j + 1, g.width, grey);
            file.push({pos_actuelle.i, pos_actuelle.j + 1});
        }

        file.pop();
        setVectorStatus(status, pos_actuelle.i, pos_actuelle.j, g.width, black);
        system("clear");
        drawVectorStatus(g, status, parameters.useColor);
		if(parameters.drawMemory)
		{
			queue<Pos> file2(file);
			unsigned size = file2.size();
			for(unsigned i=0;i<size;++i)
			{
				cout << file2.front() << endl;
				file2.pop();
			}
		}
		if(parameters.useInput)
			getchar();
		else
		{
			string sleeper = "sleep " + to_string(parameters.delay);
			system(sleeper.c_str());
		}
    }
}
////////////////////////////////////////////////////////////////////////////
// PROFONDEUR
void Profondeur(appParameters parameters, const Graph& g, unsigned iStart, unsigned jStart)
{
    v_status status;
    initVectorStatus(g, status);
    setVectorStatus(status, iStart, jStart, g.width, grey);

    stack<Pos> pile;
    pile.push({iStart, jStart});

    Pos pos_actuelle;

    while(!pile.empty()) {
        pos_actuelle = pile.top();
        pile.pop();

        if (((int) pos_actuelle.i - 1 >= 0) && (status[(pos_actuelle.i - 1) * g.width + pos_actuelle.j] == white)) {
            setVectorStatus(status, pos_actuelle.i - 1, pos_actuelle.j, g.width, grey);
            pile.push({pos_actuelle.i - 1, pos_actuelle.j});
        }

        if ((pos_actuelle.i + 1 < g.height) && (status[(pos_actuelle.i + 1) * g.width + pos_actuelle.j] == white)) {
            setVectorStatus(status, pos_actuelle.i + 1, pos_actuelle.j, g.width, grey);
            pile.push({pos_actuelle.i + 1, pos_actuelle.j});
        }
        if (((int) pos_actuelle.j - 1 >= 0) && (status[pos_actuelle.i * g.width + (pos_actuelle.j - 1)] == white)) {
            setVectorStatus(status, pos_actuelle.i, pos_actuelle.j - 1, g.width, grey);
            pile.push({pos_actuelle.i, pos_actuelle.j - 1});
        }
        if ((pos_actuelle.j + 1 < g.width) && (status[pos_actuelle.i * g.width + (pos_actuelle.j + 1)] == white)) {
            setVectorStatus(status, pos_actuelle.i, pos_actuelle.j + 1, g.width, grey);
            pile.push({pos_actuelle.i, pos_actuelle.j + 1});
        }

        setVectorStatus(status, pos_actuelle.i, pos_actuelle.j, g.width, black);
        system("clear");
        drawVectorStatus(g, status, parameters.useColor);
		if(parameters.drawMemory)
		{
			stack<Pos> pile2(pile);
			unsigned size = pile2.size();
			for(unsigned i=0;i<size;++i)
			{
				cout << pile2.top() << endl;
				pile2.pop();
			}
		}
		if(parameters.useInput)
			getchar();
		else
		{
			string sleeper = "sleep " + to_string(parameters.delay);
			system(sleeper.c_str());
		}
    }
}
