#ifndef FMULTISTATEPUSHBUTTON_H
#define FMULTISTATEPUSHBUTTON_H

#include <QtGui>
#include <QObject>
#include <QPushButton>
#include <QWidget>


class FMultiStatePushButton : public QPushButton

{
    Q_OBJECT


public:
    FMultiStatePushButton();
    FMultiStatePushButton(QWidget * parent = 0);
    ~FMultiStatePushButton();


private:
    int Status;


private slots:
     void NaechsterStatus();

signals:
    void Neuer_Status_ist(int wert);


};

#endif // FMULTISTATEPUSHBUTTON_H
