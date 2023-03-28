#pragma once
#include <iostream>
#include <windows.h>
#include <iomanip> 
#include <random>
#include "FileReader.h"
#include "BnBMIN.h"
#include "BnBALONG.h"
#include "BF.h"



using namespace std;

class TestTime
{

	long long int read_QPC();
	int** randomGraf(int size, int maxRandom);

public:
	
	void countTimeBnBMIN(int size, int maxRandom, int numberOfRepetitions);
	void countTimeBnBALONG(int size, int maxRandom, int numberOfRepetitions);
	void countTimeBF(int size, int maxRandom, int numberOfRepetitions);

	void countTimeBnBMIN_FILE(int size, int** matrix);
	void countTimeBnBALONG_FILE(int size, int** matrix);
	void countTimeBF_FILE(int size, int** matrix);
	
};