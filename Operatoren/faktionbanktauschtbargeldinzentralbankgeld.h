#ifndef FAKTIONBANKTAUECHTBARGELDINZENTRALBANKGELD_H
#define FAKTIONBANKTAUECHTBARGELDINZENTRALBANKGELD_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankTauschtBargeldInZentralbankgeld : public FFinanzTransaktion

{

public:
    FAktionBankTauschtBargeldInZentralbankgeld();
    FAktionBankTauschtBargeldInZentralbankgeld(FGeld BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    FGeld Betrag;
    int BankNr;



};

#endif
