#include "fperson.h"


FPerson::FPerson(){
    }


FPerson::FPerson(QString Buchstabe){
    PersonenName      = "Person " + Buchstabe;
    PersonenBuchstabe = Buchstabe;
    Bargeld           = FGeld("",0.0);

    // Rahmenstärke Aktivseite
    DickerRahmenBarGeld  = false;
    }


//#########################################################################################################################


void FPerson::Reset_Personenbilanz_to_Null(){
    Bargeld  = FGeld("",0.0);
    }


//#########################################################################################################################


void FPerson::Reset_alle_Rahmenstaerken_to_Duenn(){
    DickerRahmenBarGeld  = false;
    }


//#########################################################################################################################


QString FPerson::Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung(){

    if(Bargeld.Get_Cents() < 0 ){
        return("In der Bilanz der " + PersonenName + ": \n\n"
               + PersonenName + " hat nicht genug Bargeld.");
        }

    return("");
    }
