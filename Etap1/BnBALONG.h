#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip> 
#include <vector>
#include <list>
#include <queue>

using namespace std;

class BnBALONG
{
	struct Node
	{
		int pathCost;
		int v;
		vector <int> path;

		bool operator<(const Node& o) const
		{
			return pathCost > o.pathCost;
		}
	};

	int** matrix;
	int size;
	Node HB;
	list <Node> mainList;

	void writeList(list <Node> listW);
	bool checkNewHB(Node node);//metoda sprawdza czy obecny node mo�e by� HB
	bool checkLB(Node node);//sprawdza LB dla danego w�z�a 
	void addKidsToList(Node node);//dodanie wszystkich dzici wez�a do kolejki piorytetowej

public:

	BnBALONG(int** graphCon, int sizeCon);
	void BnB(); // liczenie metod� B and B sprawdzaj�c graf w wzd�u�
	void writeResult(); // wypisanie wyniku
	
};