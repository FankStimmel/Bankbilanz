#include "faktionbankzahltbonian.h"


FAktionBankZahltBoniAn::FAktionBankZahltBoniAn(){
    }


FAktionBankZahltBoniAn::FAktionBankZahltBoniAn(double BETRAG, int BANKNR, int KUNDENNR){
    Betrag   = BETRAG;
    BankNr   = BANKNR;
    KundenNr = KUNDENNR;
    }


FAktionBankZahltBoniAn::~FAktionBankZahltBoniAn(){
    }


void FAktionBankZahltBoniAn::Execute_on(FAlleDaten *AlleDaten){
    AlleDaten->Banken[BankNr].Eigenkapital         -= Betrag;
    AlleDaten->Banken[BankNr].GiroKonten[KundenNr] += Betrag;

    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung
    BeschreibungDerOperation = ") Die Bank hat Boni an den Kunden gezahlt.";
    }
