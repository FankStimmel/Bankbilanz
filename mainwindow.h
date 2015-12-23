#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QThread>



#include "fmylabel.h"
#include "fmyclearingwidget.h"
#include "Viewport/fviewport.h"

#include "Bilanzen/fallebilanzen.h"

#include "Operatoren/faktioneinjahristvorbei.h"
#include "Operatoren/faktioninitialisiereallebilanzen.h"
#include "Operatoren/faktionresetallebilanzentonull.h"

#include "Operatoren/faktionbanknimmtkreditbeiderzbankauf.h"
#include "Operatoren/faktionbanklegteigenkapitalein.h"
#include "Operatoren/faktionbanktauschtbargeldinzentralbankgeld.h"
#include "Operatoren/faktionbanktauschtzentralbankgeldinbargeld.h"
#include "Operatoren/faktionbankzahltkreditbeiderzbankzurueck.h"
#include "Operatoren/faktionbankverkauftstaatsanleiheanzbank.h"
#include "Operatoren/faktionbankkauftwertpapiere.h"

#include "Operatoren/faktionkundenimmtkreditauf.h"
#include "Operatoren/faktionkundeuebergibtbargeldan.h"
#include "Operatoren/faktionkundezahltkreditzurueck.h"
#include "Operatoren/faktionkundehebtbargeldab.h"
#include "Operatoren/faktionkundeueberweistgiralgeldan.h"
#include "Operatoren/faktionkundezahltbargeldein.h"
#include "Operatoren/faktionkundezahltsparbuchgeldein.h"
#include "Operatoren/faktionkundehebtsparbuchgeldab.h"

#include "Operatoren/faktionstaatverkauftstaatsanleihen.h"
#include "Operatoren/faktionstaatkauftstaatsanleihen.h"
#include "Operatoren/faktionstaatueberweistgiralgeldan.h"

#include "Operatoren/faktionclearingverfahrenausfuehren.h"


typedef QVector <FFinanzTransaktion*> TypAllFinanzTransaktionen;



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow

{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



    //Daten
    TypAllFinanzTransaktionen StackOfOperations;
    FAlleDaten AlleDaten;
    QGraphicsScene *scene;
    FViewport *Viewport;
    FMyLabel *LabelObjektanzeige;
    FMyClearingWidget * ClearingWidget;
    QTimer *Tausend_Milli_Sekunden_Timer;

    // Daten für Aktuelle Werte in der GUI
    int AktOpGrenze;
    int AktBankNummer;
    int AktBankKundenNummer;
    int AktPersonenNr;
    int AktScreenShotNr;
    QString LastOp;




private:
    Ui::MainWindow *ui;

    // Methoden
    void Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(int n, bool wert);
    void Refresch_Gui_und_eventuell_Screenshot_erstellen(QString BeschreibungDerOperation);
    void Eventuell_ScreenShot_erstellen();


public slots:
    void Slot_Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE angeklicktesObjekt, bool LinksKlick);

    // Finanztransaktionen der Geschäftsbank
    void Slot_Bank_legt_Eigenkapital_ein();
    void Slot_Bank_nimmt_Kredit_bei_der_Zentralbank_auf();
    void Slot_Bank_zahlt_Kredit_an_die_Zentralbank_zurueck();
    void Slot_Bank_tauscht_Bargeld_in_Zentralbankgeldguthaben();
    void Slot_Bank_tauscht_Zentralbankgeldguthaben_in_Bargeld();
    void Slot_Bank_kauft_Wertpapiere_von();
    void Slot_Bank_verkauft_Staatsanleihen_an_die_ZBank();

    // Finanztransaktionen der Personen
    void Slot_Kunde_zahlt_Kredit_an_die_Bank_zurueck();
    void Slot_Kunde_nimmt_Kredit_bei_der_Bank_auf();
    void Slot_Kunde_ueberweist_Giralgeld_an_eine_andere_Bank();
    void Slot_Kunde_gibt_anderer_Person_Bargeld();
    void Slot_Kunde_hebt_Bargeld_bei_einer_Bank_ab();
    void Slot_Kunde_zahlt_Bargeld_bei_einer_Bank_ein();
    void Slot_Kunde_zahlt_Giralgeld_auf_sein_Sparkonto_ein();
    void Slot_Kunde_hebt_Geld_von_seinem_Sparkonto_ab();

    // Finanztransaktionen des Staates
    void Slot_Staat_verkauft_Staatsanleihen_an_die_Bank();
    void Slot_Staat_kauft_Staatsanleihen_von_der_Bank();
    void Slot_Staat_ueberweist_Giralgeld();

    // Sonstige Finanztransaktionen
    void Slot_Reset_alle_Bilanzen_to_Null();
    void Slot_Initialisiere_alle_Bilanzen();
    void Slot_Ein_Jahr_ist_vorbei();

    // Sonstige
    void Slot_Toggel_Zentralbankbilanz_sichtbar();
    void Slot_Wenn_Timer_aktiv_wird_das_hier_einmal_pro_Sekunde_ausgefuehrt();
    void Slot_Animate_last_Operation(bool wert);
    void Slot_Up();
    void Slot_Down();

    void Slot_Tagesabschluss_Clearingverfahrens_Daten_anzeigen();
    void Slot_Clearingverfahren_durchfuehren();


};

#endif // MAINWINDOW_H
