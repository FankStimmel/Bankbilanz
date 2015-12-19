#include "faktionstaatverkauftstaatsanleihen.h"


FAktionStaatVerkauftStaatsanleihen::FAktionStaatVerkauftStaatsanleihen(){
    }


FAktionStaatVerkauftStaatsanleihen::FAktionStaatVerkauftStaatsanleihen(float BETRAG, int BANKNR){
    Betrag = BETRAG;
    BankNr = BANKNR;
    }


void FAktionStaatVerkauftStaatsanleihen::Execute_on(FAlleDaten *AlleDaten){

    // in den Geschäftsbankbilanzen
    AlleDaten->Banken[BankNr].Staatsanleihen  += Betrag;
    AlleDaten->Banken[BankNr].StaatsGiroKonto += Betrag;

    // in der Staatsbilanz
    AlleDaten->Staat.SchuldenAnBanken[BankNr] += Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation =   ") Der Staat hat  " + QString::number(Betrag)
                               + "  Staatsanleihen verkauft.";
    }
