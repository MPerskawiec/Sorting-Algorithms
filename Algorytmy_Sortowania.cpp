/*
 * Algorytmy_Sortowania.cpp
 *
 *  Created on: 12 kw 2018
 *      Author: Mariusz
 */

#include <iostream>
#include <cmath>


#define BLAD_SORTOWANIA 1  // Komunikat o bledzie gdy w przypadku wykrycia zle posortowanej tablicy

using namespace std;

/************************* Sortowanie szybkie ( quicksort) **************************************
*																								*
*  Funkcja ustawia warto�c l na pierwszym elemencie natomiast p na ostatnim, po czym porownuje	*
*  te elementy z wartoscia piwota. Gdy po lewo piwot napotka wiekszy element od niego, 			*
*  to elemnt ten zostaje wymieniony z pierwszym napotkanym elementem mniejszym od piwota 		*
*  idac od prawej strony. Nastepnie ineks l przesowa sie o jeden element do przodu a p do tylu.	*
*  Cala operacja wykonuje sie do momentu spotkania sie elementow l i p. Po czym nastepuje 		*
*  ponowny podzial na mniejsze tablice i procedura ta powta�a si� a� do momentu posortowania 	*
*  calej tablicy																				*
*  																								*
*  tab   <- jako argument przekazujemy tablice, ktora chcemy posortowac							*
*  lewy  <- indeks lewego( pierwszego ) elementu od ktorego tablica ma zostac posortowana		*
*  prawy <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana		*
*																								*
*///*********************************************************************************************
template<typename T>
void quicksort(T *tab, int lewy, int prawy) {     
	T piwot = tab[(lewy + prawy) / 2];	// Pobieramy wartosc srodkowego elemetu do porownywania 
	T buf;
	int l = lewy;
	int p = prawy;
	
	do {		// wykonuj do momentu spotkania sie indeksu lewego i prawego elementu tablicy. 
		while (tab[l] < piwot){		// szukanie wiekszego elementu od piwota
			l++;
		}
		while (tab[p] > piwot){		// szukanie mniejszego elementu od piwota
			p--;
		}
		if (l <= p) {				// zamiana elementow miejscami
			buf = tab[l];
			tab[l] = tab[p];
			tab[p] = buf;
			l++;
			p--;
		}
	} while (l <= p);

									// podzzial na mniejsze tablice
	if (p > lewy)					
		quicksort(tab, lewy, p);
	if (l < prawy)
		quicksort(tab, l, prawy);
}

/********************************** Sortowanie przez scalanie ***********************************
*																								*
*  Funkcja rekurencyjnie dzieli tablice na coraz mniejsze podzbiory a� do uzyskania tablic		*
*  jednoelementowych, a nastepnie rekurencja sie zamyka i  tablice w odpowiedniej kolejnosci 	*
*  sa skladanie, w calosc. Operacja skladania tablic wykonuje sie za pomoca funkcji scalanie 	*
*  																								*
*  tab   <- jako argument przekazujemy tablice, ktora chcemy posortowac							*
*  lewy  <- indeks lewego( pierwszego ) elementu od ktorego tablica ma zostac posortowana		*
*  prawy <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana		*
*																								*
*///*********************************************************************************************
template<typename T>
void sortowanie_przez_scalanie(T *tab, int lewy, int prawy) {

	if(lewy<prawy){

		int srodek = (lewy+prawy)/2;

		sortowanie_przez_scalanie(tab,lewy,srodek);
		sortowanie_przez_scalanie(tab,srodek+1,prawy);
		scalanie(tab,lewy,srodek,prawy);
	}
}

/****************************************** Scalanie ********************************************
*																								*
*  Funkcja rekurencyjnie dzieli tablice na coraz mniejsze podzbiory a� do uzyskania tablic		*
*  jednoelementowych, a nastepnie rekurencja sie zamyka i  tablice w odpowiedniej kolejnosci 	*
*  sa skladanie, w calosc. Operacja skladania tablic wykonuje sie za pomoca funkcji scalanie 	*
*  																								*
*  tab    <- jako argument przekazujemy tablice, ktora chcemy zlozyc w calosc					*
*  lewy   <- indeks lewego( pierwszego ) elementu od ktorego tablica ma zostac posortowana		*
*  srodek <- element oddzielajacy dwa elementy tablicy do scanalnia								*
*  prawy  <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana	*
*																								*
*///*********************************************************************************************
template<typename T>
void scalanie(T *tab, int lewy, int srodek, int prawy){

	T *pom;
	pom = new T[prawy -lewy +1];   // Tworzymy tablice pomocnicz� do scalania nowej posortowanej

	int i = lewy;
	int k = 0;
	int j = srodek + 1;		// pierwszy element "drugiej" tablicy


	while ((i <= srodek) && (j <= prawy)){	// znajdowanie elementow od najmniejsego do najwiekszego
		if(tab[j] < tab[i]){
			pom[k] = tab[j];
			j++;
		}
		else{
			pom[k] = tab[i];
			i++;
		}
	k++;

	}

	if(i<=srodek){			// Jezeli zostaly elementy do posortowania tylko w lewej czesci tablicy
		while(i<=srodek){
			pom[k] = tab[i];
			i++;
			k++;
		}

	}
	else{
		while(j<=prawy){	// Jezeli zostaly elementy do posortowania tylko w pawej czesci tablicy
			pom[k]= tab[j];
			j++;
			k++;
		}
	}

	for(int x = 0; x<(prawy-lewy+1);x++){	// Przepisanie posortowanych wartosci do oryginalnej tablicy
		tab[lewy+x] = pom[x];
	}

	delete pom;
}

