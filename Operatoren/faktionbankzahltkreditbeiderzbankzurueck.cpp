#include "faktionbankzahltkreditbeiderzbankzurueck.h"


FAktionBankZahltKreditBeiDerZBankZurueck::FAktionBankZahltKreditBeiDerZBankZurueck(){
    }


FAktionBankZahltKreditBeiDerZBankZurueck::FAktionBankZahltKreditBeiDerZBankZurueck(float BETRAG, int BANKNR){
    Betrag       = BETRAG;
    BankNr       = BANKNR;
    }


void FAktionBankZahltKreditBeiDerZBankZurueck::Execute_on(FAlleDaten *AlleDaten){

    // in den Geschäftsbankbilanzen
    AlleDaten->Banken[BankNr].ZentralbankGeldguthaben -= Betrag;
    AlleDaten->Banken[BankNr].VerbindGegenZentralbank -= Betrag;

    // in der Zentralbankbilanz
    AlleDaten->Zentralbank.ForderungAnBanken[BankNr]      -= Betrag;
    AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[BankNr] -= Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation =   ") Die " + AlleDaten->Banken[BankNr].NameDerBank + "  hat  "
                               + QString::number(Betrag)
                               + "  Euro Kredit bei der Z-Bank zurückgezahlt.";
    }
