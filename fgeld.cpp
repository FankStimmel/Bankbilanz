#include "fgeld.h"


//###################################################################################################
//#  Konstruktor und Destruktor
//###################################################################################################


FGeld::FGeld(){
    Cents = 0;
    Name  = "";
    }


FGeld::FGeld(QString Text, double EuroBetrag){
    Cents = EuroBetrag * 100;
    Name  = Text;
    }


FGeld::~FGeld(){
    }


//###################################################################################################
//#  Getter
//###################################################################################################


int FGeld::Get_Cents(){
    return(Cents);
    }


double FGeld::Get_Euro(){
    return(0.01*Cents);
    }


QString FGeld::Get_Name(){
    return(Name);
    }


QString FGeld::Get_Cents_as_QString(){
    return(QString::number(Cents));
    }


QString FGeld::Get_Euro_as_QString(){
    double Euro = 0.01 * Cents;
    double AufGanzeEuroGerundet = round(Euro);

    // keine Nachkommastellen
    if(Euro == AufGanzeEuroGerundet)
        return(QString::number(Euro,'f',0));

    // mit Nachkommastellen
    else
        return(QString::number(Euro,'f',2));
    }


//###################################################################################################
//#  Operatoren
//###################################################################################################


FGeld operator + (const FGeld& left, const FGeld& right){
    int SummeInCents = left.Cents + right.Cents;
    FGeld Ausgabe("Summe",0.01*SummeInCents);
    return(Ausgabe);
    }


//###################################################################################################


FGeld operator - (const FGeld& left, const FGeld& right){
    int DifferenzInCents = left.Cents - right.Cents;
    FGeld Ausgabe("Differenz",0.01*DifferenzInCents);
    return(Ausgabe);
    }


//###################################################################################################


FGeld operator * (const double& left, const FGeld& right){
    int ProduktInCent = lround(left * right.Cents);
    FGeld Ausgabe("Produkt", 0.01*ProduktInCent);
    return(Ausgabe);
    }

//###################################################################################################


bool operator > (const FGeld& left, const FGeld& right){
    if(left.Cents > right.Cents)
        return (true);
    else
        return(false);
    }


//###################################################################################################


bool operator >= (const FGeld& left, const FGeld& right){
    if(left.Cents >= right.Cents)
        return (true);
    else
        return(false);
    }


//###################################################################################################


FGeld &FGeld::operator += (const FGeld &b){
    Cents = Cents + b.Cents;
    return *this;
    }


//###################################################################################################


FGeld &FGeld::operator -= (const FGeld &b){
    Cents = Cents - b.Cents;
    return *this;
    }

