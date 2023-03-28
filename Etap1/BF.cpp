#include "BF.h"

BF::BF(int** graphCon, int sizeCon)
{
	size = sizeCon;
	matrix = graphCon;
	
}

void BF::bf()
{
	sum = 0;
	sumMin = 2147483647;

	for (int i = 1; i < size; i++)
		path.push_back(i);

	do {
		//obliczanie kosztu drogi 
		sum = matrix[0][path[0]];
		for(int i =0;i<size -2;i++ )
			sum += matrix[path[i]][path[i+1]];
		sum += matrix[path[size-2]][0];
		
		if (sum < sumMin)
		{
			sumMin = sum; 
			bestPath = path;
		}

	} while (next_permutation(path.begin(), path.end())); //tworzy nowa permutacje ktora jest sprawdzana 
}


void BF::writeResult()
{
	cout << "Minimalna droga to: " << sumMin << endl;
	cout << "0 ";
	for (int i = 0; i < size - 1; i++)
		cout << bestPath[i] << " ";
	cout << "0 " << endl;
}


