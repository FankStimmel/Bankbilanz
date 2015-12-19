#ifndef FAKTIONRESETALLEBILANZENTONULL_H
#define FAKTIONRESETALLEBILANZENTONULL_H


#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionResetAlleBilanzenToNull : public FFinanzTransaktion

{

public:

    FAktionResetAlleBilanzenToNull();

    void Execute_on(FAlleDaten *AlleDaten);

};

#endif
