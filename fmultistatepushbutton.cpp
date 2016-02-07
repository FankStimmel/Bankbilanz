#include "fmultistatepushbutton.h"


FMultiStatePushButton::FMultiStatePushButton(){
    setText("Der Fehler im Geldsystem");
    Status = 0;
    connect(this,SIGNAL(clicked()),this,SLOT(NaechsterStatus()));
    }

FMultiStatePushButton::FMultiStatePushButton(QWidget * parent) : QPushButton(parent){
    setText("Der Fehler im Geldsystem");
    Status = 0;
    connect(this,SIGNAL(clicked()),this,SLOT(NaechsterStatus()));
    }

FMultiStatePushButton::~FMultiStatePushButton(){
    }

//##################################################################################################


void FMultiStatePushButton::NaechsterStatus(){
    Status += 1;
    if(Status == 5) Status = 0;

    if(Status == 0) setText("Der Fehler im Geldsystem");
    if(Status == 1) setText("Der Fehler im Geldsystem (1. Schritt)");
    if(Status == 2) setText("Der Fehler im Geldsystem (2. Schritt)");
    if(Status == 3) setText("Der Fehler im Geldsystem (3. Schritt)");
    if(Status == 4) setText("Der Fehler im Geldsystem (Fazit)");

    emit Neuer_Status_ist(Status);
    }






