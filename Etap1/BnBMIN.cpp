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
	//!!! FUNKCJA OKAZA�A SI� NIE OPTYMALNA. ZU�YWA DU�O PAMI�CI I WI�KSZO�CI PRZYPADK�W DZIA�A WOLNO. 
	//    JEDYNYM MOMENTEM KIEDY JEST OPTYMALNA TO KIEDY MA�A LICZBA SCIE�EK JEST WYJ�TKOWO LEPSZA OD INNCH !!!
	//1.Funkcja znajduje HB
	//2.Dodaje wierzcho�ek 0 do kolejki 
	//3.Dalsza cz�� wykonuje si� do monetu gdy kolejka piorytetowa nie b�dzie pusta
	//4.Gdy najlepszy w�ze� jest wielko�ci macierzy to oznacz �e przeszed� ju� wszystkie wierzcho�ki 
	// Wtedy sprawdzamy czy mo�e si� sta� nowym HB
	// nie wa�ne od wyniku w�ze� i tak zostanie usuni�ty z kolejki
	//5.Nast�pnie sprawdzamy czy LB najlepszego w�z�a jest mniejsza od obecnego HB
	// Gdyby by�a wi�ksza oznacza�o by to �e nie ma sensu dalej rozwija� tej ga��zi
	// Je�li funkcja zwr�ci true dodajem dzieci badanego najlepszego w�z��
	//6.Nie zale�nie od wyniku checkLB usuwamy najlepszy w�ze�
	//7.Gdy kolejka jest pusta nast�puje wypisanie scie�ki i jej kosztu
	//8.Koniec

	//znalezienie HB
	HB = findHB();
	//dodanie wierzcho�ka zerowego 
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

	//tworzenie wektora kt�ry posiada jeszcze wierzcho�ki nieodwiedzone
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

	//tworzenie wektora kt�ry posiada jeszcze wierzcho�ki nieodwiedzone
	set_difference(
		allV.begin(), allV.end(),
		node.path.begin(), node.path.end(),
		back_inserter(subtractV));

	//sprawdzenie min dla sprawdzanego w�z�� nie b�d�ce 0
	for (int i = 0; i < subtractV.size(); i++)
	{
		if (min > matrix[node.v][subtractV[i]])
			min = matrix[node.v][subtractV[i]];
	}
	sumMin += min;
	
	//obliczenie wszystkich pozosta�ych min 
	for (int i = 0; i < subtractV.size(); i++)
	{
		min = 2147483647;
		for (int j = 0; j < subtractV.size(); j++)
		{
			//sprawdzenie min nie b�d�ce 0 
			if (min > matrix[subtractV[i]][subtractV[j]] && i!=j)
				min = matrix[subtractV[i]][subtractV[j]];
		}
		//sprawdzenie po��czenia z wierzcho�kiem pocz�tkowym ( z 0 )
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
		node.pathCost += matrix[node.v][0]; //musimy doda� jeszcze dorge do 0 wierzcho�ka 
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