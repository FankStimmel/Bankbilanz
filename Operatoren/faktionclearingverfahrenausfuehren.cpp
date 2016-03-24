#include "faktionclearingverfahrenausfuehren.h"


FAktionClearingVerfahrenAusfuehren::FAktionClearingVerfahrenAusfuehren(){
    }


FAktionClearingVerfahrenAusfuehren::FAktionClearingVerfahrenAusfuehren(FGeld ATOC, FGeld ATOD,
                                                                       FGeld BTOC, FGeld BTOD,
                                                                       FGeld CTOA, FGeld CTOB,
                                                                       FGeld DTOA, FGeld DTOB){
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

    // Differenzzahlung
    FGeld NachBankY = AToC + AToD + BToC + BToD;
    FGeld NachBankX = CToA + CToB + DToA + DToB;


    // Wenn mehr von Bank X nach Bank Y überwiesen wird
    if(NachBankY > NachBankX){
        FGeld Delta = NachBankY - NachBankX;
        AlleDaten->Banken[1].KreditBeiAndererBank   += Delta;
        AlleDaten->Banken[0].VerbindGegenAndereBank += Delta;
        }

    // Wenn mehr von Bank Y nach Bank X überwiesen wird
    else{
        FGeld Delta = NachBankX - NachBankY;
        AlleDaten->Banken[0].KreditBeiAndererBank   += Delta;
        AlleDaten->Banken[1].VerbindGegenAndereBank += Delta;
        }



    // Eventuell in der Bankbilanz VerbindlichkeitGegenAndereBank gegen KreditBeiAndererBank kürzen.
    for(int i=0; i<2; i++){

        FGeld Kre = AlleDaten->Banken[i].KreditBeiAndererBank;
        FGeld Ver = AlleDaten->Banken[i].VerbindGegenAndereBank;

        // Minimum rauskürzen
        FGeld Minimum("",std::min(Kre.Get_Euro(),Ver.Get_Euro()));
        if(Minimum.Get_Cents() > 0){
            AlleDaten->Banken[i].KreditBeiAndererBank   -= Minimum;
            AlleDaten->Banken[i].VerbindGegenAndereBank -= Minimum;
            }
        }


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Das Clearingverfahren wurde durchgeführt.";
    }


//#######################################################################################################################


void FAktionClearingVerfahrenAusfuehren::Set_Dicke_Rahmen(FAlleDaten *AlleDaten, bool wert){
    for(int BankNr=0; BankNr<2; BankNr++){
        AlleDaten->Banken[BankNr].DickerRahmenVerbindGegenAndereBank = wert;
        AlleDaten->Banken[BankNr].DickerRahmenKreditBeiAndererBank   = wert;
        for(int KundenNr=0; KundenNr<2; KundenNr++){
            AlleDaten->Banken[BankNr].DickerRahmenGiroKonten[KundenNr] = wert;
            }
        }
    }





