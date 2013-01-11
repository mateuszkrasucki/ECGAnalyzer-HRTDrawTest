#include "HRTAnalyzer.h"
#include "ECGSignal.h"

HRTAnalyzer::HRTAnalyzer() { }

HRTAnalyzer::~HRTAnalyzer() { }

void HRTAnalyzer::runModule(const ECGWaves & waves, const ECGRs & ecgrs, const ECGSignal & signal, const ECGInfo & ecginfo, ECGHRT & hrt_data) {
	
}

void HRTAnalyzer::run(ECGHRT & hrt_data)	{
	HRTData res= calculateHrtParams(RR,380);
	hrt_data.offset=5;
	for(int i=0; i<26; i++)	{
		hrt_data.rr.push_back(QPointF(double(i), res.avgSignal[i]));
	}
	hrt_data.ts.setLine(7.0,res.straightSignal[7],25.0,res.straightSignal[25]);

	res.printData();
}

void HRTAnalyzer::setParams(ParametersTypes &parameterTypes) { }

// G³ówna funkcja, zwraca obiekt z danymi do wizualizacji
HRTData HRTAnalyzer::calculateHrtParams(double *signal, int size)
{
	vector<int> vpc_list = findVpcOnsets(signal, size);
		
	if(vpc_list.size() < 5)
	{
		HRTData result(1);
		result.isCorrect = 0;
		result.errorDescription = "Niestety, w zarejestrowanym sygnale nie uda³o siê znaleŸæ niezbêdnych 5 przedwczesnych pobudzeñ komorowych";
		return result;
	}

	double* avgTach = calculateAvgTach(signal, vpc_list);

	double to_1 = calculateTO_1(signal, size, vpc_list);
	double to_2 = calculateTO_2(signal, size, avgTach);

	return calculateTS(signal, size, vpc_list, avgTach, to_1, to_2);
}


vector<int> HRTAnalyzer::findVpcOnsets(double *signal, int size)
{
	vector<int> vpc_list;

	for(int i = 6; i < size-19; i++)
	{
			// Interwa³ referencyjny
			double mean5before = (signal[i-5] + signal[i-4] + signal[i-3] + signal[i-2] + signal[i-1])/5;
		 
			// Sprawdzenie czy interwa³ mo¿e byæ kandydatem na VPC
			if((0.8 * mean5before < signal[i]) || (signal[i+1] < 1.1 * mean5before) || abs(signal[i-1] - signal[i-2]) > 200)
			{
			continue;
			}
			
			// Sprawdzenie czy d³ugoœæ jest >300 ms i <2000 ms
			int param = 0; 
			for(int j = i - 5; j <= i + 19; j++)
			{
			if(j == i - 1 || j == i || j == i+1)
			{
				continue;
			}

			if(signal[j] > 2000 || signal[j] < 300)
			{
				param = 1;
				break;
			}
			}
    
			if(param == 1)
			{
				continue;
			}

			// Sprawdzenie czy 2 s¹siednie zwyk³e interwa³y maj¹ ró¿nicê mniejsz¹ ni¿ o 200 ms
			// oraz czy ka¿dy ze zwyk³ych interwa³ów ró¿ni siê o mniej ni¿ 20% od interwa³u referencyjnego.
			for(int j = i-5; j <= i + 19; j++)
			{
				if(j == i-1 || j == i || j == i+1) 
				{
					continue;
				}

				if(abs(signal[j] - signal[j+1]) > 200 || (abs(signal[j] - mean5before) > 0.2 * mean5before))
				{
					param = 1;
					break;
				}
			}
    
			if(param == 1)
			{
			continue;
			}
			 
		    vpc_list.push_back(i-5);
	}

	return vpc_list;
}

double* HRTAnalyzer::calculateAvgTach(double *signal, vector<int> vpc_list)	{
	double *avgTach= new double[26];

	for(int i = 0; i < 26; i++)
	{
		avgTach[i] = 0.0;
	}

	/* Obliczanie uœrednionego tachogramu  */
	
	for(int j = 0; j < vpc_list.size(); j++)
	{
		for(int i=0; i < 26; i++)
		{
			avgTach[i] = avgTach[i] + signal[vpc_list[j] + i];
		}
	}

	for(int i = 0; i < 26; i++)
	{
		avgTach[i] = avgTach[i]/vpc_list.size();
	}

	return avgTach;
}

// wyliczenie TO
// Wzi¹³em nadal tê metodê, w której najpierw liczy siê wszystkie TO, a nastêpnie ich œredni¹
double HRTAnalyzer::calculateTO_1(double * signal, int size, vector<int> vpc_list)
{
	double to = 0.0;
	double sumto = 0.0;

	for(int i = 0; i < vpc_list.size(); i++)
	{
		to = 100*((signal[vpc_list[i] + 7] + signal[vpc_list[i] + 8]) - (signal[vpc_list[i] + 3] + signal[vpc_list[i] + 4])) / (signal[vpc_list[i] + 3] + signal[vpc_list[i] + 4]);   
		sumto += to;
	}

	to = sumto/vpc_list.size();
	return to;
}


double HRTAnalyzer::calculateTO_2(double * signal, int size, double* avgTach)
{
	double to = 0.0;
	to = 100*((avgTach[7] + avgTach[8]) - (avgTach[3] + avgTach[4])) / (avgTach[3] + avgTach[4]);   

	return to;
}



HRTData HRTAnalyzer::calculateTS(double * signal, int size, vector<int> vpc_list, double* avgTach, double to_1, double to_2)
{
	HRTData result(vpc_list.size());

    vector<double> A;
    vector<double> B;

    for (int i = 0; i < 15; i++)
	{
		double *x = new double[5];
		for(int k = 0; k < 5; k++)
		x[k] = k + i + 7;
			
		Parameters res = Matrix::getLinearEquationParameters(x, avgTach+i+7 , 5);
 
        A.push_back(res.A);
        B.push_back(res.B);
	}
        
		
	/* Wybór najwiêkszego A */
	double maxA = A[0];
	for(int i = 1; i < A.size(); i++)
	{
		if(maxA < A[i]) maxA = A[i];
	}

    double parB = B[0];
	for(int i = 0; i < A.size(); i++)
	{
		if(A[i] == maxA)
		{
				
			parB = B[i];
		}
	}

	result.TO_1 = to_1;
	result.TO_2 = to_2;
	result.vpcCounter = vpc_list.size();
	//====================USTAWIANIE OBIEKTU Z DANYMI DO WYŒWIETLENIA=======================
	// Ustawienie œredniego sygna³u tachogramu oraz
	// Ustawienie parametrów prostej ilustrujacej Turbulence Slope
	for(int i = 0; i < result.SLENGTH; i++)
	{
		result.avgSignal[i] = avgTach[i];
		result.straightSignal[i] = i*maxA + parB;
	}

	// Ustawienie wszystkich mo¿liwych sygna³ów
	for(int i = 0; i < result.ALL_SIGNALS_LENGTH; i++)
	{
		for(int j = 0; j < result.SLENGTH; j++)
		{
			double a = vpc_list[i];
			result.allSignals[i][j] = signal[vpc_list[i] + j];
		}
	}
	result.y1_to = result.avgSignal[7];

	result.length_to_1 = result.avgSignal[7]*result.TO_1/100;
	result.length_to_2 = result.avgSignal[7]*result.TO_2/100;
	result.MAXY = result.getMaxValue();
	result.TS=maxA;
	delete [] avgTach;
	return result;
}