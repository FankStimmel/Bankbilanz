#ifndef FAKTIONKUNDEZAHLTBARGELDEIN_H
#define FAKTIONKUNDEZAHLTBARGELDEIN_H

#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionKundeZahltBargeldEin : public FFinanzTransaktion

{

public:

    FAktionKundeZahltBargeldEin();
    FAktionKundeZahltBargeldEin(FGeld BETRAG, int BANKNR, int PERSONENNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    FGeld Betrag;
    int PersonenNr;
    int BankNr;


};

#endif
