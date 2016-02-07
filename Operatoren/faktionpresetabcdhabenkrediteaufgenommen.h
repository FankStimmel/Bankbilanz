#ifndef FAKTIONPRESETABCDHABENKREDITEAUFGENOMMEN_H
#define FAKTIONPRESETABCDHABENKREDITEAUFGENOMMEN_H

#include <QDebug>
#include "Bilanzen/fallebilanzen.h"
#include "ffinanztransaktion.h"


class FAktionPresetABCDhabenKrediteAufgenommen : public FFinanzTransaktion

{

public:

    FAktionPresetABCDhabenKrediteAufgenommen();
    ~FAktionPresetABCDhabenKrediteAufgenommen();

    void Execute_on(FAlleDaten *AlleDaten);



};

#endif // FAKTIONPRESETABCDHABENKREDITEAUFGENOMMEN_H
