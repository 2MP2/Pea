#include <iostream>
#include <iomanip> 
#include <windows.h>
#include "BnBMIN.h"
#include "FileReader.h"
#include "TestTime.h"
#include "BnBALONG.h"
#include "BF.h"



using namespace std;
//czy mozna uzywac unique pointer ??? 
//losowy zaczyna sie od 1 i losuje

int main() 
{
	char choice;
	bool run = true;
	string path;

	int size;
	int **graf = nullptr;

	int randomSize;
	int randomMax;
	int randomRepetitions;

	FileReader *fileReader;
	BnBMIN* bnbmin;
	BnBALONG* bnblong;
	BF* bf;
	TestTime* testTime;

	
	while (run) 
	{
		cout << "Menu:" << endl;
		cout << "1. Wprowadz plik" << endl;
		cout << "2. Branch and bound min z pliku" << endl; 
		cout << "3. Branch and bound przeglad w wzdluz z pliku" << endl;
		cout << "4. Brute force z pliku" << endl;
		cout << "5. Licz czas dla BnB min (losowe grafy)" << endl;
		cout << "6. Licz czas dla BnB w wglab  (losowe grafy)" << endl;
		cout << "7. Licz czas dla BF (losowe grafy)" << endl;
		cout << "8. Wyjdz" << endl;
		cout << "Wybor: ";

		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case '1':
			cout << "Podaje nazwe pliku" << endl; 
			cin >> path;

			fileReader = new FileReader();
			graf = fileReader->file_read_graph(path, size);

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
			if (graf != nullptr)
			{
				testTime = new TestTime();
				testTime->countTimeBnBMIN_FILE(size,graf);
				delete testTime;
			}
			else
				cout << "WPROWADZ GRAF!!!" << endl;
			break;

		case '3':
			if (graf != nullptr)
			{
				testTime = new TestTime();
				testTime->countTimeBnBALONG_FILE(size, graf);
				delete testTime;
			}
			else
				cout << "WPROWADZ GRAF!!!" << endl;
			break;

		case '4':
			if (graf != nullptr)
			{
				testTime = new TestTime();
				testTime->countTimeBF_FILE(size, graf);
				delete testTime;
			}
			else
				cout << "WPROWADZ GRAF!!!" << endl;
			break;

		case '5':

			cout << "Podaj ilosc miast " << endl;
			cin >> randomSize;
			cout << "Podaj maksymalna wielkosc drogi jak moze sie wylosowac " << endl;
			cin >> randomMax;
			cout << "Podaj liczbe prob z ktorych zostanie podany sredni czas " << endl;
			cin >> randomRepetitions;
			testTime = new TestTime();
			testTime->countTimeBnBMIN(randomSize, randomMax, randomRepetitions);
			delete testTime;
			break;

		case '6':
			cout << "Podaj ilosc miast " << endl;
			cin >> randomSize;
			cout << "Podaj maksymalna wielkosc drogi jak moze sie wylosowac " << endl;
			cin >> randomMax;
			cout << "Podaj liczbe prob z ktorych zostanie podany sredni czas " << endl;
			cin >> randomRepetitions;
			testTime = new TestTime();
			testTime->countTimeBnBALONG(randomSize, randomMax, randomRepetitions);
			delete testTime;
			break;

		case '7':
			cout << "Podaj ilosc miast " << endl;
			cin >> randomSize;
			cout << "Podaj maksymalna wielkosc drogi jak moze sie wylosowac " << endl;
			cin >> randomMax;
			cout << "Podaj liczbe prob z ktorych zostanie podany sredni czas " << endl;
			cin >> randomRepetitions;
			testTime = new TestTime();
			testTime->countTimeBF(randomSize, randomMax, randomRepetitions);
			delete testTime;
			break;

		case '8':
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
