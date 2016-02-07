#include "faktionkundezahltkreditzurueck.h"


FAktionKundeZahltKreditZurueck::FAktionKundeZahltKreditZurueck(){
    }


FAktionKundeZahltKreditZurueck::FAktionKundeZahltKreditZurueck(float BETRAG, int BANKNR, int BANKKUNDENNR){
    Betrag       = BETRAG;
    BankKundenNr = BANKKUNDENNR;
    BankNr       = BANKNR;


    }


void FAktionKundeZahltKreditZurueck::Execute_on(FAlleDaten *AlleDaten){

    // Operation bei der Geschäftsbank ausführen.
    AlleDaten->Banken[BankNr].GiroKonten[BankKundenNr]       -= Betrag;
    AlleDaten->Banken[BankNr].KrediteVonKunden[BankKundenNr] -= Betrag;

    // Operation bei dem Kunden ausführen.
    int PersonenNummer = 2*BankNr + BankKundenNr;
    AlleDaten->Kunden[PersonenNummer].Schulden -= Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    QString KundenName = AlleDaten->Kunden[2*BankNr+BankKundenNr].PersonenName;
    BeschreibungDerOperation =   " ) Die "  + KundenName
                               + "  hat  " + QString::number(Betrag)
                               + "  Euro Kredit zurückgezahlt.";
    }








