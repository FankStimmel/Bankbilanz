#ifndef FEINSTELLUNGEN_H
#define FEINSTELLUNGEN_H


#include <QtGui>
#include <QColor>
#include <QFont>


// Type erstellen
enum BilanzOBJEKTE{PERSON_A, PERSON_B, PERSON_C, PERSON_D, BANK_A, BANK_B, ZENTRALBANK, DER_STAAT};
typedef enum BilanzOBJEKTE BILANZOBJEKTE;



class FEinstellungen

{

public:

    // Konstruktor
    FEinstellungen();


    // Getter
    // Farben
    QColor Object_Color();
    QColor ObjectAktiv_Color();
    QColor Giralgeld_Color();
    QColor Bargeld_Color();
    QColor Hellgrau_Color();
    QColor SehrHellgrau_Color();

    // Schriftarten
    QFont Font_Klein();
    QFont Font_Gross();

    // Stifte
    QPen Pen_SchwarzerStift();
    QPen Pen_Dicker_SchwarzerStift();

    // Pfade
    QString Pfad_zu_Screenshots();

    // Zinsen
    double GirokontoZinsen();
    double SparkontoZinsen();
    double KreditZinsen();
    double LeitZins();



};

#endif // FEINSTELLUNGEN_H
