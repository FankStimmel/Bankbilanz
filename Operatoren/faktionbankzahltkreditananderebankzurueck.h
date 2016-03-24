#ifndef FAKTIONBANKZAHLTKREDITANANDEREBANKZURUECK_H
#define FAKTIONBANKZAHLTKREDITANANDEREBANKZURUECK_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionBankZahltKreditAnAndereBankZurueck : public FFinanzTransaktion

{

public:

    FAktionBankZahltKreditAnAndereBankZurueck();
    FAktionBankZahltKreditAnAndereBankZurueck(int GlaubigerBankNR, int SchuldnerBankNR, FGeld BETRAG);
    ~FAktionBankZahltKreditAnAndereBankZurueck();

    void Execute_on(FAlleDaten *AlleDaten);

private:
    int vonBankNr;
    int nachBankNr;
    FGeld Betrag;

};

#endif // FAKTIONBANKZAHLTKREDITANANDEREBANKZURUECK_H
