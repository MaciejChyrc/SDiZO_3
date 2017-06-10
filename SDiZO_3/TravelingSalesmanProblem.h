#pragma once
#include "GraphMatrix.h"

class TravelingSalesmanProblem
{
private:
	//static int minCost;
	static long long int read_QPC();
public:
	TravelingSalesmanProblem();
	~TravelingSalesmanProblem();
	/*static int minCost;
	static int getMinCost ();
	static void setMinCostToMaxInt ();
	static void swap (int *city1, int *city2);
	static void calculateCost (int *city, int n, int **graph, int graphSize);
	static void permute (int *city, int i, int n, int **graph, int graphSize);*/
	static void GreedyBasedOnPrim (int startV, GraphMatrix *graphMatrix, vector<double> &vectorOfTimes);
};