#include "faktionbanktauschtbargeldinzentralbankgeld.h"


FAktionBankTauschtBargeldInZentralbankgeld::FAktionBankTauschtBargeldInZentralbankgeld(){
    }



FAktionBankTauschtBargeldInZentralbankgeld::FAktionBankTauschtBargeldInZentralbankgeld(double BETRAG, int BANKNR){
    Betrag = BETRAG;
    BankNr = BANKNR;
    }


void FAktionBankTauschtBargeldInZentralbankgeld::Execute_on(FAlleDaten *AlleDaten){

    // Operation auf Geschäftsbanken ausführen.
    AlleDaten->Banken[BankNr].BarGeldDerBank          -= Betrag;
    AlleDaten->Banken[BankNr].ZentralbankGeldguthaben += Betrag;

    // Operation auf Z-Banken ausführen.in der Zentralbank
    AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[BankNr] += Betrag;
    AlleDaten->Zentralbank.Bargeldumlauf                  -= Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Bargeld wurde in Z-Bankgeld umgewandelt.";
    }
