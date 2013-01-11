#ifndef ECGANALYZER_H
#define ECGANALYZER_H

#include <QtGui/QMainWindow>
#ifdef WIN32
	#include "GeneratedFiles/ui_ecganalyzer.h"
	#include "GeneratedFiles/ui_AboutWindow.h"
#else
 #include "ui_ecganalyzer.h"
 #include "ui_AboutWindow.h"
#endif


#include "ECGController.h"
#include "plots/hrt.h"
#include "plots/plotpoincare.h"
#include "plots/plothrvtriangle.h"
#include "AboutWindow.h"


class ECGanalyzer : public QMainWindow
{
	Q_OBJECT

public:
	ECGanalyzer(QWidget *parent = 0, Qt::WFlags flags = 0);
	~ECGanalyzer();

private slots:
    void on_actionO_Qt_triggered();

    void on_actionO_Programie_triggered();

    void on_actionWczytaj_plik_z_sygnalem_triggered();

    void on_actionWyjdz_triggered();

    void on_radioButtonMovingAverage_toggled(bool checked);

    void on_radioButtonButterworthFilter_toggled(bool checked);

    void on_checkBoxRPeaksDetectThresholdAutomatically_toggled(bool checked);

    void on_actionPrzeprowadzPonownieAnalizeSygnalu_triggered();

    void on_actionZatrzymajPonownaAnalizeSygnalu_triggered();

private:
	Ui::ECGanalyzerClass ui;
	AboutWindow aboutWindow;

	void updateRunButtons(bool analysisOngoing);

	void updateAnalysisStatus(std::string status);

	ECGController _ECGcontroller;
	//Ecg2Ch _ecg2ch;
};

#endif // ECGANALYZER_H
