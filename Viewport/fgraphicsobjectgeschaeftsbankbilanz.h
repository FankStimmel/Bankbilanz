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
    void Set_Staat_hat_Konto_to(bool wert);
    QString Runden(double Wert);

    // Setter
    void Set_BankNr_To(int Nr);




private:

    // Daten
    QColor Hintergundfarbe;
    QPen AktuellerStiftFuerDenRand;
    QColor AktuelleObjectFarbe;
    FAlleDaten AlleDaten;
    bool StaatHatKonto;
    int BankNr;
    int AndereBankNr;


    // Methoden
    void Zeichne_Kasten(QPainter* p,
                        float x, float y,
                        double Zahlenwert,
                        QColor Farbe,
                        bool fetterRahmen);

    void Zeichne_Beschriftung_mit_Kasten(QPainter* p,
                                         int x, int y,
                                         double Zahlenwert,
                                         QColor Farbe,
                                         bool fetterRahmen,
                                         double xText, double yText,
                                         QString Text);



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


signals:
    void IdNummer_von_Geschaeftsbank_wurde_gesendet(BILANZOBJEKTE BilanzObjekt,bool LinksKlick);


};

#endif // FGRAPHICSOBJECTGESCHAEFTSBANKBILANZ_H
