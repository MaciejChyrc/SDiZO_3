#include "GraphMatrix.h"
#include <iostream>
#include <ctime>
#include <iomanip>

//konstruktor, destruktor i akcesory do pol klasy
GraphMatrix::GraphMatrix()
{
	matrix = nullptr;
	verticesNumber = 0;
	edgesNumber = 0;
}

GraphMatrix::~GraphMatrix()
{
	for (int i = 0; i < verticesNumber; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

int GraphMatrix::getVerticesNumber()
{
	return verticesNumber;
}

int GraphMatrix::getEdgesNumber()
{
	return edgesNumber;
}

int GraphMatrix::getStartVertex()
{
	return startVertex;
}

void GraphMatrix::setStartVertex(int startV)
{
	if (startV < verticesNumber && startV >= 0)
		startVertex = startV;
	else
		cout << "Podany numer wierzcholka jest za duzy/mniejszy od 0.\nPodaj wartosc od 0 do wielkosci zbioru wierzcholkow - 1.\n";
}

int ** GraphMatrix::getMatrix()
{
	return matrix;
}
///<note>Budowanie grafu nieskierowanego o zadanej ilosci wierzcholkow z istniejacej listy krawedzi.
///<note>Nalezy uprzednio wypelnic liste krawedziami i uzyc copyListOfEdges!!!
void GraphMatrix::createGraphFromListOfEdges(int v)
{
	//jesli nieprawidlowa liczba krawedzi, to czyscimy liste krawedzi i wychodzimy z metody
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
	matrix = new int*[v];
	verticesNumber = v;
	edgesNumber = listOfEdges.size();
	vector<Edge> tempListOfEdges = listOfEdges;

	for (int i = 0; i < v; i++)
	{
		matrix[i] = new int[v];
	}
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			matrix[i][j] = INT_MAX;
		}
	}
	while (!tempListOfEdges.empty())
	{
		matrix[tempListOfEdges.back().fromVertexId][tempListOfEdges.back().destVertexId] = tempListOfEdges.back().weight;
		matrix[tempListOfEdges.back().destVertexId][tempListOfEdges.back().fromVertexId] = tempListOfEdges.back().weight;
		tempListOfEdges.pop_back();
	}
}
///<note>Budowanie grafu skierowanego o zadanej ilosci wierzcholkow z istniejacej listy krawedzi.
///<note>Nalezy uprzednio wypelnic liste krawedziami i uzyc copyListOfEdges!!!
void GraphMatrix::createDirectedGraphFromListOfEdges(int v)
{
	//jesli nieprawidlowa liczba krawedzi, to czyscimy liste krawedzi i wychodzimy z metody
	if (listOfEdges.size() > v * (v - 1))
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
	matrix = new int*[v];
	verticesNumber = v;
	edgesNumber = listOfEdges.size();
	vector<Edge> tempListOfEdges = listOfEdges;

	for (int i = 0; i < v; i++)
	{
		matrix[i] = new int[v];
	}
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			matrix[i][j] = INT_MAX;
		}
	}
	while (!tempListOfEdges.empty())
	{
		matrix[tempListOfEdges.back().fromVertexId][tempListOfEdges.back().destVertexId] = tempListOfEdges.back().weight;
		tempListOfEdges.pop_back();
	}
}
///<note>Budowanie LOSOWEGO grafu nieskierowanego o zadanej ilosci wierzcholkow.
///<note>Metoda sama tworzy krawedzie najpierw tworzac drzewo (dla pewnosci, ze graf bedzie spojny),
///<note>a nastepnie dodajac brakujace krawedzie losowo do grafu.
///<note>Wagi przyjmuja losowa wartosc od 1 do 10.
void GraphMatrix::createRandomGraph(int v, int fillPercent)
{
	if (fillPercent > 100 || fillPercent < 25)
	{
		cout << "Nieprawidlowy wspolczynnik gestosci grafu.\n";
		return;
	}

	srand(time(NULL));
	int edgesToCreate = static_cast<double>(fillPercent) / 100 * (static_cast<double>(v) * (static_cast<double>(v) - 1)) / 2;

	if (edgesToCreate < (v - 1))
	{
		cout << "Nieprawidlowy wspolczynnik gestosci grafu.\n";
		cout << "Nie uda sie przy takiej gestosci uzyskac grafu spojnego.\n";
		return;
	}

	matrix = new int*[v];
	verticesNumber = v;
	edgesNumber = edgesToCreate;

	for (int i = 0; i < v; i++)
	{
		matrix[i] = new int[v];
	}
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
		{
			matrix[i][j] = INT_MAX;
		}
	}

	int v1, v2, w;
	Edge* edge = nullptr;
	//tworzymy najpierw drzewo aby byc pewnym ze graf jest spojny
	for (int i = 0; i < v - 1; i++, edgesToCreate--)
	{
		v2 = i + 1;
		w = rand() % 10 + 1;
		matrix[i][v2] = w;
		matrix[v2][i] = w;
		edge = new Edge (w, i, v2);
		listOfEdges.push_back(*edge);
	}
	//nastepnie reszta krawedzi jest generowana losowo
	for (int i = 0; i < edgesToCreate; i++)
	{
		v1 = rand() % v;
		v2 = rand() % v;
		w = rand() % 10 + 1;
		while (v1 == v2 || matrix[v1][v2] != INT_MAX)
		{
			v1 = rand() % v;
			v2 = rand() % v;
		}
		matrix[v1][v2] = w;
		matrix[v2][v1] = w;
		edge = new Edge (w, v1, v2);
		listOfEdges.push_back(*edge);
	}
	delete edge;
}
///<note>Dodajemy do klasy liste krawedzi wczytana poza klasa (np. z pliku).
void GraphMatrix::copyListOfEdges(vector<Edge> par)
{
	listOfEdges = par;
}
///<note>Wydruk grafu na ekran
void GraphMatrix::print()
{
	cout << "Reprezentacja macierzowa:\n   ";
	for (int i = 0; i < verticesNumber; i++)
	{
		cout << setw(3) << i;
	}
	cout << "\n";
	for (int i = 0; i < verticesNumber; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < verticesNumber; j++)
		{
			if (matrix[i][j] == INT_MAX) cout << setw(3) << "x";
			else if (matrix[i][j] < 10) cout << setw(3) << matrix[i][j];
			else cout << setw(3) << matrix[i][j];
		}
		cout << "\n";
	}
}