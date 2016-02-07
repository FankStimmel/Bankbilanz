#include "geschaeftsbankbilanz.h"


//####################################################################################################################################
//#
//####################################################################################################################################


FGeschaeftsbankBilanz::FGeschaeftsbankBilanz(){

    // allgemeine Daten
    NameDerBank           = "Leer";


    // Aktiva
    BarGeldDerBank = 0;
    ZentralbankGeldguthaben = 0;
    KreditBeiAndererBank = 0;
    KrediteVonKunden << 0 << 0;
    Staatsanleihen = 0;
    Wertpapiere    = 0;

    // Passiva
    VerbindGegenZentralbank = 0;
    VerbindGegenAndereBank = 0;
    SparbuchKonten << 0 << 0;
    GiroKonten     << 0 << 0;
    StaatsGiroKonto = 0;
    Eigenkapital    = 0;


    // Rahmenstärke Aktivseite
    DickerRahmenBarGeldDerBank          = false;
    DickerRahmenZentralbankGeldguthaben = false;
    DickerRahmenKreditBeiAndererBank    = false;
    DickerRahmenHypotheken              << false << false;
    DickerRahmenStaatsanleihen          = false;
    DickerRahmenWertpapiere             = false;

    // Rahmenstärke Passiv
    DickerRahmenVerbindGegenZentralbank = false;
    DickerRahmenVerbindGegenAndereBank  = false;
    DickerRahmenSparbuchKonten          << false << false;
    DickerRahmenGiroKonten              << false << false;
    DickerRahmenStaatsGiroKonto         = false;
    DickerRahmenEigenkapital            = false;
    }


FGeschaeftsbankBilanz::FGeschaeftsbankBilanz(QString BUCHSTABE){

    // allgemeine Daten
    NameDerBank   = "Bank " + BUCHSTABE;
    BankBuchstabe = BUCHSTABE;


    // Aktiva
    BarGeldDerBank = 0;
    ZentralbankGeldguthaben = 0;
    KreditBeiAndererBank = 0;
    KrediteVonKunden << 0 << 0;
    Staatsanleihen = 0;
    Wertpapiere    = 0;

    // Passiva
    VerbindGegenZentralbank = 0;
    VerbindGegenAndereBank = 0;
    SparbuchKonten << 0 << 0;
    GiroKonten     << 0 << 0;
    StaatsGiroKonto = 0;
    Eigenkapital    = 0;

    // Rahmenstärke Aktivseite
    DickerRahmenBarGeldDerBank          = false;
    DickerRahmenZentralbankGeldguthaben = false;
    DickerRahmenKreditBeiAndererBank    = false;
    DickerRahmenHypotheken              << false << false;
    DickerRahmenStaatsanleihen          = false;
    DickerRahmenWertpapiere             = false;

    // Rahmenstärke Passiv
    DickerRahmenVerbindGegenZentralbank = false;
    DickerRahmenVerbindGegenAndereBank  = false;
    DickerRahmenSparbuchKonten          << false << false;
    DickerRahmenGiroKonten              << false << false;
    DickerRahmenStaatsGiroKonto         = false;
    DickerRahmenEigenkapital            = false;
    }


//####################################################################################################################################
//#
//####################################################################################################################################


void FGeschaeftsbankBilanz::Reset_alle_Rahmenstaerken_to_Duenn(){

    // Aktivseite
    DickerRahmenBarGeldDerBank          = false;
    DickerRahmenZentralbankGeldguthaben = false;
    DickerRahmenHypotheken[0]           = false;
    DickerRahmenHypotheken[1]           = false;
    DickerRahmenStaatsanleihen          = false;
    DickerRahmenWertpapiere             = false;

    // Rahmenstärke Passiv
    DickerRahmenVerbindGegenZentralbank = false;
    DickerRahmenSparbuchKonten[0]       = false;
    DickerRahmenSparbuchKonten[1]       = false;
    DickerRahmenGiroKonten[0]           = false;
    DickerRahmenGiroKonten[1]           = false;
    DickerRahmenStaatsGiroKonto         = false;
    DickerRahmenEigenkapital            = false;
    }


//####################################################################################################################################


void FGeschaeftsbankBilanz::Reset_Geschaeftsbankbilanz_to_Null(){

    // Aktiva
    BarGeldDerBank          = 0;
    ZentralbankGeldguthaben = 0;
    KreditBeiAndererBank    = 0;
    KrediteVonKunden[0]     = 0;
    KrediteVonKunden[1]     = 0;
    Staatsanleihen          = 0;
    Wertpapiere             = 0;

    // Passiva
    VerbindGegenZentralbank = 0;
    VerbindGegenAndereBank  = 0;
    SparbuchKonten[0]       = 0;
    SparbuchKonten[1]       = 0;
    GiroKonten[0]           = 0;
    GiroKonten[1]           = 0;
    StaatsGiroKonto         = 0;
    Eigenkapital            = 0;
    }


//####################################################################################################################################


