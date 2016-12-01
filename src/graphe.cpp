#include "graphe.hpp"
#include <fstream>
#include <string>
#include <ostream>
#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <stack>

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

void loadGraph(string filename, Graph& g)
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

void drawVectorStatus(const Graph& g, const v_status& vect)
{
    for (unsigned j = 0; j < g.height; j++) {
        for (unsigned i = 0; i < g.width; i++) {
            switch (vect[j * g.width + i]) {
                case white:
                    cout << "B";
                    break;
                case grey:
                    cout << "G";
                    break;
                case black:
                    cout << "N";
                    break;
                default:
                    break;
            }
            cout << " ";
        }

        cout << endl;
    }
}


void Dijkstra(const Graph& g, unsigned iStart, unsigned jStart, unsigned iEnd, unsigned jEnd)
{
    v_status status;
    initVectorStatus(g, status);
    drawVectorStatus(g, status);
}


void Largeur(const Graph& g, unsigned iStart, unsigned jStart)
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
        drawVectorStatus(g, status);
        system("sleep 0.5");
    }
}

void Profondeur(const Graph& g, unsigned iStart, unsigned jStart)
{
    v_status status;
    initVectorStatus(g, status);
    setVectorStatus(status, iStart, jStart, g.width, grey);

    stack<Pos> file;
    file.push({iStart, jStart});

    Pos pos_actuelle;

    while(!file.empty()) {
        pos_actuelle = file.top();

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
        drawVectorStatus(g, status);
        system("sleep 0.5");
    }
}
