#include <QtGui/QApplication>
#include "nouvellesserveur.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NouvellesServeur w;
    w.show();
    
    return a.exec();
}
