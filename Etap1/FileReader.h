#pragma once
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <windows.h>
#include <sstream>

using namespace std;

class FileReader
{
	bool file_read_line(ifstream& file, int tab[], int size); 
	bool fileHamiltonianCycle(int** matrix, int size); //funkcja sprawdza czy jest mo¿liwe utoworzenie cylku Hamiltona  

public:
	
	int ** file_read_graph(string file_name, int &size);

};