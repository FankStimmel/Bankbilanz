#ifndef FAKTIONINITIALISIEREALLEBILANZEN_H
#define FAKTIONINITIALISIEREALLEBILANZEN_H

#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionInitialisiereAlleBilanzen : public FFinanzTransaktion

{

public:

    FAktionInitialisiereAlleBilanzen();

    void Execute_on(FAlleDaten *AlleDaten);




};

#endif
