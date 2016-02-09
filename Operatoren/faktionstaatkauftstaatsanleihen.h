#ifndef FAKTIONSTAATKAUFTSTAATSANLEIHEN_H
#define FAKTIONSTAATKAUFTSTAATSANLEIHEN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionStaatKauftStaatsanleihen : public FFinanzTransaktion

{

public:

    FAktionStaatKauftStaatsanleihen();
    FAktionStaatKauftStaatsanleihen(double BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    double Betrag;
    int BankNr;




};

#endif
