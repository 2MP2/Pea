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
	int size; // wielko�� grafu
	unsigned long long stopTime; // czas w sekundach

	long long int frequency, start, elapsed; // zmienne potrzebne do wyliczenia najlepszego czasu

	struct Journey
	{
		vector <int> path;
		int cost;
	};

	Journey theBest; //najlepsza scie�ka 

	int crossoverProbability; // w promilach 
	int mutationProbability; // w promilach 
	int populationSize;

	vector <Journey> population; 


	void mutation(Journey& journey); // zamiana max 4 wierzcho�ki 
	void mutation2(Journey& journey); // 2 kraw�dzie zamiana (odwr�cenie kawa�ka cyklu)
	Journey crossover(Journey journey1, Journey journey2); // jednopuntkowy crossover
	Journey crossover2(Journey journey1, Journey journey2); // Operator krzy�owania PMX
	void firstPopulation(); // tworzenie pierwszej populacji 
	void newPopulation(int mut, int cross); // tworzenie nowej populacji. Mozliwy wyb�r cross i mut 

	long long int read_QPC();
	void writeResult(); // wypisanie wynik�w 
	bool random(int probability); // funkcja zwraca true albo false. Podaje sie prawd. na true
	int countPathCost(Journey journey); // oblicza koszt �cie�ki
	int randomNumber(int min, int max); // zwraca losow� liczb� z zakresu <min,max>
	void changeBestPath(Journey journey);// jesli journey ma mniejszy koszt to staje si� theBest
	void coutPopulation(); //funkcja pomocnicza do test�w 
	void coutPath(Journey journey); //funkcja pomocnicza do test�w

public:
	Genetic(int** matrixCon, int sizeCon, unsigned long long stopTimeCon,
			int populationSize, int crossoverProbabilityCon, int mutationProbabilityCon);
	void genetic(int mut, int cross);//g��wna funkcja 

};