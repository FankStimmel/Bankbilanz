#include "faktioneinjahristvorbei.h"


FAktionEinJahrIstVorbei::FAktionEinJahrIstVorbei(){
    }



void FAktionEinJahrIstVorbei::Execute_on(FAlleDaten *AlleDaten){

    // Beschreibung der Operation
    BeschreibungDerOperation = ") Zinsen:  ";


    // Operation ausführen
    AlleDaten->Jahr +=1;



    // Zinssätze
    FEinstellungen Einstellungen;
    float GirokontenZinssatz = Einstellungen.GirokontoZinsen();
    float Leitzinssatz       = Einstellungen.LeitZins();
    float SparkontoZinssatz  = Einstellungen.SparkontoZinsen();
    float KreditZinssatz     = Einstellungen.KreditZinsen();



    // Zinsen auf Girokonten, Sparbücher und Kredite der Kunden berechnen und in der Geschäftsbankbilanz buchen.
    for (int BankNr = 0; BankNr < 2 ; BankNr++){
        for(int KundenNr = 0; KundenNr < 2; KundenNr++){
            double GiroKontenZinsen = GirokontenZinssatz * AlleDaten->Banken[BankNr].GiroKonten[KundenNr];
            double KreditZinsen     = KreditZinssatz     * AlleDaten->Banken[BankNr].KrediteVonKunden[KundenNr];
            double Sparbuchzinsen   = SparkontoZinssatz  * AlleDaten->Banken[BankNr].SparbuchKonten[KundenNr];


            if(GiroKontenZinsen > 0){
                // Zinsen
                AlleDaten->Banken[BankNr].Eigenkapital         -= GiroKontenZinsen;
                AlleDaten->Banken[BankNr].GiroKonten[KundenNr] += GiroKontenZinsen;

                // Beschreibung der Operation
                QString Zinsentext = "Giro " + AlleDaten->Kunden[2*BankNr+KundenNr].PersonenBuchstabe +
                                     " +" + Runden(GiroKontenZinsen) + "€  |  ";
                BeschreibungDerOperation += Zinsentext;
                }


            if(KreditZinsen > 0){
                // Zinsen
                AlleDaten->Banken[BankNr].Eigenkapital         += KreditZinsen;
                AlleDaten->Banken[BankNr].GiroKonten[KundenNr] -= KreditZinsen;

                // Beschreibung der Operation
                QString Zinsentext = "Giro " + AlleDaten->Kunden[2*BankNr+KundenNr].PersonenBuchstabe +
                                     " -" + Runden(KreditZinsen) + "€  |  ";
                BeschreibungDerOperation += Zinsentext;
                }


            if(Sparbuchzinsen > 0){
                // Zinsen von Sparbuch
                AlleDaten->Banken[BankNr].Eigenkapital             -= Sparbuchzinsen;
                AlleDaten->Banken[BankNr].SparbuchKonten[KundenNr] += Sparbuchzinsen;

                // Beschreibung der Operation
                QString Zinsentext = "Sparbuch " + AlleDaten->Kunden[2*BankNr+KundenNr].PersonenBuchstabe +
                                     " +" + Runden(Sparbuchzinsen) + "€  |  ";
                BeschreibungDerOperation += Zinsentext;
                }

            }
        }



    // Zinsen auf Staatsanleihen und Staatsgirokonto berechen und in der Geschäftsbankbilanz von Bank A buchen.
    // Bank B kann keine Staatsanleihen aufnehmen.
    double ZinsenAufStaatsanleihen  = KreditZinssatz     * AlleDaten->Staat.SchuldenAnBanken[0];
    double ZinsenAufStaatsgirokonto = GirokontenZinssatz * AlleDaten->Banken[0].StaatsGiroKonto;


    if(ZinsenAufStaatsanleihen > 0){
        // Zinsen auf Staatsanleihen
        AlleDaten->Banken[0].Eigenkapital    += ZinsenAufStaatsanleihen;
        AlleDaten->Banken[0].StaatsGiroKonto -= ZinsenAufStaatsanleihen;

        // Beschreibung der Operation
        BeschreibungDerOperation += "Staat -" + Runden(ZinsenAufStaatsanleihen) + "€  |  ";
        }


    if(ZinsenAufStaatsgirokonto > 0){
        // Zinsen aufs Staatsgirokonto
        AlleDaten->Banken[0].Eigenkapital    -= ZinsenAufStaatsgirokonto;
        AlleDaten->Banken[0].StaatsGiroKonto += ZinsenAufStaatsgirokonto;

        // Beschreibung der Operation
        BeschreibungDerOperation += "Staat +" + Runden(ZinsenAufStaatsgirokonto) + "€  |  ";
        }




    // Zinsen auf Zentralbankkredite gegen Banken berechen
    // Bei Bank C werden keine Zinsen fällig!
    for (int BankNr = 0; BankNr<2; BankNr++){
        double Zinsen = Leitzinssatz * AlleDaten->Zentralbank.ForderungAnBanken[BankNr];

        if(Zinsen > 0){
            // Zinsen in der Zentralbankbilanz buchen.
            AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[BankNr] -= Zinsen;
            AlleDaten->Zentralbank.Eigenkapital                   += Zinsen;

            // Zinsen in den Geschäftsbankbankbilanzen buchen.
            AlleDaten->Banken[BankNr].Eigenkapital            -= Zinsen;
            AlleDaten->Banken[BankNr].ZentralbankGeldguthaben -= Zinsen;

            // Beschreibung der Operation
            QString Zinsentext = AlleDaten->Banken[BankNr].NameDerBank +
                                 " -" + Runden(Zinsen) + "€  |  ";
            BeschreibungDerOperation += Zinsentext;
            }
        }



    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();
    }


