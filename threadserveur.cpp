#include "threadserveur.h"
#include <QMessageBox>
#include "nouvellesserveur.h"


ThreadServeur::ThreadServeur(QObject *parent, int socketDescriptor) :
    QThread(parent)
{
    Adresse[0] = "http://rss.lapresse.ca/178.xml"; //Actualité
    Adresse[1] = "http://rss.lapresse.ca/241.xml"; //Environement
    Adresse[2] = "http://rss.lapresse.ca/242.xml"; //Voyage
    Adresse[3] = "http://rss.lapresse.ca/279.xml"; //Insolite
    Adresse[4] = "http://rss.lapresse.ca/229.xml"; //Sports
    Adresse[5] = "http://rss.lapresse.ca/940.xml"; //rima elkouri
    Adresse[6] = "http://rss.lapresse.ca/863.xml"; //Europe
    Adresse[7] = "http://rss.lapresse.ca/338.xml"; //Bruno Blanchet

    m_socketDescriptor = socketDescriptor;
    TimerHeure = new QTimer(this);
    connect(TimerHeure, SIGNAL(timeout()), this, SLOT(Gestion_TimerHeure()));

}
void ThreadServeur::run()
{
    QByteArray baReception;
    QString Lien;
    int i;
    socket.setSocketDescriptor(m_socketDescriptor);
    TimerHeure->start(1000);

    Rouge =0;
    Bleu =0;
    Vert= 0;

    //Envoie le lien rss
    do
    {
        socket.waitForReadyRead();
        baReception = socket.read(socket.bytesAvailable());
        i = baReception[0]-48;
        if (i>=0 && i <=7)
        {
            Lien = Adresse[i];
            Trame = "n";
            Trame += Lien;
            socket.write(Trame);
            socket.waitForReadyRead();
            baReception = socket.read(socket.bytesAvailable());
        }

        if (EnvoyerHeure)
        {
            socket.write(m_TrameHeure);
            EnvoyerHeure = false;
        }

    }
    while (1);


}
//Envoie de l'heure à chaque seconde
void ThreadServeur::Gestion_TimerHeure()
{

    QTime t_Heure = QTime::currentTime();
    QString Heure = "h" + t_Heure.toString("hh:mm:ss");
    QByteArray TrameHeure = "";

    for (int i(0); i < Heure.length(); ++i)
    {
        TrameHeure += Heure[i].toAscii();
    }


    char Couleur = 'c';
    //QByteArray TrameCouleur;


    if (Rouge <=255 && Rouge!=0 && Bleu ==255 && Vert == 255)
        Rouge -=5;
        else if (Rouge ==0 && Bleu!=0 && Bleu <=255 && Vert == 255)
            Bleu -=5;
            else if (Rouge ==0 && Bleu==0 && Vert !=0 && Vert <= 255)
                Vert-=5;
                else if (Rouge < 255)
                    Rouge+=5;
                    else if(Bleu < 255)
                        Bleu+=5;
                        else if (Vert <255)
                            Vert+=5;
    char c;
    TrameHeure +=Couleur;
    c = Rouge;
    TrameHeure += c;
    c = Vert;
    TrameHeure += c;
    c = Bleu;
    TrameHeure += c;
    m_TrameHeure = TrameHeure;
    EnvoyerHeure = true;

}
