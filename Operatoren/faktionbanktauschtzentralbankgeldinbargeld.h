#ifndef FAKTIONBANKTAUSCHTZENTRALBANKGELDINBARGELD_H
#define FAKTIONBANKTAUSCHTZENTRALBANKGELDINBARGELD_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankTauschtZentralbankgeldInBargeld : public FFinanzTransaktion

{

public:

    FAktionBankTauschtZentralbankgeldInBargeld();
    FAktionBankTauschtZentralbankgeldInBargeld(double BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    double Betrag;
    int BankNr;


};

#endif
