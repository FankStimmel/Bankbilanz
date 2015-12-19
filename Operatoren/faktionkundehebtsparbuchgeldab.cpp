#include "faktionkundehebtsparbuchgeldab.h"


FAktionKundeHebtSparbuchgeldAb::FAktionKundeHebtSparbuchgeldAb(){
    }


FAktionKundeHebtSparbuchgeldAb::FAktionKundeHebtSparbuchgeldAb(float BETRAG, int BANKNR, int BANKKUNDENNR){
    Betrag       = BETRAG;
    BankKundenNr = BANKKUNDENNR;
    BankNr       = BANKNR;
    }


void FAktionKundeHebtSparbuchgeldAb::Execute_on(FAlleDaten *AlleDaten){

    // Operation bei der Geschäftsbank ausführen.
    AlleDaten->Banken[BankNr].GiroKonten[BankKundenNr]     += Betrag;
    AlleDaten->Banken[BankNr].SparbuchKonten[BankKundenNr] -= Betrag;

    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung
    QString KundenName  = AlleDaten->Kunden[2*BankNr+BankKundenNr].PersonenName;
    BeschreibungDerOperation = ") Die " + KundenName  + " hat  "
                               + QString::number(Betrag) + "  Euro von seinem Sparbuch abgehoben.";

    }
