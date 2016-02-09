#ifndef FAKTIONBANKVERKAUFTSTAATSANLEIHEANZBANK_H
#define FAKTIONBANKVERKAUFTSTAATSANLEIHEANZBANK_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankVerkauftStaatsanleiheAnZBank  : public FFinanzTransaktion

{

public:

    FAktionBankVerkauftStaatsanleiheAnZBank();
    FAktionBankVerkauftStaatsanleiheAnZBank(double BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    double Betrag;
    int BankNr;



};

#endif
