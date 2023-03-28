#include <iostream>
#include <iomanip> 
#include <windows.h>
#include "FileReader.h"
#include "TestTime.h"
#include "TabuSearch.h"



using namespace std;
//czy mozna uzywac unique pointer ??? 
//losowy zaczyna sie od 1 i losuje

int main() 
{
	char choice;
	bool run = true;
	string path;

	int size=0;
	int **graf = nullptr;
	int time = 0;
	bool diversification = false;
	string choiceD;

	FileReader *fileReader;
	TestTime* testTime;

	TabuSearch* tabuSearch;
	
	
	while (run) 
	{
		cout << "Menu:" << endl;
		cout << "1. Wczytanie danych z pliku" << endl;
		cout << "2. Wprowadzenie kryterium stopu" << endl; 
		cout << "3. Wlaczenie/wylaczenie dywersyfikacji" << endl;
		cout << "4. Uruchomianie algorytmu TS dla wczytanych danych i ustawionych parametrow oraz wyswietlenie wynikow i czasu wykonania" << endl;
		cout << "5. Wyjdz" << endl;
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
			break;

		case '3':
			cout << "Wybierz:" << endl;
			cout << "1. Wylaczenie dywersyfikacji" << endl;
			cout << "2. Wlaczenie dywersyfikacji" << endl;
			cout << "Wybor: ";
			cin >> choiceD;

			if (choiceD == "1")
				diversification = false;
			else if (choiceD == "2")
				diversification = true;
			else
				cout << "Blad!!!" << endl;

			break;

		case '4':
			if (graf != nullptr)
			{
				if (time > 0)
				{
					if (diversification)
						cout << "Algorytm wykonuje sie z dywersyfikacja" << endl;
					else
						cout << "Algorytm wykonuje sie bez dywersyfikacji " << endl;

					tabuSearch = new TabuSearch(graf, size, time);
					tabuSearch->tabuSearch(diversification);
					delete tabuSearch;
				}
				else
					cout << "Wprowadz czas" << endl;
			}
			else
				cout << "WPROWADZ GRAF!!!" << endl;
			break;

		case '5':
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
