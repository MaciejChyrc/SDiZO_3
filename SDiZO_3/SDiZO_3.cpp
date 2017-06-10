#include <iostream>
#include <cstdlib>
#include "GraphMatrix.h"
#include "KnapsackProblem.h"
#include "TravelingSalesmanProblem.h"
#include <ctime>

using namespace std;

int main()
{
	srand(time(NULL));
	BpItem item(1, 4), item2(5, 6), item3(2, 2), item4(4, 2);
	vector<BpItem> vec;
	vec.push_back(item); vec.push_back(item2); vec.push_back(item3); vec.push_back(item4);
	KnapsackProblem::Dynamic(vec, 10);
	/*KnapsackProblem::GreedyByProfit(vec, 6);
	KnapsackProblem::GreedyByValue(vec, 6);*/
	/*GraphMatrix *graphM = new GraphMatrix ();
	graphM->createRandomGraph(10, 100);
	graphM->print();
	int** graph = graphM->matrix;
	int graphSize = graphM->getVerticesNumber();
	TravelingSalesmanProblem::TspGreedyBasedOnPrim(0, graphM);
	delete graphM;*/
	system("PAUSE");
}