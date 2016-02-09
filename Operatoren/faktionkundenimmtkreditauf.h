#ifndef FAKTIONKUNDENIMMTKREDITAUF_H
#define FAKTIONKUNDENIMMTKREDITAUF_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"

class FAktionKundeNimmtKreditAuf : public FFinanzTransaktion

{

public:

    FAktionKundeNimmtKreditAuf();
    FAktionKundeNimmtKreditAuf(double BETRAG, int BANKNR, int BANKKUNDENNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    double Betrag;
    int BankKundenNr;
    int BankNr;

};

#endif
