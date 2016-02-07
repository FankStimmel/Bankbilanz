#ifndef GESCHAEFTSBANKBILANZ_H
#define GESCHAEFTSBANKBILANZ_H


#include <QtGui>
#include "feinstellungen.h"



class FGeschaeftsbankBilanz

{

public:

    // Konstruktor
    FGeschaeftsbankBilanz();
    FGeschaeftsbankBilanz(QString BUCHSTABE);


    // Getter
    QString Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung();
    QString Get_Bilanzsumme_as_String();
    QString Get_MindestReserveQuote_as_QString();
    QString Get_EigenKapitalQuote_as_String();
    double Get_EigenKapitalQuote();
    double Get_Summe_der_vergebenen_Kredite();
    bool Ist_die_Aktivsumme_gleich_der_Passivsumme();


    // Setter
    void Reset_Geschaeftsbankbilanz_to_Null();
    void Reset_alle_Rahmenstaerken_to_Duenn();




    // allgemeine Daten
    QString NameDerBank;
    QString BankBuchstabe;


    // Aktiva
    double BarGeldDerBank;
    double ZentralbankGeldguthaben;
    double KreditBeiAndererBank;
    QVector <double> KrediteVonKunden;
    double Staatsanleihen;
    double Wertpapiere;


    // Passiva
    double VerbindGegenZentralbank;
    double VerbindGegenAndereBank;
    QVector <double> SparbuchKonten;
    QVector <double> GiroKonten;
    double StaatsGiroKonto;
    double Eigenkapital;



    // Aktiva  Rahmenstärke dick oder dünn
    bool DickerRahmenBarGeldDerBank;
    bool DickerRahmenZentralbankGeldguthaben;
    bool DickerRahmenKreditBeiAndererBank;
    QVector <bool> DickerRahmenHypotheken;
    bool DickerRahmenStaatsanleihen;
    bool DickerRahmenWertpapiere;


    // Passiva  Rahmenstärke dick oder dünn
    bool DickerRahmenVerbindGegenZentralbank;
    bool DickerRahmenVerbindGegenAndereBank;
    QVector <bool> DickerRahmenSparbuchKonten;
    QVector <bool> DickerRahmenGiroKonten;
    bool DickerRahmenStaatsGiroKonto;
    bool DickerRahmenEigenkapital;



};

#endif // GESCHAEFTSBANKBILANZ_H
