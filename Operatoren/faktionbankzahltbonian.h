#ifndef FAKTIONBANKZAHLTBONIAN_H
#define FAKTIONBANKZAHLTBONIAN_H

#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankZahltBoniAn : public FFinanzTransaktion

{

public:

    FAktionBankZahltBoniAn();
    FAktionBankZahltBoniAn(double BETRAG, int BANKNR, int KUNDENNR);
    ~FAktionBankZahltBoniAn();

    void Execute_on(FAlleDaten *AlleDaten);


private:
    double Betrag;
    int KundenNr;
    int BankNr;


};

#endif // FAKTIONBANKZAHLTBONIAN_H
