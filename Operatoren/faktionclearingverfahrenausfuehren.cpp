#include "faktionclearingverfahrenausfuehren.h"


FAktionClearingVerfahrenAusfuehren::FAktionClearingVerfahrenAusfuehren(){
    }


FAktionClearingVerfahrenAusfuehren::FAktionClearingVerfahrenAusfuehren(double ATOC, double ATOD,
                                                                       double BTOC, double BTOD,
                                                                       double CTOA, double CTOB,
                                                                       double DTOA, double DTOB){
    AToC = ATOC;
    AToD = ATOD;
    BToC = BTOC;
    BToD = BTOD;
    CToA = CTOA;
    CToB = CTOB;
    DToA = DTOA;
    DToB = DTOB;
    }


//############################################################################################################


void FAktionClearingVerfahrenAusfuehren::Execute_on(FAlleDaten *AlleDaten){

    // Überweisung A -> C
    AlleDaten->Banken[1].GiroKonten[0] += AToC;
    AlleDaten->Banken[0].GiroKonten[0] -= AToC;

    // Überweisung A -> D
    AlleDaten->Banken[1].GiroKonten[1] += AToD;
    AlleDaten->Banken[0].GiroKonten[0] -= AToD;

    // Überweisung B -> C
    AlleDaten->Banken[1].GiroKonten[0] += BToC;
    AlleDaten->Banken[0].GiroKonten[1] -= BToC;

    // Überweisung B -> D
    AlleDaten->Banken[1].GiroKonten[1] += BToD;
    AlleDaten->Banken[0].GiroKonten[1] -= BToD;

    // Überweisung C -> A
    AlleDaten->Banken[0].GiroKonten[0] += CToA;
    AlleDaten->Banken[1].GiroKonten[0] -= CToA;

    // Überweisung C -> B
    AlleDaten->Banken[0].GiroKonten[1] += CToB;
    AlleDaten->Banken[1].GiroKonten[0] -= CToB;

    // Überweisung D -> A
    AlleDaten->Banken[0].GiroKonten[0] += DToA;
    AlleDaten->Banken[1].GiroKonten[1] -= DToA;

    // Überweisung D -> B
    AlleDaten->Banken[0].GiroKonten[1] += DToB;
    AlleDaten->Banken[1].GiroKonten[1] -= DToB;

    // Differenzzahlung Zentralbankgeld
    double Delta = (CToA + CToB + DToA + DToB) - (AToC + AToD + BToC + BToD);
    AlleDaten->Banken[0].ZentralbankGeldguthaben += Delta;
    AlleDaten->Banken[1].ZentralbankGeldguthaben -= Delta;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation =   ") Das Clearingverfahren wurde durchgeführt.";
    }
