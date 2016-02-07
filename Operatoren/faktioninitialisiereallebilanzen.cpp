#include "faktioninitialisiereallebilanzen.h"


FAktionInitialisiereAlleBilanzen::FAktionInitialisiereAlleBilanzen(){

    }



void FAktionInitialisiereAlleBilanzen::Execute_on(FAlleDaten *AlleDaten){

    // Reset
    AlleDaten->Initialisiere_alle_Bilanzen();


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Alle Bilanzen wurden initialisiert.";
    }
