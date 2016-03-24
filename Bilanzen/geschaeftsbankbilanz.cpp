#include "geschaeftsbankbilanz.h"


//####################################################################################################################################
//#
//####################################################################################################################################


FGeschaeftsbankBilanz::FGeschaeftsbankBilanz(){

    // allgemeine Daten
    NameDerBank           = "Leer";


    FGeld Nichts("",0.0);

    // Aktiva
    BarGeldDerBank = Nichts;
    ZentralbankGeldguthaben = Nichts;
    KreditBeiAndererBank = Nichts;
    KrediteVonKunden << Nichts << Nichts;
    Staatsanleihen = Nichts;
    Wertpapiere    = Nichts;

    // Passiva
    VerbindGegenZentralbank = Nichts;
    VerbindGegenAndereBank = Nichts;
    SparbuchKonten << Nichts << Nichts;
    GiroKonten     << Nichts << Nichts;
    StaatsGiroKonto = Nichts;
    Eigenkapital    = Nichts;


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
    BarGeldDerBank          = FGeld("",0.0);
    ZentralbankGeldguthaben = FGeld("",0.0);
    KreditBeiAndererBank    = FGeld("",0.0);
    KrediteVonKunden << FGeld("",0.0) << FGeld("",0.0);
    Staatsanleihen = FGeld("",0.0);
    Wertpapiere    = FGeld("",0.0);

    // Passiva
    VerbindGegenZentralbank = FGeld("",0.0);
    VerbindGegenAndereBank  = FGeld("",0.0);
    SparbuchKonten << FGeld("",0.0) << FGeld("",0.0);
    GiroKonten     << FGeld("",0.0) << FGeld("",0.0);
    StaatsGiroKonto = FGeld("",0.0);
    Eigenkapital    = FGeld("",0.0);

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
    DickerRahmenKreditBeiAndererBank    = false;
    DickerRahmenHypotheken[0]           = false;
    DickerRahmenHypotheken[1]           = false;
    DickerRahmenStaatsanleihen          = false;
    DickerRahmenWertpapiere             = false;

    // Rahmenstärke Passiv
    DickerRahmenVerbindGegenZentralbank = false;
    DickerRahmenVerbindGegenAndereBank  = false;
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
    BarGeldDerBank          = FGeld("",0.0);
    ZentralbankGeldguthaben = FGeld("",0.0);
    KreditBeiAndererBank    = FGeld("",0.0);
    KrediteVonKunden[0]     = FGeld("",0.0);
    KrediteVonKunden[1]     = FGeld("",0.0);
    Staatsanleihen          = FGeld("",0.0);
    Wertpapiere             = FGeld("",0.0);

    // Passiva
    VerbindGegenZentralbank = FGeld("",0.0);
    VerbindGegenAndereBank  = FGeld("",0.0);
    SparbuchKonten[0]       = FGeld("",0.0);
    SparbuchKonten[1]       = FGeld("",0.0);
    GiroKonten[0]           = FGeld("",0.0);
    GiroKonten[1]           = FGeld("",0.0);
    StaatsGiroKonto         = FGeld("",0.0);
    Eigenkapital            = FGeld("",0.0);
    }


//####################################################################################################################################


QString FGeschaeftsbankBilanz::Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung(){

    // Aktiva
    if(BarGeldDerBank.Get_Cents() < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat zu wenig Bargeld.");
        }

    if(ZentralbankGeldguthaben.Get_Cents() < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat zu wenig Zentralbankgeldguthaben.");
        }

    if(KreditBeiAndererBank.Get_Cents() < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die Position Bankkredite darf nicht negativ sein.");
        }

    if(KrediteVonKunden[0].Get_Cents() < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 0 hat bei der " + NameDerBank + " nicht so viele Kredite.");
        }

    if(KrediteVonKunden[1].Get_Cents() < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 1 hat bei der " + NameDerBank + " nicht so viele Kredite.");
        }

    if(Staatsanleihen.Get_Cents() < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat nicht so viele Staatsanleihen.");
        }

    if(Wertpapiere.Get_Cents() < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat nicht so viele Wertpapiere.");
        }


    // Passiva
    if(VerbindGegenZentralbank.Get_Cents() < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die Verbindlichkeiten gegen die Zentralbank von der " + NameDerBank + " dürfen nicht kleiner Null sein.");
        }


    if(VerbindGegenAndereBank.Get_Cents() < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die Position BankVerbind. darf nicht negativ sein.");
        }

    if(SparbuchKonten[0].Get_Cents() < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 0 hat nicht genug Geld auf dem Sparbuch.");
        }

    if(SparbuchKonten[1].Get_Cents() < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 0 hat nicht genug Geld auf dem Sparbuch.");
        }

    if(GiroKonten[0].Get_Cents() < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 0 hat nicht genug Geld auf dem Girokonto.");
        }

    if(GiroKonten[1].Get_Cents() < 0){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Kunde 1 hat nicht genug Geld auf dem Girokonto.");
        }

    if(StaatsGiroKonto.Get_Cents() < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Der Staat hat nicht genug Geld auf dem Girokonto.");
        }

    if(Eigenkapital.Get_Cents() < 0 ){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Das Eigenkapital der " + NameDerBank + " darf nicht kleiner Null sein.");
        }


    // Eigenkapitalquote checken
    if(Get_EigenKapitalQuote() < 0.08){
        return("In der Bilanz von " + NameDerBank + ": \n\n"
               "Die " + NameDerBank + " hat nicht genug Eigenkapital.\n"
               "Basel III verlangt mindestens  8 %.");
        }


    // Mindestreservequote checken



    // Sonst keine Fehler melden.
    return("");
    }


