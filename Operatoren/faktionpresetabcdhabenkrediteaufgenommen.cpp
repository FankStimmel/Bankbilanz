#include "faktionpresetabcdhabenkrediteaufgenommen.h"


FAktionPresetABCDhabenKrediteAufgenommen::FAktionPresetABCDhabenKrediteAufgenommen(){

    }

FAktionPresetABCDhabenKrediteAufgenommen::~FAktionPresetABCDhabenKrediteAufgenommen(){
    }


void FAktionPresetABCDhabenKrediteAufgenommen::Execute_on(FAlleDaten *AlleDaten){

    // Operation bei der Geschäftsbank ausführen.
    AlleDaten->Set_alle_Daten_to_Preset_ABCD_haben_Kredite_aufgenommen();

    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();

    // Beschreibung
    BeschreibungDerOperation = ") Die Kunden A, B, C und D und die Banken haben Kredite aufgenommen.";
    }
