#include "BnBMIN.h"



BnBMIN::BnBMIN(int** graphCon, int sizeCon)
{
	size = sizeCon;
	matrix = graphCon;
}


void BnBMIN::writeQueue(priority_queue <Node> q)
{
	while (!q.empty())
	{
		cout << q.top().v << " ";
		q.pop();
	}
	cout << endl;
}

void BnBMIN::BnB()
{
	//!!! FUNKCJA OKAZA£A SIÊ NIE OPTYMALNA. ZU¯YWA DU¯O PAMIÊCI I WIÊKSZOŒCI PRZYPADKÓW DZIA£A WOLNO. 
	//    JEDYNYM MOMENTEM KIEDY JEST OPTYMALNA TO KIEDY MA£A LICZBA SCIE¯EK JEST WYJ¥TKOWO LEPSZA OD INNCH !!!
	//1.Funkcja znajduje HB
	//2.Dodaje wierzcho³ek 0 do kolejki 
	//3.Dalsza czêœæ wykonuje siê do monetu gdy kolejka piorytetowa nie bêdzie pusta
	//4.Gdy najlepszy wêze³ jest wielkoœci macierzy to oznacz ¿e przeszed³ ju¿ wszystkie wierzcho³ki 
	// Wtedy sprawdzamy czy mo¿e siê staæ nowym HB
	// nie wa¿ne od wyniku wêze³ i tak zostanie usuniêty z kolejki
	//5.Nastêpnie sprawdzamy czy LB najlepszego wêz³a jest mniejsza od obecnego HB
	// Gdyby by³a wiêksza oznacza³o by to ¿e nie ma sensu dalej rozwijaæ tej ga³êzi
	// Jeœli funkcja zwróci true dodajem dzieci badanego najlepszego wêz³¹
	//6.Nie zale¿nie od wyniku checkLB usuwamy najlepszy wêze³
	//7.Gdy kolejka jest pusta nastêpuje wypisanie scie¿ki i jej kosztu
	//8.Koniec

	//znalezienie HB
	HB = findHB();
	//dodanie wierzcho³ka zerowego 
	Node node0;
	node0.path.push_back(0);
	node0.pathCost = 0;
	node0.v = 0;
	pq.push(node0);

	//szukanie
	while (!pq.empty())
	{
		if (pq.top().path.size() == size)
		{
			checkNewHB(pq.top());
		}
		else if (checkLB(pq.top()))
		{
			addKidsToQueue(pq.top());
		}
		pq.pop();
	}
	
}

void BnBMIN::addKidsToQueue(Node node)
{
	Node kid;
	Node kopia;
	kopia = node;
	vector <int> allV(size);
	vector <int> subtractV;


	for (int i = 0; i < size; i++)
		allV[i] = i;

	sort(node.path.begin(), node.path.end());

	//tworzenie wektora który posiada jeszcze wierzcho³ki nieodwiedzone
	set_difference(
		allV.begin(), allV.end(),
		node.path.begin(), node.path.end(),
		back_inserter(subtractV));

	//dodawanie dzieci jesli do kolejki jesli jest przejscie 
	for (int i = 0; i < subtractV.size(); i++)
	{
			kid.v = subtractV[i];
			kid.path = kopia.path;
			kid.path.push_back(kid.v);
			kid.pathCost = kopia.pathCost + matrix[kopia.v][subtractV[i]];
			if(kid.pathCost<HB.pathCost)
			pq.push(kid);
	}
	
}

bool BnBMIN::checkLB(Node node)
{
	vector <int> allV(size);
	vector <int> subtractV;
	int sumMin = 0;
	int pathTo0 = 0;
	int min = 2147483647;

	for (int i = 0; i < size; i++)
		allV[i] = i;

	sort(node.path.begin(), node.path.end());

	//tworzenie wektora który posiada jeszcze wierzcho³ki nieodwiedzone
	set_difference(
		allV.begin(), allV.end(),
		node.path.begin(), node.path.end(),
		back_inserter(subtractV));

	//sprawdzenie min dla sprawdzanego wêz³¹ nie bêd¹ce 0
	for (int i = 0; i < subtractV.size(); i++)
	{
		if (min > matrix[node.v][subtractV[i]])
			min = matrix[node.v][subtractV[i]];
	}
	sumMin += min;
	
	//obliczenie wszystkich pozosta³ych min 
	for (int i = 0; i < subtractV.size(); i++)
	{
		min = 2147483647;
		for (int j = 0; j < subtractV.size(); j++)
		{
			//sprawdzenie min nie bêd¹ce 0 
			if (min > matrix[subtractV[i]][subtractV[j]] && i!=j)
				min = matrix[subtractV[i]][subtractV[j]];
		}
		//sprawdzenie po³¹czenia z wierzcho³kiem pocz¹tkowym ( z 0 )
		if (min > matrix[subtractV[i]][0])
			min = matrix[subtractV[i]][0];
				
		sumMin += min;
	}

		sumMin += node.pathCost;
		if (sumMin < HB.pathCost)
			return true;
		else
			return false;
}

bool BnBMIN::checkNewHB(Node node)
{
		node.pathCost += matrix[node.v][0]; //musimy dodaæ jeszcze dorge do 0 wierzcho³ka 
		if (node.pathCost < HB.pathCost)
		{
			HB = node;
			return true;
		}
		return false;
}


BnBMIN::Node BnBMIN::findHB() 
{
	vector <int> path (size);
	int sum = 0;

	for (int i = 0; i < size; i++)
		path[i] = i;

	for (int i = 0; i < size -1; i++)
		sum += matrix[path[i]][path[i + 1]];
	sum += matrix[path[size - 1]][0];

	Node node;
	node.path = path;
	node.pathCost = sum;
	node.v = path[size - 1];

	return node;

}

void BnBMIN::writeResult()
{
	cout << "Droga to: " << HB.pathCost << endl;
	for (int i = 0; i < size; i++)
		cout << HB.path[i] << " ";
	cout << "0";
	cout << endl;
}