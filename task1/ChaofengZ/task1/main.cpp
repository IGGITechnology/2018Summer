#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int res =-1;
    do{
        MainWindow w;
        w.show();

        res = a.exec();
    }while(res !=0 );


    return res;
}
