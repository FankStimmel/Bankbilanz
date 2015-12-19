#ifndef FAKTIONBANKKAUFTWERTPAPIERE_H
#define FAKTIONBANKKAUFTWERTPAPIERE_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankKauftWertpapiere : public FFinanzTransaktion

{

public:

    FAktionBankKauftWertpapiere();
    FAktionBankKauftWertpapiere(float BETRAG, int BANKNR, int BANKKUNDENNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int BankNr;
    int BankKundenNr;




};

#endif
