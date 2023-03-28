#include "TestTime.h"


long long int TestTime::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

int** TestTime::randomGraf(int size, int maxRandom)
{
	int** matrix = new int* [size];
	for (int i = 0; i < size; i++)
		matrix[i] = new int[size];


	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(0, maxRandom); // distribute results between
												// 1 and 1000000 inclusive

	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++)
		{
			if (i!=j)
				matrix[i][j] = dist(gen); //loswanie liczby w zakresie <0,maxRandom)
			else
				matrix[i][j] = 0;
		}
	}
	return matrix;
}

void TestTime::countTimeBnBMIN_FILE(int size, int** matrix)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	BnBMIN* tsp = new BnBMIN(matrix, size);
	start = read_QPC();
	tsp->BnB();
	elapsed = read_QPC() - start;
	tsp->writeResult();
	delete tsp;

	cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;

}

void TestTime::countTimeBnBALONG_FILE(int size, int** matrix)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	BnBALONG* tsp = new BnBALONG(matrix, size);
	start = read_QPC();
	tsp->BnB();
	elapsed = read_QPC() - start;
	tsp->writeResult();
	delete tsp;

	cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;
}

void TestTime::countTimeBF_FILE(int size, int** matrix)
{
	long long int frequency, start, elapsed;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	BF* tsp = new BF(matrix, size);
	start = read_QPC();
	tsp->bf();
	elapsed = read_QPC() - start;
	tsp->writeResult();
	delete tsp;

	cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;
}

void TestTime::countTimeBnBMIN(int size, int maxRandom, int numberOfRepetitions)
{
	long long int frequency, start, elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	for (int i = 0; i < numberOfRepetitions; i++)
	{
		BnBMIN* tsp = new BnBMIN(randomGraf(size, maxRandom), size);
		start = read_QPC();
		tsp->BnB();
		elapsed += read_QPC() - start;
		delete tsp;
	}

	elapsed /= numberOfRepetitions;
	
	cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;
	
}

void TestTime::countTimeBnBALONG(int size, int maxRandom, int numberOfRepetitions)
{
	long long int frequency, start, elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	for (int i = 0; i < numberOfRepetitions; i++)
	{
		BnBALONG* tsp = new BnBALONG(randomGraf(size, maxRandom), size);
		start = read_QPC();
		tsp->BnB();
		elapsed += read_QPC() - start;
		delete tsp;
	}

	elapsed /= numberOfRepetitions;

	cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;
}

void TestTime::countTimeBF(int size, int maxRandom, int numberOfRepetitions)
{
	long long int frequency, start, elapsed = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);

	for (int i = 0; i < numberOfRepetitions; i++)
	{
		BF* tsp = new BF(randomGraf(size, maxRandom), size);
		start = read_QPC();
		tsp->bf();
		elapsed += read_QPC() - start;
		delete tsp;
	}

	elapsed /= numberOfRepetitions;

	cout << "Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;
}
