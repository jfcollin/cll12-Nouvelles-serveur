#-------------------------------------------------
#
# Project created by QtCreator 2012-04-30T14:18:43
#
#-------------------------------------------------

QT       += core gui network webkit xml

TARGET = Nouvelles-serveur
TEMPLATE = app


SOURCES += main.cpp\
        nouvellesserveur.cpp \
    tcpserveur.cpp \
    threadserveur.cpp

HEADERS  += nouvellesserveur.h \
    tcpserveur.h \
    threadserveur.h

FORMS    += nouvellesserveur.ui
