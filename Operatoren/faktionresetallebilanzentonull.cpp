#include "faktionresetallebilanzentonull.h"


FAktionResetAlleBilanzenToNull::FAktionResetAlleBilanzenToNull(){

    }



void FAktionResetAlleBilanzenToNull::Execute_on(FAlleDaten *AlleDaten){

    AlleDaten->Reset_alle_Daten_to_Null();

    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Alle Bilanzen wurden auf null gesetzt.";
    }
