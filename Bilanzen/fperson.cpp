#include "fperson.h"


FPerson::FPerson(){
    }


FPerson::FPerson(QString Buchstabe){
    PersonenName      = "Person " + Buchstabe;
    PersonenBuchstabe = Buchstabe;
    Bargeld           = 0.0;
    Schulden          = 0.0;
    }


//#########################################################################################################################


void FPerson::Reset_Personenbilanz_to_Null(){
    Bargeld  = 0.0;
    Schulden = 0.0;
    }


//#########################################################################################################################


QString FPerson::Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung(){

    if(Bargeld < 0 ){
        return("In der Bilanz der " + PersonenName + ": \n\n"
               "Das Bargeld von " + PersonenName + " darf nicht negativ sein.");
        }

    if(Schulden < 0 ){
        return("In der Bilanz der " + PersonenName + ": \n\n"
               "Die Schulden von " + PersonenName + " dürfen nicht negativ sein.");
        }

    return("");
    }
