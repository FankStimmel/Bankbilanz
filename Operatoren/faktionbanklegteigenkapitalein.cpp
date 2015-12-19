#include "faktionbanklegteigenkapitalein.h"


FAktionBankLegtEigenkapitalEin::FAktionBankLegtEigenkapitalEin(){
    }


FAktionBankLegtEigenkapitalEin::FAktionBankLegtEigenkapitalEin(float BETRAG, int BANKNR){
    Betrag       = BETRAG;
    BankNr       = BANKNR;
    }


void FAktionBankLegtEigenkapitalEin::Execute_on(FAlleDaten *AlleDaten){

    // Operation auf Geschäftsbanken ausführen.
    AlleDaten->Banken[BankNr].Eigenkapital   += Betrag;
    AlleDaten->Banken[BankNr].BarGeldDerBank += Betrag;

    // Operation auf Z-Banken ausführen.
    AlleDaten->Zentralbank.Bargeldumlauf        += Betrag;
    AlleDaten->Zentralbank.ForderungAnBanken[2] += Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung
    BeschreibungDerOperation =   ") Die "  + AlleDaten->Banken[BankNr].NameDerBank
                               + "  hat  " + QString::number(Betrag)
                               + "  Euro Eigenkapital eingelegt.";
    }
