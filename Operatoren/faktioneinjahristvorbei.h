#ifndef FAKTIONEINJAHRISTVORBEI_H
#define FAKTIONEINJAHRISTVORBEI_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionEinJahrIstVorbei : public FFinanzTransaktion

{

public:

    FAktionEinJahrIstVorbei();


    void Execute_on(FAlleDaten *AlleDaten);
    void Set_Dicke_Rahmen(FAlleDaten *AlleDaten, bool wert);


    // Daten
    QString Fehlerbeschreibung;


private:

    // Methoden
    QString Runden(double wert);
    double Runden_auf_Cent(double wert);




};

#endif
