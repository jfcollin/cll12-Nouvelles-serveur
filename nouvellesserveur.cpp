#include "nouvellesserveur.h"
#include "ui_nouvellesserveur.h"

NouvellesServeur::NouvellesServeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NouvellesServeur)
{

    ui->setupUi(this);


}

NouvellesServeur::~NouvellesServeur()
{
    delete ui;
}

void NouvellesServeur::on_Demarer_clicked()
{
    socketServeur = new tcpserveur();
    if(!socketServeur->listen(QHostAddress::Any,60123))
        QMessageBox::information(this, "Erreur", "Erreur listen");

}

