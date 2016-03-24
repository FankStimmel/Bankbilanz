#include "fzentralbankbilanz.h"


FZentralbankBilanz::FZentralbankBilanz(){
    // allgemeine Daten
    NameDerBank = "Zentralbank";

    // Aktiva
    ForderungAnBanken << FGeld("",0.0) << FGeld("",0.0) << FGeld("",0.0);
    Staatsanleihen    << FGeld("",0.0) << FGeld("",0.0);

    // Passiva
    ZGeldGuthabenVonBanken << FGeld("",0.0) << FGeld("",0.0) << FGeld("",0.0);
    Bargeldumlauf          = FGeld("",0.0);
    Eigenkapital           = FGeld("",0.0);

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
    ForderungAnBanken[0] = FGeld("",0.0);
    ForderungAnBanken[1] = FGeld("",0.0);
    ForderungAnBanken[2] = FGeld("",0.0);
    Staatsanleihen[0]    = FGeld("",0.0);
    Staatsanleihen[1]    = FGeld("",0.0);

    // Passiva
    ZGeldGuthabenVonBanken[0] = FGeld("",0.0);
    ZGeldGuthabenVonBanken[1] = FGeld("",0.0);
    ZGeldGuthabenVonBanken[2] = FGeld("",0.0);
    Bargeldumlauf = FGeld("",0.0);
    Eigenkapital  = FGeld("",0.0);
    }


//####################################################################################################################################


QString FZentralbankBilanz::Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung(){

    // Aktiva
    if(ForderungAnBanken[0].Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Forderung gegen die Bank A darf nicht negativ sein.");
        }

    if(ForderungAnBanken[1].Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Forderung gegen die Bank B darf nicht negativ sein.");
        }

    if(ForderungAnBanken[2].Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Forderung gegen die Bank C darf nicht negativ sein.");
        }

    if(Staatsanleihen[0].Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Staatsanleihen von Bank A dürfen nicht negativ sein.");
        }

    if(Staatsanleihen[1].Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Die Staatsanleihen von Bank B dürfen nicht negativ sein.");
        }



    // Passiva
    if(ZGeldGuthabenVonBanken[0].Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Das Zentralbankgeldguthaben von Bank A darf nicht negativ sein.");
        }

    if(ZGeldGuthabenVonBanken[1].Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Das Zentralbankgeldguthaben von Bank B darf nicht negativ sein.");
        }

    if(ZGeldGuthabenVonBanken[2].Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Das Zentralbankgeldguthaben von Bank C darf nicht negativ sein.");
        }

    if(Bargeldumlauf.Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Der Bargeldumlauf darf nicht negativ sein.");
        }

    if(Eigenkapital.Get_Cents() < 0){
        return("In der Zentralbankbilanz: \n\n"
               "Das Eigenkapital der Zentralbank darf nicht negativ sein.");
        }


    // Sonst keine Fehler melden.
    return("");
    }


//####################################################################################################################################


bool FZentralbankBilanz::Ist_die_Aktivsumme_gleich_der_Passivsumme(){

    FGeld AktivsummeSumme =    ForderungAnBanken[0]
                             + ForderungAnBanken[1]
                             + ForderungAnBanken[2]
                             + Staatsanleihen[0]
                             + Staatsanleihen[1];

    FGeld PassivSumme      =   ZGeldGuthabenVonBanken[0]
                             + ZGeldGuthabenVonBanken[1]
                             + ZGeldGuthabenVonBanken[2]
                             + Bargeldumlauf
                             + Eigenkapital;

    float Epsilon = 0.0001;
    if(abs(AktivsummeSumme.Get_Cents() - PassivSumme.Get_Cents()) < Epsilon){
        return(true);
        }

    else{
        return(false);
        };
    }


//####################################################################################################################################





