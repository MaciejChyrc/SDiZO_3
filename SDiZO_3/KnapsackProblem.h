#pragma once
#include <vector>
#include <queue>
#include "MinorStructs.h"

using namespace std;

class KnapsackProblem
{
	static long long int read_QPC();
public:
	KnapsackProblem();
	~KnapsackProblem();
	static void GreedyByProfit(vector<BpItem> items, int capacity, vector<double> &vectorOfTimes);
	static void GreedyByValue(vector<BpItem> items, int capacity, vector<double> &vectorOfTimes);
	static void Dynamic(vector<BpItem> items, int capacity, vector<double> &vectorOfTimes);
};