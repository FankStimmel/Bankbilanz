#ifndef EINSTELLUNGEN_H
#define EINSTELLUNGEN_H

#include <QtGui>
#include <QColor>
#include <QFont>


class Einstellungen

{

public:

    // Konstruktor
    Einstellungen();

    // Getter
    QColor Object_Color();
    QColor ObjectAktiv_Color();
    QColor Giralgeld_Color();
    QColor Bargeld_Color();
    QColor Hellgrau_Color();
    QColor SehrHellgrau_Color();

    QFont Font_Klein();
    QFont Font_Gross();

    QPen Pen_SchwarzerStift();
    QPen Pen_Dicker_SchwarzerStift();


private:

    // Daten
    QColor ObjectColor;
    QColor ObjectAktivColor;
    QColor GiralgeldColor;
    QColor BargeldColor;
    QColor Hellgrau;
    QColor SehrHellgrau;

    // Stifte
    QPen PenSchwarzerStift;
    QPen PenDickerSchwarzerStift;

    // Schriftarten
    QFont FontKlein;
    QFont FontGross;


};

#endif // EINSTELLUNGEN_H
