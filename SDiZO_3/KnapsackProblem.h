#pragma once
#include <vector>
#include <queue>
#include "MinorStructs.h"

using namespace std;

class KnapsackProblem
{

public:
	KnapsackProblem();
	~KnapsackProblem();
	static void GreedyByProfit(vector<BpItem> items, int capacity);
	static void GreedyByValue(vector<BpItem> items, int capacity);
	static void Dynamic(vector<BpItem> items, int capacity);
};