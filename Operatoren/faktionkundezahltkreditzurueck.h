#ifndef FAKTIONKUNDEZAHLTKREDITZURUECK_H
#define FAKTIONKUNDEZAHLTKREDITZURUECK_H

#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionKundeZahltKreditZurueck : public FFinanzTransaktion

{

public:

    FAktionKundeZahltKreditZurueck();
    FAktionKundeZahltKreditZurueck(float BETRAG, int BANKNR, int BANKKUNDENNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int BankKundenNr;
    int BankNr;

};

#endif
