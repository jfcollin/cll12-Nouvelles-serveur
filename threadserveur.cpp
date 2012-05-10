#include "threadserveur.h"
#include <QMessageBox>
#include "nouvellesserveur.h"


ThreadServeur::ThreadServeur(QObject *parent, int socketDescriptor) :
    QThread(parent)
{
    Adresse[0] = "http://www.lapresse.ca/rss/178.xml"; //Actualité
    Adresse[1] = "http://www.lapresse.ca/rss/241.xml"; //Environement
    Adresse[2] = "http://www.lapresse.ca/rss/242.xml"; //Voyage
    Adresse[3] = "http://www.lapresse.ca/rss/279.xml"; //Insolite
    Adresse[4] = "http://www.lapresse.ca/rss/229.xml"; //Sports
    Adresse[5] = "http://www.lapresse.ca/rss/940.xml"; //rima elkouri
    Adresse[6] = "http://www.lapresse.ca/rss/863.xml"; //Europe
    Adresse[7] = "http://www.lapresse.ca/rss/338.xml"; //Bruno Blanchet

    m_socketDescriptor = socketDescriptor;
    TimerHeure = new QTimer(this);
    connect(TimerHeure, SIGNAL(timeout()), this, SLOT(Gestion_TimerHeure()));

}
void ThreadServeur::run()
{
    QByteArray baReception;
    QByteArray Trame;
    QString Test;
    int i;
    socket.setSocketDescriptor(m_socketDescriptor);
    //Envoie du lien RSS désiré
    socket.waitForReadyRead();
    baReception = socket.read(socket.bytesAvailable());
    i = baReception.toInt();
    Test = Adresse[i];
    Trame = "n";
    Trame += Test;
    socket.write(Trame);

    TimerHeure->start(1000);

    Compteur=0;
    Rouge =0;
    Bleu =0;
    Vert= 0;

    do
    {
        socket.waitForReadyRead();
        baReception = socket.read(socket.bytesAvailable());
        i = baReception.toInt();
        Test = Adresse[i];
        Trame = "n";
        Trame += Test;
        socket.write(Trame);



    }
    while (1);


}
//Envoie de l'heure à chaque seconde
void ThreadServeur::Gestion_TimerHeure()
{

    QTime t_Heure = QTime::currentTime();
    QString Heure = "h" + t_Heure.toString("hh:mm:ss");
    QByteArray Trame;

    for (int i(0); i < Heure.length(); ++i)
    {
        Trame += Heure[i].toAscii();
    }


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
