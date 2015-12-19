#ifndef FAKTIONSTAATVERKAUFTSTAATSANLEIHEN_H
#define FAKTIONSTAATVERKAUFTSTAATSANLEIHEN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionStaatVerkauftStaatsanleihen : public FFinanzTransaktion

{

public:

    FAktionStaatVerkauftStaatsanleihen();
    FAktionStaatVerkauftStaatsanleihen(float BETRAG, int BANKNR);

    void Execute_on(FAlleDaten *AlleDaten);



private:

    // Daten
    float Betrag;
    int BankNr;





};

#endif
