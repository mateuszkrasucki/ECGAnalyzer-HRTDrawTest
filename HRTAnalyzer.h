#pragma once

#include "ModulesInterfaces.h"
#include "HRTData.h"
#include "Matrix.h"
using namespace std;

// testowe
static double RR[] = {800,1425, 810, 800,1050, 800, 800, 800, 800, 800, 610, 960, 775, 777, 780, 785, 795, 797,790, 790, 795, 800, 810, 800, 810, 800, 810, 800, 810, 800, 800, 800, 800, 
	600, 950, 820, 780, 782, 810, 840, 870, 900, 790, 790, 792, 795, 795, 797, 800, 800, 805, 800, 800, 805, 800, 800, 800, 600, 685, 800, 825, 800, 825,
    800, 825, 825, 825, 800, 800, 800, 800, 605, 930, 825, 788, 775, 795, 800, 800, 800, 800, 800, 805, 805, 805, 800, 809, 800, 805, 800, 805, 800, 805, 800, 825, 800,
    825, 800, 825, 880, 825, 800, 825, 800, 825, 800, 825, 1000, 800, 1025, 800, 800, 1050, 800, 800, 800, 800, 800, 530, 1100,  775, 777,780, 785, 795, 797,790, 790, 795, 
	800, 810, 800, 810, 800, 810, 800, 810, 800, 800, 800, 805, 800, 805, 800, 805, 800, 800, 805, 795, 805, 805, 825, 800, 800, 800, 800, 600, 950, 800, 865, 800, 825, 800, 
	825, 299, 800, 825, 800, 825, 800, 825, 850, 800, 825, 800, 800, 825, 610, 695, 775, 777, 780, 785, 795, 797, 790, 790, 795, 800, 810, 800, 810, 800, 810, 800, 810, 800, 800, 
	800, 805, 800, 805, 800, 805, 800, 805, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 390, 825, 800, 825, 800, 825, 800, 825, 900, 800, 925, 800, 800, 1050,
    800, 600, 950, 800, 825, 800, 825, 800, 825, 850, 800, 825, 800, 825, 800, 825, 850, 800, 825, 850, 825, 875, 825, 800, 600, 970, 775, 777, 780, 785, 795, 797, 790, 
	790, 795, 800, 810, 800, 810, 800, 810, 800, 810, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 825, 800, 825, 850, 800, 825, 800, 825, 800, 825, 850, 800, 825, 800, 800, 
	825, 600, 585, 800, 825, 800, 825, 800, 825, 825, 825, 650, 1000,782, 779, 777, 780, 785, 795, 797, 790, 790, 795, 860, 810, 800, 810, 800, 820, 800, 810, 800, 800, 800, 800, 808, 
	809, 810, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 800, 825, 390, 825, 800, 825, 800, 
	825, 800, 700, 700, 700, 709, 700, 700, 825, 810, 810, 600, 800};

/**
 * @class Class for parameters created in HRV1 module
 */
class HRTAnalyzer : public HRTModule {

public:
	HRTAnalyzer();
	~HRTAnalyzer();

	void runModule(const ECGWaves &, const ECGRs &, const ECGSignal &, const ECGInfo &, ECGHRT &);
	void run(ECGHRT &);
	void setParams(ParametersTypes &);

private:
	HRTData calculateHrtParams(double *signal, int size);
	
	vector<int> findVpcOnsets(double *signal, int size);
	double* calculateAvgTach(double *signal, vector<int> vpc_list);

	// wyliczenie TO
	// Wzi��em nadal t� metod�, w kt�rej najpierw liczy si� wszystkie TO, a nast�pnie ich �redni�
	double calculateTO_1(double * signal, int size, vector<int> vpc_list);
	double calculateTO_2(double * signal, int size, double* avgTach);

	HRTData calculateTS(double * signal, int size, vector<int> vpc_list, double* avgTach, double to_1, double to_2);

};

