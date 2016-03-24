#ifndef FAKTIONBANKNIMMTKREDITBEIDERZBANKAUF_H
#define FAKTIONBANKNIMMTKREDITBEIDERZBANKAUF_H

#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"

class FAktionBankNimmtKreditBeiDerZBankAuf : public FFinanzTransaktion

{

public:

    FAktionBankNimmtKreditBeiDerZBankAuf();
    FAktionBankNimmtKreditBeiDerZBankAuf(FGeld BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    FGeld Betrag;
    int BankNr;

};

#endif
