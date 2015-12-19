#ifndef FFINANZTRANSAKTION_H
#define FFINANZTRANSAKTION_H

#include <QString>
#include <QDebug>
#include "Bilanzen/fallebilanzen.h"

class FFinanzTransaktion

{

public:

    // Konstruktor
    FFinanzTransaktion();
    virtual ~FFinanzTransaktion();

    // Daten
    QString BeschreibungDerOperation;
    QString Fehlerbeschreibung;


    // Methode
    virtual void Execute_on(FAlleDaten *AlleDaten);


};

#endif // FFINANZTRANSAKTION_H
