#ifndef HRTDATAX
#define HRTDATAX exists
#include <iostream>
using namespace std;

// klasa przechowuj¹ca wszystkie dane niezbêdne do rysowania, to ostateczny wynik dzia³ania modu³u
class HRTData
{
	public:
	int isCorrect; // W razie jeœli wykryto zbyt ma³o VPC, lub w przypadku wyst¹pienia innych wad sygna³u (np. zbyt krótki zapis) - ustawiana jest ta flag
				   // czyli, GOŒCIU OD WYKRESÓW, JEŒLI WIDZISZ FLAGÊ == 0, WYŒWIETL KOMUNIKAT O B£ÊDZIE 

	/* DANE DO WYPISANIA --------------------------------------------------- */

	string errorDescription; //  jeœli isCorrect == 0 , w tym stringu znajduje siê opis b³êdu!!
	// w przeciwnym razie
	
	int vpcCounter;		//  iloœæ znalezionych VPC,
	double TS;			// wartoœæ Turbulence Slope
	double TO_1;			// wartoœæ Turbulence Onset - œrednia z pojedynczych TO
	double TO_2;		//wartoœæ Turbulence Onset - obliczone na AvgTach

	/* DANE DO MALOWANIA ---------------------------------------------------- */
	const int SLENGTH; // Ka¿dy z poni¿szych sygna³ów bêdzie mia³ indeksy od 0 DO SLENGTH
	double *avgSignal;			// uœredniony sygna³
	const int ALL_SIGNALS_LENGTH;
	double **allSignals;		// wszystkie wyciête z sygna³u fragmenty zawieraj¹ce VPC
	double *straightSignal; //  punkty z najlepszej prostej TS wyznaczone dla argumentów
	
	const double x1_to; // wspó³rzêdne odcinka Turbulence Onset metoda 1 // pocz¹tek i koniec
	double y1_to;
	double length_to_1; // ujemna d³ugoœæ -> malowanie w górê, dodatnia malowanie w dó³
	double length_to_2; 

	//  Osie, czyli jaki zakres nale¿y ustawiæ na wykresie
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