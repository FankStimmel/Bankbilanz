#ifndef FGRAPHICSOBJECTGESCHAEFTSBANKBILANZ_H
#define FGRAPHICSOBJECTGESCHAEFTSBANKBILANZ_H

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


class FGraphicsObjectGeschaeftsBankbilanz : public QGraphicsObject

{

    Q_OBJECT

public:

    // Konstruktor
    FGraphicsObjectGeschaeftsBankbilanz(QGraphicsItem *parent = 0);
    FGraphicsObjectGeschaeftsBankbilanz(float BANKNR, QGraphicsItem *parent = 0);


    // Methoden
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void Set_Object_visual_marked(bool wert);
    void Neu_zeichnen(FAlleDaten AlleDATEN);
    QString Runden(double Wert);


    // allgemeine Daten
    int BankNummer;



private:

    // Daten
    QColor Hintergundfarbe;
    QPen AktuellerStiftFuerDenRand;
    QColor AktuelleObjectFarbe;
    FAlleDaten AlleDaten;

    // Methoden
    void Zeichne_Kasten_in_der_Bilanz(QPainter* p,
                                      float xKasten, float yKasten,
                                      float xText,
                                      QString Text,
                                      double Zahlenwert,
                                      QColor Farbe);



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


signals:
    void IdNummer_von_Geschaeftsbank_wurde_gesendet(BILANZOBJEKTE BilanzObjekt,bool LinksKlick);


};

#endif // FGRAPHICSOBJECTGESCHAEFTSBANKBILANZ_H
