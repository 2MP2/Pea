#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip> 
#include <vector>
#include <queue>


using namespace std;

class BnBMIN
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
	priority_queue <Node> pq;

	void writeQueue(priority_queue <Node> q);
	Node findHB();//metoda znajduje "losowe" HB (nazuwane UB)
	bool checkNewHB(Node node);//metoda sprawdza czy obecny node mo¿e byæ HB
	bool checkLB(Node node);//sprawdza LB dla danego wêz³a 
	void addKidsToQueue(Node node);//dodanie wszystkich dzici wez³a do kolejki piorytetowej

public:
	
	BnBMIN(int ** graphCon, int sizeCon);
	void BnB(); // liczenie metod¹ B and B sprawdzaj¹c zawsze najlepszy wêze³
	void writeResult(); //wypisanie wyniku 
};
