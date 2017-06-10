#include "HamiltonCycle.h"
#include <iostream>
#include <iomanip>

using namespace std;

//konstruktory i destruktor

HamiltonCycle::HamiltonCycle()
{
	adjList = nullptr;
	verticesNumber = edgesNumber = weight = 0;
}

HamiltonCycle::HamiltonCycle (int v)
{
	adjList = new ListElement*[v];
	for (int i = 0; i < v; i++)
	{
		adjList[i] = nullptr;
	}
	verticesNumber = v;
	weight = 0;
}

HamiltonCycle::~HamiltonCycle()
{
	ListElement *ptr, *dltPtr;
	for (int i = 0; i < verticesNumber; i++)
	{
		ptr = adjList[i];
		while (ptr != nullptr)
		{
			dltPtr = ptr;
			ptr = ptr->next;
			delete dltPtr;
		}
	}
	delete[] adjList;
}
///<note>Utworzenie MST z vectora krawedzi o zadanej ilosci wierzcholkow.
void HamiltonCycle::createCycleFromListOfEdges(int v)
{
	if (listOfEdges.size() > (v * (v - 1)) / 2)
	{
		cout << "Zbyt duzo krawedzi w grafie.\n";
		while (listOfEdges.size() > 0)
		{
			listOfEdges.pop_back();
		}
		return;
	}
	else if (listOfEdges.size() < v - 1)
	{
		cout << "Zbyt malo krawedzi aby otrzymac spojny graf.\n";
		while (listOfEdges.size() > 0)
		{
			listOfEdges.pop_back();
		}
		return;
	}
	adjList = new ListElement*[v];
	edgesNumber = listOfEdges.size();
	verticesNumber = v;
	vector<Edge> tempListOfEdges = listOfEdges;
	int v1, v2, w;

	for (int i = 0; i < v; i++)
	{
		adjList[i] = nullptr;
	}
	for (int i = 0; i < tempListOfEdges.size(); i++)
	{
		v1 = tempListOfEdges[i].fromVertexId;
		v2 = tempListOfEdges[i].destVertexId;
		w = tempListOfEdges[i].weight;
		ptr = new ListElement;
		ptr->weight = w;
		ptr->destVertexId = v2;
		ptr->next = adjList[v1];
		adjList[v1] = ptr;
		ptr = new ListElement;
		ptr->weight = w;
		ptr->destVertexId = v1;
		ptr->next = adjList[v2];
		adjList[v2] = ptr;
		weight += ptr->weight;
	}
}
///<note>Dodanie krawedzi do vectora.
void HamiltonCycle::add(Edge edge)
{
	listOfEdges.push_back(edge);
}

Edge HamiltonCycle::getEdge(int index)
{
	return listOfEdges[index];
}
//-----------------------------------------------------------------------------
ListElement* HamiltonCycle::getAdjList(int i)
{
	return adjList[i];
}
///<note>Wydruk MST w postaci listowej.
void HamiltonCycle::printAdjacencyList()
{
	ListElement* ptr;

	for (int i = 0; i < verticesNumber; i++)
	{
		cout << i << ": ";
		ptr = adjList[i];
		while (ptr != nullptr)
		{
			cout << "(" << ptr->weight << "|" << ptr->destVertexId << ") ";
			ptr = ptr->next;
		}
		cout << "\n";
	}
	cout << "\nWaga cyklu: " << weight << "\n";
}
///<note>Wydruk MST w postaci listy krawedzi.
void HamiltonCycle::printListOfEdges()
{
	cout << "Krawedz | Waga\n";
	for (int i = 0; i < listOfEdges.size(); i++)
	{
		cout << "(" << listOfEdges[i].fromVertexId << "|" << listOfEdges[i].destVertexId << ")";
		cout << "  " << listOfEdges[i].weight << "\n";
	}
	cout << "\nWaga cyklu: " << weight << "\n";
}