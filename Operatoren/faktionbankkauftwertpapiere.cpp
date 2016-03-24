#include "faktionbankkauftwertpapiere.h"


FAktionBankKauftWertpapiere::FAktionBankKauftWertpapiere(){
    }



FAktionBankKauftWertpapiere::FAktionBankKauftWertpapiere(FGeld BETRAG, int BANKNR, int BANKKUNDENNR){
    Betrag       = BETRAG;
    BankNr       = BANKNR;
    BankKundenNr = BANKKUNDENNR;
    }



void FAktionBankKauftWertpapiere::Execute_on(FAlleDaten *AlleDaten){

    // Operation auf Geschäftsbanken ausführen.
    AlleDaten->Banken[BankNr].Wertpapiere              += Betrag;
    AlleDaten->Banken[BankNr].GiroKonten[BankKundenNr] += Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung
    BeschreibungDerOperation = ") Die Bank hat Wertpapiere gekauft.";
    }
