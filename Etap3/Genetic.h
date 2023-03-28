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

class Genetic
{
	int** matrix; // graf
	int size; // wielkoœæ grafu
	unsigned long long stopTime; // czas w sekundach

	long long int frequency, start, elapsed; // zmienne potrzebne do wyliczenia najlepszego czasu

	struct Journey
	{
		vector <int> path;
		int cost;
	};

	Journey theBest; //najlepsza scie¿ka 

	int crossoverProbability; // w promilach 
	int mutationProbability; // w promilach 
	int populationSize;

	vector <Journey> population; 


	void mutation(Journey& journey); // zamiana max 4 wierzcho³ki 
	void mutation2(Journey& journey); // 2 krawêdzie zamiana (odwrócenie kawa³ka cyklu)
	Journey crossover(Journey journey1, Journey journey2); // jednopuntkowy crossover
	Journey crossover2(Journey journey1, Journey journey2); // Operator krzy¿owania PMX
	void firstPopulation(); // tworzenie pierwszej populacji 
	void newPopulation(int mut, int cross); // tworzenie nowej populacji. Mozliwy wybór cross i mut 

	long long int read_QPC();
	void writeResult(); // wypisanie wyników 
	bool random(int probability); // funkcja zwraca true albo false. Podaje sie prawd. na true
	int countPathCost(Journey journey); // oblicza koszt œcie¿ki
	int randomNumber(int min, int max); // zwraca losow¹ liczbê z zakresu <min,max>
	void changeBestPath(Journey journey);// jesli journey ma mniejszy koszt to staje siê theBest
	void coutPopulation(); //funkcja pomocnicza do testów 
	void coutPath(Journey journey); //funkcja pomocnicza do testów

public:
	Genetic(int** matrixCon, int sizeCon, unsigned long long stopTimeCon,
			int populationSize, int crossoverProbabilityCon, int mutationProbabilityCon);
	void genetic(int mut, int cross);//g³ówna funkcja 

};