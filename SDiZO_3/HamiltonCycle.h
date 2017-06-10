#pragma once
#include <vector>
#include "MinorStructs.h"

class HamiltonCycle
{
private:
	ListElement** adjList;
	ListElement* ptr;
	int verticesNumber, edgesNumber, weight;
public:
	std::vector<Edge> listOfEdges;
	HamiltonCycle ();
	HamiltonCycle (int v);
	~HamiltonCycle ();
	void createCycleFromListOfEdges (int v);
	void add (Edge edge);
	Edge getEdge(int index);
	ListElement* getAdjList (int i);
	void printAdjacencyList ();
	void printListOfEdges ();
};