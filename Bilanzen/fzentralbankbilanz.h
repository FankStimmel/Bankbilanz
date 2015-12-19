#ifndef FZENTRALBANKBILANZ_H
#define FZENTRALBANKBILANZ_H


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
    QVector <double> ForderungAnBanken;
    QVector <double> Staatsanleihen;

    // Passiva
    QVector <double> ZGeldGuthabenVonBanken;
    double Bargeldumlauf;
    double Eigenkapital;


};

#endif // FZENTRALBANKBILANZ_H
