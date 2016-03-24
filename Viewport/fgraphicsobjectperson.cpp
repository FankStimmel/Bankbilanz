#include "fgraphicsobjectperson.h"


//##################################################################################################################################
//#     Konstruktor
//##################################################################################################################################



FGrapicsObjectPerson::FGrapicsObjectPerson(QGraphicsItem *parent) : QGraphicsObject(parent){
    FEinstellungen Einstel;
    AktuellerStiftFuerDenRand  = Einstel.Pen_SchwarzerStift();
    AktuelleObjectFarbe        = Einstel.Object_Color();
    }


FGrapicsObjectPerson::FGrapicsObjectPerson(int IdNUMMER, QGraphicsItem *parent) : QGraphicsObject(parent) {
    FEinstellungen Einstel;
    KundenNummer              = IdNUMMER;
    AktuellerStiftFuerDenRand = Einstel.Pen_SchwarzerStift();
    AktuelleObjectFarbe       = Einstel.Object_Color();
    }


//##################################################################################################################################


QRectF FGrapicsObjectPerson::boundingRect() const{        // Dieser Bereich ist anklickbar!
    return QRectF(0, 0, 145, 80);
    }

//###################################################################################################################################


void FGrapicsObjectPerson::Neu_zeichnen(FAlleDaten AlleDATEN){
    AlleDaten = AlleDATEN;
    update();
    }

//###################################################################################################################################


void FGrapicsObjectPerson::setPos_My(float x, float y){
    setPos(x,y);
    Kastenposition = QPointF(x,y);
    }


//###################################################################################################################################


void FGrapicsObjectPerson::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    // Einstellungen
    FEinstellungen Einstel;
    QColor BargeldColor    = Einstel.Bargeld_Color();
    QColor HellgrauColor   = Einstel.Hellgrau_Color();
    QPen PenSchwarzerStift = Einstel.Pen_SchwarzerStift();
    QFont serifFont        = Einstel.Font_Gross();
    QFont serifFont2       = Einstel.Font_Klein();



    // Kasten um alles
    painter->setPen(PenSchwarzerStift);
    painter->setBrush(Einstel.SehrSehrHellgrau_Color());
    painter->drawRect(0,0,145,80);

    // Hintergrund der Person
    painter->setBrush(AktuelleObjectFarbe);
    painter->drawRect(0,0,145,30);

    // Text für die Person
    painter->setFont(serifFont);
    painter->drawText(65,23,AlleDaten.Kunden[KundenNummer].PersonenBuchstabe);

    int xKasten = 70;
    int y       = 30;

    // Bargeld Anzeige
    painter->setFont(serifFont2);
    Zeichne_Kasten_in_der_Bilanz(painter,
                                 xKasten, 1*y+10, 10,
                                 "Bar:", AlleDaten.Kunden[KundenNummer].Bargeld,
                                 BargeldColor,
                                 AlleDaten.Kunden[KundenNummer].DickerRahmenBarGeld);
    }


//####################################################################################################################################


void FGrapicsObjectPerson::Zeichne_Kasten_in_der_Bilanz(QPainter* p,
                                                        float x, float y, float xText,
                                                        QString Text,
                                                        FGeld Zahlenwert,
                                                        QColor Farbe,
                                                        bool fetterRahmen){

    // Stift
    FEinstellungen Einstel;

    // Beschriftung zeichnen
    p->setPen(Einstel.Pen_SchwarzerStift());
    p->drawText(xText, y+18, Text);


    // Negative Werte als Warnung mit rotem Hintergrund zeichnen.
    if( Zahlenwert.Get_Cents() < 0 ){
        p->setBrush(Qt::red);
        p->setPen(Einstel.Pen_SchwarzerStift());
        p->drawRect(x,   y, 60, 25);
        p->drawText(x+5, y+18, Zahlenwert.Get_Euro_as_QString());
        }


    // Positive Werte mit der Farbe zeichnen.
    else if( Zahlenwert.Get_Cents() > 0 ){

        // Rahmen
        if(fetterRahmen)  p->setPen(Einstel.Pen_Dicker_RoterStift());
        else              p->setPen(Einstel.Pen_SchwarzerStift());

        p->setBrush(Farbe);
        p->drawRect(x, y, 60, 25);

        // Zahlentext
        p->setPen(Einstel.Pen_SchwarzerStift());
        p->setBrush(Farbe);
        p->drawText(x+5, y+18, Zahlenwert.Get_Euro_as_QString());
        }


    // Werte nahe 0 nur zeichnen, wenn der Rahmen fett ist.
    else{
        if(fetterRahmen){

            // Rahmen
            p->setPen(Einstel.Pen_Dicker_RoterStift());
            p->setBrush(Einstel.Hellgrau_Color());
            p->drawRect(x, y, 60, 25);

            // Zahlentext
            p->setPen(Einstel.Pen_SchwarzerStift());
            p->drawText(x+5, y+18, "");
            }
        }

    }


//####################################################################################################################################


void FGrapicsObjectPerson::Set_Object_visual_marked(bool wert){
    FEinstellungen Einstel;
    if(wert == true){
        AktuellerStiftFuerDenRand = Einstel.Pen_Dicker_SchwarzerStift();
        AktuelleObjectFarbe       = Einstel.ObjectAktiv_Color();
        }
    else{
        AktuellerStiftFuerDenRand = Einstel.Pen_SchwarzerStift();
        AktuelleObjectFarbe       = Einstel.Object_Color();
        }
    update();
    }


//####################################################################################################################################


void FGrapicsObjectPerson::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    if (KundenNummer == 0 ) emit IdNummer_von_Person_wurde_gesendet(PERSON_A, true);
    if (KundenNummer == 1 ) emit IdNummer_von_Person_wurde_gesendet(PERSON_B, true);
    if (KundenNummer == 2 ) emit IdNummer_von_Person_wurde_gesendet(PERSON_C, true);
    if (KundenNummer == 3 ) emit IdNummer_von_Person_wurde_gesendet(PERSON_D, true);
    }



