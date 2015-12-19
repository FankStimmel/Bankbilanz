#ifndef FAKTIONBANKVERKAUFTSTAATSANLEIHEANZBANK_H
#define FAKTIONBANKVERKAUFTSTAATSANLEIHEANZBANK_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankVerkauftStaatsanleiheAnZBank  : public FFinanzTransaktion

{

public:

    FAktionBankVerkauftStaatsanleiheAnZBank();
    FAktionBankVerkauftStaatsanleiheAnZBank(float BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int BankNr;



};

#endif
