#ifndef FAKTIONSTAATKAUFTSTAATSANLEIHEN_H
#define FAKTIONSTAATKAUFTSTAATSANLEIHEN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionStaatKauftStaatsanleihen : public FFinanzTransaktion

{

public:

    FAktionStaatKauftStaatsanleihen();
    FAktionStaatKauftStaatsanleihen(float BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int BankNr;




};

#endif
