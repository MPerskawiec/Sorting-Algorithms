/*
 * main.cpp
 *
 *  Created on: 12 kw 2018
 *      Author: Mariusz
 */

#include <iostream>
#include <cmath>
#include <ctime>

#include "Algorytmy_Sortowania.cpp"


using namespace std;

int main() {

int wiersze =100;
int ile = 10000;
	clock_t start, stop;
	double czas1;

	cout << "Prezentacja dzialania programu oraz czasu wykonywania sortowania " << endl;
	cout << "Program sortujacy n tablic o n wielko�ci losowych danych" << endl;
	cout << "Podaj ile tablic chcesz posortowac: " ;
	cin >> wiersze;
	cout << "Podaj z ilu elementow ma sie skladac kazda tablcia: ";
	cin >> ile;
	cout << "Trwa sortowanie prosze czekac" << endl;




	// tworzenie tablicy o zadanych warto�ciach
	double **tab1 = new double *[wiersze]; //alokacja pamieci
	for (int i = 0; i < wiersze; ++i) {
		tab1[i] = new double[ile]; //alokacja pamieci
	}



	// LOSOWE ELEMENTY
	for (int i = 0; i < wiersze; ++i) {
		for (int j = 0; j < ile; ++j) //wpisanie wartosci do tablicy
			tab1[i][j] = rand();
	}

	start = clock();
	for (int i = 0; i < wiersze; ++i) {
	sortowanie_przez_scalanie(tab1[i],0,ile-1);
	}
	stop = clock();
	czas1 = (double) (stop - start) / CLOCKS_PER_SEC;
	cout << "Sortowanie przez scalanie. Czas algorytmu to: " << czas1 << endl;


	// LOSOWE ELEMENTY
	for (int i = 0; i < wiersze; ++i) {
		for (int j = 0; j < ile; ++j) //wpisanie wartosci do tablicy
			tab1[i][j] = rand();
	}

	start = clock();
	for (int i = 0; i < wiersze; ++i) {
		quicksort(tab1[i],0,ile-1);
	}
	stop = clock();
	czas1 = (double) (stop - start) / CLOCKS_PER_SEC;
	cout << "Sortowanie szybkie.	   Czas algorytmu to: " << czas1 << endl;


	// LOSOWE ELEMENTY
	for (int i = 0; i < wiersze; ++i) {
		for (int j = 0; j < ile; ++j) //wpisanie wartosci do tablicy
			tab1[i][j] = rand();
	}

	start = clock();
	for (int i = 0; i < wiersze; ++i) {
		sortowanie_introspektywne(tab1[i],ile-1);
	}
	stop = clock();
	czas1 = (double) (stop - start) / CLOCKS_PER_SEC;
	cout << "sortowanie_introspektywne. Czas algorytmu to: " << czas1 << endl;


	for (int i(0); i < wiersze; ++i)
		delete[] tab1[i]; //uwolnienie pamieci
	delete[] tab1; //uwolnienie pamieci
	tab1 = NULL;


	cout << "Wprowadz dowolny znak aby zakonczyc: " << endl;
	cin >> ile;
	return 0;
}
