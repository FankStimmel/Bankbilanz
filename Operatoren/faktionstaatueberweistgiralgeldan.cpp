#include "faktionstaatueberweistgiralgeldan.h"


FAktionStaatUeberweistGiralgeldAn::FAktionStaatUeberweistGiralgeldAn(){
    }


FAktionStaatUeberweistGiralgeldAn::FAktionStaatUeberweistGiralgeldAn(float BETRAG, int NACHBANKNR, int NACHBANKKUNDENNR){
    Betrag           = BETRAG;
    NachBankNr       = NACHBANKNR;
    NachBankKundenNr = NACHBANKKUNDENNR;
    }


void FAktionStaatUeberweistGiralgeldAn::Execute_on(FAlleDaten *AlleDaten){

    // Der Fall, dass Giralgeld innerhalb einer Bank überwiesen wird.
    if(NachBankNr == 0){
        AlleDaten->Banken[0].GiroKonten[NachBankKundenNr] += Betrag;
        AlleDaten->Banken[0].StaatsGiroKonto              -= Betrag;
        }


    // Der Fall, dass Giralgeld auf eine fremde Bank überwiesen wird.
    if(NachBankNr == 1){

        // in Zentralbank.
        AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[0] -= Betrag;
        AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[1] += Betrag;

        // von Bank.
        AlleDaten->Banken[0].StaatsGiroKonto         -= Betrag;
        AlleDaten->Banken[0].ZentralbankGeldguthaben -= Betrag;

        // nach Bank.
        AlleDaten->Banken[1].GiroKonten[NachBankKundenNr] += Betrag;
        AlleDaten->Banken[1].ZentralbankGeldguthaben      += Betrag;
        }


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Kunde  hat  " + QString::number(Betrag) + "  Euro Giralgeld überwiesen.";
    }
