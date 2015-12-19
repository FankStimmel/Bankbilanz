#ifndef FAKTIONBANKZAHLTKREDITBEIDERZBANKZURUECK_H
#define FAKTIONBANKZAHLTKREDITBEIDERZBANKZURUECK_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankZahltKreditBeiDerZBankZurueck : public FFinanzTransaktion

{

public:

    FAktionBankZahltKreditBeiDerZBankZurueck();
    FAktionBankZahltKreditBeiDerZBankZurueck(float BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int BankNr;

};


#endif
