#pragma once
#include <iostream>
#include <iomanip> 
#include <vector>
#include <list>
#include <queue>
#include <chrono>
#include <random>
#include <windows.h>

using namespace std;
using namespace std::chrono_literals;
using Clock = std::chrono::system_clock;

class TabuSearch
{
	int** matrix; //graf
	int size; //wielkoœæ grafu
	unsigned long long stopTime; //czas w sekundach

	vector <int > bestPath; //najlepsza œcie¿ka
	int bestPathLength; //koszt najlepszej œcie¿ki 

	vector <int > currentPath; //obecna œcie¿ka 
	int currentPathLength; //koszt obecnej œcie¿ki 

	int** tabuMatrix; //Tabu List
	list<vector<int>> tabuHelp; //tu znajduja siê krawêdzie dodane do tabu (struktura pomocnicza)
	int tabuTenure; //kadencja

	long int whenDiversification; //po ilu cyklach wykonac dywersyfikacje 
	long int countNotFind; //licznik do dywersyfikacji 

	long long int frequency, start, elapsed; //zmienne potrzebne do wyliczenia najlepszego czasu

	//prawdopodobna zamia wierzcho³ków i jej koszt 
	struct Move
	{
		int vIndex1;
		int vIndex2;
		int cost;

		bool operator<(const Move& o) const
		{
			return cost > o.cost;
		}
	};


	void coutFirstPath(); //znalezienie pierwszej drogi greedy algorymem 
	priority_queue<Move> generateNeighbourhood(vector<int> path); //tworzenie s¹siedztwa 
	void decrementTabuMatrix(); //zmiejszenie kadencji zakazanych krawedzi i usuniêcie z tabuHelp wketorów 
	void checkIfBestPath(); //porównanie najlepszej i obecnej drogi i zamina jesli obecna jest mniejsza 
	void diversification(); //dywersyfikacja
	void clearQueue(priority_queue<Move>& q);//usuniecie wszystkich wartoœci z kolejki 
	long long int read_QPC(); 

public:
	TabuSearch(int** matrixCon, int sizeCon, unsigned long long stopTimeCon);
	~TabuSearch();

	void tabuSearch(bool isDiversification); //g³ówna metoda 
	void writeResult(); //wypisanie wyników 


};