#ifndef FAKTIONCLEARINGVERFAHRENAUSFUEHREN_H
#define FAKTIONCLEARINGVERFAHRENAUSFUEHREN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionClearingVerfahrenAusfuehren : public FFinanzTransaktion

{

public:
    FAktionClearingVerfahrenAusfuehren();
    FAktionClearingVerfahrenAusfuehren(FGeld ATOC, FGeld ATOD,
                                       FGeld BTOC, FGeld BTOD,
                                       FGeld CTOA, FGeld CTOB,
                                       FGeld DTOA, FGeld DTOB);

    void Execute_on(FAlleDaten *AlleDaten);
    void Set_Dicke_Rahmen(FAlleDaten *AlleDaten, bool wert);



private:

    // Daten
    FGeld AToC,AToD,BToC,BToD,CToA,CToB,DToA,DToB;


};

#endif // FAKTIONCLEARINGVERFAHRENAUSFUEHREN_H
