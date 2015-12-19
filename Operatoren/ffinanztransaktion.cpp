#include "ffinanztransaktion.h"


FFinanzTransaktion::FFinanzTransaktion(){
    }

FFinanzTransaktion::~FFinanzTransaktion(){
    }


//########################################################################################################


// Diese Methode wird überschrieben.
void FFinanzTransaktion::Execute_on(FAlleDaten *AlleDaten){
    qDebug() << "Fehler: Diese virtuelle Methode wurde nicht überschrieben!";
    }


