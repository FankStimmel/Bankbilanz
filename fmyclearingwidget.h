#ifndef FMYCLEARINGWIDGET_H
#define FMYCLEARINGWIDGET_H

#include <QWidget>
#include "Bilanzen/fallebilanzen.h"



namespace Ui {
class FMyClearingWidget;
}



class FMyClearingWidget : public QWidget

{

    Q_OBJECT


public:
    explicit FMyClearingWidget(QWidget *parent = 0);
    ~FMyClearingWidget();

    // Daten
    double AToC,AToD,BToC,BToD,CToA,CToB,DToA,DToB;

    // Methoden
    void Ueberweisungsbetraege_eintragen(FAlleDaten AlleDaten);
    void paintEvent(QPaintEvent *event);


private:
    Ui::FMyClearingWidget *ui;

    void Zeichne_eine_Ueberweisungsposition(QPainter *painter, int y, QString von, QString nach, double Betrag, QString Richtung);
    double Runden_auf_Cent(double wert);


};

#endif // FMYCLEARINGWIDGET_H
