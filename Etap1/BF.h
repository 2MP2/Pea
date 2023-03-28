#pragma once
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class BF
{
	int** matrix;
	int size;
	int sum;
	int sumMin;
	vector <int> path;
	vector <int> bestPath;

public:

	BF(int** graphCon, int sizeCon);
	void bf(); // liczenie metod¹ BF
	void writeResult(); //wypisanie wyniku

};