#include "ecganalyzer.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ECGanalyzer w;
	w.show();
	return a.exec();
}
