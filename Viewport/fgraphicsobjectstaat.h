#ifndef FGRAPHICSOBJECTSTAAT_H
#define FGRAPHICSOBJECTSTAAT_H

#include <QtWidgets>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QPainter>
#include <QDebug>
#include <QObject>
#include "feinstellungen.h"
#include "Bilanzen/fallebilanzen.h"


class QGraphicsSceneMouseEvent;


class FGraphicsObjectStaat : public QGraphicsObject

{
     Q_OBJECT


public:
    FGraphicsObjectStaat(QGraphicsItem *parent = 0);
    FGraphicsObjectStaat(int IdNUMMER, QGraphicsItem *parent = 0);

    // Methoden
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void Set_Object_visual_marked(bool wert);
    void Neu_zeichnen(FAlleDaten AlleDATEN);


    // Daten
    int IdNummer;


private:

    // Daten
    FAlleDaten AlleDaten;
    QPen AktuellerStiftFuerDenRand;
    QColor AktuelleObjectFarbe;


    // Methoden
    void Zeichne_Kasten_in_der_Bilanz(QPainter* p,
                                      float xKasten, float yKasten, float xText,
                                      QString Text,
                                      double Zahlenwert,
                                      QColor Farbe);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


signals:
    void IdNummer_vom_Staat_wurde_gesendet(BILANZOBJEKTE BilanzObjekt, bool LinksKlick);


};

#endif // FGRAPHICSOBJECTSTAAT_H
