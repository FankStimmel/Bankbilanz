#ifndef FAKTIONBANKTAUECHTBARGELDINZENTRALBANKGELD_H
#define FAKTIONBANKTAUECHTBARGELDINZENTRALBANKGELD_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankTauschtBargeldInZentralbankgeld : public FFinanzTransaktion

{

public:
    FAktionBankTauschtBargeldInZentralbankgeld();
    FAktionBankTauschtBargeldInZentralbankgeld(double BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    double Betrag;
    int BankNr;



};

#endif
