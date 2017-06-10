#include "KnapsackProblem.h"
#include <iostream>
#include <iomanip>

KnapsackProblem::KnapsackProblem()
{

}

KnapsackProblem::~KnapsackProblem()
{

}

void KnapsackProblem::GreedyByProfit(vector<BpItem> items, int capacity)
{
	priority_queue<BpItem, vector<BpItem>, CmpProfitability> itemQ;
	
	for (int i = 0; i < items.size(); i++)
	{
		itemQ.push(items[i]);
	}
	
	vector<BpItem> backpack;
	int backpackCurrentWeight = 0, backpackCurrentValue = 0;

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

void KnapsackProblem::GreedyByValue(vector<BpItem> items, int capacity)
{
	priority_queue<BpItem, vector<BpItem>, CmpValue> itemQ;

	for (int i = 0; i < items.size(); i++)
	{
		itemQ.push(items[i]);
	}

	vector<BpItem> backpack;
	int backpackCurrentWeight = 0, backpackCurrentValue = 0;

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

void KnapsackProblem::Dynamic(vector<BpItem> items, int capacity)
{	
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

	cout << "Max wartosc: " << sol[items.size() - 1][capacity] << "\n   ";

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
}