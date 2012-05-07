#include "tcpserveur.h"
#include "threadserveur.h"

tcpserveur::tcpserveur(QObject *parent) :
    QTcpServer(parent)
{
}
void tcpserveur::incomingConnection(int socketDescriptor)
{
    ThreadServeur *thServeur= new ThreadServeur(0, socketDescriptor);
    thServeur->start();

}
