#include "fgraphicsobjectzentralbankbilanz.h"

FGraphicsObjectZentralBankBilanz::FGraphicsObjectZentralBankBilanz(QGraphicsItem *parent)
    : QGraphicsObject(parent){

    // allgemeine Daten
    FEinstellungen Einstellungen;
    AktuellerStiftFuerDenRand = Einstellungen.Pen_SchwarzerStift();
    AktuelleObjectFarbe       = Einstellungen.Object_Color();

    IdNummer    = 6;
    }



//##################################################################################################################################


QRectF FGraphicsObjectZentralBankBilanz::boundingRect() const{
    return QRectF(0, -40, 2*280+55, 260);
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

    // Farben
    FEinstellungen Einstellungen;
    QColor Hellgrau       = Einstellungen.Hellgrau_Color();
    QColor SehrHellgrau   = Einstellungen.SehrHellgrau_Color();




    // Stifte
    QPen PenSchwarzerStift = Einstellungen.Pen_SchwarzerStift();


    // Schriftarten
    QFont FontKlein = Einstellungen.Font_Klein();
    QFont FontGross = Einstellungen.Font_Gross();

    int L = 280;


    // Rahmen um die Bilanz zeichnen
    painter->setPen(AktuellerStiftFuerDenRand);
    painter->setBrush(SehrHellgrau);
    painter->drawRect(0, -40, 2*L+55, 260);



    // Überschrift zeichnen
    painter->setPen(AktuellerStiftFuerDenRand);
    painter->setBrush(AktuelleObjectFarbe);
    painter->drawRect(0, -40, 2*L+55, 30);
    painter->setPen(PenSchwarzerStift);
    painter->setFont(FontGross);
    painter->drawText(245, -17, AlleDaten.Zentralbank.NameDerBank);


    // Trennlinien
    painter->drawLine(305,-10,305,220); // Senkrecht
    painter->drawLine(0,20,615,20);     // Waagerecht


    // Aktivseite.
    painter->setFont(FontGross);
    painter->drawText(60, 14, "A k t i v");
    painter->setFont(FontKlein);


    // Positionen zeichnen
    int y  = 30;
    int x2 = 210;
    float xText1 = 15;

    Zeichne_Kasten_in_der_Bilanz(painter, x2, 1*y+4, xText1,
                                 "Forderungen an Bank A", AlleDaten.Zentralbank.ForderungAnBanken[0],
                                  Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, x2, 2*y+4, xText1,
                                 "Forderungen an Bank B", AlleDaten.Zentralbank.ForderungAnBanken[1],
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, x2, 3*y+4, xText1,
                                 "Forderungen an Bank C", AlleDaten.Zentralbank.ForderungAnBanken[2],
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, x2, 4*y+4, xText1,
                                 "Staatsanleihen von Bank A", AlleDaten.Zentralbank.Staatsanleihen[0],
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, x2, 5*y+4, xText1,
                                 "Staatsanleihen von Bank B", AlleDaten.Zentralbank.Staatsanleihen[1],
                                 Hellgrau);


    // Passivseite.
    painter->setFont(FontGross);
    painter->drawText(L+70, 0*y+14, "P a s s i v");
    painter->setFont(FontKlein);


    // Positionen zeichnen
    int x3 = 525;
    float xText = 320;
    Zeichne_Kasten_in_der_Bilanz(painter, x3, 1*y+4, xText,
                                 "Z Geldguthaben von Bank A", AlleDaten.Zentralbank.ZGeldGuthabenVonBanken[0],
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, x3, 2*y+4, xText,
                                 "Z Geldguthaben von Bank B", AlleDaten.Zentralbank.ZGeldGuthabenVonBanken[1],
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, x3, 3*y+4, xText,
                                 "Z Geldguthaben von Bank C", AlleDaten.Zentralbank.ZGeldGuthabenVonBanken[2],
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, x3, 4*y+4, xText,
                                 "Bargeldumlauf",             AlleDaten.Zentralbank.Bargeldumlauf,
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, x3, 5*y+4, xText,
                                 "Eigenkapital",              AlleDaten.Zentralbank.Eigenkapital,
                                 Hellgrau);
    }


//####################################################################################################################################


void FGraphicsObjectZentralBankBilanz::Zeichne_Kasten_in_der_Bilanz(QPainter* p,
                                                                    float xKasten, float yKasten, float xText,
                                                                    QString Text,
                                                                    double Zahlenwert,
                                                                    QColor Farbe){

    // Beschriftung zeichnen
    p->drawText(xText, yKasten+18, Text);

    // Negative Werte als Warnung mit rot zeichnen.
    double Epsilon = 0.00001;
    if( Zahlenwert < -Epsilon ){
        p->setBrush(Qt::red);
        p->drawRect(xKasten,   yKasten, 70, 25);
        p->drawText(xKasten+5, yKasten+18, QString::number(Zahlenwert));
        }

    // Positive Werte mit der Farbe zeichnen.
    if( Zahlenwert > Epsilon ){
        p->setBrush(Farbe);
        p->drawRect(xKasten,   yKasten, 70, 25);
        p->drawText(xKasten+5, yKasten+18, QString::number(Zahlenwert));
        }
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








