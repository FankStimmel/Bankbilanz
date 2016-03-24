#include "faktionkundeueberweistgiralgeldan.h"


FAktionKundeUeberweistGiralgeldAn::FAktionKundeUeberweistGiralgeldAn(){
    }


FAktionKundeUeberweistGiralgeldAn::FAktionKundeUeberweistGiralgeldAn(FGeld BETRAG,
                                                             int VONBANKNR, int NACHBANKNR,
                                                             int VONBANKKUNDENNR, int NACHBANKKUNDENNR){
    Betrag           = BETRAG;
    VonBankNr        = VONBANKNR;
    NachBankNr       = NACHBANKNR;
    VonBankKundenNr  = VONBANKKUNDENNR;
    NachBankKundenNr = NACHBANKKUNDENNR;
    }


void FAktionKundeUeberweistGiralgeldAn::Execute_on(FAlleDaten *AlleDaten){

    // Überweisung an sich selbst ausschließen.
    if((VonBankNr == NachBankNr)  &&  (VonBankKundenNr == NachBankKundenNr )){
        Fehlerbeschreibung = "Eine Ueberweisung an sich selbst gibt es nicht.";
        return;
        }


    // Der Fall, dass Giralgeld innerhalb einer Bank überwiesen wird.
    if(VonBankNr == NachBankNr){

        // Wenn zum Kunden überwiesen wird.
        if(NachBankKundenNr < 2){
            AlleDaten->Banken[VonBankNr].GiroKonten[VonBankKundenNr]  -= Betrag;
            AlleDaten->Banken[VonBankNr].GiroKonten[NachBankKundenNr] += Betrag;
            }

        // Wenn zum Staat überwiesen wird.
        if(NachBankKundenNr == 2){
            AlleDaten->Banken[VonBankNr].GiroKonten[VonBankKundenNr] -= Betrag;
            AlleDaten->Banken[VonBankNr].StaatsGiroKonto             += Betrag;
            }
        }


    // Der Fall, dass Giralgeld auf eine fremde Bank überwiesen wird.
    if(VonBankNr != NachBankNr){

        // von Bank.
        AlleDaten->Banken[VonBankNr].GiroKonten[VonBankKundenNr] -= Betrag;
        AlleDaten->Banken[VonBankNr].VerbindGegenAndereBank      += Betrag;

        // nach Bank.  Wenn zum Kunden überwiesen wird.
        if(NachBankKundenNr < 2){
            AlleDaten->Banken[NachBankNr].GiroKonten[NachBankKundenNr] += Betrag;
            AlleDaten->Banken[NachBankNr].KreditBeiAndererBank         += Betrag;
            }

        // nach Bank.  Wenn zum Staat überwiesen wird.
        if(NachBankKundenNr == 2){
            AlleDaten->Banken[NachBankNr].StaatsGiroKonto      += Betrag;
            AlleDaten->Banken[NachBankNr].KreditBeiAndererBank += Betrag;
            }

        }

    // Eventuell in der Bankbilanz VerbindlichkeitGegenAndereBank gegen KreditBeiAndererBank kürzen.
    for(int i=0; i<2; i++){

        FGeld Kre = AlleDaten->Banken[i].KreditBeiAndererBank;
        FGeld Ver = AlleDaten->Banken[i].VerbindGegenAndereBank;

        // Minimum rauskürzen
        FGeld Minimum("",std::min(Kre.Get_Euro(),Ver.Get_Euro()));
        if(Minimum.Get_Cents() > 0){
            AlleDaten->Banken[i].KreditBeiAndererBank   -= Minimum;
            AlleDaten->Banken[i].VerbindGegenAndereBank -= Minimum;
            }
        }


    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();


    // Beschreibung der Operation
    BeschreibungDerOperation = ") Kunde  hat  " + Betrag.Get_Euro_as_QString() + "  Euro Giralgeld überwiesen.";
    }


//####################################################################################################


void FAktionKundeUeberweistGiralgeldAn::DickenRahmen_zeichnen(FAlleDaten *AlleDaten, bool wert){

    // Wenn an den Staat überwiesen wird
    if(NachBankKundenNr == 2){
        AlleDaten->Banken[VonBankNr].DickerRahmenGiroKonten[VonBankKundenNr] = wert;
        AlleDaten->Banken[NachBankNr].DickerRahmenStaatsGiroKonto            = wert;
        }

    // sonst
    else{
        AlleDaten->Banken[VonBankNr].DickerRahmenGiroKonten[VonBankKundenNr]   = wert;
        AlleDaten->Banken[NachBankNr].DickerRahmenGiroKonten[NachBankKundenNr] = wert;
        }

    // bei Überweisungen auf fremde Banken
    if(VonBankNr != NachBankNr){
        AlleDaten->Banken[VonBankNr].DickerRahmenKreditBeiAndererBank    = wert;
        AlleDaten->Banken[VonBankNr].DickerRahmenVerbindGegenAndereBank  = wert;
        AlleDaten->Banken[NachBankNr].DickerRahmenKreditBeiAndererBank   = wert;
        AlleDaten->Banken[NachBankNr].DickerRahmenVerbindGegenAndereBank = wert;
        }


    }




