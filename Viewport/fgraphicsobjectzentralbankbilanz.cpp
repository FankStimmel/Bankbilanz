#include "fgraphicsobjectzentralbankbilanz.h"

FGraphicsObjectZentralBankBilanz::FGraphicsObjectZentralBankBilanz(QGraphicsItem *parent)
    : QGraphicsObject(parent){

    // allgemeine Daten
    FEinstellungen Einstellungen;
    AktuellerStiftFuerDenRand = Einstellungen.Pen_SchwarzerStift();
    AktuelleObjectFarbe       = Einstellungen.Object_Color();

    IdNummer = 6;
    }



//##################################################################################################################################


QRectF FGraphicsObjectZentralBankBilanz::boundingRect() const{
    return QRectF(0, 0, 2*330, 200);
    }


//###################################################################################################################################


void FGraphicsObjectZentralBankBilanz::Neu_zeichnen(FAlleDaten AlleDATEN){

    // Überprüfen, ob die Bilanzen gleichgroß sind.
    if( AlleDATEN.Zentralbank.Ist_die_Aktivsumme_gleich_der_Passivsumme() == false )
        qDebug() << "Fehler in der Bilanz der Zentralbankbank";


    // Werte übergeben und neu zeichnen
    AlleDaten = AlleDATEN;
    update();
    }



//###################################################################################################################################


void FGraphicsObjectZentralBankBilanz::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    //
    FEinstellungen Einstellungen;
    QColor Hellgrau         = Einstellungen.Hellgrau_Color();
    QPen PenSchwarzerStift  = Einstellungen.Pen_SchwarzerStift();
    QFont FontKlein         = Einstellungen.Font_Klein();
    QFont FontGross         = Einstellungen.Font_Gross();
    QColor SehrHellgrau     = Einstellungen.SehrHellgrau_Color();
    QColor SehrSehrHellgrau = Einstellungen.SehrSehrHellgrau_Color();

    int Hoehe = 200;
    int L = 330;


    // Rahmen um die Bilanz zeichnen
    painter->setPen(PenSchwarzerStift);
    painter->setBrush(Einstellungen.SehrSehrHellgrau_Color());
    painter->drawRect(0, 0, 2*L, Hoehe);


    // Hintergundschraffierung
    double HH = 33;
    double y0 = 60;
    double y1 = y0+HH;
    double y2 = y1+HH;
    double y3 = y2+HH;
    double y4 = y3+HH;

    painter->setPen(Qt::NoPen);
    painter->setBrush(SehrHellgrau);
    painter->drawRect(1, y0, 2*L, y1-y0);
    painter->setBrush(SehrHellgrau);
    painter->drawRect(2, y1, 2*L, y2-y1);
    painter->setBrush(SehrSehrHellgrau);
    painter->drawRect(2, y2, 2*L, y3-y2);
    painter->setBrush(SehrSehrHellgrau);
    painter->drawRect(2, y3, 2*L, y4-y3);
    painter->setPen(PenSchwarzerStift);



    // Überschrift zeichnen
    painter->setBrush(AktuelleObjectFarbe);
    painter->drawRect(0, 0, 2*L, 30);
    painter->setFont(FontGross);
    painter->drawText(245, 23, AlleDaten.Zentralbank.NameDerBank);


    // Linien
    painter->drawLine(L,  30,L,  Hoehe);     // Senkrecht
    painter->drawLine(0,  60,2*L,60   );     // Waagerecht
    painter->drawLine(2*L,0, 2*L,Hoehe);

    // Aktivseite.
    painter->setFont(FontGross);
    painter->drawText(110, 54, "A k t i v");
    painter->setFont(FontKlein);


    // Positionen zeichnen
    int xx1 = 15;
    int xx2 = 115;
    int xx3 = 215;


    painter->drawText(15, y0+4+18, "Forderungen an Banken:");

    Zeichne_Kasten_mit_Text(painter,
                            xx1+20, y1, xx1,
                            "X", AlleDaten.Zentralbank.ForderungAnBanken[0],
                            Hellgrau,
                            AlleDaten.Zentralbank.DickerRahmenForderungAnBanken[0]);

    Zeichne_Kasten_mit_Text(painter,
                            xx2+20, y1, xx2,
                            "Y", AlleDaten.Zentralbank.ForderungAnBanken[1],
                            Hellgrau,
                            AlleDaten.Zentralbank.DickerRahmenForderungAnBanken[1]);

    Zeichne_Kasten_mit_Text(painter,
                            xx3+20, y1, xx3,
                            "Z", AlleDaten.Zentralbank.ForderungAnBanken[2],
                            Hellgrau,
                            AlleDaten.Zentralbank.DickerRahmenForderungAnBanken[2]);

    painter->drawText(15, y2+4+18, "Staatsanleihen:");

    Zeichne_Kasten_mit_Text(painter,
                            xx1+20, y3, xx1,
                            "X", AlleDaten.Zentralbank.Staatsanleihen[0],
                            Hellgrau,
                            AlleDaten.Zentralbank.DickerRahmenStaatsanleihen[0]);

    Zeichne_Kasten_mit_Text(painter,
                            xx2+20, y3, xx2,
                            "Y", AlleDaten.Zentralbank.Staatsanleihen[1],
                            Hellgrau,
                            AlleDaten.Zentralbank.DickerRahmenStaatsanleihen[1]);


    // Passivseite.
    painter->setFont(FontGross);
    painter->drawText(L+110, 54, "P a s s i v");
    painter->setFont(FontKlein);


    // Positionen zeichnen
    int x3 = 525;
    int xx4 = L+15;
    int xx5 = L + 115;
    int xx6 = L + 215;


    painter->drawText(xx4, y0+4+18, "Z-Geld Guthaben von Banken:");

    Zeichne_Kasten_mit_Text(painter,
                            xx4+20, y1, xx4,
                            "X", AlleDaten.Zentralbank.ZGeldGuthabenVonBanken[0],
                            Hellgrau,
                            AlleDaten.Zentralbank.DickerRahmenZGeldGuthabenVonBanken[0]);

    Zeichne_Kasten_mit_Text(painter,
                            xx5+20, y1,xx5,
                            "Y", AlleDaten.Zentralbank.ZGeldGuthabenVonBanken[1],
                            Hellgrau,
                            AlleDaten.Zentralbank.DickerRahmenZGeldGuthabenVonBanken[1]);

    Zeichne_Kasten_mit_Text(painter,
                            xx6+20, y1, xx6,
                            "Z", AlleDaten.Zentralbank.ZGeldGuthabenVonBanken[2],
                            Hellgrau,
                            AlleDaten.Zentralbank.DickerRahmenZGeldGuthabenVonBanken[2]);

    painter->drawText(L+15, y2+4+18, "Bargeldumlauf:");
    Zeichne_Kasten(painter,
                   x3, y2+4,
                   AlleDaten.Zentralbank.Bargeldumlauf,
                   Hellgrau,
                   AlleDaten.Zentralbank.DickerRahmenBargeldumlauf);

    painter->drawText(L+15, y3+4+18, "Eigenkapital:");
    Zeichne_Kasten(painter,
                   x3, y3+4,
                   AlleDaten.Zentralbank.Eigenkapital,
                   Hellgrau,
                   AlleDaten.Zentralbank.DickerRahmenEigenkapital);
    }


