#pragma once
///<note>Pomniejsze struktury: krawedz(waga ,v poczatkowy, v koncowy),
///<note>krawedz do listy sasiadow (waga, v koncowy, wskaznik na nastepny element),
///<note>przedmiot wkladany do plecaka (wartosc, waga, stosunek wartosc/waga),
///<note>struktury porownan wykorzystywane w kolejce priorytetowej biblioteki standardowej
struct Edge
{
	int weight, fromVertexId, destVertexId;

	Edge ()
	{
		weight = -1; fromVertexId = -1; destVertexId = -1;
	}

	Edge (int weight, int fromVertexId, int destVertexId)
	{
		this->weight = weight;
		this->fromVertexId = fromVertexId;
		this->destVertexId = destVertexId;
	}
};

struct ListElement
{
	ListElement* next;
	int weight, destVertexId;
};

struct BpItem
{
	int value, weight;
	double profitability;

	BpItem ()
	{
		this->value = 0;
		this->weight = 0;
		this->profitability = static_cast<double>(value) / static_cast<double>(weight);
	}

	BpItem (int value, int weight)
	{
		this->value = value;
		this->weight = weight;
		this->profitability = static_cast<double>(value) / static_cast<double>(weight);
	}
};

struct CmpProfitability
{
	bool operator () (BpItem const& item1, BpItem const& item2)
	{
		return item1.profitability < item2.profitability;
	}
};

struct CmpValue
{
	bool operator () (BpItem const& item1, BpItem const& item2)
	{
		return item1.value < item2.value;
	}
};

struct CmpEdgeWeight
{
	bool operator () (Edge const& e1, Edge const& e2)
	{
		return e1.weight > e2.weight;
	}
};