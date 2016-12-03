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


void initVectorStatus(const Graph& g, v_status& vect)
{
    for (unsigned j = 0; j < g.height; j++) {
        for (unsigned i = 0; i < g.width; i++)
            vect.push_back(white);
    }
}

void setVectorStatus(v_status& vect, unsigned i, unsigned j, unsigned width, color c)
{
    vect[i * width + j] = c;
}

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
void drawDijkstraMap(const Graph& g, const dijkstra_map& dMap, const v_status& vect, bool useColor)
{
    for (unsigned i = 0; i < g.height; i++) {
        for (unsigned j = 0; j < g.width; j++) {
			
			int dist = dMap[i * g.width + j].distance;
			string toDraw = " ● ";
			if(dist < 10000)
				toDraw = to_string(dist);
			
            switch (vect[i * g.width + j]) {
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
			
			Pos last = dMap[i * g.width + j].last;
			if(last.i == i && last.j == j+1)
				cout << "← ";
			else if(j<g.width)
			{
				Pos last2 = dMap[i * g.width + j+1].last;
				if(last2.i == i && last2.j == j)
					cout << "→ ";
				else
					cout << "  ";
			}
        }
		cout << endl;
		for (unsigned j = 0; j < g.width; j++)
		{
			Pos last = dMap[i * g.width + j].last;
			if(last.i == i+1 && last.j == j)
				cout << " ↑";
			else if(i<g.height)
			{
				Pos last2 = dMap[(i+1) * g.width + j].last;
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
bool operator<(const dijkstraNode& n1, const dijkstraNode& n2)
{
	return n1.distance > n2.distance;
}
////////////////////////////////////////////////////////////////////////////
void dijNeiboor(const Graph& g, dijkstra_map& dMap, unsigned i, unsigned j, unsigned i1, unsigned j1, v_status& status, priority_queue<dijkstraNode>& file)
{
	if ((i1 >= 0 && i1 < g.height) && (j1 >= 0 && j1 < g.width) && (status[i1 * g.width + j1] != black))
	{
		int localDistanceToIt = sqrt(1 + pow(getVertex(g,i,j,self) - getVertex(g,i1,j1,self),2));
		int globalDistanceToIt = dMap[i * g.width + j].distance + localDistanceToIt;
		if(dMap[i1 * g.width + j1].distance > globalDistanceToIt)
		{
			dMap[i1 * g.width + j1].distance = globalDistanceToIt;
			dMap[i1 * g.width + j1].last = {i, j};
		}
		if(status[i1 * g.width + j1] == white)
		{
			setVectorStatus(status, i1, j1, g.width, grey);
			file.push(dMap[i1 * g.width + j1]);
		}
	}
}
void dijNode(const Graph& g,dijkstra_map& dMap, unsigned i, unsigned j, v_status& status, priority_queue<dijkstraNode>& file)
{		
	dijNeiboor(g, dMap, i, j, i-1, j, status, file);
	dijNeiboor(g, dMap, i, j, i+1, j, status, file);
	dijNeiboor(g, dMap, i, j, i, j-1, status, file);
	dijNeiboor(g, dMap, i, j, i, j+1, status, file);
		
}
void Dijkstra(appParameters parameters, const Graph& g, unsigned iStart, unsigned jStart)
{
	//------------------------- datas
    v_status status;
	dijkstra_map dMap;
	
	priority_queue<dijkstraNode> file;
	dijkstraNode pos_actuelle;
	
	//------------------------- inits
    initVectorStatus(g, status);
	for (unsigned i = 0; i < g.height; i++) {
        for (unsigned j = 0; j < g.width; j++) {
			dMap.push_back({{i,j},{iStart,jStart},10000});
		}
	}
	
	//------------------------- execution inits
	dMap[iStart * g.width + jStart].distance = 0;
    setVectorStatus(status, iStart, jStart, g.width, grey);
	file.push(dMap[iStart * g.width + jStart]);
	
	//------------------------- execute
	while(!file.empty()) 
	{
        pos_actuelle = file.top();
		unsigned i = pos_actuelle.position.i;
		unsigned j = pos_actuelle.position.j;
        setVectorStatus(status, i, j, g.width, black);
		dijNode(g,dMap,i,j,status,file);
		
		
        file.pop();
        system("clear");
        drawDijkstraMap(g, dMap, status, parameters.useColor);
		if(parameters.drawMemory)
		{
			priority_queue<dijkstraNode> file2(file);
			for(unsigned i=0;i<file2.size();++i)
			{
				cout << file2.top() << endl;
				file2.pop();
			}
		}
		if(parameters.useInput)
			getchar();
		else
			system("sleep 0.5");
	}
}
////////////////////////////////////////////////////////////////////////////
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
			for(unsigned i=0;i<file2.size();++i)
			{
				cout << file2.front() << endl;
				file2.pop();
			}
		}
		if(parameters.useInput)
			getchar();
		else
			system("sleep 0.5");
    }
}
////////////////////////////////////////////////////////////////////////////
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
			for(unsigned i=0;i<pile2.size();++i)
			{
				cout << pile2.top() << endl;
				pile2.pop();
			}
		}
		if(parameters.useInput)
			getchar();
		else
			system("sleep 0.5");
    }
}
