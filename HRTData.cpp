#include "HRTData.h"
using namespace std;

HRTData::HRTData(int size):SLENGTH(26),MINX(-2.0),MAXX(28.0),MINY(0.0),ALL_SIGNALS_LENGTH(size),x1_to(7)
{
	straightSignal = new double[SLENGTH];
	avgSignal = new double[SLENGTH];
	for(int j = 0; j < SLENGTH; j++)
	{
		avgSignal[j] = 0.0;
		straightSignal[j] = 0.0;
	}

	allSignals = new double*[ALL_SIGNALS_LENGTH];
	for(int i = 0; i < ALL_SIGNALS_LENGTH; i++)
	{
		allSignals[i] = new double[SLENGTH];
		for(int j = 0; j < SLENGTH; j++)
		{
			allSignals[i][j]=0.0;
		}
	}
}

double HRTData::getMaxValue()
{
	double maxx = allSignals[0][0];
	for(int i = 0; i < ALL_SIGNALS_LENGTH; i++)
	{
		for(int j = 0; j < SLENGTH; j++)
		{
			if(allSignals[i][j] > maxx) maxx= allSignals[i][j];
		}
	}
	return maxx;
}

void HRTData::printData()
{
	cout<<endl;
	cout<<"-------------------------------------------------------------------------------";
	cout<<endl<< "vpcCounter: " << vpcCounter;
	cout<<endl<< "TS: " << TS;
	cout<<endl<< "TO_1: " << TO_1 << " TO_2: " << TO_2 << endl;
	cout<<endl<< "minx: " << MINX;
	cout<<endl<< "maxx: " << MAXX;
	cout<<endl<< "miny: " << MINY;
	cout<<endl<< "maxy: " << MAXY << endl;
	cout<<endl<< "t onset wsp.x punkt 1: " << x1_to;
	cout<<endl<< "t onset wsp.y punkt 1: " << y1_to;
	cout<<endl<< "dlugosc TO_1 " << length_to_1 << " dlugosc TO_2 " << length_to_2<<endl;
	cout<<endl<< "Punkty prostej regresji: " << endl;
	for(int i = 0; i < SLENGTH; i++)
	{
		cout<< straightSignal[i] <<" ";
	}
	cout<<endl;

	cout<<"Sygna³ uœredniony: "<<endl;
	for(int i = 0; i < SLENGTH; i++)
	{
		cout<< avgSignal[i] <<" ";
	}
	cout<<endl;

	cout<<"Sygna³y kolejnych VPC: "<<endl;
	for(int i = 0; i < ALL_SIGNALS_LENGTH; i++)
	{
		cout<<endl;
		for(int j = 0; j < SLENGTH; j++)
		{
			cout<< allSignals[i][j]<<" ";
		}
	}

	cout<<endl<<"-------------------------------------------------------------------------------";
	cout<<endl;
}

HRTData& HRTData::operator=(HRTData xx)
{
	return *this;
}