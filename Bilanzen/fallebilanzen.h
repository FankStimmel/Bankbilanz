#ifndef FALLEBILANZEN_H
#define FALLEBILANZEN_H


#include <QtGui>

#include "geschaeftsbankbilanz.h"
#include "fzentralbankbilanz.h"
#include "fperson.h"
#include "fstaat.h"


class FAlleDaten

{

public:

    // Konstruktor
    FAlleDaten();

    // Methoden
    QString Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();
    void Reset_alle_Daten_to_Null();
    void Reset_alle_Rahmenstaerke_auf_duenn();
    void Initialisiere_alle_Bilanzen();
    void Set_alle_Daten_to_Preset_ABCD_haben_Kredite_aufgenommen();
    QString Get_Eigenkapitalrendite_Bank(int i);


    // Daten
    FZentralbankBilanz Zentralbank;
    QVector <FGeschaeftsbankBilanz> Banken;
    QVector <FPerson> Kunden;
    FStaat Staat;

    int Jahr;


};

#endif // FALLEBILANZEN_H
