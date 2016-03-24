#ifndef FAKTIONBANKVERKAUFTSTAATSANLEIHEANZBANK_H
#define FAKTIONBANKVERKAUFTSTAATSANLEIHEANZBANK_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankVerkauftStaatsanleiheAnZBank  : public FFinanzTransaktion

{

public:

    FAktionBankVerkauftStaatsanleiheAnZBank();
    FAktionBankVerkauftStaatsanleiheAnZBank(FGeld BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    FGeld Betrag;
    int BankNr;



};

#endif
