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

	mainList.push_front(node0); //dodajemy pierwszy wierzcho³ek

	while(!mainList.empty()) //program wykonuje siê dopóki lista nie bêdzie pusta 
	{
		if (mainList.front().path.size() == size) // sprawdzamy czy to liœæ (nie licz¹c powrotu do 0)
		{
			checkNewHB(mainList.front()); // sprawdzamy czy liœæ jest najlepszym rozwi¹zaniem 
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

	if (HB.pathCost != 2147483647)
	{
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
	}
	if (sumMin < HB.pathCost)
		return true;
	else
		return false;
}

void BnBALONG::addKidsToList(Node node)
{
	Node kid;

	Node kopia; //kopia aby móc stworzyc wektor nieodwiedzonych wierzcho³ków 
	kopia = node;

	Node kopia2; //kopia aby móc usun¹æ ojca przed dodaniem dzieci
	kopia2 = node;

	vector <int> allV(size);
	vector <int> subtractV;

	mainList.pop_front(); // usuwanie ojca 

	for (int i = 0; i < size; i++)
		allV[i] = i;

	sort(kopia.path.begin(), kopia.path.end());

	//tworzenie wektora który posiada jeszcze wierzcho³ki nieodwiedzone
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
		node.pathCost += matrix[node.v][0]; //musimy dodaæ jeszcze dorge do 0 wierzcho³ka 
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