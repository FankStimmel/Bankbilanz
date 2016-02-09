#include "fgraphicsobjectgeschaeftsbankbilanz.h"

FGraphicsObjectGeschaeftsBankbilanz::FGraphicsObjectGeschaeftsBankbilanz(QGraphicsItem *parent)
    : QGraphicsObject(parent){

    // allgemeine Daten
    FEinstellungen Einstel;
    AktuellerStiftFuerDenRand = Einstel.Pen_SchwarzerStift();
    AktuelleObjectFarbe       = Einstel.Object_Color();
    StaatHatKonto             = true;
    }


FGraphicsObjectGeschaeftsBankbilanz::FGraphicsObjectGeschaeftsBankbilanz(float BANKNR, QGraphicsItem *parent)
    : QGraphicsObject(parent) {

    // allgemeine Daten
    FEinstellungen Einstel;
    BankNr                    = BANKNR;
    AktuellerStiftFuerDenRand = Einstel.Pen_SchwarzerStift();
    AktuelleObjectFarbe       = Einstel.Object_Color();
    StaatHatKonto             = true;
    }


//##################################################################################################################################


QRectF FGraphicsObjectGeschaeftsBankbilanz::boundingRect() const{
    return QRectF(0, 0, 416, 360);
    }


//###################################################################################################################################


void FGraphicsObjectGeschaeftsBankbilanz::Set_BankNr_To(int Nr){
    BankNr = Nr;
    if(BankNr == 0) AndereBankNr = 1;
    if(BankNr == 1) AndereBankNr = 0;
    }


//###################################################################################################################################


void FGraphicsObjectGeschaeftsBankbilanz::Neu_zeichnen(FAlleDaten AlleDATEN){

    // Überprüfen, ob die Bilanzen gleichgroß sind.
    if( AlleDATEN.Banken[0].Ist_die_Aktivsumme_gleich_der_Passivsumme() == false )
        qDebug() << "Fehler in der Bilanz von Geschäftsbank A";

    if( AlleDATEN.Banken[1].Ist_die_Aktivsumme_gleich_der_Passivsumme() == false )
        qDebug() << "Fehler in der Bilanz von Geschäftsbank B";

    // Werte übergeben und neu zeichnen
    AlleDaten = AlleDATEN;
    update();
    }

//########################################################################################################


void FGraphicsObjectGeschaeftsBankbilanz::Set_Staat_hat_Konto_to(bool wert){
    StaatHatKonto = wert;
    }


//###################################################################################################################################


