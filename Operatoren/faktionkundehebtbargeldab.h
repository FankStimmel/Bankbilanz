#ifndef FAKTIONKUNDEHEBTBARGELDAB_H
#define FAKTIONKUNDEHEBTBARGELDAB_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionKundeHebtBargeldAb : public FFinanzTransaktion

{

public:

    FAktionKundeHebtBargeldAb();
    FAktionKundeHebtBargeldAb(float BETRAG, int BANKNR, int PERSONENNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int PersonenNr;
    int BankNr;



};

#endif
