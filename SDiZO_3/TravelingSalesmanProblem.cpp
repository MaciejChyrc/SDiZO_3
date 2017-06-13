#include "TravelingSalesmanProblem.h"
#include <iostream>
#include "HamiltonCycle.h"
#include <queue>
#include <windows.h>
//-----------------------------------------------------------------------------
long long int TravelingSalesmanProblem::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return static_cast<long long int>(count.QuadPart);
}

TravelingSalesmanProblem::TravelingSalesmanProblem()
{

}

TravelingSalesmanProblem::~TravelingSalesmanProblem()
{

}

/*int TravelingSalesmanProblem::minCost = INT_MAX;

int TravelingSalesmanProblem::getMinCost()
{
	return minCost;
}

void TravelingSalesmanProblem::setMinCostToMaxInt()
{
	minCost = INT_MAX;
}

void TravelingSalesmanProblem::swap(int * city1, int * city2)
{
	int temp = *city1;
	*city1 = *city2;
	*city2 = temp;
}

void TravelingSalesmanProblem::calculateCost(int *city, int n, int **graph, int graphSize)
{
	int numberOfCities = graphSize;
	//cout << "numberOfCities w tej chwili: " << numberOfCities << "\n";
	int totalCost = 0;

	for (int i = 0; i <= n; i++)
	{
		totalCost += graph[city[i % numberOfCities]][city[(i + 1) % numberOfCities]];
		
		if (totalCost < minCost) minCost = totalCost;
		//cout << "minCost w tej chwili: " << minCost << "\n";
	}
}

void TravelingSalesmanProblem::permute(int *city, int i, int n, int **graph, int graphSize)
{
	if (i == n) calculateCost(city, n, graph, graphSize);
	else
	{
		for (int j = i; j <= n; j++)
		{
			swap (city + i, city + j);
			permute (city, i + 1, n, graph, graphSize);
			swap (city + i, city + j);
		}
	}
}*/
///<note>Algorytm zachlanny wyznaczajacy sciezke miedzy wszystkimi miastami i wraca do miasta startowego
///<note>W odroznieniu do algorytmu Prima czyszczona jest kolejka po przejsciu do nastepnego wierzcholka (miasta),
///<note>dzieki czemu kazdy wierzcholek jest 2-ego stopnia i tworzony jest cykl Hamiltona.
void TravelingSalesmanProblem::GreedyBasedOnPrim(int startV, GraphMatrix *graphMatrix, vector<double> &vectorOfTimes)
{
	if ((startV < 0 || startV >= graphMatrix->getVerticesNumber()) || graphMatrix == nullptr)
	{
		cout << "Nieodpowiednie parametry.\nNiewlasciwe miasto poczatkowe lub zbior miast jest niezainicjalizowany.\n";
		return;
	}
	
	long long int frequency, timeStart, timeElapsed;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	timeStart = read_QPC();
	int** graph = graphMatrix->matrix;
	int verticesNumber = graphMatrix->getVerticesNumber();
	bool* visited = new bool[verticesNumber];
	vector<Edge> edges = graphMatrix->listOfEdges;
	HamiltonCycle cycle (verticesNumber);
	priority_queue<Edge, vector<Edge>, CmpEdgeWeight> edgeQ;
	Edge edge;
	int i, x;

	for (i = 0; i < verticesNumber; i++)
	{
		visited[i] = false;
	}

	x = startV;
	visited[x] = true;
	//1 krok mniej od ilosci wierzcholkow, bo V startowy juz jest odwiedzony
	for (i = 1; i < verticesNumber; i++)
	{
		for (int l = 0; l < verticesNumber; l++)
		{
			if (!visited[l])
			{
				edge.fromVertexId = x;
				edge.destVertexId = l;
				edge.weight = graph[x][l];
				edgeQ.push(edge);
			}
		}
		do
		{
			edge = edgeQ.top();
			edgeQ.pop();
		} while (visited[edge.destVertexId]);

		cycle.add(edge);
		visited[edge.destVertexId] = true;
		x = edge.destVertexId;
		while (!edgeQ.empty()) edgeQ.pop();
	}
	//prowadzimy sciezke od ostatniego odwiedzonego miasta z powrotem do miasta poczatkowego
	edge.destVertexId = cycle.getEdge(0).fromVertexId;
	edge.fromVertexId = cycle.getEdge(cycle.listOfEdges.size() - 1).destVertexId;
	edge.weight = graph[edge.fromVertexId][edge.destVertexId];
	cycle.add(edge);

	timeElapsed = read_QPC() - timeStart;
	vectorOfTimes.push_back(static_cast<double>(timeElapsed) / static_cast<double>(frequency) * 1000000.0);

	cycle.createCycleFromListOfEdges(verticesNumber);
	cout << "Najkrotsza sciezka (algorytm zachlanny):\n";
	cycle.printListOfEdges();
}