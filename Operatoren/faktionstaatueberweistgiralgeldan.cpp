#include "faktionstaatueberweistgiralgeldan.h"


FAktionStaatUeberweistGiralgeldAn::FAktionStaatUeberweistGiralgeldAn(){
    }


FAktionStaatUeberweistGiralgeldAn::FAktionStaatUeberweistGiralgeldAn(FGeld BETRAG, int NACHBANKNR, int NACHBANKKUNDENNR){
    Betrag           = BETRAG;
    NachBankNr       = NACHBANKNR;
    NachBankKundenNr = NACHBANKKUNDENNR;
    }


void FAktionStaatUeberweistGiralgeldAn::Execute_on(FAlleDaten *AlleDaten){

    // Der Fall, dass Giralgeld innerhalb einer Bank überwiesen wird.
    if(NachBankNr == 0){
        AlleDaten->Banken[0].GiroKonten[NachBankKundenNr] += Betrag;
        AlleDaten->Banken[0].StaatsGiroKonto              -= Betrag;
        }


    // Der Fall, dass Giralgeld auf eine fremde Bank überwiesen wird.
    if(NachBankNr == 1){

        // von Bank.
        AlleDaten->Banken[0].StaatsGiroKonto        -= Betrag;
        AlleDaten->Banken[0].VerbindGegenAndereBank += Betrag;

        // nach Bank.
        AlleDaten->Banken[1].GiroKonten[NachBankKundenNr] += Betrag;
        AlleDaten->Banken[1].KreditBeiAndererBank         += Betrag;
        }


    // Eventuell in der Bankbilanz VerbindlichkeitGegenAndereBank gegen KreditBeiAndererBank kürzen.
    for(int i=0; i<2; i++){

        FGeld Kre = AlleDaten->Banken[i].KreditBeiAndererBank;
        FGeld Ver = AlleDaten->Banken[i].VerbindGegenAndereBank;

        // Minimum rauskürzen
        double Minimum = std::min(Kre.Get_Euro(),Ver.Get_Euro());
        if(Minimum > 0){
            AlleDaten->Banken[i].KreditBeiAndererBank   -= FGeld("",Minimum);
            AlleDaten->Banken[i].VerbindGegenAndereBank -= FGeld("",Minimum);
            }
        }


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Kunde  hat  " + Betrag.Get_Euro_as_QString() + "  Euro Giralgeld überwiesen.";
    }


void FAktionStaatUeberweistGiralgeldAn::Dicke_Rahmen_zeichnen(FAlleDaten *AlleDaten, bool wert){
    AlleDaten->Banken[0].DickerRahmenStaatsGiroKonto = wert;

    // Bank interne Überweisung
    if(NachBankNr == 0){
        AlleDaten->Banken[0].DickerRahmenGiroKonten[NachBankKundenNr] = wert;
        }

    // Bank externe Überweisung
    if(NachBankNr == 1){
        AlleDaten->Banken[1].DickerRahmenGiroKonten[NachBankKundenNr] = wert;
        AlleDaten->Banken[0].DickerRahmenVerbindGegenAndereBank = wert;
        AlleDaten->Banken[1].DickerRahmenKreditBeiAndererBank   = wert;
        }
    }


