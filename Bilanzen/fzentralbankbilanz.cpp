#include "fzentralbankbilanz.h"


FZentralbankBilanz::FZentralbankBilanz(){
    // allgemeine Daten
    NameDerBank = "Zentralbank";

    // Aktiva
    ForderungAnBanken << 0 << 0 << 0;
    Staatsanleihen << 0 << 0;

    // Passiva
    ZGeldGuthabenVonBanken << 0 << 0 << 0;
    Bargeldumlauf          = 0;
    Eigenkapital           = 0;

    // Rahmenstärke Aktivseite
    DickerRahmenForderungAnBanken << false << false << false;
    DickerRahmenStaatsanleihen    << false << false;

    // Rahmenstärke Passiv
    DickerRahmenZGeldGuthabenVonBanken << false << false << false;
    DickerRahmenBargeldumlauf          = false;
    DickerRahmenEigenkapital           = false;


    }


//####################################################################################################################################


void FZentralbankBilanz::Reset_Zentralbankbilanz_to_Null(){
    // Aktiva
    ForderungAnBanken[0] = 0;
    ForderungAnBanken[1] = 0;
    ForderungAnBanken[2] = 0;
    Staatsanleihen[0]    = 0;
    Staatsanleihen[1]    = 0;

    // Passiva
    ZGeldGuthabenVonBanken[0] = 0;
    ZGeldGuthabenVonBanken[1] = 0;
    ZGeldGuthabenVonBanken[2] = 0;
    Bargeldumlauf = 0;
    Eigenkapital  = 0;
    }


//####################################################################################################################################


QString FZentralbankBilanz::Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung(){

    // Aktiva
    if(ForderungAnBanken[0] < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Forderung gegen die Bank A darf nicht negativ sein.");
        }

    if(ForderungAnBanken[1] < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Forderung gegen die Bank B darf nicht negativ sein.");
        }

    if(ForderungAnBanken[2] < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Forderung gegen die Bank C darf nicht negativ sein.");
        }

    if(Staatsanleihen[0] < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Staatsanleihen von Bank A dürfen nicht negativ sein.");
        }

    if(Staatsanleihen[1] < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Staatsanleihen von Bank B dürfen nicht negativ sein.");
        }



    // Passiva
    if(ZGeldGuthabenVonBanken[0] < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Das Zentralbankgeldguthaben von Bank A darf nicht negativ sein.");
        }

    if(ZGeldGuthabenVonBanken[1] < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Das Zentralbankgeldguthaben von Bank B darf nicht negativ sein.");
        }

    if(ZGeldGuthabenVonBanken[2] < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Das Zentralbankgeldguthaben von Bank C darf nicht negativ sein.");
        }

    if(Bargeldumlauf < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Der Bargeldumlauf darf nicht negativ sein.");
        }

    if(Eigenkapital < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Das Eigenkapital der Zentralbank darf nicht negativ sein.");
        }


    // Sonst keine Fehler melden.
    return("");
    }


//####################################################################################################################################


bool FZentralbankBilanz::Ist_die_Aktivsumme_gleich_der_Passivsumme(){

    double AktivsummeSumme =   ForderungAnBanken[0]
                             + ForderungAnBanken[1]
                             + ForderungAnBanken[2]
                             + Staatsanleihen[0]
                             + Staatsanleihen[1];

    double PassivSumme     =   ZGeldGuthabenVonBanken[0]
                             + ZGeldGuthabenVonBanken[1]
                             + ZGeldGuthabenVonBanken[2]
                             + Bargeldumlauf
                             + Eigenkapital;

    float Epsilon = 0.0001;
    if(abs(AktivsummeSumme - PassivSumme) < Epsilon){
        return(true);
        }

    else{
        return(false);
        };
    }


//####################################################################################################################################





