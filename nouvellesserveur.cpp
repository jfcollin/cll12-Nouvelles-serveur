#include "nouvellesserveur.h"
#include "ui_nouvellesserveur.h"

NouvellesServeur::NouvellesServeur(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NouvellesServeur)
{
    ui->setupUi(this);

    QUrl url("http://affaires.lapresse.ca/rss/2343.xml");

    http.setHost(url.host());
    connectionId = http.get(url.path());

    xml.addData(http.readAll());

    ui->WV->load(QUrl(url));
    ui->WV->show();

}

NouvellesServeur::~NouvellesServeur()
{
    delete ui;
}