/***********************************Sortowanie introspektywne ***********************************
*																								*
*  Rodzaj sortowania, ktore do swojego dzialanai uzywa sortowania szybkiego, sortowania 		*
*  przez kopcowanie oraz sortowania przez wstawianie. Sortowanie introspektywne pozwala 		*
*  unikn�� najgorszego przypadku dla sortowania szybkiego (nier�wnomierny podzia� tablicy		*
*  w przypadku, gdy jako element osiowy zostanie wybrany element najmniejszy lub najwi�kszy).	*
*  W sortowaniu tym obliczana jest maksymalna glebokosc rekurencji jaka mo�e sie wykonac 		*
*  dla sortowania szybkiego. W momencie przekroczenia jej watosci tablica zostaje uporzadkowana	*
*  za pomoca metody sortowania przez kopcowanie.  												*
*  																								*
*  tab <- jako argument przekazujemy tablice, ktora chcemy zlozyc w calosc						*
*  p   <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana		*
*																								*
*///*********************************************************************************************
template<typename T>
void sortowanie_introspektywne (T *tab, int p)
{
  IntroSort(tab,p,(int)floor(2*log(p+1)/log(2)));   
  sortowanie_przez_wstawianie(tab,p);				
}

/****************************************** Partition *******************************************
*																								*
*  Funkcja ustawia warto�c l na pierwszym elemencie natomiast p na ostatnim, po czym porownuje	*
*  te elementy z wartoscia piwota. Gdy po lewo piwot napotka wiekszy element od niego, 			*
*  to elemnt ten zostaje wymieniony z pierwszym napotkanym elementem mniejszym od piwota 		*
*  idac od prawej strony. Nastepnie ineks l przesowa sie o jeden element do przodu a p do tylu.	*
*  Cala operacja wykonuje sie do momentu spotkania sie elementow l i p.	Nasteonie funkcja 		*
*  zwraca adres elementu, ktory okresla przedzial tablic										*
*  																								*
*  tab <- jako argument przekazujemy tablice, ktora chcemy zlozyc w calosc						*
*  p   <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana		*
*  l   <- indeks lewego  ( pierwszego ) elementu od ktorego tablica ma zostac posortowana		*
*																								*
*///*********************************************************************************************
template<typename T>
int Partition(T *tab, int l, int p) {        
	T piwot = tab[(l + p) / 2];	// Pobieramy wartosc srodkowego elemetu do porownywania 
	T buf;

	do {		// wykonuj do momentu spotkania sie indeksu lewego i prawego elementu tablicy. 
		while (tab[l] < piwot){
			l++;
		}
		while (tab[p] > piwot){
			p--;
		}
		if (l <= p) {				// zamiana elementow miejscami
			buf = tab[l];
			tab[l] = tab[p];
			tab[p] = buf;
			l++;
			p--;
		}
	} while (l <= p);

	return l;  // zwracamy przedzial tablicy
}

/****************************************** Introsort *******************************************
*																								*
*  Funkcja sortowania introspektywnego, zarz�dzaj�ca kt�re sortowanie ma zostac wykonane		*
*  tablice mniejsze od 9 elementow nie sa sortowane, poniewaz dla nich zostanie wywolane		*
*  sortowanie przez wstawianie																	*
*  																								*
*  tab <- jako argument przekazujemy tablice, ktora chcemy zlozyc w calosc						*
*  p   <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana		*
*  M   <- glebokosc rekurncji okreslajaca ile razy jescze maksymalnie mozna wywolac rekurencje	*
*																								*
*///*********************************************************************************************
template<typename T>
void IntroSort (T *tab, int p, int M)
{
  int lewy;
  if (M<=0)
  {
	  sortowanie_przez_kopcowanie(tab, p);
    return;
  }
  lewy=Partition(tab,0,p);
  if (lewy>=9)               // dla tablicy wi�kszej od 9 wykonuje si�
    IntroSort(tab,lewy,M-1);
  if (p-lewy>9)			 // TUTAJ CHYBA 8 zamiast 9 a tu podspodem przekazuej tab+1
    IntroSort(tab+lewy,p-lewy,M-1);
}

