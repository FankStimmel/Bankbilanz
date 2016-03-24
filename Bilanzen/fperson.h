#ifndef FPERSON_H
#define FPERSON_H

#include "fgeld.h"
#include <QtGui>


class FPerson

{

public:

    // Konstruktor
    FPerson();
    FPerson(QString Buchstabe);


    // Daten
    QString PersonenName;
    QString PersonenBuchstabe;
    FGeld Bargeld;

    bool DickerRahmenBarGeld;


    // Methoden
    void Reset_Personenbilanz_to_Null();
    void Reset_alle_Rahmenstaerken_to_Duenn();
    QString Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung();


};

#endif // FPERSON_H
