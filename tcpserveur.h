#ifndef TCPSERVEUR_H
#define TCPSERVEUR_H

#include <QTcpServer>

class tcpserveur : public QTcpServer
{
    Q_OBJECT
public:
    explicit tcpserveur(QObject *parent = 0);
    
signals:
    
public slots:
    void incomingConnection(int socketDescriptor);
    
};

#endif // TCPSERVEUR_H
