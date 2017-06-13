#include "KnapsackProblem.h"
#include <iostream>
#include <iomanip>
#include <windows.h>
//-----------------------------------------------------------------------------
long long int KnapsackProblem::read_QPC()
{
	LARGE_INTEGER count;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&count);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return static_cast<long long int>(count.QuadPart);
}

KnapsackProblem::KnapsackProblem()
{

}

KnapsackProblem::~KnapsackProblem()
{

}
///<note>Algorytm zachalanny wybierajacy przedmioty o najwiekszym stosunku wartosc/waga.
void KnapsackProblem::GreedyByProfit(vector<BpItem> items, int capacity, vector<double> &vectorOfTimes)
{
	if (items.empty() || capacity <= 0)
	{
		cout << "Nieodpowiednie parametry. Brak przedmiotow lub pojemnosc plecaka niedodatnia.\n";
		return;
	}
	
	long long int frequency, timeStart, timeElapsed;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	timeStart = read_QPC();
	priority_queue<BpItem, vector<BpItem>, CmpProfitability> itemQ;
	vector<BpItem> backpack;
	int backpackCurrentWeight = 0, backpackCurrentValue = 0;

	for (int i = 0; i < items.size(); i++)
	{
		itemQ.push(items[i]);
	}

	while (backpackCurrentWeight <= capacity && !itemQ.empty())
	{
		if (backpackCurrentWeight + itemQ.top().weight <= capacity)
		{
			backpack.push_back(itemQ.top());
			backpackCurrentWeight += itemQ.top().weight;
			backpackCurrentValue += itemQ.top().value;
			itemQ.pop();
		}
		else break;
	}

	timeElapsed = read_QPC() - timeStart;
	vectorOfTimes.push_back(static_cast<double>(timeElapsed) / static_cast<double>(frequency) * 1000000.0);
	cout << "\n---Algorytm zachlanny oparty na oplacalnosci przedmiotow---\n\n";
	cout << "Pojemnosc plecaka: " << capacity << "\n";
	cout << "Waga zapakowanych przedmiotow: " << backpackCurrentWeight << "\n";
	cout << "Wartosc zapakowanych przedmiotow: " << backpackCurrentValue << "\n\n";
	cout << "Umieszczone przedmioty:\n";
	cout << "Waga | Wartosc | Oplacalnosc\n";
	for (int i = 0; i < backpack.size(); i++)
	{
		cout << setw(5) << backpack[i].weight << setw(9) << backpack[i].value << setw(12) << backpack[i].profitability << "\n";
	}
}
///<note>Algorytm zachalanny wybierajacy przedmioty o najwiekszej wartosci.
void KnapsackProblem::GreedyByValue(vector<BpItem> items, int capacity, vector<double> &vectorOfTimes)
{
	if (items.empty() || capacity <= 0)
	{
		cout << "Nieodpowiednie parametry. Brak przedmiotow lub pojemnosc plecaka niedodatnia.\n";
		return;
	}
	
	long long int frequency, timeStart, timeElapsed;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	timeStart = read_QPC();
	priority_queue<BpItem, vector<BpItem>, CmpValue> itemQ;
	vector<BpItem> backpack;
	int backpackCurrentWeight = 0, backpackCurrentValue = 0;

	for (int i = 0; i < items.size(); i++)
	{
		itemQ.push(items[i]);
	}

	while (backpackCurrentWeight <= capacity && !itemQ.empty())
	{
		if (backpackCurrentWeight + itemQ.top().weight <= capacity)
		{
			backpack.push_back(itemQ.top());
			backpackCurrentWeight += itemQ.top().weight;
			backpackCurrentValue += itemQ.top().value;
			itemQ.pop();
		}
		else break;
	}

	timeElapsed = read_QPC() - timeStart;
	vectorOfTimes.push_back(static_cast<double>(timeElapsed) / static_cast<double>(frequency) * 1000000.0);
	cout << "\n---Algorytm zachlanny oparty na wartosci przedmiotow---\n\n";
	cout << "Pojemnosc plecaka: " << capacity << "\n";
	cout << "Waga zapakowanych przedmiotow: " << backpackCurrentWeight << "\n";
	cout << "Wartosc zapakowanych przedmiotow: " << backpackCurrentValue << "\n\n";
	cout << "Umieszczone przedmioty:\n";
	cout << "Waga | Wartosc | Oplacalnosc\n";
	for (int i = 0; i < backpack.size(); i++)
	{
		cout << setw(5) << backpack[i].weight << setw(9) << backpack[i].value << setw(12) << backpack[i].profitability << "\n";
	}
}
///<note>Rozwiazanie oparte na programowaniu dynamicznym. Tworzy rozwiazania dla
///<note>pomniejszych problemow i rozwiazanie ostateczne oparte na nich.
void KnapsackProblem::Dynamic(vector<BpItem> items, int capacity, vector<double> &vectorOfTimes)
{	
	if (items.empty() || capacity <= 0)
	{
		cout << "Nieodpowiednie parametry. Brak przedmiotow lub pojemnosc plecaka niedodatnia.\n";
		return;
	}
	
	long long int frequency, timeStart, timeElapsed;
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&frequency));
	timeStart = read_QPC();
	vector<vector<int>> sol(items.size() + 1);
	
	for (int i = 0; i <= items.size(); i++)
		for (int j = 0; j <= capacity; j++)
			sol[i].push_back(0);

	for (int i = 1; i <= items.size()-1; i++)
	{
		int weight = items[i].weight, value = items[i].value;

		for (int j = 1; j <= capacity; j++)
		{
			int prev = sol[i - 1][j];
			if (weight > j) sol[i][j] = prev;
			else
			{
				int next = sol[i - 1][j - weight] + value;
				if (next > prev) sol[i][j] = next;
				else sol[i][j] = prev;
			}
		}
	}

	timeElapsed = read_QPC() - timeStart;
	vectorOfTimes.push_back(static_cast<double>(timeElapsed) / static_cast<double>(frequency) * 1000000.0);
	cout << "\n---Algorytm oparty na programowaniu dynamicznym---\n\n";
	cout << "Pojemnosc plecaka: " << capacity << "\n";
	cout << "Wartosc zapakowanych przedmiotow: " << sol[items.size() - 1][capacity] << "\n";
	cout << "Macierz rozwiazan pomniejszych problemow.\n   ";
	for (int i = 0; i <= capacity; i++)
		cout << setw(3) << i;
	cout << "\n";
	for (int i = 0; i < sol.size(); i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j <= capacity; j++)
			cout << setw(3) << sol[i][j];
		cout << "\n";
	}

	cout << "Umieszczone przedmioty:\n";
	cout << "Waga | Wartosc | Oplacalnosc\n";
	int i = items.size() - 1;
	int j = capacity;
	while (i > 0 && j > 0)
	{
		while (i > 0 && sol[i][j] == sol[i - 1][j]) i--;
		cout << setw(5) << items[i].weight << setw(9) <<items[i].value << setw(12) << items[i].profitability << "\n";
		j -= items[i].weight;
		i--;
	}
}