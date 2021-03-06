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

private:
    int m_socketDescriptor;
    QTimer *TimerHeure;
    QTcpSocket socket;
    int Rouge;
    int Bleu;
    int Vert;
    QString Adresse[8];
    bool EnvoyerHeure;
    QByteArray Trame;
    QByteArray m_TrameHeure;
};

#endif // THREADSERVEUR_H
