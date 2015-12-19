#ifndef FVIEWPORT_H
#define FVIEWPORT_H

#include <QWidget>
#include <QtWidgets>
#include <QGraphicsObject>
#include <QPainter>
#include <QDebug>
#include <QObject>
#include <QVector>
#include <QGraphicsView>

#include "fgraphicsobjectzentralbankbilanz.h"
#include "fgraphicsobjectgeschaeftsbankbilanz.h"
#include "fgraphicsobjectperson.h"
#include "fgraphicsobjectstaat.h"



class FViewport : public QGraphicsView

{
    Q_OBJECT

public:

    // Konstruktor
    FViewport(QWidget *parent = 0);


    // Items
    FGraphicsObjectZentralBankBilanz *Zentralbankbilanz;
    QVector <FGraphicsObjectGeschaeftsBankbilanz*> AlleBanken;
    QVector <FGrapicsObjectPerson*> AllePersonen;
    FGraphicsObjectStaat *Staat;


    // Methoden
    void Alles_neu_zeichnen(FAlleDaten AlleDATEN);


    // Setter
    void Set_Zentralbankbilanz_sichtbar(bool sichtbar);



private:

    // Daten
    QGraphicsScene *scene;

    FAlleDaten AlleDaten;
    QTimer *Zehn_Milli_Sekunden_Timer;
    float Zeit;
    QPointF Flugstart;
    QPointF Flugziel;


public slots:
    void Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE BilanzObjekt, bool LinksKlick);


signals:
    void IdNummer_wurde_gesendet(BILANZOBJEKTE BilanzObjekt, bool LinksKlick);
    void Flug_ist_beendet();



};

#endif // FVIEWPORT_H
