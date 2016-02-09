#ifndef FAKTIONBANKLEGTEIGENKAPITALEIN_H
#define FAKTIONBANKLEGTEIGENKAPITALEIN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankLegtEigenkapitalEin : public FFinanzTransaktion

{

public:

    FAktionBankLegtEigenkapitalEin();
    FAktionBankLegtEigenkapitalEin(double BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    double Betrag;
    int BankNr;




};

#endif
