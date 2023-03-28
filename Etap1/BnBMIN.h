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
	bool checkNewHB(Node node);//metoda sprawdza czy obecny node mo�e by� HB
	bool checkLB(Node node);//sprawdza LB dla danego w�z�a 
	void addKidsToQueue(Node node);//dodanie wszystkich dzici wez�a do kolejki piorytetowej

public:
	
	BnBMIN(int ** graphCon, int sizeCon);
	void BnB(); // liczenie metod� B and B sprawdzaj�c zawsze najlepszy w�ze�
	void writeResult(); //wypisanie wyniku 
};
