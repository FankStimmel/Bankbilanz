#include "faktionstaatkauftstaatsanleihen.h"


FAktionStaatKauftStaatsanleihen::FAktionStaatKauftStaatsanleihen(){
    }


FAktionStaatKauftStaatsanleihen::FAktionStaatKauftStaatsanleihen(FGeld BETRAG, int BANKNR){
    Betrag = BETRAG;
    BankNr = BANKNR;
    }


void FAktionStaatKauftStaatsanleihen::Execute_on(FAlleDaten *AlleDaten){

    // in den Geschäftsbankbilanzen
    AlleDaten->Banken[BankNr].Staatsanleihen  -= Betrag;
    AlleDaten->Banken[BankNr].StaatsGiroKonto -= Betrag;

    // in der Staatsbilanz
    AlleDaten->Staat.SchuldenAnBanken[BankNr] -= Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation =   ") Der Staat hat  " + Betrag.Get_Euro_as_QString()
                               + "  Staatsanleihen gekauft.";
    }