void FGraphicsObjectGeschaeftsBankbilanz::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    // Farben
    FEinstellungen Einstel;

    QColor GiralgeldColor = Einstel.Giralgeld_Color();
    QColor BargeldColor   = Einstel.Bargeld_Color();
    QColor Hellgrau       = Einstel.Hellgrau_Color();
    QColor SehrHellgrau   = Einstel.SehrHellgrau_Color();
    QColor SehrSehrHellgrau   = Einstel.SehrSehrHellgrau_Color();

    // Stifte
    QPen PenSchwarzerStift = Einstel.Pen_SchwarzerStift();


    // Schriftarten
    QFont FontKlein = Einstel.Font_Klein();
    QFont FontGross = Einstel.Font_Gross();

    int HalbeWeite = 208;
    int Hoehe = 360;


    // Rahmen um die Bilanz zeichnen
    painter->setBrush(SehrSehrHellgrau);
    painter->drawRect(0, 0, 2*HalbeWeite, Hoehe);


    // Hintergundschraffierung
    double HH = 33;
    double y0 = 60;
    double y1 = y0+HH;
    double y2 = y1+HH;
    double y3 = y2+HH;
    double y4 = y3+2*HH;
    double y5 = y4+2*HH;
    double y6 = y5+HH;
    double y7 = y6+HH;

    painter->setPen(Qt::NoPen);
    painter->setBrush(SehrSehrHellgrau);
    painter->drawRect(0, y0, 2*HalbeWeite, y1-y0);
    painter->setBrush(SehrHellgrau);
    painter->drawRect(0, y1, 2*HalbeWeite, y2-y1);
    painter->setBrush(SehrSehrHellgrau);
    painter->drawRect(0, y2, 2*HalbeWeite, y3-y2);
    painter->setBrush(SehrSehrHellgrau);
    painter->drawRect(0, y3, 2*HalbeWeite, y4-y3);
    painter->setBrush(SehrHellgrau);
    painter->drawRect(0, y4, 2*HalbeWeite, y5-y4);
    painter->setBrush(SehrSehrHellgrau);
    painter->drawRect(0, y5, 2*HalbeWeite, y6-y5);
    painter->setBrush(SehrHellgrau);
    painter->drawRect(0, y6, 2*HalbeWeite, y7-y6);

    painter->setPen(PenSchwarzerStift);
    painter->setBrush(SehrHellgrau);


    // Überschrift zeichnen
    painter->setBrush(AktuelleObjectFarbe);
    painter->drawRect(0, 0, 2*HalbeWeite, 30);
    painter->setFont(FontGross);
    painter->drawText(165, 23, AlleDaten.Banken[BankNr].NameDerBank);


    // Trennlinien
    painter->drawLine(HalbeWeite,   30, HalbeWeite,   Hoehe);     // Senkrecht
    painter->drawLine(0,            60, 2*HalbeWeite, 60   );     // Waagerecht
    painter->drawLine(2*HalbeWeite, 30, 2*HalbeWeite, Hoehe);
    painter->drawLine(0,            30, 0,            Hoehe);


    // Aktivseite.
    painter->setFont(FontGross);
    painter->drawText(60, 54, "A k t i v");
    painter->setFont(FontKlein);


    int xKasten1 = 130;
    painter->drawText(15, y0+4+18, "Bargeld:");
    Zeichne_Kasten(painter,
                   xKasten1, y0+4,
                   AlleDaten.Banken[BankNr].BarGeldDerBank,
                   BargeldColor,
                   AlleDaten.Banken[BankNr].DickerRahmenBarGeldDerBank);

    painter->drawText(15, y1+4+18, "Z-Geld:");
    Zeichne_Kasten(painter,
                   xKasten1, y1+4,
                   AlleDaten.Banken[BankNr].ZentralbankGeldguthaben,
                   BargeldColor,
                   AlleDaten.Banken[BankNr].DickerRahmenZentralbankGeldguthaben);

    painter->drawText(15, y2+18,"Kreditforderungen an:" );

    Zeichne_Beschriftung_mit_Kasten(painter,
                                    35, y3-2,
                                    AlleDaten.Banken[BankNr].KreditBeiAndererBank,
                                    Hellgrau,
                                    AlleDaten.Banken[BankNr].DickerRahmenKreditBeiAndererBank,
                                    15,y2+HH-2,
                                    AlleDaten.Banken[AndereBankNr].BankBuchstabe);


    Zeichne_Beschriftung_mit_Kasten(painter,
                                    35,y3+HH-2,
                                    AlleDaten.Banken[BankNr].KrediteVonKunden[0],
                                    Hellgrau,
                                    AlleDaten.Banken[BankNr].DickerRahmenHypotheken[0],
                                    15,y3+HH-2,
                                    AlleDaten.Kunden[2*BankNr+0].PersonenBuchstabe);


    Zeichne_Beschriftung_mit_Kasten(painter,
                                    130,y3+HH-2,
                                    AlleDaten.Banken[BankNr].KrediteVonKunden[1],
                                    Hellgrau,
                                    AlleDaten.Banken[BankNr].DickerRahmenHypotheken[1],
                                    110,y3+HH-2,
                                    AlleDaten.Kunden[2*BankNr+1].PersonenBuchstabe);


    if(StaatHatKonto == true){
        painter->drawText(15, y5+4+18,"Staatsanleihen:");
        Zeichne_Kasten(painter,
                       xKasten1, y5+4,
                       AlleDaten.Banken[BankNr].Staatsanleihen,
                       Hellgrau,
                       AlleDaten.Banken[BankNr].DickerRahmenStaatsanleihen);
        }

    painter->drawText(15, y6+4+18, "Wertpapiere:");
    Zeichne_Kasten(painter,
                   xKasten1, y6+4,
                   AlleDaten.Banken[BankNr].Wertpapiere,
                   Hellgrau,
                   AlleDaten.Banken[BankNr].DickerRahmenWertpapiere);


    // Passivseite.
    painter->setFont(FontGross);
    painter->drawText(250, 54, "P a s s i v");
    painter->setFont(FontKlein);


    float xKasten = 330;
    float xText   = 220;

    painter->drawText(220, y1+4+18, "Z-Bank-Verb:");
    Zeichne_Kasten(painter,
                   xKasten, y1+4,
                   AlleDaten.Banken[BankNr].VerbindGegenZentralbank,
                   Hellgrau,
                   AlleDaten.Banken[BankNr].DickerRahmenVerbindGegenZentralbank);

    painter->drawText(xText, y2+18,"Verbindlichkeiten gegen:" );


    Zeichne_Beschriftung_mit_Kasten(painter,
                                    240, y3-2,
                                    AlleDaten.Banken[BankNr].VerbindGegenAndereBank,
                                    Hellgrau,
                                    AlleDaten.Banken[BankNr].DickerRahmenVerbindGegenAndereBank,
                                    220,y3-2,
                                    AlleDaten.Banken[AndereBankNr].BankBuchstabe);

    Zeichne_Beschriftung_mit_Kasten(painter,
                                    240,y3+HH-2,
                                    AlleDaten.Banken[BankNr].GiroKonten[0],
                                    GiralgeldColor,
                                    AlleDaten.Banken[BankNr].DickerRahmenGiroKonten[0],
                                    220,y3+HH-2,
                                    AlleDaten.Kunden[2*BankNr+0].PersonenBuchstabe);


    Zeichne_Beschriftung_mit_Kasten(painter,
                                    330,y3+HH-2,
                                    AlleDaten.Banken[BankNr].GiroKonten[1],
                                    GiralgeldColor,
                                    AlleDaten.Banken[BankNr].DickerRahmenGiroKonten[1],
                                    310,y3+HH-2,
                                    AlleDaten.Kunden[2*BankNr+1].PersonenBuchstabe);

    painter->drawText(xText, y4+18,"Sparkonten:" );

    Zeichne_Beschriftung_mit_Kasten(painter,
                                    240,y4+HH-2,
                                    AlleDaten.Banken[BankNr].SparbuchKonten[0],
                                    GiralgeldColor,
                                    AlleDaten.Banken[BankNr].DickerRahmenSparbuchKonten[0],
                                    220,y4+HH-2,
                                    AlleDaten.Kunden[2*BankNr+0].PersonenBuchstabe);


    Zeichne_Beschriftung_mit_Kasten(painter,
                                    330,y4+HH-2,
                                    AlleDaten.Banken[BankNr].SparbuchKonten[1],
                                    GiralgeldColor,
                                    AlleDaten.Banken[BankNr].DickerRahmenSparbuchKonten[1],
                                    310,y4+HH-2,
                                    AlleDaten.Kunden[2*BankNr+1].PersonenBuchstabe);

     if(StaatHatKonto == true){
        painter->drawText(220, y5+4+18, "Staat:");
        Zeichne_Kasten(painter,
                       xKasten, y5+4,
                       AlleDaten.Banken[BankNr].StaatsGiroKonto,
                       GiralgeldColor,
                       AlleDaten.Banken[BankNr].DickerRahmenStaatsGiroKonto);
        }

    painter->drawText(220, y6+4+18, "Eigenkapital:");
    Zeichne_Kasten(painter,
                   xKasten, y6+4,
                   AlleDaten.Banken[BankNr].Eigenkapital,
                   Hellgrau,
                   AlleDaten.Banken[BankNr].DickerRahmenEigenkapital);
    }


