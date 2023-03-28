#include "Genetic.h"

Genetic::Genetic(int** matrixCon, int sizeCon, unsigned long long stopTimeCon, int populationSizeCon, int crossoverProbabilityCon, int mutationProbabilityCon)
{
	matrix = matrixCon;
	size = sizeCon;
	stopTime = stopTimeCon;
	populationSize = populationSizeCon;
	crossoverProbability = crossoverProbabilityCon;
	mutationProbability = mutationProbabilityCon;
}

void Genetic::mutation(Journey& journey) // zamiana wierzcho³ków
{
	for (int i = 0; i < 2; i++) // mutujemy max 4 geny
		swap(journey.path[randomNumber(1, journey.path.size() - 1)], journey.path[randomNumber(1, journey.path.size() - 1)]);
}

void Genetic::mutation2(Journey& journey) // zamiana krawêdzi
{
	int point1 = randomNumber(1, journey.path.size()/2 -1);
	int point2 = randomNumber(0, journey.path.size()/2 -1);

	reverse(journey.path.begin()+ point1, journey.path.end()- point2);
}

// funckja to jednopunktowy crossover 
Genetic::Journey Genetic::crossover(Journey journey1, Journey journey2)
{
	Journey newJourney;
	bool contains = false;

	int crosspoint = randomNumber(1, journey1.path.size() - 1); //wybór punktu od którego robimy zamiane

	// przespiujemy pierwsz¹ czêœæ
	for (int i = 0; i < crosspoint; i++) 
	{
		newJourney.path.push_back(journey1.path[i]);
	};

	// przepisujemy z drugiego rodzica od pozycji crossoveru w pierwszym  rodzicu 
	for (int i = crosspoint; i < journey2.path.size(); i++)
	{
		for (int j = 0; j < newJourney.path.size(); j++)
		{
			if (newJourney.path[j] == journey2.path[i])
			{
				contains = true;
				break;
			}
		}
		if (!contains)
			newJourney.path.push_back(journey2.path[i]);

		contains = false;
	}
	// przepisujemy od pocz¹tku drugiego rodzica do pozycji crossoveru w pierwszym  rodzicu
	for (int i = 0; i < crosspoint; i++)
	{
		for (int j = 0; j < newJourney.path.size(); j++)
		{
			if (newJourney.path[j] == journey2.path[i])
			{
				contains = true;
				break;
			}
		}
		if (!contains)
			newJourney.path.push_back(journey2.path[i]);

		contains = false;
	}

	return newJourney;
}

Genetic::Journey Genetic:: crossover2(Journey journey1, Journey journey2)
{
	Journey newJourney;

	for (int i = 0; i < journey1.path.size(); i++) // newJourney wype³niamy -1
		newJourney.path.push_back(-1);

	int crosspoint1 = randomNumber(1, journey1.path.size() - 1);
	int crosspoint2 = randomNumber(1, journey1.path.size() - 1);
	bool contains;

	int szukanaLiczba;
	int iteratorSzukanejLiczby = 0;

	if (crosspoint1 == crosspoint2) // wyjœcie gdy punkty krzyzowania s¹ takie same po pola nie ma
		return journey1;
	else if (crosspoint1 > crosspoint2)
		swap(crosspoint1, crosspoint2);

	for (int i = crosspoint1; i <= crosspoint2; i++) //przepisujemy pole z pierwszego rodzica
		newJourney.path[i] = journey1.path[i];

	for (int i = crosspoint1; i <= crosspoint2; i++) //sprawdzaie pola
	{
		contains = false;
		for (int j = crosspoint1; j <= crosspoint2; j++) //sprawdzanie czy zawiera siê w polu bo jesli tak to nic sie nie dzieje
		{
			if (journey2.path[i] == journey1.path[j])
			{
				contains = true;
				break;
			}
		}

		iteratorSzukanejLiczby = i;
		while (!contains) // mo¿liwe wielokrotne sprawdzanie 
		{
			szukanaLiczba = journey1.path[iteratorSzukanejLiczby];
			for (int j = 0; j < journey2.path.size(); j++)
			{
				if (szukanaLiczba == journey2.path[j])
				{
					iteratorSzukanejLiczby = j;
					break;
				}
			}

			// sprawdzamy czy liczba znaleziona znajduje sie w polu
			// jeœli tak to pêtla od nowa a jeœli nie to zapisujemy w nowej œciezce
			if (iteratorSzukanejLiczby < crosspoint1 || iteratorSzukanejLiczby > crosspoint2)
			{
				newJourney.path[iteratorSzukanejLiczby] = journey2.path[i];
				contains = true;
			}
		}

	}

	// dopisanie reszty 
	for (int i = 0; i < newJourney.path.size(); i++)
	{
		if (newJourney.path[i] == -1)
			newJourney.path[i] = journey2.path[i];
	}

	return newJourney;
}

