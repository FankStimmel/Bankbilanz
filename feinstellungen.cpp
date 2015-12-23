#include "feinstellungen.h"

FEinstellungen::FEinstellungen(){
   }


//#######################################################################################################
//#  GETTER
//#######################################################################################################


// Farben
QColor FEinstellungen::Object_Color(){
    return(QColor(160,210,240));
    }


QColor FEinstellungen::ObjectAktiv_Color(){
    return(QColor(100,150,255));
    }


QColor FEinstellungen::Giralgeld_Color(){
    return(QColor(200,255,200));
    }


QColor FEinstellungen::Bargeld_Color(){
    return(QColor(100,255,100));
    }


QColor FEinstellungen::Hellgrau_Color(){
    return(QColor(210,210,210));
    }


QColor FEinstellungen::SehrHellgrau_Color(){
    return(QColor(230,230,230));
    }



// Schriftarten
QFont FEinstellungen::Font_Klein(){
    return(QFont("Times", 12, QFont::Bold));
    }


QFont FEinstellungen::Font_Gross(){
    return(QFont("Times", 18, QFont::Bold));
    }



// Stifte
QPen FEinstellungen::Pen_SchwarzerStift(){
    return(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }


QPen FEinstellungen::Pen_Dicker_SchwarzerStift(){
    return(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }


// Pfade
QString FEinstellungen::Pfad_zu_Screenshots(){
    return(QDir::homePath() + "/Bilder/");
    }


// Zinsen
double FEinstellungen::GirokontoZinsen(){
    return(0.01);
    }

double FEinstellungen::SparkontoZinsen(){
    return(0.02);
    }

double FEinstellungen::KreditZinsen(){
    return(0.05);
    }

double FEinstellungen::LeitZins(){
    return(0.01);
    }




