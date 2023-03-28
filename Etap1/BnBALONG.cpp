#include "BnBALONG.h"

BnBALONG::BnBALONG(int** graphCon, int sizeCon)
{
	size = sizeCon;
	matrix = graphCon;
}

void BnBALONG::writeList(list <Node> listW)
{
	for (auto& elm : listW)
		cout << elm.v << " ";
	cout << endl;
}

void BnBALONG::BnB()
{
	HB.pathCost = 2147483647;

	Node node0;
	node0.path.push_back(0);
	node0.pathCost = 0;
	node0.v = 0;

	mainList.push_front(node0); //dodajemy pierwszy wierzcho�ek

	while(!mainList.empty()) //program wykonuje si� dop�ki lista nie b�dzie pusta 
	{
		if (mainList.front().path.size() == size) // sprawdzamy czy to li�� (nie licz�c powrotu do 0)
		{
			checkNewHB(mainList.front()); // sprawdzamy czy li�� jest najlepszym rozwi�zaniem 
			mainList.pop_front();
		}
		else if (checkLB(mainList.front())) //funkcja sprawdza czy LB < HB 
			addKidsToList(mainList.front()); //dodajemy dzieci 
		else
			mainList.pop_front();
	}
	
}

bool BnBALONG::checkLB(Node node)
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

	if (HB.pathCost != 2147483647)
	{
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
	}
	if (sumMin < HB.pathCost)
		return true;
	else
		return false;
}

void BnBALONG::addKidsToList(Node node)
{
	Node kid;

	Node kopia; //kopia aby m�c stworzyc wektor nieodwiedzonych wierzcho�k�w 
	kopia = node;

	Node kopia2; //kopia aby m�c usun�� ojca przed dodaniem dzieci
	kopia2 = node;

	vector <int> allV(size);
	vector <int> subtractV;

	mainList.pop_front(); // usuwanie ojca 

	for (int i = 0; i < size; i++)
		allV[i] = i;

	sort(kopia.path.begin(), kopia.path.end());

	//tworzenie wektora kt�ry posiada jeszcze wierzcho�ki nieodwiedzone
	set_difference(
		allV.begin(), allV.end(),
		kopia.path.begin(), kopia.path.end(),
		back_inserter(subtractV));

	//dodawanie dzieci jesli do kolejki jesli jest przejscie 
	for (int i = 0; i < subtractV.size(); i++)
	{
			kid.v = subtractV[i];
			kid.path = kopia2.path;
			kid.path.push_back(kid.v);
			kid.pathCost = kopia2.pathCost + matrix[kopia2.v][subtractV[i]];
			if (kid.pathCost < HB.pathCost)
				mainList.push_front(kid);
	}

}

bool BnBALONG::checkNewHB(Node node)
{
		node.pathCost += matrix[node.v][0]; //musimy doda� jeszcze dorge do 0 wierzcho�ka 
		if (node.pathCost < HB.pathCost)
		{
			HB = node;
			return true;
		}
		return false;
}

void BnBALONG::writeResult()
{
	cout << "Droga to: " << HB.pathCost << endl;
	for (int i = 0; i < size; i++)
		cout << HB.path[i] << " ";
	cout << "0";
	cout << endl;
}