QString FGeschaeftsbankBilanz::Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung(){

    // Aktiva
    if(BarGeldDerBank < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat zu wenig Bargeld.");
        }

    if(ZentralbankGeldguthaben < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat zu wenig Zentralbankgeldguthaben.");
        }

    if(KreditBeiAndererBank < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die Position Bankkredite darf nicht negativ sein.");
        }

    if(KrediteVonKunden[0] < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 0 hat bei der " + NameDerBank + " nicht so viele Kredite.");
        }

    if(KrediteVonKunden[1] < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 1 hat bei der " + NameDerBank + " nicht so viele Kredite.");
        }

    if(Staatsanleihen < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat nicht so viele Staatsanleihen.");
        }

    if(Wertpapiere < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat nicht so viele Wertpapiere.");
        }


    // Passiva
    if(VerbindGegenZentralbank < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die Verbindlichkeiten gegen die Zentralbank von der " + NameDerBank + " dürfen nicht kleiner Null sein.");
        }


    if(VerbindGegenAndereBank < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die Position BankVerbind. darf nicht negativ sein.");
        }

    if(SparbuchKonten[0] < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 0 hat nicht genug Geld auf dem Sparbuch.");
        }

    if(SparbuchKonten[1] < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 0 hat nicht genug Geld auf dem Sparbuch.");
        }

    if(GiroKonten[0] < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 0 hat nicht genug Geld auf dem Girokonto.");
        }

    if(GiroKonten[1] < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 1 hat nicht genug Geld auf dem Girokonto.");
        }

    if(StaatsGiroKonto < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Staat hat nicht genug Geld auf dem Girokonto.");
        }

    if(Eigenkapital < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Das Eigenkapital der " + NameDerBank + " darf nicht kleiner Null sein.");
        }


    // Eigenkapitalquote checken
    if(Get_EigenKapitalQuote() < 0.08){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat nicht genug Eigenkapital, um weitere Aktiva anzukaufen.\n"
               "Basel II verlangt mindestens  8 %.");
        }


    // Mindestreservequote checken



    // Sonst keine Fehler melden.
    return("");
    }


//####################################################################################################################################


QString FGeschaeftsbankBilanz::Get_EigenKapitalQuote_as_String(){
    if( KrediteVonKunden[0] == 0  &&  KrediteVonKunden[1] == 0 &&  Staatsanleihen == 0 && Wertpapiere == 0 ){
        return("unendlich");
        }
    double Quote = 100.0 * Eigenkapital / (KrediteVonKunden[0] + KrediteVonKunden[1] + Staatsanleihen + Wertpapiere );
    return(QString::number(Quote,'f',2) + " %");
    }


//####################################################################################################################################


double FGeschaeftsbankBilanz::Get_EigenKapitalQuote(){
    if( KrediteVonKunden[0] == 0  &&  KrediteVonKunden[1] == 0 &&  Staatsanleihen == 0  && Wertpapiere == 0){
        return(1.0);
        }
    double Quote = 1.0 * Eigenkapital / (KrediteVonKunden[0] + KrediteVonKunden[1] + Staatsanleihen + Wertpapiere);
    return(Quote);
    }


//####################################################################################################################################


QString FGeschaeftsbankBilanz::Get_MindestReserveQuote_as_QString(){
    if(    GiroKonten[0] == 0      &&  GiroKonten[1] == 0
        && SparbuchKonten[1] == 0  &&  SparbuchKonten[1] == 0
        && StaatsGiroKonto == 0   ){
            return("unendlich");
            }

    double Quote = 100.00 * (BarGeldDerBank + ZentralbankGeldguthaben )
                          / (SparbuchKonten[0] + SparbuchKonten[1] + GiroKonten[0] + GiroKonten[1] + StaatsGiroKonto);
    return(QString::number(Quote,'f',2) + " %");
    }


//####################################################################################################################################


double FGeschaeftsbankBilanz::Get_Summe_der_vergebenen_Kredite(){
    double Summe;
    Summe = KrediteVonKunden[0] + KrediteVonKunden[1] + Staatsanleihen;
    return(Summe);
    }


//####################################################################################################################################


QString FGeschaeftsbankBilanz::Get_Bilanzsumme_as_String(){

    double AktivsummeSumme =   BarGeldDerBank
                             + ZentralbankGeldguthaben
                             + KreditBeiAndererBank
                             + KrediteVonKunden[0] + KrediteVonKunden[1]
                             + Staatsanleihen
                             + Wertpapiere;

    double PassivSumme     =   VerbindGegenZentralbank
                             + VerbindGegenAndereBank
                             + SparbuchKonten[0] + SparbuchKonten[1]
                             + GiroKonten[0] + GiroKonten[1]
                             + StaatsGiroKonto
                             + Eigenkapital;

    if(abs(AktivsummeSumme - PassivSumme) > 0.001)
        qDebug() << "Fehler: Aktiv != Passiv in Geschäftsbank" << AktivsummeSumme << PassivSumme;

    return(QString::number(AktivsummeSumme,'f',2));
    }


//####################################################################################################################################


bool FGeschaeftsbankBilanz::Ist_die_Aktivsumme_gleich_der_Passivsumme(){

    double AktivsummeSumme =  BarGeldDerBank
                            + ZentralbankGeldguthaben
                            + KreditBeiAndererBank
                            + KrediteVonKunden[0] + KrediteVonKunden[1]
                            + Staatsanleihen
                            + Wertpapiere;

    double PassivSumme     =  VerbindGegenZentralbank
                            + VerbindGegenAndereBank
                            + SparbuchKonten[0] + SparbuchKonten[1]
                            + GiroKonten[0] + GiroKonten[1]
                            + StaatsGiroKonto
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



