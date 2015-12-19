#ifndef FAKTIONKUNDEHEBTSPARBUCHGELDAB_H
#define FAKTIONKUNDEHEBTSPARBUCHGELDAB_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionKundeHebtSparbuchgeldAb : public FFinanzTransaktion

{

public:

    FAktionKundeHebtSparbuchgeldAb();
    FAktionKundeHebtSparbuchgeldAb(float BETRAG, int BANKNR, int BANKKUNDENNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int BankKundenNr;
    int BankNr;




};

#endif // FAKTIONKUNDEHEBTSPARBUCHGELDAB_H