/******************************** Sortowanie przez kopcowanie ***********************************
*																								*
*  Funkcja tworzy tak zwane drzewo binarne na tablicy, a przy pomocy funkcji rotacje_kopca		*
*  dokonuje odpowiednich rotacja, aby najwiekszy element znalazl sie na samej gorze( indeks		*
*  o numerze "0" w tablicy sortowanej). W nastepnym kroku element ten jest zamieiant z ostatnim	*
*  a nastepnie funkcja wywoluje sie rekurenyjnie dla tablicy o jeden element mniejszej czyli	*
*  zostaje pomijany ostatni najwielszy element( gdyz jest juz na swoim miejscu) cala operacja	*
*  powtarza sie do momentu posortowania calej tablicy.											*
*  																								*
*  tab <- jako argument przekazujemy tablice, ktora chcemy zlozyc w calosc						*
*  p   <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana		*
*																								*
*///*********************************************************************************************
template<typename T>
void sortowanie_przez_kopcowanie(T *tab, int p){



	for(int i = (p+1)/2; i>0;){
		--i;
		rotacje_kopca(tab, i,p);
	}


	while(p>1){
		p--;
		rotacje_kopca(tab,0,p);

	}
}

/************************************ Rotacje kopca *********************************************
*																								*
*  Funkcja dokonujaca rotacji kopca, opis dzialania algorytmy zosta opisany powyzej				*
*  																								*
*  tab  <- jako argument przekazujemy tablice, ktora chcemy zlozyc w calosc						*
*  p    <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana		*
*  l    <- indeks  lewego ( pierwszego ) elementu do ktorego tablica ma zostac posortowana		*
*																								*
*///*********************************************************************************************
template<typename T>
void rotacje_kopca(T *tab, int l, int p){

	int x;
	T pom;

		while(l<=((p-1)/2)){ 


		x = 2*l + 1;
		if(x + 1 <=p && tab[x+1] > tab[x]){
			x = x+1;
		}
		if(tab[l] < tab[x] ){
			pom = tab[l];
			tab[l] = tab[x];
			tab[x] = pom;
		}
		else break;
		l = x;

		}

		pom = tab[p];      // zamiana najwi�kszego elementu na sam koniec tablicy
		tab[p] = tab[0];
		tab[0] = pom;

}

/********************************* Sortowanie przez wstawianie **********************************
*																								*
*  Funkcja sprawdzajaca czy element tablicy jest  wiekszy od poprzedzajacego go.				*
*  W przypadku gdy jest mniejszy przesuwa si� w lewo a� znajdze dla niego odpowiednie 			*
*  miejsce i tam go wstawia. Po czym wraca do miejsca skad zaczynala i tam kontynuuj swoja		*
*  prace do momentu, a� posortuje cala tablice.													*
*  																								*
*  tab <- jako argument przekazujemy tablice, ktora chcemy posortowac					    	*
*  p   <- indeks prawego ( ostatniego ) elementu do ktorego tablica ma zostac posortowana		*
*																								*
*///*********************************************************************************************
template<typename T>
void  sortowanie_przez_wstawianie (T *tab, int p)
{
  int j;
  T pom;
  for (int i=1; i<=p; ++i)
  {
    pom=tab[i];

    for (j=i; j>0 && pom<tab[j-1]; --j){
      tab[j]=tab[j-1];
    }

    tab[j]=pom;
  }
}


/************************************* Test sortowania ******************************************
*																								*
*  W funkcji tej nastepuje sprawdzanie czy tablica jest odpowiednio posortowana					*
*  Funkcja sprawdza czy element wystepujacy wczesniej w tablicy nie jest wiekszy od nastepnego,	*
*  jezeli tak sie stanie funkcja zwraca komunikat i konczy dalsze sprawdzanie					*
*  																								*
*  tab     <- jako argument przekazujemy tablice, ktora chcemy przetestowac						*
*  rozmiar <- rozmiar tablicy, w ktorej sprawdzamy poprawnosc sortowania						*
*																								*
*///*********************************************************************************************
template<typename T>
bool test_sortowania (T *tab, int rozmiar){

		if(rozmiar == 0){   // Jezeli brak elemento zakonc
		return 0;
		}
		if(rozmiar==1){		// tablica 1 elementowa nie wymaga testow sorotwania 
		return 0;
		}
		
		for(int i =1; i<rozmiar;i++){	// Jezeli elemmrnt wczesniej wystepujacy jest mniejszy
				if(tab[i-1]>tab[i]){	// zakoncz i zwroc komunikat 
				return BLAD_SORTOWANIA ;
			
				}
		}
		return 0;c
		
}



