#include "faktionbankzahltkreditananderebankzurueck.h"

FAktionBankZahltKreditAnAndereBankZurueck::FAktionBankZahltKreditAnAndereBankZurueck(){
    }


FAktionBankZahltKreditAnAndereBankZurueck::FAktionBankZahltKreditAnAndereBankZurueck(int vonBankNR,
                                                                                     int nachBankNR,
                                                                                     double BETRAG){
    vonBankNr  = vonBankNR;
    nachBankNr = nachBankNR;
    Betrag     = BETRAG;
    }


FAktionBankZahltKreditAnAndereBankZurueck::~FAktionBankZahltKreditAnAndereBankZurueck(){
    }


void FAktionBankZahltKreditAnAndereBankZurueck::Execute_on(FAlleDaten *AlleDaten){

    AlleDaten->Banken[vonBankNr].VerbindGegenAndereBank  -= Betrag;
    AlleDaten->Banken[vonBankNr].ZentralbankGeldguthaben -= Betrag;

    AlleDaten->Banken[nachBankNr].KreditBeiAndererBank    -= Betrag;
    AlleDaten->Banken[nachBankNr].ZentralbankGeldguthaben += Betrag;

    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation =   ") Es wurd der Kredit zurückbezahlt.";
    }
