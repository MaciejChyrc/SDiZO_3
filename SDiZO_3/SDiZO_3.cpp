#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <conio.h>
#include "GraphMatrix.h"
#include "KnapsackProblem.h"
#include "TravelingSalesmanProblem.h"
#include <ctime>
#include <iomanip>

using namespace std;

double averageOperationTime (const vector<double> vectorOfTimes);
void readCitiesFromTextFile (string filepath, GraphMatrix *graphM);
void readKnapsackParametersFromTextFile (string filepath, int &capacity, vector<BpItem> &items);
void saveTimesToTextFile (bool kpOrTsp, string capOrCities, string nOfItems, double avgTime1, double avgTime2, double avgTime3);
void knapsackTests (vector<double> &greedyProfitTimes, vector<double> &greedyValueTimes, vector<double> &dynamicTimes);
void tspTests (vector<double> &tspGreedyTimes);
vector<BpItem> generateRandomItemSet (int numberOfItems);

int main()
{
	string filepath = "";
	char menuKey = 0, menuKeySecondary = 0;
	int knapsackCapacity = 0;
	vector<BpItem> knapsackProblemItems;
	GraphMatrix *tspCities = new GraphMatrix ();
	vector<double> greedyProfitTimes, greedyValueTimes, dynamicTimes, tspGreedyTimes;

	srand(time(NULL));

	do
	{
		cout << "\n---------------GLOWNE MENU---------------\n"
			<< "1. Wczytaj dane do problemu plecakowego z pliku.\n"
			<< "2. Wczytaj dane do problemu komiwojazera z pliku.\n"
			<< "3. Problem plecakowy.\n"
			<< "4. Problem komiwojazera.\n"
			<< "5. Zautomatyzowane testy czasowe.\n"
			<< "6. Zresetuj obiekty.\n"
			<< "0. Wyjdz z programu.\n"
			<< "Wcisnij przycisk...\n";
		menuKey = _getch();
		switch (menuKey)
		{
		case '1':
			system("cls");
			cout << "Podaj sciezke wczytywanego pliku\n"
				<< "Na przyklad: C:\\\\Users\\\\User\\\\Documents\\\\textfile.txt\n"
				<< "Pamietaj o podwojnych backslashach jesli podajesz pelna sciezke!\n";
			cin >> filepath;
			readKnapsackParametersFromTextFile(filepath, knapsackCapacity, knapsackProblemItems);
			break;
		case '2':
			system("cls");
			cout << "Podaj sciezke wczytywanego pliku\n"
				<< "Na przyklad: C:\\\\Users\\\\User\\\\Documents\\\\textfile.txt\n"
				<< "Pamietaj o podwojnych backslashach jesli podajesz pelna sciezke!\n";
			cin >> filepath;
			readCitiesFromTextFile(filepath, tspCities);
			break;
		case '3':
			do
			{
				//system("cls");
				cout << "\n------------PROBLEM PLECAKOWY------------\n"
					<< "1. Rozwiaz problem plecakowy algorytmem zachlannym wyberajac przedmioty\n   o najwiekszym stosunku wartosc/waga.\n"
					<< "2. Rozwiaz problem plecakowy algorytmem zachlannym wyberajac przedmioty\n   o najwiekszej wartosci.\n"
					<< "3. Rozwiaz problem plecakowy algorytmem opartym na programowaniu dynamicznym.\n"
					<< "4. Wszyscy razem!\n"
					<< "9. Wroc do glownego menu.\n";
				menuKey = _getch();
				switch (menuKey)
				{
				case '1':
					KnapsackProblem::GreedyByProfit(knapsackProblemItems, knapsackCapacity, greedyProfitTimes);
					break;
				case '2':
					KnapsackProblem::GreedyByValue(knapsackProblemItems, knapsackCapacity, greedyValueTimes);
					break;
				case '3':
					KnapsackProblem::Dynamic(knapsackProblemItems, knapsackCapacity, dynamicTimes);
					break;
				case '4':
					KnapsackProblem::GreedyByProfit(knapsackProblemItems, knapsackCapacity, greedyProfitTimes);
					KnapsackProblem::GreedyByValue(knapsackProblemItems, knapsackCapacity, greedyValueTimes);
					KnapsackProblem::Dynamic(knapsackProblemItems, knapsackCapacity, dynamicTimes);
					break;
				case '0':
					menuKey = '9';
					break;
				default:
					break;
				}
			} while (menuKey != '9');
			break;
		case '4':
			do
			{
				//system("cls");
				cout << "\n-----------PROBLEM KOMIWOJAZERA----------\n"
					<< "1. Wyznacz najkrotsza droge algorytmem zachlannym.\n"
					<< "9. Wroc do glownego menu.\n";
				menuKey = _getch();
				switch (menuKey)
				{
				case '1':
					TravelingSalesmanProblem::GreedyBasedOnPrim(0, tspCities, tspGreedyTimes);
					break;
				case '0':
					menuKey = '9';
					break;
				default:
					break;
				}
			} while (menuKey != '9');
			break;
		case '5':
			do
			{
				//system("cls");
				cout << "\n---------------TRYB TESTOWY--------------\n"
					<< "1. Przeprowadz testy dla problemu plecakowego.\n"
					<< "2. Przeprowadz testy dla problemu komiwojazera.\n"
					<< "9. Wroc do glownego menu.\n";
				menuKey = _getch();
				switch (menuKey)
				{
				case '1':
					do
					{
						cout << "Na pewno chcesz przeprowadzic testy?\nMoze to chwilke zajac. (y/n)\n";
						menuKeySecondary = _getch();
						if (menuKeySecondary == 'y' || menuKeySecondary == 'Y')
						{
							knapsackTests(greedyProfitTimes, greedyValueTimes, dynamicTimes);
						}
					} while (menuKeySecondary != 'y' && menuKeySecondary != 'Y' && menuKeySecondary != 'n' && menuKeySecondary != 'N');
					break;
				case '2':
					do
					{
						cout << "Na pewno chcesz przeprowadzic testy?\nMoze to chwilke zajac. (y/n)\n";
						menuKeySecondary = _getch();
						if (menuKeySecondary == 'y' || menuKeySecondary == 'Y')
						{
							tspTests(tspGreedyTimes);
						}
					} while (menuKeySecondary != 'y' && menuKeySecondary != 'Y' && menuKeySecondary != 'n' && menuKeySecondary != 'N');
					break;
				case '0':
					menuKey = '9';
					break;
				default:
					break;
				}
			} while (menuKey != '9');
			break;
		case '6':
			knapsackCapacity = 0;
			knapsackProblemItems.clear();
			delete tspCities;
			tspCities = new GraphMatrix ();
			cout << "Zresetowano obiekty.\n";
			break;
		default:
			break;
		}
	} while (menuKey != '0');

	delete tspCities;

	return 0;
}
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
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
//-----------------------------------------------------------------------------
void saveTimesToTextFile (bool kpOrTsp, string capOrCities, string nOfItems, double avgTime1, double avgTime2, double avgTime3)
{
	string winUser = "";
	cout << "Nazwe uzytkownika w windowsie";
	cin >> winUser;
	if (kpOrTsp)
	{
		std::ofstream file;
		string numberOfCities = capOrCities;
		//cout << "Podaj ilosc miast:\n";
		//cin >> numberOfCities;
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
		string capacity = capOrCities, numberOfItems = nOfItems;
		//cout << "Podaj pojemnosc plecaka:\n";
		//cin >> capacity; 
		//cout << "Podaj ilosc przedmiotow:\n";
		//cin >> numberOfItems;
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
//-----------------------------------------------------------------------------
void knapsackTests (vector<double> &greedyProfitTimes, vector<double> &greedyValueTimes, vector<double> &dynamicTimes)
{
	int numberOfItems = 10;
	vector<BpItem> testItems;
	//testy dla 10 przedmiotow i pojemnosci 10, 15, 20
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 10, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 10, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 10, dynamicTimes);
	}
	saveTimesToTextFile(false, "10", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 15, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 15, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 15, dynamicTimes);
	}
	saveTimesToTextFile(false, "15", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 20, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 20, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 20, dynamicTimes);
	}
	saveTimesToTextFile(false, "20", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();

	numberOfItems = 15;
	//testy dla 15 przedmiotow i pojemnosci 10, 15, 20
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 10, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 10, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 10, dynamicTimes);
	}
	saveTimesToTextFile(false, "10", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 15, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 15, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 15, dynamicTimes);
	}
	saveTimesToTextFile(false, "15", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 20, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 20, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 20, dynamicTimes);
	}
	saveTimesToTextFile(false, "20", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();

	numberOfItems = 20;
	//testy dla 20 przedmiotow i pojemnosci 10, 15, 20
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 10, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 10, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 10, dynamicTimes);
	}
	saveTimesToTextFile(false, "10", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 15, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 15, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 15, dynamicTimes);
	}
	saveTimesToTextFile(false, "15", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 20, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 20, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 20, dynamicTimes);
	}
	saveTimesToTextFile(false, "20", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();

	numberOfItems = 25;
	//testy dla 25 przedmiotow i pojemnosci 10, 15, 20
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 10, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 10, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 10, dynamicTimes);
	}
	saveTimesToTextFile(false, "10", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 15, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 15, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 15, dynamicTimes);
	}
	saveTimesToTextFile(false, "15", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 20, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 20, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 20, dynamicTimes);
	}
	saveTimesToTextFile(false, "20", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();

	numberOfItems = 30;
	//testy dla 30 przedmiotow i pojemnosci 10, 15, 20
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 10, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 10, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 10, dynamicTimes);
	}
	saveTimesToTextFile(false, "10", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 15, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 15, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 15, dynamicTimes);
	}
	saveTimesToTextFile(false, "15", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();
	for (int i = 0; i < 100; i++)
	{
		testItems = generateRandomItemSet(numberOfItems);
		KnapsackProblem::GreedyByProfit(testItems, 20, greedyProfitTimes);
		KnapsackProblem::GreedyByValue(testItems, 20, greedyValueTimes);
		KnapsackProblem::Dynamic(testItems, 20, dynamicTimes);
	}
	saveTimesToTextFile(false, "20", to_string(numberOfItems), averageOperationTime(greedyProfitTimes), averageOperationTime(greedyValueTimes), averageOperationTime(dynamicTimes));
	greedyProfitTimes.clear();
	greedyValueTimes.clear();
	dynamicTimes.clear();

	cout << "Test zakonczony.\n";
}
//-----------------------------------------------------------------------------
void tspTests (vector<double> &tspGreedyTimes)
{
	int numberOfCities = 20;
	GraphMatrix *cities = new GraphMatrix ();

	while (numberOfCities <= 100)
	{
		for (int i = 0; i < 100; i++)
		{
			delete cities;
			cities = new GraphMatrix ();
			cities->createRandomGraph(numberOfCities, 100);
			TravelingSalesmanProblem::GreedyBasedOnPrim(0, cities, tspGreedyTimes);
		}
		saveTimesToTextFile(true, to_string(numberOfCities), "", averageOperationTime(tspGreedyTimes), NULL, NULL);
		tspGreedyTimes.clear();
		numberOfCities += 20;
	}

	cout << "Test zakonczony.\n";
}
//-----------------------------------------------------------------------------
vector<BpItem> generateRandomItemSet (int numberOfItems)
{
	vector<BpItem> result;
	BpItem *temp = new BpItem ();
	int v, w;

	for (int i = 0; i < numberOfItems; i++)
	{
		delete temp;
		v = rand () % 10 + 1;
		w = rand () % 10 + 1;
		temp = new BpItem (v, w);
		result.push_back(*temp);
	}

	delete temp;

	return result;
}