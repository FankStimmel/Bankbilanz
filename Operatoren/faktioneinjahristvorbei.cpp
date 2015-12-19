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
            double KreditZinsen     = KreditZinssatz     * AlleDaten->Banken[BankNr].Hypotheken[KundenNr];
            double Sparbuchzinsen   = SparkontoZinssatz  * AlleDaten->Banken[BankNr].SparbuchKonten[KundenNr];

            AlleDaten->Banken[BankNr].Eigenkapital             += KreditZinsen - GiroKontenZinsen - Sparbuchzinsen;
            AlleDaten->Banken[BankNr].GiroKonten[KundenNr]     += GiroKontenZinsen - KreditZinsen;
            AlleDaten->Banken[BankNr].SparbuchKonten[KundenNr] += Sparbuchzinsen;

            // Beschreibung der Operation
            if(GiroKontenZinsen > 0){
                QString Zinsentext = "Giro " + AlleDaten->Kunden[2*BankNr+KundenNr].PersonenBuchstabe +
                                     " +" + Runden(GiroKontenZinsen) + "€  |  ";
                BeschreibungDerOperation += Zinsentext;
                }

            // Beschreibung der Operation
            if(KreditZinsen > 0){
                QString Zinsentext = "Giro " + AlleDaten->Kunden[2*BankNr+KundenNr].PersonenBuchstabe +
                                     " -" + Runden(KreditZinsen) + "€  |  ";
                BeschreibungDerOperation += Zinsentext;
                }

            // Beschreibung der Operation
            if(Sparbuchzinsen > 0){
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

    AlleDaten->Banken[0].Eigenkapital    += ZinsenAufStaatsanleihen  - ZinsenAufStaatsgirokonto;
    AlleDaten->Banken[0].StaatsGiroKonto += ZinsenAufStaatsgirokonto - ZinsenAufStaatsanleihen;

    // Beschreibung der Operation
    if(ZinsenAufStaatsanleihen > 0){
        BeschreibungDerOperation += "Staat -" + Runden(ZinsenAufStaatsanleihen) + "€  |  ";
        }

    // Beschreibung der Operation
    if(ZinsenAufStaatsgirokonto > 0){
        BeschreibungDerOperation += "Staat +" + Runden(ZinsenAufStaatsgirokonto) + "€  |  ";
        }




    // Zinsen auf Zentralbankkredite gegen Banken berechen
    // Bei Bank C werden keine Zinsen fällig!
    for (int BankNr = 0; BankNr<2; BankNr++){
        double Zinsen = Leitzinssatz * AlleDaten->Zentralbank.ForderungAnBanken[BankNr];

        // Zinsen in der Zentralbankbilanz buchen.
        AlleDaten->Zentralbank.ZGeldGuthabenVonBanken[BankNr] -= Zinsen;
        AlleDaten->Zentralbank.Eigenkapital                   += Zinsen;

        // Zinsen in den Geschäftsbankbankbilanzen buchen.
        AlleDaten->Banken[BankNr].Eigenkapital            -= Zinsen;
        AlleDaten->Banken[BankNr].ZentralbankGeldguthaben -= Zinsen;

        // Beschreibung der Operation
        if(Zinsen > 0){
            QString Zinsentext = AlleDaten->Banken[BankNr].NameDerBank +
                                 " -" + Runden(Zinsen) + "€  |  ";
            BeschreibungDerOperation += Zinsentext;
            }
        }



    // Fehlermeldungen
    Fehlerbeschreibung = AlleDaten->Checken_ob_alle_Bilanzen_valide_sind_sonst_Fehlermeldung();
    }


//#######################################################################################################################


QString FAktionEinJahrIstVorbei::Runden(double wert){
    return(QString::number(wert,'f',2));
    }




