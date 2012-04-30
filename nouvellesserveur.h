#ifndef NOUVELLESSERVEUR_H
#define NOUVELLESSERVEUR_H

#include <QMainWindow>

namespace Ui {
class NouvellesServeur;
}

class NouvellesServeur : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit NouvellesServeur(QWidget *parent = 0);
    ~NouvellesServeur();
    
private:
    Ui::NouvellesServeur *ui;
};

#endif // NOUVELLESSERVEUR_H