//####################################################################################################################################


void FGraphicsObjectGeschaeftsBankbilanz::Zeichne_Kasten(QPainter* p,
                                                         float x, float y,
                                                         double Zahlenwert,
                                                         QColor Farbe,
                                                         bool fetterRahmen){
    // Stift
    FEinstellungen Einstel;
    double Epsilon = 0.00001;


    // Negative Werte als Warnung mit rotem Hintergrund zeichnen.
    if( Zahlenwert < -Epsilon ){
        p->setBrush(Qt::red);
        p->setPen(Einstel.Pen_SchwarzerStift());
        p->drawRect(x,   y, 60, 25);
        p->drawText(x+5, y+18, QString::number(Zahlenwert));
        }


    // Positive Werte mit der Farbe zeichnen.
    else if( Zahlenwert > Epsilon ){

        // Rahmen
        if(fetterRahmen)  p->setPen(Einstel.Pen_Dicker_RoterStift());
        else              p->setPen(Einstel.Pen_SchwarzerStift());

        p->setBrush(Farbe);
        p->drawRect(x, y, 60, 25);

        // Zahlentext
        p->setPen(Einstel.Pen_SchwarzerStift());
        p->setBrush(Farbe);
        p->drawText(x+5, y+18, QString::number(Zahlenwert));
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


void FGraphicsObjectGeschaeftsBankbilanz::Zeichne_Beschriftung_mit_Kasten(QPainter* p,
                                                                          int x, int y,
                                                                          double Zahlenwert,
                                                                          QColor Farbe,
                                                                          bool fetterRahmen,
                                                                          double xText, double yText,
                                                                          QString Text){

    FEinstellungen Einstel;

    Zeichne_Kasten(p, x, y, Zahlenwert, Farbe, fetterRahmen);

    double Epsilon = 0.00001;
    if(Zahlenwert > Epsilon || fetterRahmen == true){
        p->setPen(Einstel.Pen_SchwarzerStift());
        p->drawText(xText, yText+18, Text);
        }
    }


//####################################################################################################################################


void FGraphicsObjectGeschaeftsBankbilanz::Set_Object_visual_marked(bool wert){
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


void FGraphicsObjectGeschaeftsBankbilanz::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);

    if (event->button() == Qt::LeftButton){
        if(BankNr == 0) emit IdNummer_von_Geschaeftsbank_wurde_gesendet(BANK_X, true);
        if(BankNr == 1) emit IdNummer_von_Geschaeftsbank_wurde_gesendet(BANK_Y, true);
        }

    else{
        if(BankNr == 0) emit IdNummer_von_Geschaeftsbank_wurde_gesendet(BANK_X, false);
        if(BankNr == 1) emit IdNummer_von_Geschaeftsbank_wurde_gesendet(BANK_Y, false);
        }
    }








