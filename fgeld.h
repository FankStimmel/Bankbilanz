#ifndef FGELD_H
#define FGELD_H

#include <QtGui>

class FGeld

{

public:
    FGeld();
    FGeld(QString Text, double EuroBetrag);
    ~FGeld();


    // Getter
    int Get_Cents();
    double Get_Euro();
    QString Get_Name();
    QString Get_Cents_as_QString();
    QString Get_Euro_as_QString();


    // Operatoren as non-member Function
    friend FGeld operator +  (const FGeld  &left, const FGeld &right);
    friend FGeld operator -  (const FGeld  &left, const FGeld &right);
    friend FGeld operator *  (const double &left, const FGeld &right);
    friend bool  operator >  (const FGeld  &left, const FGeld &right);
    friend bool  operator >= (const FGeld  &left, const FGeld &right);

    // Operatoren as member Function
    FGeld &operator += (const FGeld &b);
    FGeld &operator -= (const FGeld &b);


private:
    int Cents;
    QString Name;

};

#endif // FGELD_H