//####################################################################################################################################


QString FGeschaeftsbankBilanz::Get_EigenKapitalQuote_as_String(){
    if( KrediteVonKunden[0].Get_Cents() == 0  &&
        KrediteVonKunden[1].Get_Cents() == 0  &&
        Staatsanleihen.Get_Cents() == 0       &&
        Wertpapiere.Get_Cents() == 0 ){
            return("unendlich");
            }
    double Quote = 100.0 *
                   Eigenkapital.Get_Euro() /
                   (KrediteVonKunden[0].Get_Euro()
                    + KrediteVonKunden[1].Get_Euro()
                    + Staatsanleihen.Get_Euro()
                    + Wertpapiere.Get_Euro() );
    return(QString::number(Quote,'f',2) + " %");
    }


//####################################################################################################################################


double FGeschaeftsbankBilanz::Get_EigenKapitalQuote(){
    if(     KrediteVonKunden[0].Get_Cents() == 0
        &&  KrediteVonKunden[1].Get_Cents() == 0
        &&  Staatsanleihen.Get_Cents() == 0
        &&  Wertpapiere.Get_Cents() == 0){
        return(1.0);
        }
    double Quote = 1.0 * Eigenkapital.Get_Euro() /
            (KrediteVonKunden[0].Get_Euro()
            + KrediteVonKunden[1].Get_Euro()
            + Staatsanleihen.Get_Euro()
            + Wertpapiere.Get_Euro());
    return(Quote);
    }


//####################################################################################################################################


QString FGeschaeftsbankBilanz::Get_MindestReserveQuote_as_QString(){
    FGeld SummeGiralgeld =   GiroKonten[0]
                           + GiroKonten[1]
                           + SparbuchKonten[0]
                           + SparbuchKonten[1]
                           + StaatsGiroKonto;

    if( SummeGiralgeld.Get_Cents() == 0 )
        return("unendlich");


    double Quote = 100.00 * (BarGeldDerBank.Get_Euro() + ZentralbankGeldguthaben.Get_Euro() )
                          / SummeGiralgeld.Get_Euro();
    return(QString::number(Quote,'f',2) + " %");
    }


//####################################################################################################################################


FGeld FGeschaeftsbankBilanz::Get_Summe_der_vergebenen_Kredite(){
    FGeld Summe =  KrediteVonKunden[0]
                 + KrediteVonKunden[1]
                 + Staatsanleihen;
    return(Summe);
    }


//####################################################################################################################################


QString FGeschaeftsbankBilanz::Get_Bilanzsumme_as_String(){

    FGeld AktivsummeSumme =    BarGeldDerBank
                             + ZentralbankGeldguthaben
                             + KreditBeiAndererBank
                             + KrediteVonKunden[0] + KrediteVonKunden[1]
                             + Staatsanleihen
                             + Wertpapiere;

    FGeld PassivSumme     =    VerbindGegenZentralbank
                             + VerbindGegenAndereBank
                             + SparbuchKonten[0] + SparbuchKonten[1]
                             + GiroKonten[0] + GiroKonten[1]
                             + StaatsGiroKonto
                             + Eigenkapital;

    if( AktivsummeSumme.Get_Cents() != PassivSumme.Get_Cents() )
        qDebug() << "Fehler: Aktiv != Passiv in Geschäftsbank"
                 << AktivsummeSumme.Get_Euro_as_QString()
                 << PassivSumme.Get_Euro_as_QString();

    return(AktivsummeSumme.Get_Euro_as_QString());
    }


//####################################################################################################################################


bool FGeschaeftsbankBilanz::Ist_die_Aktivsumme_gleich_der_Passivsumme(){

    FGeld AktivsummeSumme =   BarGeldDerBank
                            + ZentralbankGeldguthaben
                            + KreditBeiAndererBank
                            + KrediteVonKunden[0] + KrediteVonKunden[1]
                            + Staatsanleihen
                            + Wertpapiere;

    FGeld PassivSumme     =   VerbindGegenZentralbank
                            + VerbindGegenAndereBank
                            + SparbuchKonten[0] + SparbuchKonten[1]
                            + GiroKonten[0] + GiroKonten[1]
                            + StaatsGiroKonto
                            + Eigenkapital;

    if(AktivsummeSumme.Get_Cents() == PassivSumme.Get_Cents() ){
        return(true);
        }

    else{
        return(false);
        };
    }


//####################################################################################################################################



