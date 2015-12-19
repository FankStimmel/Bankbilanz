#include "faktioninitialisiereallebilanzen.h"


FAktionInitialisiereAlleBilanzen::FAktionInitialisiereAlleBilanzen(){

    }



void FAktionInitialisiereAlleBilanzen::Execute_on(FAlleDaten *AlleDaten){

    // Reset
    AlleDaten->Reset_alle_Daten_to_Null();


    // Zentralbank
    AlleDaten->Zentralbank.ForderungAnBanken[2] = 1000;
    AlleDaten->Zentralbank.Bargeldumlauf        = 1000;


    // Geschäftsbanken
    for(int i=0; i<2; i++){
        AlleDaten->Banken[i].BarGeldDerBank = 500;
        AlleDaten->Banken[i].Eigenkapital   = 500;
        }

    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Alle Bilanzen wurden initialisiert.";
    }
