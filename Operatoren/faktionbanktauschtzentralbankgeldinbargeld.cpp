#include "faktionbanktauschtzentralbankgeldinbargeld.h"


FAktionBankTauschtZentralbankgeldInBargeld::FAktionBankTauschtZentralbankgeldInBargeld(){
    }


FAktionBankTauschtZentralbankgeldInBargeld::FAktionBankTauschtZentralbankgeldInBargeld(double BETRAG, int BANKNR){
    Betrag = BETRAG;
    BankNr = BANKNR;
    }


void FAktionBankTauschtZentralbankgeldInBargeld::Execute_on(FAlleDaten *AlleDaten){

    // Operation auf Z-Banken ausführen.
    AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[BankNr] -= Betrag;
    AlleDaten->Zentralbank.Bargeldumlauf                  += Betrag;


    // Operation auf Geschäftsbanken ausführen.Geschäftsbanken
    AlleDaten->Banken[BankNr].BarGeldDerBank          += Betrag;
    AlleDaten->Banken[BankNr].ZentralbankGeldguthaben -= Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Z-Bankgeld wurde in Bargeld umgewandelt.";
    }
