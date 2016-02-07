#ifndef FGRAPHICSOBJECTZENTRALBANKBILANZ_H
#define FGRAPHICSOBJECTZENTRALBANKBILANZ_H

#include <QtWidgets>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QDebug>
#include <QObject>
#include <QVector>

#include "feinstellungen.h"
#include "Bilanzen/fallebilanzen.h"


class QGraphicsSceneMouseEvent;


class FGraphicsObjectZentralBankBilanz : public QGraphicsObject

{

    Q_OBJECT

public:

    // Konstruktor
    FGraphicsObjectZentralBankBilanz(QGraphicsItem *parent = 0);


    // Methoden
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void Set_Object_visual_marked(bool wert);
    void Neu_zeichnen(FAlleDaten AlleDATEN);


    // allgemeine Daten
    int IdNummer;



 private:

    // Daten
    FAlleDaten AlleDaten;
    QColor Hintergundfarbe;
    QPen AktuellerStiftFuerDenRand;
    QColor AktuelleObjectFarbe;

    //Methoden
    void Zeichne_Kasten(QPainter* p,
                        float x, float y,
                        double Zahlenwert,
                        QColor Farbe,
                        bool fetterRahmen);

    void Zeichne_Kasten_mit_Text(QPainter* p,
                                 float x, float y, float xText,
                                 QString Text,
                                 double Zahlenwert,
                                 QColor Farbe,
                                 bool fetterRahmen);



 protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


 signals:
    void IdNummer_von_Zentralbank_wurde_gesendet(BILANZOBJEKTE BilanzObjekt, bool LinksKlick);



};

#endif // FGRAPHICSOBJECTZENTRALBANKBILANZ_H
