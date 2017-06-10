#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "GraphMatrix.h"
#include "KnapsackProblem.h"
#include "TravelingSalesmanProblem.h"
#include <ctime>
#include <iomanip>

using namespace std;

double averageOperationTime (const vector<double> vectorOfTimes);
void readCitiesFromTextFile (string filepath, GraphMatrix *graphM);
void readKnapsackParametersFromTextFile (string filepath, int &capacity, vector<BpItem> &items);
void saveTimesToTextFile (bool kpOrTsp, string size1, string size2, double avgTime1, double avgTime2, double avgTime3);

int main()
{
	return 0;
}

double averageOperationTime (const vector<double> vectorOfTimes)
{
	double averageTime = 0;
	for (int i = 0; i < vectorOfTimes.size(); i++)
	{
		averageTime += vectorOfTimes[i];
	}
	averageTime = averageTime / vectorOfTimes.size();

	return averageTime;
}

void readCitiesFromTextFile (string filepath, GraphMatrix *graphM)
{
	vector<Edge> edges;
	ifstream file;
	file.open(filepath, ios::in);
	if (file.is_open())
	{
		Edge temp;
		int verticesNumber = 0, startVertex = 0;
		file >>  verticesNumber;
		if (file.fail()) cout << "Blad odczytu pierwszej linii pliku.\n";
		else
		{
			for (int i = 0; i < verticesNumber; i++)
			{
				for (int j = 0; j < verticesNumber; j++)
				{
					temp.fromVertexId = i;
					file >> temp.weight;
					temp.destVertexId = j;
					if (file.fail())
					{
						cout << "Blad odczytu.\n";
						return;
					}
					edges.push_back(temp);
				}
			}
			graphM->copyListOfEdges(edges);
			graphM->createGraphFromListOfEdges(verticesNumber);
			graphM->setStartVertex(startVertex);
			file.close();
		}
	}
	else cout << "Blad otwarcia pliku.\n";
}

void readKnapsackParametersFromTextFile(string filepath, int &capacity, vector<BpItem> &items)
{
	ifstream file;
	file.open(filepath, ios::in);
	if (file.is_open())
	{
		int numberOfItems = 0, w, v;
		BpItem *temp = new BpItem();
		file >> capacity >> numberOfItems;
		if (file.fail()) cout << "Blad odczytu pierwszej linii pliku.\n";
		else
		{
			for (int i = 0; i < numberOfItems; i++)
			{
				delete temp;
				file >> w >> v;
				temp = new BpItem(v, w);
				if (file.fail())
				{
					cout << "Blad odczytu.\n";
					return;
				}
				items.push_back(*temp);
			}
			file.close();
		}
	}
	else cout << "Blad otwarcia pliku.\n";
}

void saveTimesToTextFile (bool kpOrTsp, string size1, string size2, double avgTime1, double avgTime2, double avgTime3)
{
	string winUser = "";
	cout << "Nazwe uzytkownika w windowsie";
	cin >> winUser;
	if (kpOrTsp)
	{
		std::ofstream file;
		string numberOfCities;
		cout << "Podaj ilosc miast:\n";
		cin >> numberOfCities;
		file.open("c:\\users\\" + winUser + "\\desktop\\komiwojazer" + numberOfCities + ".txt", std::ios::out);

		if (file.is_open())
		{
			file << "Greedy\n";
			if (file.fail()) std::cerr << "Blad zapisu.\n";
			else
			{
				file << avgTime1;
				if (file.fail()) std::cerr << "Blad zapisu.\n";
			}
			file.close();
		}
		else std::cerr << "Blad otwarcia pliku.\n";
	}
	else
	{
		std::ofstream file;
		string capacity, numberOfItems;
		cout << "Podaj pojemnosc plecaka:\n";
		cin >> capacity; 
		cout << "Podaj ilosc przedmiotow:\n";
		cin >> numberOfItems;
		file.open("c:\\users\\" + winUser + "\\desktop\\plecak_poj" + capacity + "_przed" + numberOfItems + ".txt", std::ios::out);

		if (file.is_open())
		{
			file << "GreedyProfit, GreedyValue, Dynamic\n";
			if (file.fail()) std::cerr << "Blad zapisu.\n";
			else
			{
				file << setw(12) << avgTime1 << ", " << setw(11) << avgTime2 << ", " << setw(7) << avgTime3;
				if (file.fail()) std::cerr << "Blad zapisu.\n";
			}
			file.close();
		}
		else std::cerr << "Blad otwarcia pliku.\n";
	}
}