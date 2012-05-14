#ifndef NOUVELLESSERVEUR_H
#define NOUVELLESSERVEUR_H

#include <QMainWindow>
#include "tcpserveur.h"
#include <QMessageBox>
namespace Ui {
class NouvellesServeur;
}

class NouvellesServeur : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit NouvellesServeur(QWidget *parent = 0);
    ~NouvellesServeur();

private slots:
    void on_Demarer_clicked();
signals:


private:
    Ui::NouvellesServeur *ui;

    tcpserveur *socketServeur;

};

#endif // NOUVELLESSERVEUR_H
