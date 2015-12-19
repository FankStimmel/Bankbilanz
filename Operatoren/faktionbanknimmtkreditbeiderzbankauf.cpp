#include "faktionbanknimmtkreditbeiderzbankauf.h"


FAktionBankNimmtKreditBeiDerZBankAuf::FAktionBankNimmtKreditBeiDerZBankAuf(){
    }


FAktionBankNimmtKreditBeiDerZBankAuf::FAktionBankNimmtKreditBeiDerZBankAuf(float BETRAG, int BANKNR){
    Betrag       = BETRAG;
    BankNr       = BANKNR;

    }


void FAktionBankNimmtKreditBeiDerZBankAuf::Execute_on(FAlleDaten *AlleDaten){

    // // Operation auf Geschäftsbanken ausführen.
    AlleDaten->Banken[BankNr].ZentralbankGeldguthaben     += Betrag;
    AlleDaten->Banken[BankNr].VerbindGegenZentralbank     += Betrag;

    // // Operation auf Z-Banken ausführen.
    AlleDaten->Zentralbank.ForderungAnBanken[BankNr]      += Betrag;
    AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[BankNr] += Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation =   ") Die "  + AlleDaten->Banken[BankNr].NameDerBank
                               + "  hat  " + QString::number(Betrag)
                               + "  Euro Kredit bei der Z-Bank aufgenommen.";
    }
