#ifndef FAKTIONSTAATVERKAUFTSTAATSANLEIHEN_H
#define FAKTIONSTAATVERKAUFTSTAATSANLEIHEN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionStaatVerkauftStaatsanleihen : public FFinanzTransaktion

{

public:

    FAktionStaatVerkauftStaatsanleihen();
    FAktionStaatVerkauftStaatsanleihen(double BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    double Betrag;
    int BankNr;





};

#endif
