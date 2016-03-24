#ifndef FZENTRALBANKBILANZ_H
#define FZENTRALBANKBILANZ_H


#include "fgeld.h"
#include <QtGui>


class FZentralbankBilanz

{

public:

    // Konstruktor
    FZentralbankBilanz();


    // Methoden
    void Reset_Zentralbankbilanz_to_Null();


    // Getter
    bool Ist_die_Aktivsumme_gleich_der_Passivsumme();
    QString Checken_ob_Bilanz_valide_ist_sonst_Fehlermeldung();


    // allgemeine Daten
    QString NameDerBank;


    // Aktiva
    QVector <FGeld> ForderungAnBanken;
    QVector <FGeld> Staatsanleihen;

    // Passiva
    QVector <FGeld> ZGeldGuthabenVonBanken;
    FGeld Bargeldumlauf;
    FGeld Eigenkapital;


    // Rahmenstärke Aktivseite
    QVector <bool> DickerRahmenForderungAnBanken;
    QVector <bool> DickerRahmenStaatsanleihen;

    // Rahmenstärke Passiv
    QVector <bool> DickerRahmenZGeldGuthabenVonBanken;
    bool DickerRahmenBargeldumlauf;
    bool DickerRahmenEigenkapital;


};

#endif // FZENTRALBANKBILANZ_H
