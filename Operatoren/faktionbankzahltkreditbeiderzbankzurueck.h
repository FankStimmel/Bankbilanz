#ifndef FAKTIONBANKZAHLTKREDITBEIDERZBANKZURUECK_H
#define FAKTIONBANKZAHLTKREDITBEIDERZBANKZURUECK_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankZahltKreditBeiDerZBankZurueck : public FFinanzTransaktion

{

public:

    FAktionBankZahltKreditBeiDerZBankZurueck();
    FAktionBankZahltKreditBeiDerZBankZurueck(FGeld BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    FGeld Betrag;
    int BankNr;

};


#endif
