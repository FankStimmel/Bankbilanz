/*
 *  Wichtig:   Mit Synaptic das Paket 'unclutter' entfernen, damit der Mauszeiger nicht nach 1 Sekunde
 *             automatisch verschwindet und so unbeabsichtigt Signale auslöst.
 *
 */


#include "fmypushbutton.h"

//########################################################################################################


FMyPushButton::FMyPushButton(){
    }


FMyPushButton::FMyPushButton(QString Text, QWidget * parent) : QPushButton(parent){
    setText(Text);
    setFont(QFont ("System", 11,QFont::Normal));
    }


FMyPushButton::~FMyPushButton(){
    }


//########################################################################################################


void FMyPushButton::enterEvent ( QEvent * event ){
    // qDebug() << "Pushbutton " + text() + " enter";
    emit DickenRahmenZeichnen(true);
    emit EnterButton();
    event->accept();
    }

void FMyPushButton::leaveEvent ( QEvent * event ){
    // qDebug() <<"Pushbutton " + text() + " leave";
    emit DickenRahmenZeichnen(false);
    event->accept();
    }
