#ifndef FAKTIONSTAATUEBERWEISTGIRALGELDAN_H
#define FAKTIONSTAATUEBERWEISTGIRALGELDAN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionStaatUeberweistGiralgeldAn : public FFinanzTransaktion

{

public:

    FAktionStaatUeberweistGiralgeldAn();
    FAktionStaatUeberweistGiralgeldAn(float BETRAG, int NACHBANKNR, int NACHBANKKUNDENNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int NachBankNr;
    int NachBankKundenNr;

};

#endif
