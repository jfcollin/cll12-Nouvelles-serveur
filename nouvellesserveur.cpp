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
