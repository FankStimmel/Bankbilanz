#include "fmyclearingwidget.h"
#include "ui_fmyclearingwidget.h"


FMyClearingWidget::FMyClearingWidget(QWidget *parent) :  QWidget(parent), ui(new Ui::FMyClearingWidget){
    ui->setupUi(this);
    update();
    }


FMyClearingWidget::~FMyClearingWidget(){
    delete ui;
    }


//###################################################################################################################################


void FMyClearingWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    FEinstellungen Einstellungen;
    painter.setPen(QPen(Qt::black, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.setBrush(Einstellungen.ObjectAktiv_Color());
    QFont MyFont("Times", 14);
    painter.setFont(MyFont);

    Zeichne_eine_Ueberweisungsposition(&painter, 60 + 0*40, "A", "C", AToC, "nachRechts");
    Zeichne_eine_Ueberweisungsposition(&painter, 60 + 1*40, "A", "D", AToD, "nachRechts");
    Zeichne_eine_Ueberweisungsposition(&painter, 60 + 2*40, "B", "C", BToC, "nachRechts");
    Zeichne_eine_Ueberweisungsposition(&painter, 60 + 3*40, "B", "D", BToD, "nachRechts");

    Zeichne_eine_Ueberweisungsposition(&painter, 60 + 4*40, "A", "C", CToA, "nachLinks");
    Zeichne_eine_Ueberweisungsposition(&painter, 60 + 5*40, "A", "D", DToA, "nachLinks");
    Zeichne_eine_Ueberweisungsposition(&painter, 60 + 6*40, "B", "C", CToB, "nachLinks");
    Zeichne_eine_Ueberweisungsposition(&painter, 60 + 7*40, "B", "D", DToB, "nachLinks");

    painter.drawText(10,390,"Differenzzahlung:");

    // Zahlungsdifferenz anzeigen
    FGeld VonBankA = AToC + AToD + BToC + BToD;
    FGeld VonBankB = CToA + CToB + DToA + DToB;
    if(VonBankA.Get_Euro() >= VonBankB.Get_Euro()){
        Zeichne_eine_Ueberweisungsposition(&painter, 420, "X", "Y", VonBankA - VonBankB, "nachRechts");
        }
    if(VonBankB.Get_Euro() > VonBankA.Get_Euro()){
        Zeichne_eine_Ueberweisungsposition(&painter, 420, "X", "Y", VonBankB - VonBankA, "nachLinks");
        }

    event->accept();
    }


//###################################################################################################################################


void FMyClearingWidget::Zeichne_eine_Ueberweisungsposition(QPainter *painter, int y, QString von, QString nach, FGeld Betrag, QString Richtung){
    int LinieXStart = 60;
    int LinieXEnd   = 200;
    painter->drawText(LinieXStart-35, y+5,von);
    painter->drawText(LinieXEnd+20,y+5,nach);
    painter->drawText(120, y-5,Betrag.Get_Euro_as_QString() + " €");
    painter->drawLine(LinieXStart, y,LinieXEnd,y);

    // Pfeile zeichnen
    if(Richtung == "nachRechts"){
        const QPointF points[4] = {
            QPointF(LinieXEnd+5, y),
            QPointF(LinieXEnd,   y+5),
            QPointF(LinieXEnd,   y-5),
            QPointF(LinieXEnd+5, y),
            };
        painter->drawPolyline(points, 4);
        }

    if(Richtung == "nachLinks"){
        const QPointF points[4] = {
            QPointF(LinieXStart-5, y),
            QPointF(LinieXStart,   y+5),
            QPointF(LinieXStart,   y-5),
            QPointF(LinieXStart-5, y),
            };
        painter->drawPolyline(points, 4);
        }
    }


//###################################################################################################################################


void FMyClearingWidget::Ueberweisungsbetraege_eintragen(FAlleDaten AlleDaten){

    // Zufallszahlen initialisieren.
    AToC = FGeld("",0.0);
    AToD = FGeld("",0.0);
    BToC = FGeld("",0.0);
    BToD = FGeld("",0.0);
    CToA = FGeld("",0.0);
    CToB = FGeld("",0.0);
    DToA = FGeld("",0.0);
    DToB = FGeld("",0.0);

    // Nur wenn auf dem Konto mehr als 10 Euro sind, können ausgehende Überweiseungen getätigt werden.
    if(AlleDaten.Banken[0].GiroKonten[0].Get_Euro() > 10 ){
        int MaxZufallsBetrag = 0.2 * AlleDaten.Banken[0].GiroKonten[0].Get_Euro();
        AToC = Zufallszahl_bis(MaxZufallsBetrag);
        AToD = Zufallszahl_bis(MaxZufallsBetrag);
        }

    if(AlleDaten.Banken[0].GiroKonten[1].Get_Euro() > 10 ){
        int MaxZufallsBetrag = 0.2 * AlleDaten.Banken[0].GiroKonten[1].Get_Euro();
        BToC = Zufallszahl_bis(MaxZufallsBetrag);
        BToD = Zufallszahl_bis(MaxZufallsBetrag);
        }

    if(AlleDaten.Banken[1].GiroKonten[0].Get_Euro() > 10 ){
        int MaxZufallsBetrag = 0.2 * AlleDaten.Banken[1].GiroKonten[0].Get_Euro();
        CToA = Zufallszahl_bis(MaxZufallsBetrag);
        CToB = Zufallszahl_bis(MaxZufallsBetrag);
        }

    if(AlleDaten.Banken[1].GiroKonten[1].Get_Euro() > 10 ){
        int MaxZufallsBetrag = 0.2 * AlleDaten.Banken[1].GiroKonten[1].Get_Euro();
        DToA = Zufallszahl_bis(MaxZufallsBetrag);
        DToB = Zufallszahl_bis(MaxZufallsBetrag);
        }

    update();
    }


//############################################################################################################


FGeld FMyClearingWidget::Zufallszahl_bis(int MaxZufallsBetrag){
    FGeld Betrag("",rand() %MaxZufallsBetrag);
    return(Betrag);
    }







