#include <iostream>
#include <iomanip> 
#include <windows.h>
#include "FileReader.h"
#include "Genetic.h"

using namespace std;

int main() 
{
	char choice;
	bool run = true;
	string path;

	int size=0;
	int **graf = nullptr;
	int time = 0;

	int crossoverProbability = -1; // w promilach 
	int mutationProbability = -1; // w promilach 
	int populationSize = -1;

	int mut = -1;
	int cross = -1;
	
	FileReader *fileReader;
	Genetic* genetic;

	while (run) 
	{
		cout << "WPROWADZENIE PUNKTOW 1,2,3,4,5,6,7 OBOWIAZKOWE !!!" << endl;
		cout << "Menu:" << endl;
		cout << "1. Wczytanie danych z pliku i wyswietlenie wczytanych danych" << endl;
		cout << "2. Wprowadzenie kryterium stopu" << endl; 
		cout << "3. Ustawienie wielkosci populacji poczatkowej" << endl;
		cout << "4. Ustawienie prawdopodobienstwo mutacji (w promilach)" << endl;
		cout << "5. Ustawienia prawdopodobienstwo krzyzowania (w promilach)" << endl;
		cout << "6. Wybor metody mutacji" << endl;
		cout << "7. Wybor metody krzyzowania" << endl;
		cout << "8. Uruchomianie algorytmu dla wczytanych danych i ustawionych parametrow oraz wyswietlenie wynikow" << endl;
		cout << "9. Wyjdz" << endl;
		cout << "Wybor: ";

		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case '1':
			cout << "Podaje nazwe pliku" << endl; 
			cin >> path;
			fileReader = new FileReader();

			if(graf == nullptr)
			graf = fileReader->file_read_graph(path, size);
			else
			{
				for (int i = 0; i < size; i++)
					delete[]graf[i];
				delete[] graf;

				graf = fileReader->file_read_graph(path, size);
			}

			if (graf)
			{
				cout << "wielkosc grafu = "<< size << endl;
				for (int i = 0; i < size; i++)
				{
					for (int j = 0; j < size; j++)
						cout << setw(4) << graf[i][j] << " ";

					cout << endl;
					cout << endl;
				}
			}
			delete fileReader;
			break;

		case '2':
			cout << "Wprowadz czas w sekundach" << endl;
			cin >> time;

			if (time <= 0)
				cout << "WPROWADZONO BLEDNY CZAS!!!" << endl;
			break;

		case '3':
			cout << "Wprowadz wielkosc populacji" << endl;
			cin >> populationSize;

			if (populationSize <= 2)
				cout << "WPROWADZONO BLEDNA WIELKOSC!!!" << endl;
			break;

		case '4':
			cout << "Wprowadz prawdopodobienstwo mutacji (w promilach)" << endl;
			cin >> mutationProbability;

			if (mutationProbability < 0 || mutationProbability > 1000)
				cout << "WPROWADZONO BLEDNA WIELKOSC!!!" << endl;

			break;

		case '5':
			cout << "Wprowadz prawdopodobienstwo krzyzowania (w promilach)" << endl;
			cin >> crossoverProbability;

			if (crossoverProbability < 0 || crossoverProbability > 1000)
				cout << "WPROWADZONO BLEDNA WIELKOSC!!!" << endl;

			break;

		case '6':
			cout << "WYBIERZ METODE MUTACJI:" << endl;
			cout << " 1. Inversion Mutation" << endl;
			cout << " 2. Scramble Mutation" << endl;
			cin >> mut;
			
			if (mut < 1 || mut > 2)
				cout << "BLAD !!!" << endl;
			break;

		case '7':
			cout << "WYBIERZ METODE KRZYZOWANIA:" << endl;
			cout << " 1. One-point Crossover" << endl;
			cout << " 2. PMX " << endl;
			cin >> cross;

			if (cross < 1 || cross > 2)
				cout << "BLAD !!!" << endl;

			break;

		case '8':
			if (graf != nullptr)
			{
				if (time > 0 && populationSize > 2 && (mutationProbability >=0 && mutationProbability <=1000) 
					&& (crossoverProbability >=0 && crossoverProbability <= 1000)
					&& (mut >= 1 && mut<=2) && (cross >= 1 && cross <= 2))
				{
					genetic = new Genetic(graf, size, time, populationSize, crossoverProbability, mutationProbability);
					genetic->genetic(mut, cross);
					delete genetic;
				}
				else
					cout << "Brak lub bledne dane!!!" << endl;
			}
			else
				cout << "WPROWADZ GRAF!!!" << endl;
			break;

		case '9':
			run = false;

			if (graf != nullptr)
			{
				for (int i = 0; i < size; i++)
					delete[]graf[i];
				delete[] graf;
			}
			break;

		default:
			break;
		}
	}

	return 0;
	
}
