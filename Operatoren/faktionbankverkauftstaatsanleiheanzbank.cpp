#include "faktionbankverkauftstaatsanleiheanzbank.h"


FAktionBankVerkauftStaatsanleiheAnZBank::FAktionBankVerkauftStaatsanleiheAnZBank(){
    }



FAktionBankVerkauftStaatsanleiheAnZBank::FAktionBankVerkauftStaatsanleiheAnZBank(double BETRAG, int BANKNR){
    Betrag = BETRAG;
    BankNr = BANKNR;

    }



void FAktionBankVerkauftStaatsanleiheAnZBank::Execute_on(FAlleDaten *AlleDaten){

    // Geschäftsbanken
    AlleDaten->Banken[BankNr].Staatsanleihen          -= Betrag;
    AlleDaten->Banken[BankNr].ZentralbankGeldguthaben += Betrag;

    // Zentralbank
    AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[BankNr] += Betrag;
    AlleDaten->Zentralbank.Staatsanleihen[BankNr]         += Betrag;


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung
    BeschreibungDerOperation = ") Die Bank hat Staatsanleihen an die Zentralbank verkauft.";
    }
