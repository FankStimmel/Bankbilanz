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
    painter.setPen(Einstellungen.Pen_SchwarzerStift());
    painter.setBrush(Einstellungen.ObjectAktiv_Color());
    painter.drawRect(2, 2, 307, 30);
    painter.setFont(Einstellungen.Font_Gross());

    // Icons zeichnen
    if(MyBilanzObjekt == PERSON_A){
        QPixmap PixUp(":/Bilder/Person.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Person A");
        }

    if(MyBilanzObjekt == PERSON_B){
        QPixmap PixUp(":/Bilder/Person.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Person B");
        }
    if(MyBilanzObjekt == PERSON_C){
        QPixmap PixUp(":/Bilder/Person.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Person C");
        }
    if(MyBilanzObjekt == PERSON_D){
        QPixmap PixUp(":/Bilder/Person.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Person D");
        }

    if(MyBilanzObjekt == BANK_X){
        QPixmap PixUp(":/Bilder/Bank.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Bank X");
        }

    if(MyBilanzObjekt == BANK_Y){
        QPixmap PixUp(":/Bilder/Bank.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Bank Y");
        }

    if(MyBilanzObjekt == ZENTRALBANK){
        QPixmap PixUp(":/Bilder/ZBank.png");
        painter.drawImage(65,7,PixUp.toImage());
        painter.drawText(120, 26, "Zentralbank");
        }

    if(MyBilanzObjekt == DER_STAAT){
        QPixmap PixUp(":/Bilder/Staat.png");
        painter.drawImage(90,7,PixUp.toImage());
        painter.drawText(130, 26, "Staat");
        }

    event->accept();
    }
