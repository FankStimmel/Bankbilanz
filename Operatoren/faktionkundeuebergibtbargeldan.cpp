#include "faktionkundeuebergibtbargeldan.h"


FAktionKundeUebergibtBargeldAn::FAktionKundeUebergibtBargeldAn(){
    }


FAktionKundeUebergibtBargeldAn::FAktionKundeUebergibtBargeldAn(float BETRAG, int VonPersonenNR, int NachPersonenNR){
    Betrag         = BETRAG;
    VonPersonenNr  = VonPersonenNR;
    NachPersonenNr = NachPersonenNR;
    }


void FAktionKundeUebergibtBargeldAn::Execute_on(FAlleDaten *AlleDaten){

    // Operation
    AlleDaten->Kunden[VonPersonenNr].Bargeld  -= Betrag;
    AlleDaten->Kunden[NachPersonenNr].Bargeld += Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();

    if( VonPersonenNr == NachPersonenNr ){
        Fehlerbeschreibung = "Eine Überweisung an sich selbst gibt es nicht.";
        }



    // Beschreibung
    BeschreibungDerOperation = ") Bargeld wurde übergeben.";
    }




