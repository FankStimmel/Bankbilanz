#ifndef FAKTIONBANKLEGTEIGENKAPITALEIN_H
#define FAKTIONBANKLEGTEIGENKAPITALEIN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankLegtEigenkapitalEin : public FFinanzTransaktion

{

public:

    FAktionBankLegtEigenkapitalEin();
    FAktionBankLegtEigenkapitalEin(float BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int BankNr;




};

#endif
