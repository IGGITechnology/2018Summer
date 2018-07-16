#include "IGGE.h"
#include <QtWidgets/QApplication>
#include "mywin.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mywin w;
	w.show();
	return a.exec();
}
