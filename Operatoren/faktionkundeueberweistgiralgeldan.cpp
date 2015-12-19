#include "faktionkundeueberweistgiralgeldan.h"


FAktionKundeUeberweistGiralgeldAn::FAktionKundeUeberweistGiralgeldAn(){
    }


FAktionKundeUeberweistGiralgeldAn::FAktionKundeUeberweistGiralgeldAn(float BETRAG,
                                                             int VONBANKNR, int NACHBANKNR,
                                                             int VONBANKKUNDENNR, int NACHBANKKUNDENNR){
    Betrag           = BETRAG;
    VonBankNr        = VONBANKNR;
    NachBankNr       = NACHBANKNR;
    VonBankKundenNr  = VONBANKKUNDENNR;
    NachBankKundenNr = NACHBANKKUNDENNR;
    }


void FAktionKundeUeberweistGiralgeldAn::Execute_on(FAlleDaten *AlleDaten){

    // Der Fall, dass Giralgeld innerhalb einer Bank überwiesen wird.
    if(VonBankNr == NachBankNr){

        // Wenn zum Kunden überwiesen wird.
        if(NachBankKundenNr < 2){
            AlleDaten->Banken[VonBankNr].GiroKonten[VonBankKundenNr]  -= Betrag;
            AlleDaten->Banken[VonBankNr].GiroKonten[NachBankKundenNr] += Betrag;
            }

        // Wenn zum Staat überwiesen wird.
        if(NachBankKundenNr == 2){
            AlleDaten->Banken[VonBankNr].GiroKonten[VonBankKundenNr]  -= Betrag;
            AlleDaten->Banken[VonBankNr].StaatsGiroKonto              += Betrag;
            }
        }


    // Der Fall, dass Giralgeld auf eine fremde Bank überwiesen wird.
    if(VonBankNr != NachBankNr){

        // in Zentralbank.
        AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[VonBankNr]   -= Betrag;
        AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[NachBankNr]  += Betrag;

        // von Bank.
        AlleDaten->Banken[VonBankNr].GiroKonten[VonBankKundenNr] -= Betrag;
        AlleDaten->Banken[VonBankNr].ZentralbankGeldguthaben     -= Betrag;

        // nach Bank.  Wenn zum Kunden überwiesen wird.
        if(NachBankKundenNr < 2){
            AlleDaten->Banken[NachBankNr].GiroKonten[NachBankKundenNr] += Betrag;
            AlleDaten->Banken[NachBankNr].ZentralbankGeldguthaben      += Betrag;
            }

        // nach Bank.  Wenn zum Staat überwiesen wird.
        if(NachBankKundenNr == 2){
            AlleDaten->Banken[NachBankNr].StaatsGiroKonto          += Betrag;
            AlleDaten->Banken[NachBankNr].ZentralbankGeldguthaben  += Betrag;
            }

        }


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


/*
    int VonPersonenNr  = 2 * VonBankNr  + VonBankKundenNr;
    int NachPersonenNr = 2 * NachBankNr + NachBankKundenNr;
    if( VonPersonenNr == NachPersonenNr ){
        Fehlerbeschreibung = "Eine Überweisung an sich selbst gibt es nicht.";
        }
*/

    // Beschreibung der Operation
    BeschreibungDerOperation = ") Kunde  hat  " + QString::number(Betrag) + "  Euro Giralgeld überwiesen.";
    }
