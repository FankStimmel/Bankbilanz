#include "faktionkundenimmtkreditauf.h"


FAktionKundeNimmtKreditAuf::FAktionKundeNimmtKreditAuf(){
    }


FAktionKundeNimmtKreditAuf::FAktionKundeNimmtKreditAuf(FGeld BETRAG, int BANKNR, int BANKKUNDENNR){
    Betrag       = BETRAG;
    BankKundenNr = BANKKUNDENNR;
    BankNr       = BANKNR;
    }


void FAktionKundeNimmtKreditAuf::Execute_on(FAlleDaten *AlleDaten){

    // Operation in der Geschäftsbankbilanz ausführen.
    AlleDaten->Banken[BankNr].GiroKonten[BankKundenNr]       += Betrag;
    AlleDaten->Banken[BankNr].KrediteVonKunden[BankKundenNr] += Betrag;



    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    QString KundenName = AlleDaten->Kunden[2*BankNr+BankKundenNr].PersonenName;
    BeschreibungDerOperation =   ") Die "  + KundenName
                               + "  hat  " + Betrag.Get_Euro_as_QString()
                               + "  Euro Kredit aufgenommen.";
    }
