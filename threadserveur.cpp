#include "threadserveur.h"
#include <QMessageBox>
#include "nouvellesserveur.h"


ThreadServeur::ThreadServeur(QObject *parent, int socketDescriptor) :
    QThread(parent)
{
    m_socketDescriptor = socketDescriptor;
    TimerHeure = new QTimer(this);
    connect(TimerHeure, SIGNAL(timeout()), this, SLOT(Gestion_TimerHeure()));

}
void ThreadServeur::run()
{
    socket.setSocketDescriptor(m_socketDescriptor);
    TimerHeure->start(1000);
    Compteur=0;
    Rouge =0;
    Bleu =0;
    Vert= 0;
    while (1);

}
//Envoie de l'heure à chaque seconde
void ThreadServeur::Gestion_TimerHeure()
{

    QTime t_Heure = QTime::currentTime();
    QString Heure = "h" + t_Heure.toString("hh:mm:ss");
    QByteArray Trame;
    QByteArray BaReception;

    for (int i(0); i < Heure.length(); ++i)
    {
        Trame += Heure[i].toAscii();
    }

    /*if (Compteur==0)
    {
        socket.write(Trame);
    }
    else
    {
        socket.waitForReadyRead(500);
        socket.write(Trame);

    }*/


    char Couleur = 'c';
    //QByteArray TrameCouleur;


    if (Rouge <=255 && Rouge!=0 && Bleu ==255 && Vert == 255)
        Rouge -=15;
        else if (Rouge ==0 && Bleu!=0 && Bleu <=255 && Vert == 255)
            Bleu -=15;
            else if (Rouge ==0 && Bleu==0 && Vert !=0 && Vert <= 255)
                Vert-=15;
                else if (Rouge < 255)
                    Rouge+=15;
                    else if(Bleu < 255)
                        Bleu+=15;
                        else if (Vert <255)
                            Vert+=15;
    char c;
    Trame +=Couleur;
    c = Rouge;
    Trame += c;
    c = Vert;
    Trame += c;
    c = Bleu;
    Trame += c;


    socket.write(Trame);
    ++Compteur;


}
