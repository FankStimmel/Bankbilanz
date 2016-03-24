#include "faktionkundehebtbargeldab.h"


FAktionKundeHebtBargeldAb::FAktionKundeHebtBargeldAb(){
    }



FAktionKundeHebtBargeldAb::FAktionKundeHebtBargeldAb(FGeld BETRAG, int BANKNR, int PERSONENNR){
    Betrag     = BETRAG;
    PersonenNr = PERSONENNR;
    BankNr     = BANKNR;
    }


void FAktionKundeHebtBargeldAb::Execute_on(FAlleDaten *AlleDaten){

    // Operation
    int BankKundenNummer;
    if(PersonenNr == 0) BankKundenNummer = 0;
    if(PersonenNr == 1) BankKundenNummer = 1;
    if(PersonenNr == 2) BankKundenNummer = 0;
    if(PersonenNr == 3) BankKundenNummer = 1;

    // in den Geschäftsbankbilanzen
    AlleDaten->Banken[BankNr].BarGeldDerBank               -= Betrag;
    AlleDaten->Banken[BankNr].GiroKonten[BankKundenNummer] -= Betrag;

    // bei den Kunden
    AlleDaten->Kunden[PersonenNr].Bargeld += Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung
    QString KundenName  = AlleDaten->Kunden[PersonenNr].PersonenName;
    BeschreibungDerOperation = ") Der " + KundenName  + " hat  "
                               + Betrag.Get_Euro_as_QString() + "  Euro Bargeld abgehoben.";
    }
