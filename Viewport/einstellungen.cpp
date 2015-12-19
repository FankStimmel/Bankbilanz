#include "einstellungen.h"

Einstellungen::Einstellungen(){

    // Farben
    ObjectColor      = QColor(160,210,240);
    ObjectAktivColor = QColor(100,150,255);
    GiralgeldColor   = QColor(200,255,200);
    BargeldColor     = QColor(100,255,100);
    Hellgrau         = QColor(210,210,210);
    SehrHellgrau     = QColor(230,230,230);


    // Stifte
    PenSchwarzerStift       = QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    PenDickerSchwarzerStift = QPen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);


    // Schriftarten
    FontKlein = QFont("Times", 12, QFont::Bold);
    FontGross = QFont("Times", 18, QFont::Bold);
    }


//#######################################################################################################
//#  GETTER
//#######################################################################################################


QColor Einstellungen::Object_Color(){
    return(ObjectColor);
    }

QColor Einstellungen::ObjectAktiv_Color(){
    return(ObjectAktivColor);
    }

QColor Einstellungen::Giralgeld_Color(){
    return(GiralgeldColor);
    }

QColor Einstellungen::Bargeld_Color(){
    return(BargeldColor);
    }

QColor Einstellungen::Hellgrau_Color(){
    return(Hellgrau);
    }

QColor Einstellungen::SehrHellgrau_Color(){
    return(SehrHellgrau);
    }

QFont Einstellungen::Font_Klein(){
    return(FontKlein);
    }

QFont Einstellungen::Font_Gross(){
    return(FontGross);
    }

QPen Einstellungen::Pen_SchwarzerStift(){
    return(PenSchwarzerStift);
    }

QPen Einstellungen::Pen_Dicker_SchwarzerStift(){
    return(PenDickerSchwarzerStift);
    }

