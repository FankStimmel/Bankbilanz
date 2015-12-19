#include "fmylabel.h"


//##########################################################################################


FMyLabel::FMyLabel(){
    }


FMyLabel::FMyLabel(BILANZOBJEKTE BilanzObjekt, QWidget * parent) : QLabel(parent){
    MyBilanzObjekt = BilanzObjekt;
    }


//##########################################################################################


void FMyLabel::setDaten(BILANZOBJEKTE BilanzObjekt){
    MyBilanzObjekt = BilanzObjekt;
    update();
    }


void FMyLabel::paintEvent ( QPaintEvent * event ) {
    QPainter painter(this);
    FEinstellungen Einstellungen;
    painter.setPen(Einstellungen.Pen_Dicker_SchwarzerStift());
    painter.setBrush(Einstellungen.ObjectAktiv_Color());
    painter.drawRect(2, 2, 307, 30);
    painter.setFont(Einstellungen.Font_Gross());

    // Icons zeichnen
    if(MyBilanzObjekt == PERSON_A){
        QPixmap PixUp(Einstellungen.Pfad_zu_den_Icons() + "Person.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Person A");
        }

    if(MyBilanzObjekt == PERSON_B){
        QPixmap PixUp(Einstellungen.Pfad_zu_den_Icons() + "Person.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Person B");
        }
    if(MyBilanzObjekt == PERSON_C){
        QPixmap PixUp(Einstellungen.Pfad_zu_den_Icons() + "Person.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Person C");
        }
    if(MyBilanzObjekt == PERSON_D){
        QPixmap PixUp(Einstellungen.Pfad_zu_den_Icons() + "Person.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Person D");
        }

    if(MyBilanzObjekt == BANK_A){
        QPixmap PixUp(Einstellungen.Pfad_zu_den_Icons() + "Bank.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Bank A");
        }

    if(MyBilanzObjekt == BANK_B){
        QPixmap PixUp(Einstellungen.Pfad_zu_den_Icons() + "Bank.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Bank B");
        }

    if(MyBilanzObjekt == ZENTRALBANK){
        QPixmap PixUp(Einstellungen.Pfad_zu_den_Icons() + "ZBank.png");
        painter.drawImage(65,7,PixUp.toImage());
        painter.drawText(120, 26, "Zentralbank");
        }

    if(MyBilanzObjekt == DER_STAAT){
        QPixmap PixUp(Einstellungen.Pfad_zu_den_Icons() + "Staat.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Staat");
        }

    }
