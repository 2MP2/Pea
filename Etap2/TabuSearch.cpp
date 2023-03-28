#include "TabuSearch.h"

TabuSearch::TabuSearch (int** matrixCon, int sizeCon, unsigned long long stopTimeCon)
{
	matrix = matrixCon;
	size = sizeCon;
	stopTime = stopTimeCon;

	tabuMatrix = new int* [size];
	for (int i = 0; i < size; i++)
		tabuMatrix[i] = new int[size];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			tabuMatrix[i][j] = 0;

	whenDiversification = 20000;
	tabuTenure = size;
	bestPathLength = 0;
	currentPathLength = 0;
	countNotFind = 0;
}

void  TabuSearch::coutFirstPath()
{
	//greedy algorytm 
	vector <int> notVisitedV;
	vector<int>::iterator it;
	int min = INT_MAX;
	int minV;


	for (int i = 1; i < size; i++)
		notVisitedV.push_back(i);

	bestPath.push_back(0); // 0 jest pocz¹tkowy wierzcho³kiem 
	currentPath.push_back(0); // 0 jest pocz¹tkowy wierzcho³kiem

	while (!notVisitedV.empty())
	{
		for (int i = 0; i < notVisitedV.size(); i++)
		{
			if (min > matrix[currentPath.back()][notVisitedV[i]])
			{
				min = matrix[currentPath.back()][notVisitedV[i]];
				minV = notVisitedV[i];
				it = notVisitedV.begin() + i;
			}
		}
		bestPath.push_back(minV);
		currentPath.push_back(minV);
;
		bestPathLength += min;
		currentPathLength += min;

		min = INT_MAX;
		notVisitedV.erase(it);
	}

	bestPathLength += matrix[currentPath.back()][0]; //dodanie dorogi z ostatniego do 0
	currentPathLength += matrix[currentPath.back()][0]; //dodanie dorogi z ostatniego do 0
}

priority_queue<TabuSearch::Move> TabuSearch::generateNeighbourhood(vector<int> path)
{
	priority_queue <Move> pq;
	Move move;
	int cost = 0;

	//dodanie do kolejki piorytetowej wszystkich wariancji ze zmiana wierzcho³ka
	//na 1 pozycji z pozosta³ym wierzcho³kami prócz z 0 pozycji 
	// koszt to ró¿nica drogi nowopowsta³ej i obecnej 
	for (int i = 2; i < size; i++)
	{
		move.vIndex1 = 1;
		move.vIndex2 = i;

		swap(currentPath[1], currentPath[i]);

		for (int j = 0; j < size-1; j++)
		{
			cost+= matrix[currentPath[j]][currentPath[j+1]];
		}
		cost+= matrix[currentPath[size-1]][currentPath[0]];

		move.cost = cost - currentPathLength;
		cost = 0;

		swap(currentPath[1], currentPath[i]);
		pq.push(move);
	}

	return pq;
}

void  TabuSearch::decrementTabuMatrix()
{
	list<vector<int>>::iterator itHelp = tabuHelp.begin();
	list<vector<int>>::iterator it;
	vector<int> vec;
	bool block = false;



	for (it = tabuHelp.begin(); it != tabuHelp.end(); ++it)
	{
		vec = *it;
		
		//dzia³amy na po³owie tabuMatrix bo nie ma znaczenia 
		//czy zamienimy wierzcho³ek A z B czy B z A 
		//ale wiem ze zawsze wketory w tabuHelp s¹ juz puk³adane 
		if (tabuMatrix[vec[0]][vec[1]] == 1)
			block = true;

		tabuMatrix[vec[0]][vec[1]]--;

		if(!block)
		itHelp++;
	}

	if (block)
	{
		vec = *itHelp;
		vec.clear();
		vec.shrink_to_fit();
		tabuHelp.erase(itHelp);
	}

}

void TabuSearch::checkIfBestPath()
{
	if (currentPathLength < bestPathLength)
	{
		bestPath = currentPath;
		bestPathLength = currentPathLength;
		countNotFind = 0; //resetujemy licznik do dywersyfikacji 
		elapsed = read_QPC() - start; //zmienna do obliczenia czasu

		writeResult();
	}
}

long long int TabuSearch::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

//odrazu zamina v1 i v2 jesli wieksze 

void  TabuSearch::tabuSearch(bool isDiversification)
{
	priority_queue <Move> pq;
	bool keepGooing;

	int v1, v2;
	coutFirstPath();
	
	std::chrono::seconds stop = std::chrono::seconds(stopTime); //zaminana na skeundy 
	auto timeLimit = Clock::now() + stop;

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC(); 

	writeResult();

	while (Clock::now() < timeLimit)
	{
		countNotFind++;
		keepGooing = true;
		pq = generateNeighbourhood(currentPath);

		while (keepGooing)
		{
			v1 = currentPath[pq.top().vIndex1];
			v2 = currentPath[pq.top().vIndex2];

			if (v2 < v1) //uzywamy tylko 1/2 tabuMatrix bo A do B to B do A
				swap(v1, v2);

			if (tabuMatrix[v1][v2])  
			{
				if (currentPathLength + pq.top().cost < bestPathLength)
				{
					tabuMatrix[v1][v2] = tabuTenure + 1;
					decrementTabuMatrix();
					swap(currentPath[pq.top().vIndex1], currentPath[pq.top().vIndex2]);
					keepGooing = false;

					currentPathLength += pq.top().cost; 
					checkIfBestPath();
				}
				else
				{
					if (pq.size() == 1) //wybieramy ostatni aby unikn¹æ pêtlenia siê algorytmu
					{
						tabuMatrix[v1][v2] = tabuTenure + 1;
						decrementTabuMatrix();
						swap(currentPath[pq.top().vIndex1], currentPath[pq.top().vIndex2]);
						keepGooing = false;

						currentPathLength += pq.top().cost;
					}
					else
						pq.pop();
				}
					
			}
			else //gdy nie jest na liscie tabu 
			{
				decrementTabuMatrix();
				tabuMatrix[v1][v2] = tabuTenure;

				vector <int> vec{ v1,v2 };
				tabuHelp.push_back(vec);
				swap(currentPath[pq.top().vIndex1], currentPath[pq.top().vIndex2]);
				keepGooing = false;
				currentPathLength += pq.top().cost;

				if (pq.top().cost < 0)
					checkIfBestPath();
			}
		}
		
		if (countNotFind > whenDiversification && isDiversification)
			diversification();

		clearQueue(pq);
	}
}

void  TabuSearch::writeResult()
{
	for (int i = 0; i < size; i++)
		cout << bestPath[i] << " ";
	cout << "0";
	cout << endl;
	cout << "Koszt to: " << bestPathLength << endl;

	cout << "bestPath Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "bestPath Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "bestPath Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;
}

void  TabuSearch::diversification()
{
	//wymieszanie wszystkich wierzcho³ków 
	
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(0, 1); // distribute results between

	for (int i = 1; i < size; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			if (dist(gen)) //50% szans na zamianê
				swap(currentPath[i], currentPath[j]);
		}
	}
	countNotFind = 0;
}

void TabuSearch::clearQueue(priority_queue<Move>& q)
{
	std::priority_queue<Move> empty;
	std::swap(q, empty);
}

TabuSearch::~TabuSearch()
{
	for (int i = 0; i < size; i++)
		delete[]tabuMatrix[i];
	delete[] tabuMatrix;
}