//#######################################################################################################################


void FAktionEinJahrIstVorbei::Set_Dicke_Rahmen(FAlleDaten *AlleDaten, bool wert){

    // Rahmen auf Zinsfüsse die von Bankkrediten kommen.
    for(int BankNr=0; BankNr<2; BankNr++){
        for(int KundenNr=0; KundenNr<2;KundenNr++ ){
            if(AlleDaten->Banken[BankNr].KrediteVonKunden[KundenNr] > 0){
                    AlleDaten->Banken[BankNr].DickerRahmenGiroKonten[KundenNr] = wert;
                    AlleDaten->Banken[BankNr].DickerRahmenEigenkapital = wert;
                    }
            }
        }

    // Rahmen auf Zinsfüsse die von Sparkonten kommen.
    for(int BankNr=0; BankNr<2; BankNr++){
        for(int KundenNr=0; KundenNr<2;KundenNr++ ){
            if(AlleDaten->Banken[BankNr].SparbuchKonten[KundenNr]>0){
                AlleDaten->Banken[BankNr].DickerRahmenSparbuchKonten[KundenNr] = wert;
                AlleDaten->Banken[BankNr].DickerRahmenEigenkapital = wert;
                }
            }
        }

    // Rahmen auf Zinsfüsse die von Zentralbankkrediten kommen.
    for(int BankNr=0; BankNr<2; BankNr++ ){
        if(AlleDaten->Banken[BankNr].VerbindGegenZentralbank > 0){
                AlleDaten->Banken[BankNr].DickerRahmenZentralbankGeldguthaben = wert;
                AlleDaten->Banken[BankNr].DickerRahmenEigenkapital = wert;
                AlleDaten->Zentralbank.DickerRahmenEigenkapital = wert;
                AlleDaten->Zentralbank.DickerRahmenZGeldGuthabenVonBanken[BankNr] = wert;
                }
        }

    // Rahmen auf Zinsfüsse die von Staatsanleihen kommen
    for(int BankNr=0; BankNr<2; BankNr++ ){
        if(AlleDaten->Banken[BankNr].Staatsanleihen > 0){
            AlleDaten->Banken[BankNr].DickerRahmenStaatsGiroKonto = wert;
            AlleDaten->Banken[BankNr].DickerRahmenEigenkapital = wert;
            }
        }
    }


//#######################################################################################################################


QString FAktionEinJahrIstVorbei::Runden(double wert){
    return(QString::number(wert,'f',2));
    }




