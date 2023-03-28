#include "FileReader.h"


bool FileReader::file_read_line(ifstream& file, int tab[], int size)
{
	string s;
	getline(file, s);

	if (file.fail() || s.empty())
		return(false);

	istringstream in_ss(s);

	for (int i = 0; i < size; i++)
	{
		in_ss >> tab[i];
		if (in_ss.fail())
			return(false);
	}
	return(true);
}


bool FileReader::fileHamiltonianCycle(int** matrix, int size)
{
	int sum1 = 0;
	int sum2 = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			sum1 += matrix[i][j];
			sum2 += matrix[j][i];
		}
		if (sum1 == 0)
			return false;
		sum1 = 0;

		if (sum2 == 0)
			return false;
		sum2 = 0;
	}
	return true;
}


int ** FileReader::file_read_graph(string file_name, int &size)
{
	ifstream file;
	int tab[1];
	file.open(file_name.c_str());

	if (file.is_open())
	{
		if (file_read_line(file, tab, 1))
		{
			size = tab[0];

			//inicjalizowanie macierzy  
			int **matrix = new int *[size];
			for (int i = 0; i < size; i++)
				matrix[i] = new int[size];

			for (int i = 0; i < size; i++)
				if (!file_read_line(file, matrix[i], size))
				{
					cout << "File error - READ EDGE" << endl;
					return nullptr;
				}

			file.close();

			if(fileHamiltonianCycle(matrix,size))
				return matrix;
			else
			{
				cout << "You cant make Hamiltonian Cycle" << endl;
				return nullptr;
			}
		}
		else 
		{
			cout << "File error - READ INFO" << endl;
			return nullptr;
		}
		file.close();
		return nullptr;
	}
	else
	{
		cout << "File error - OPEN" << endl;
		return nullptr;
	}
		
}