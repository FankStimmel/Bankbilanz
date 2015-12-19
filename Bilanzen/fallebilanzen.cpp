#include "fallebilanzen.h"



FAlleDaten::FAlleDaten(){

    // Zentralbank initialisieren.


    // Geschäftsbanken initialisieren.
    Banken.append(FGeschaeftsbankBilanz("A"));
    Banken.append(FGeschaeftsbankBilanz("B"));


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
