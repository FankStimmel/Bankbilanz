#include "fgraphicsobjectgeschaeftsbankbilanz.h"

FGraphicsObjectGeschaeftsBankbilanz::FGraphicsObjectGeschaeftsBankbilanz(QGraphicsItem *parent)
    : QGraphicsObject(parent){

    // allgemeine Daten
    FEinstellungen Einstel;
    AktuellerStiftFuerDenRand = Einstel.Pen_SchwarzerStift();
    AktuelleObjectFarbe       = Einstel.Object_Color();


    }


FGraphicsObjectGeschaeftsBankbilanz::FGraphicsObjectGeschaeftsBankbilanz(float BANKNR, QGraphicsItem *parent)
    : QGraphicsObject(parent) {

    // allgemeine Daten
    FEinstellungen Einstel;
    BankNummer                = BANKNR;
    AktuellerStiftFuerDenRand = Einstel.Pen_SchwarzerStift();
    AktuelleObjectFarbe       = Einstel.Object_Color();
    }


//##################################################################################################################################


QRectF FGraphicsObjectGeschaeftsBankbilanz::boundingRect() const{
    return QRectF(0, -40, 415, 320);
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


//###################################################################################################################################


void FGraphicsObjectGeschaeftsBankbilanz::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *){

    // Farben
    FEinstellungen Einstel;

    QColor GiralgeldColor = Einstel.Giralgeld_Color();
    QColor BargeldColor   = Einstel.Bargeld_Color();
    QColor Hellgrau       = Einstel.Hellgrau_Color();
    QColor SehrHellgrau   = Einstel.SehrHellgrau_Color();


    // Stifte
    QPen PenSchwarzerStift       = Einstel.Pen_SchwarzerStift();


    // Schriftarten
    QFont FontKlein = Einstel.Font_Klein();
    QFont FontGross = Einstel.Font_Gross();


    // Rahmen um die Bilanz zeichnen
    painter->setPen(AktuellerStiftFuerDenRand);
    painter->setBrush(SehrHellgrau);
    painter->drawRect(0, -40, 415, 320);


    // Überschrift zeichnen
    painter->setPen(AktuellerStiftFuerDenRand);
    painter->setBrush(AktuelleObjectFarbe);
    painter->drawRect(0, -40, 415, 30);
    painter->setPen(PenSchwarzerStift);
    painter->setFont(FontGross);
    painter->drawText(165, -17, AlleDaten.Banken[BankNummer].NameDerBank);


    // Trennlinien
    painter->drawLine(205,-10,205,280); // Senkrecht
    painter->drawLine(0,20,415,20);     // Waagerecht



    // Aktivseite.
    painter->setFont(FontGross);
    painter->drawText(60, 14, "A k t i v");
    painter->setFont(FontKlein);


    int xKasten1 = 120;
    int y = 30;
    Zeichne_Kasten_in_der_Bilanz(painter, xKasten1, 1*y+4, 15,
                                 "Bargeld",        AlleDaten.Banken[BankNummer].BarGeldDerBank,
                                 BargeldColor);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten1, 2*y+4, 15,
                                 "Z-Geld",         AlleDaten.Banken[BankNummer].ZentralbankGeldguthaben,
                                 BargeldColor);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten1, 5*y+4, 15,
                                 "Kredit " + AlleDaten.Kunden[2*BankNummer+0].PersonenBuchstabe,
                                 AlleDaten.Banken[BankNummer].Hypotheken[0],
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten1, 6*y+4, 15,
                                 "Kredit " + AlleDaten.Kunden[2*BankNummer+1].PersonenBuchstabe,
                                 AlleDaten.Banken[BankNummer].Hypotheken[1],
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten1, 7*y+4, 15,
                                 "Staatsanleihen", AlleDaten.Banken[BankNummer].Staatsanleihen,
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten1, 8*y+4, 15,
                                 "Wertpapiere",    AlleDaten.Banken[BankNummer].Wertpapiere,
                                 Hellgrau);


    // Passivseite.
    painter->setFont(FontGross);
    painter->drawText(250, 14, "P a s s i v");
    painter->setFont(FontKlein);


    float xKasten = 325;
    float xText   = 220;
    Zeichne_Kasten_in_der_Bilanz(painter, xKasten, 2*y+4, xText,
                                 "Z-Bank-Verb", AlleDaten.Banken[BankNummer].VerbindGegenZentralbank,
                                 Hellgrau);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten, 3*y+4, xText,
                                 "Sparkonto " + AlleDaten.Kunden[2*BankNummer+0].PersonenBuchstabe,
                                 AlleDaten.Banken[BankNummer].SparbuchKonten[0],
                                 GiralgeldColor);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten, 4*y+4, xText,
                                 "Sparkonto " + AlleDaten.Kunden[2*BankNummer+1].PersonenBuchstabe,
                                 AlleDaten.Banken[BankNummer].SparbuchKonten[1],
                                 GiralgeldColor);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten, 5*y+4, xText,
                                 "Giro " + AlleDaten.Kunden[2*BankNummer+0].PersonenBuchstabe,
                                 AlleDaten.Banken[BankNummer].GiroKonten[0],
                                 GiralgeldColor);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten, 6*y+4, xText,
                                 "Giro " + AlleDaten.Kunden[2*BankNummer+1].PersonenBuchstabe,
                                 AlleDaten.Banken[BankNummer].GiroKonten[1],
                                 GiralgeldColor);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten, 7*y+4, xText,
                                 "Staat",  AlleDaten.Banken[BankNummer].StaatsGiroKonto,
                                 GiralgeldColor);

    Zeichne_Kasten_in_der_Bilanz(painter, xKasten, 8*y+4, xText,
                                 "Eigenkapital", AlleDaten.Banken[BankNummer].Eigenkapital,
                                 Hellgrau);
    }


//####################################################################################################################################


void FGraphicsObjectGeschaeftsBankbilanz::Zeichne_Kasten_in_der_Bilanz(QPainter* p,
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
        p->drawText(xKasten+5, yKasten+18, Runden(Zahlenwert));
        }

    // Positive Werte mit der Farbe zeichnen.
    if( Zahlenwert > Epsilon ){
        p->setBrush(Farbe);
        p->drawRect(xKasten,   yKasten, 70, 25);
        p->drawText(xKasten+5, yKasten+18, Runden(Zahlenwert));
        }
    }


//####################################################################################################################################


QString FGraphicsObjectGeschaeftsBankbilanz::Runden(double Wert){

    // Wenn es keine Nachkommastellen gibt, werden auch keine angezeigt.
    QString out;
    double Delta = fabs(Wert - floor(Wert));
    if( Delta < 0.0001){
        out = QString::number(Wert,'f',0);
        }

    // Wenn es Nachkommastellen gibt, auf zwei Stellen runden.
    else{
        out = QString::number(Wert,'f',2);
        }

    return(out);
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
        if(BankNummer == 0) emit IdNummer_von_Geschaeftsbank_wurde_gesendet(BANK_A, true);
        if(BankNummer == 1) emit IdNummer_von_Geschaeftsbank_wurde_gesendet(BANK_B, true);
        }

    else{
        if(BankNummer == 0) emit IdNummer_von_Geschaeftsbank_wurde_gesendet(BANK_A, false);
        if(BankNummer == 1) emit IdNummer_von_Geschaeftsbank_wurde_gesendet(BANK_B, false);
        }
    }