// losowa populacja 
void Genetic::firstPopulation()
{
	Journey journey;

	for (int i = 0; i < size; i++)
		journey.path.push_back(i);
	

	for (int i = 0; i < populationSize; i++)
	{
		for (int j = 1; j < journey.path.size(); j++)
		{
			if (randomNumber(0,2))
				swap(journey.path[1], journey.path[j]);
		}

		journey.cost = countPathCost(journey);
		population.push_back(journey);
	}
	theBest = journey; // przypisanie pierwszego najlepszego rozwi¹zania
}

void Genetic::newPopulation(int mut, int cross)
{
	vector <Journey> newPopulation;
	int bestJourney = 0;

	int sum = 0; // suma wszytkich genów w populacji 
	int rouletteSum; // suma ca³kowita dla ruletki 
	int currentSum; // suma do sprawdzania 
	int random1;
	int random2;

	Journey parent1;
	Journey parent2;
	Journey kid;

	for (int i = 0; i < population.size(); i++)
	{
		sum += population[i].cost;

		if (population[bestJourney].cost > population[i].cost)
			bestJourney = i;
	}
	newPopulation.push_back(population[bestJourney]); //elitaryzm
	changeBestPath(population[bestJourney]); //sprawdzenie najlepszego DNA z poprzedniej populacji

	//sum -= population[bestJourney].cost; // zmiejszamy liczbê bo rouletteSum bêdzie mniejsze
	rouletteSum = sum * (population.size() - 1);

	while (newPopulation.size() < population.size())
	{
		currentSum = 0;
		random1 = randomNumber(0, rouletteSum - 1);
		random2 = randomNumber(0, rouletteSum - 1);

		for (int i = 0; i < population.size(); i++)
		{
			currentSum += sum - population[i].cost;
			
			if (currentSum > random1)
			{
				parent1 = population[i];
				break;
			}
		}
		currentSum = 0;

		for (int i = 0; i < population.size(); i++)
		{
			currentSum += sum - population[i].cost;

			if (currentSum > random2)
			{
				parent2 = population[i];
				break;
			}
		}

		if (random(crossoverProbability)) //crossover
		{
			if(cross == 1)
				kid = crossover(parent1, parent2);
			else
				kid = crossover2(parent1, parent2);
		}
		else
			kid = parent1;

		if (random(mutationProbability)) // mutacja
		{
			if (mut == 1)
				mutation(kid);
			else 
				mutation2(kid);
		}
			

		kid.cost = countPathCost(kid); // wyliczenie kosztu dziecka 
		newPopulation.push_back(kid); // dodanie dziecka do populacji 
	}
	
	population.swap(newPopulation); // przypisania nowej populacji do starej

	// po mutacji policz koszt scieZki 

}

void Genetic::genetic(int mut, int cross)
{
	
	std::chrono::seconds stop = std::chrono::seconds(stopTime); // zaminana na skeundy 
	auto timeLimit = Clock::now() + stop;

	QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	start = read_QPC();

	firstPopulation();
	//coutPopulation();
	while (Clock::now() < timeLimit)
	{
		newPopulation(mut,cross);
		//coutPopulation();
	}
	cout << "KONCOWY WYNIK TO: " << endl;
	writeResult();
	
}

void Genetic::coutPopulation() //wypisanie populacji 
{
	for (int i = 0; i < population.size(); i++)
	{
		for (int j = 0; j < size; j++)
			cout << population[i].path[j] << " ";
		cout << "0";
		cout << endl;
		cout << "Koszt to: " << population[i].cost << endl;
	}
}

void Genetic::coutPath(Journey journey) // wypisanie sciezki 
{
	for (int j = 0; j < journey.path.size(); j++)
		cout << journey.path[j] << " ";
	cout << "0";
	cout << endl;
}

void Genetic:: changeBestPath(Journey journey)
{
	if (journey.cost < theBest.cost)
	{
		theBest = journey;
		elapsed = read_QPC() - start; //zmienna do obliczenia czasu

		//writeResult();
	}
}

int Genetic::countPathCost(Journey journey)
{
	int sum = 0;
	for (int i = 0; i < journey.path.size() - 1; i++)
	{
		sum += matrix[journey.path[i]][journey.path[i + 1]];
	}
	
	sum += matrix[journey.path[size-1]][0];

	return sum;
}

bool Genetic::random(int probability)
{
	return probability - randomNumber(0,1000) + 1;
}

int Genetic::randomNumber(int min, int max)
{
	random_device rd; // non-deterministic generator
	mt19937 gen(rd()); // random engine seeded with rd()
	uniform_int_distribution<> dist(min, max);

	return dist(gen);
}

long long int Genetic::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}

void  Genetic::writeResult()
{
	for (int i = 0; i < size; i++)
		cout << theBest.path[i] << " ";
	cout << "0";
	cout << endl;
	cout << "Koszt to: " << theBest.cost << endl;

	cout << "bestPath Time [s] = " << fixed << setprecision(3) << (float)elapsed /
		frequency << endl;
	cout << "bestPath Time [ms] = " << setprecision(0) << (1000.0 * elapsed) /
		frequency << endl;
	cout << "bestPath Time [us] = " << setprecision(0) << (1000000.0 * elapsed) /
		frequency << endl << endl;
}