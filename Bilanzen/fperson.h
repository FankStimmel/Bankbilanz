#ifndef FPERSON_H
#define FPERSON_H


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
    double Bargeld;
    double Schulden;

    // Methoden
    void Reset_Personenbilanz_to_Null();
    QString Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung();


};

#endif // FPERSON_H
