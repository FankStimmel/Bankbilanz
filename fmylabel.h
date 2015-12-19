#ifndef FMYLABEL_H
#define FMYLABEL_H


#include <QtGui>
#include <QObject>
#include <QLabel>
#include <QWidget>

#include "feinstellungen.h"


class FMyLabel : public QLabel

{
    Q_OBJECT

public:

    // Konstruktor
    FMyLabel();
    FMyLabel(BILANZOBJEKTE BilanzObjekt, QWidget * parent = 0);

    // Daten
    BILANZOBJEKTE MyBilanzObjekt;

    // Methoden
    void paintEvent(QPaintEvent *event);
    void setDaten(BILANZOBJEKTE BilanzObjekt);


};

#endif // FMYLABEL_H
