#ifndef FAKTIONCLEARINGVERFAHRENAUSFUEHREN_H
#define FAKTIONCLEARINGVERFAHRENAUSFUEHREN_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionClearingVerfahrenAusfuehren : public FFinanzTransaktion

{

public:
    FAktionClearingVerfahrenAusfuehren();
    FAktionClearingVerfahrenAusfuehren(double ATOC, double ATOD,
                                       double BTOC, double BTOD,
                                       double CTOA, double CTOB,
                                       double DTOA, double DTOB);

    void Execute_on(FAlleDaten *AlleDaten);
    void Set_Dicke_Rahmen(FAlleDaten *AlleDaten, bool wert);



private:

    // Daten
    double AToC,AToD,BToC,BToD,CToA,CToB,DToA,DToB;


};

#endif // FAKTIONCLEARINGVERFAHRENAUSFUEHREN_H