//####################################################################################################################################


void FGraphicsObjectZentralBankBilanz::Zeichne_Kasten(QPainter* p,
                                                      float x, float y,
                                                      double Zahlenwert,
                                                      QColor Farbe,
                                                      bool fetterRahmen){

    // Stift
    FEinstellungen Einstel;
    if(fetterRahmen) p->setPen(Einstel.Pen_Dicker_SchwarzerStift());
    else             p->setPen(Einstel.Pen_SchwarzerStift());



    // Negative Werte als Warnung mit rot zeichnen.
    double Epsilon = 0.00001;
    if( Zahlenwert < -Epsilon ){
        p->setBrush(Qt::red);
        p->drawRect(x,   y, 70, 25);
        p->drawText(x+5, y+18, QString::number(Zahlenwert));
        }

    // Positive Werte mit der Farbe zeichnen.
    else if( Zahlenwert > Epsilon ){
        p->setBrush(Farbe);
        p->drawRect(x,   y, 70, 25);
        p->drawText(x+5, y+18, QString::number(Zahlenwert));
        }

    // Werte nahe 0 nur zeichnen, wenn der Rahmen fett ist.
    else{
        if(fetterRahmen){
            p->setBrush(Einstel.Hellgrau_Color());
            p->drawRect(x,   y, 70, 25);
            p->drawText(x+5, y+18, "");
            }
        }
    }


//####################################################################################################################################


void FGraphicsObjectZentralBankBilanz::Zeichne_Kasten_mit_Text(QPainter* p,
                                                               float x, float y, float xText,
                                                               QString Text,
                                                               double Zahlenwert,
                                                               QColor Farbe,
                                                               bool fetterRahmen){
    if(Zahlenwert > 0 || fetterRahmen == true){
        p->drawText(xText, y+18, Text);
        }

    Zeichne_Kasten(p, x, y, Zahlenwert, Farbe, fetterRahmen);
    }

//####################################################################################################################################


void FGraphicsObjectZentralBankBilanz::Set_Object_visual_marked(bool wert){
    FEinstellungen Einstellungen;
    if(wert == true){
        AktuellerStiftFuerDenRand = Einstellungen.Pen_Dicker_SchwarzerStift();
        AktuelleObjectFarbe       = Einstellungen.ObjectAktiv_Color();
        }
    else{
        AktuellerStiftFuerDenRand = Einstellungen.Pen_SchwarzerStift();
        AktuelleObjectFarbe       = Einstellungen.Object_Color();
        }
    update();
    }


//####################################################################################################################################


void FGraphicsObjectZentralBankBilanz::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    emit IdNummer_von_Zentralbank_wurde_gesendet(ZENTRALBANK, true);
    }








