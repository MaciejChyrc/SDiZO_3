#pragma once
#include <vector>
#include "MinorStructs.h"

using namespace std;

class GraphMatrix
{
private:
	int verticesNumber, edgesNumber, startVertex;
public:
	int **matrix;
	vector<Edge> listOfEdges;
	GraphMatrix ();
	~GraphMatrix ();
	int getVerticesNumber ();
	int getEdgesNumber ();
	int getStartVertex ();
	void setStartVertex (int startV);
	int** getMatrix ();
	void createGraphFromListOfEdges (int v);
	void createDirectedGraphFromListOfEdges (int v);
	void createRandomGraph (int v, int fillPercent);
	void copyListOfEdges (vector<Edge> par);
	void print ();
};