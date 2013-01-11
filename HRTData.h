#ifndef HRTDATAX
#define HRTDATAX exists
#include <iostream>
using namespace std;

// klasa przechowuj�ca wszystkie dane niezb�dne do rysowania, to ostateczny wynik dzia�ania modu�u
class HRTData
{
	public:
	int isCorrect; // W razie je�li wykryto zbyt ma�o VPC, lub w przypadku wyst�pienia innych wad sygna�u (np. zbyt kr�tki zapis) - ustawiana jest ta flag
				   // czyli, GO�CIU OD WYKRES�W, JE�LI WIDZISZ FLAG� == 0, WY�WIETL KOMUNIKAT O B��DZIE 

	/* DANE DO WYPISANIA --------------------------------------------------- */

	string errorDescription; //  je�li isCorrect == 0 , w tym stringu znajduje si� opis b��du!!
	// w przeciwnym razie
	
	int vpcCounter;		//  ilo�� znalezionych VPC,
	double TS;			// warto�� Turbulence Slope
	double TO_1;			// warto�� Turbulence Onset - �rednia z pojedynczych TO
	double TO_2;		//warto�� Turbulence Onset - obliczone na AvgTach

	/* DANE DO MALOWANIA ---------------------------------------------------- */
	const int SLENGTH; // Ka�dy z poni�szych sygna��w b�dzie mia� indeksy od 0 DO SLENGTH
	double *avgSignal;			// u�redniony sygna�
	const int ALL_SIGNALS_LENGTH;
	double **allSignals;		// wszystkie wyci�te z sygna�u fragmenty zawieraj�ce VPC
	double *straightSignal; //  punkty z najlepszej prostej TS wyznaczone dla argument�w
	
	const double x1_to; // wsp�rz�dne odcinka Turbulence Onset metoda 1 // pocz�tek i koniec
	double y1_to;
	double length_to_1; // ujemna d�ugo�� -> malowanie w g�r�, dodatnia malowanie w d�
	double length_to_2; 

	//  Osie, czyli jaki zakres nale�y ustawi� na wykresie
	const int MINX; 
	const int MAXX;
	int MAXY;
	const int MINY;

	HRTData(int size);
	void printData();
	HRTData& operator=(HRTData xx);
	double getMaxValue();
};

#endif