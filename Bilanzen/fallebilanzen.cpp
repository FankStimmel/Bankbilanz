#include "fallebilanzen.h"



FAlleDaten::FAlleDaten(){

    // Zentralbank initialisieren.


    // Geschäftsbanken initialisieren.
    Banken.append(FGeschaeftsbankBilanz("X"));
    Banken.append(FGeschaeftsbankBilanz("Y"));


    // Kunden initialisieren.
    Kunden.append(FPerson("A"));
    Kunden.append(FPerson("B"));
    Kunden.append(FPerson("C"));
    Kunden.append(FPerson("D"));


    // Staat initialisieren.
    Staat = FStaat("Staat");


    // Zeit initialisieren.
    Jahr = 0;
    }

//###################################################################################################################


void FAlleDaten::Reset_alle_Rahmenstaerke_auf_duenn(){
    Banken[0].Reset_alle_Rahmenstaerken_to_Duenn();
    Banken[1].Reset_alle_Rahmenstaerken_to_Duenn();
    }


//###################################################################################################################


void FAlleDaten::Reset_alle_Daten_to_Null(){

    Zentralbank.Reset_Zentralbankbilanz_to_Null();

    Banken[0].Reset_Geschaeftsbankbilanz_to_Null();
    Banken[1].Reset_Geschaeftsbankbilanz_to_Null();

    Kunden[0].Reset_Personenbilanz_to_Null();
    Kunden[1].Reset_Personenbilanz_to_Null();
    Kunden[2].Reset_Personenbilanz_to_Null();
    Kunden[3].Reset_Personenbilanz_to_Null();

    Staat.Reset_Staatsbilanz_to_Null();

    Jahr = 0;
    }

//###################################################################################################################


void FAlleDaten::Initialisiere_alle_Bilanzen(){

    // Reset
    Reset_alle_Daten_to_Null();

    // Zentralbank
    Zentralbank.ForderungAnBanken[2] = 1000;
    Zentralbank.Bargeldumlauf        = 1000;


    // Geschäftsbanken
    for(int i=0; i<2; i++){
        Banken[i].BarGeldDerBank = 500;
        Banken[i].Eigenkapital   = 500;
        }
    }


//###################################################################################################################


void FAlleDaten::Set_alle_Daten_to_Preset_ABCD_haben_Kredite_aufgenommen(){
    Initialisiere_alle_Bilanzen();

    // Kundenkredite
    for(int KundenNr=0;KundenNr<4;KundenNr++){
        Kunden[KundenNr].Schulden += 3000;
        }

    for(int BankNr=0; BankNr<2; BankNr++){
        for(int KundenNr=0; KundenNr<2; KundenNr++){
            Banken[BankNr].GiroKonten[KundenNr]       += 3000;
            Banken[BankNr].KrediteVonKunden[KundenNr] += 3000;
            }
        }
    }


//###################################################################################################################


QString FAlleDaten::Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung(){

    // Zentralbankbilanz checken.
    QString FehlermeldungZentralbank = Zentralbank.Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung();
    if( FehlermeldungZentralbank != "" ){
        return(FehlermeldungZentralbank);
        }


    // Geschäftsbankbilanzen checken.
    for(int i=0; i<2; i++){
        QString FehlermeldungBank = Banken[i].Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung();
        if( FehlermeldungBank != "" ){
            return(FehlermeldungBank);
            }
        }


    // Kunden checken.
    for(int i=0; i<4; i++){
        QString FehlermeldungKunde = Kunden[i].Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung();
        if(FehlermeldungKunde != ""){
            return(FehlermeldungKunde);
            }
        }

    // Staat checken.
    QString FehlermeldungStaat = Staat.Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung();
    if( FehlermeldungStaat != "" ){
        return(FehlermeldungStaat);
        }


    // Sonst keine Fehler melden.
    return("");
    }


//###################################################################################################################


QString FAlleDaten::Get_Eigenkapitalrendite_Bank(int i){
    if(Jahr == 0) return("0 %");

    double wert = (pow(Banken[i].Eigenkapital / 500.0, 1.0/Jahr) - 1.0) * 100;
    return(QString::number(wert,'f',2) + " %");
    }

//###################################################################################################################
