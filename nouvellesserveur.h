#ifndef NOUVELLESSERVEUR_H
#define NOUVELLESSERVEUR_H

#include <QMainWindow>
#include <QList>
#include <QtWebKit>


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
    int connectionId;
    QXmlStreamReader xml;
    QHttp http;

};

#endif // NOUVELLESSERVEUR_H
