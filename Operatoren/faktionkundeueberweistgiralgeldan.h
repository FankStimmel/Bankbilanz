#ifndef FAKTIONKUNDEUEBERWEISTGIRALGELDAN_H
#define FAKTIONKUNDEUEBERWEISTGIRALGELDAN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionKundeUeberweistGiralgeldAn : public FFinanzTransaktion

{

public:

    FAktionKundeUeberweistGiralgeldAn();
    FAktionKundeUeberweistGiralgeldAn(float BETRAG,
                                  int VONBANKNR, int NACHBANKNR,
                                  int VONBANKKUNDENNR, int NACHBANKKUNDENNR);

    void Execute_on(FAlleDaten *AlleDaten);
    void DickenRahmen_zeichnen(FAlleDaten *AlleDaten, bool wert);



private:

    // Daten
    float Betrag;
    int VonBankNr;
    int NachBankNr;
    int VonBankKundenNr;
    int NachBankKundenNr;



};

#endif
