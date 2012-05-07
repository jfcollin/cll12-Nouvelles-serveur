#ifndef NOUVELLESSERVEUR_H
#define NOUVELLESSERVEUR_H

#include <QMainWindow>
#include <QList>
#include <QtWebKit>
#include <QTreeWidgetItem>
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

public slots :
    void parseXml();
    void readData(const QHttpResponseHeader &resp);

private slots:
    void on_TW_itemActivated(QTreeWidgetItem *item);

    void on_Demarer_clicked();

private:
    Ui::NouvellesServeur *ui;
    int connectionId;
    QXmlStreamReader xml;
    QHttp http;
    QString currentTag;
    QString linkString;
    QString titleString;
    QString dateString;

    QTreeWidgetItem *feed;
    tcpserveur *socketServeur;

};

#endif // NOUVELLESSERVEUR_H
