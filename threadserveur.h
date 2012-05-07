#ifndef THREADSERVEUR_H
#define THREADSERVEUR_H

#include <QThread>
#include <QTcpSocket>
#include <QTimer>
#include <QTime>

class ThreadServeur : public QThread
{
    Q_OBJECT
public:
    explicit ThreadServeur(QObject *parent = 0, int socketDescriptor = 0);
    void run();

signals:
    
public slots:
    void Gestion_TimerHeure();
    //void Gestion_TimerCouleur();
private:
    int m_socketDescriptor;
    QTimer *TimerHeure;
    //QTimer *TimerCouleur;
    QTcpSocket socket;
    int Rouge;
    int Bleu;
    int Vert;
    int Compteur;

};

#endif // THREADSERVEUR_H
