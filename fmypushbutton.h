#ifndef FMYPUSHBUTTON_H
#define FMYPUSHBUTTON_H

#include <QtGui>
#include <QObject>
#include <QPushButton>
#include <QWidget>

#include "feinstellungen.h"


class FMyPushButton: public QPushButton

{

    Q_OBJECT

public:
    FMyPushButton();
    FMyPushButton(QString Text, QWidget * parent = 0);
    ~FMyPushButton();


protected slots:
    virtual void enterEvent ( QEvent * event );
    virtual void leaveEvent ( QEvent * event );


signals:
    void DickenRahmenZeichnen(bool wert);
    void EnterButton();

};

#endif // FMYPUSHBUTTON_H
