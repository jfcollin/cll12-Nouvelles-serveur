#include "threadserveur.h"
#include <QMessageBox>
#include "nouvellesserveur.h"


ThreadServeur::ThreadServeur(QObject *parent, int socketDescriptor) :
    QThread(parent)
{
    m_socketDescriptor = socketDescriptor;
    TimerHeure = new QTimer(this);
    connect(TimerHeure, SIGNAL(timeout()), this, SLOT(Gestion_TimerHeure()));
    //TimerCouleur = new QTimer(this);
    //connect(TimerCouleur, SIGNAL(timeout()), this, SLOT(Gestion_TimerCouleur()));

}
void ThreadServeur::run()
{
    socket.setSocketDescriptor(m_socketDescriptor);
    TimerHeure->start(1000);
    //TimerCouleur->start(1333);
    Compteur=0;
    while (1);

}
//Envoie de l'heure à chaque seconde
void ThreadServeur::Gestion_TimerHeure()
{
    /*
    QTime t_Heure = QTime::currentTime();
    QString Heure = "h" + t_Heure.toString("hh:mm:ss");
    QByteArray Trame;
    QByteArray BaReception;

    for (int i(0); i < Heure.length(); ++i)
    {
        Trame += Heure[i].toAscii();
    }

    if (Compteur==0)
    {
        socket.write(Trame);
    }
    else
    {
        socket.waitForReadyRead(500);
        socket.write(Trame);

    }
    */


    char Couleur = 'c';
    QByteArray TrameCouleur;
    Rouge =0;
    Bleu =0;
    Vert= 0;

    if (Rouge <255 && Rouge!=0 && Bleu ==255 && Vert == 255)
        Rouge -=1;
        else if (Rouge ==0 && Bleu!=0 && Bleu <=255 && Vert == 255)
            Bleu -=1;
            else if (Rouge ==0 && Bleu==0 && Vert !=0 && Vert <= 255)
                Vert-=1;
                else if (Rouge < 255)
                    Rouge+=1;
                    else if(Bleu < 255)
                        Bleu+=1;
                        else if (Vert <255)
                            Vert+=1;
    char c;
    TrameCouleur +=Couleur;
    c = Rouge;
    TrameCouleur += c;
    c = Vert;
    TrameCouleur += c;
    c = Bleu;
    TrameCouleur += c;

    if (Compteur==0)
    {
        socket.write(TrameCouleur);
    }
    else
    {
        socket.waitForReadyRead(500);
        socket.write(TrameCouleur);
    }


    ++Compteur;


}
//Envoie d'une couleur à chaque 1.333 seconde
/*
void ThreadServeur::Gestion_TimerCouleur()
{
    QString Couleur = "c";
    QByteArray Trame = Couleur.toAscii();
    QByteArray BaReception;
    Rouge =0;
    Bleu =0;
    Vert= 0;

    if (Rouge <255 && Rouge!=0 && Bleu ==255 && Vert == 255)
        Rouge -=3;
        else if (Rouge ==0 && Bleu!=0 && Bleu <=255 && Vert == 255)
            Bleu -=3;
            else if (Rouge ==0 && Bleu==0 && Vert !=0 && Vert <= 255)
                Vert-=3;
                else if (Rouge < 255)
                    Rouge+=3;
                    else if(Bleu < 255)
                        Bleu+=3;
                        else if (Vert <255)
                            Vert+=3;
    Trame += Rouge;
    Trame += Vert;
    Trame += Bleu;

    socket.waitForReadyRead(1000);
    BaReception.append(socket.bytesAvailable());
    if (BaReception.left(1)=="c")
        socket.write(Trame);
}*/
