#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QMainWindow>
#include <QMessageBox>
#include <QVector>
#include <QEvent>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QThread>


#include "dialoginfo.h"
#include "fmylabel.h"
#include "fmypushbutton.h"
#include "fmultistatepushbutton.h"
#include "fmyclearingwidget.h"
#include "Viewport/fviewport.h"

#include "Bilanzen/fallebilanzen.h"

#include "Operatoren/faktioneinjahristvorbei.h"
#include "Operatoren/faktioninitialisiereallebilanzen.h"
#include "Operatoren/faktionresetallebilanzentonull.h"
#include "Operatoren/faktionpresetabcdhabenkrediteaufgenommen.h"

#include "Operatoren/faktionbanknimmtkreditbeiderzbankauf.h"
#include "Operatoren/faktionbankzahltkreditananderebankzurueck.h"
#include "Operatoren/faktionbanklegteigenkapitalein.h"
#include "Operatoren/faktionbanktauschtbargeldinzentralbankgeld.h"
#include "Operatoren/faktionbanktauschtzentralbankgeldinbargeld.h"
#include "Operatoren/faktionbankzahltkreditbeiderzbankzurueck.h"
#include "Operatoren/faktionbankverkauftstaatsanleiheanzbank.h"
#include "Operatoren/faktionbankkauftwertpapiere.h"
#include "Operatoren/faktionbankzahltbonian.h"

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



    // Daten
    TypAllFinanzTransaktionen StackOfOperations;
    FAlleDaten AlleDaten;
    QGraphicsScene *scene;
    FViewport *Viewport;
    FMyClearingWidget * ClearingWidget;
    QTimer *Tausend_Milli_Sekunden_Timer;

    // Label für das stacked Widget
    FMyLabel *LabelPersonen;
    FMyLabel *LabelBanken;
    FMyLabel *LabelZentralBanken;
    FMyLabel *LabelStaat;

    // Daten für Aktuelle Werte in der GUI
    int AktOpGrenze;
    int AktBankNummer;
    int AktBankKundenNummer;
    int AktPersonenNr;
    int AktScreenShotNr;
    QString LastOp;


protected:
    void resizeEvent(QResizeEvent *event);


private:
    Ui::MainWindow *ui;

    // Toolbar
    FMultiStatePushButton *MultiStatePushButton;
    QPushButton *PushButtonOperationUp;
    QPushButton *PushButtonOperationDown;
    FMyPushButton *PushButtonNeuesJahr;
    QPushButton *PushButtonInitialisiere;

    // Pushbuttons für Kundenaktionen
    FMyPushButton *PushButtonKundeNimmtKreditAuf;
    FMyPushButton *PushButtonKundeZahltKreditZurueck;
    FMyPushButton *PushButtonBargeldEinzahlen;
    FMyPushButton *PushButtonBargeldAuszahlen;
    FMyPushButton *PushButtonSparbuchgeldEinzahlen;
    FMyPushButton *PushButtonSparbuchgeldAuszahlen;
    FMyPushButton *PushButtonKundeUeberweistGiralgeld;
    FMyPushButton *PushButtonKundeUeberweistBargeld;

    // Pushbuttons für Bankaktionen
    FMyPushButton *PushButtonBankNimmtZKreditAuf;
    FMyPushButton *PushButtonBankZahltZKreditZurueck;
    FMyPushButton *PushButtonBankTauschtBargeldInZGeld;
    FMyPushButton *PushButtonBankTauschtZGeldInBargeld;
    FMyPushButton *PushButtonBankVerkauftStaatsanleihenAnZBank;
    FMyPushButton *PushButtonBankLegtEigenkapitalEin;
    FMyPushButton *PushButtonBankKaufWertpapiereAn;
    FMyPushButton *PushButtonBankZahltKreditAnAndereBankZurueck;
    FMyPushButton *PushButtonBankZahltBoniAn;

    //
    FMyPushButton *PushButtonBankFuehrtClearingverfahrenDurch;

    // Pushbuttons für Staatsaktionen
    FMyPushButton *PushButtonStaatVerkauftStaatsanleihenAnDieBank;
    FMyPushButton *PushButtonStaatKauftStaatsanleihenVonDerBank;
    FMyPushButton *PushButtonStaatUeberweistGiralgeldAnKunden;

    // Methoden
    void Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(int n, bool wert);
    void Refresch_Gui_und_eventuell_Screenshot_erstellen(QString BeschreibungDerOperation);
    void Eventuell_ScreenShot_erstellen();


public slots:

    // GUI
    void Slot_Zeige_InfoWidget();
    void Slot_Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE angeklicktesObjekt, bool LinksKlick);


    // Finanztransaktionen der Geschäftsbank
    void Slot_Bank_nimmt_Kredit_bei_der_Zentralbank_auf();
    void Slot_Bank_zahlt_Kredit_an_die_Zentralbank_zurueck();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_nimmt_ZKredit_auf_oder_zahlt_zurueck(bool wert);

    void Slot_Bank_bezahlt_mit_ZGeld_Kredit_an_andere_Bank_zurueck();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_bezahlt_mit_ZGeld_Kredit_an_andere_Bank_zurueck(bool wert);

    void Slot_Bank_tauscht_Bargeld_in_Zentralbankgeldguthaben();
    void Slot_Bank_tauscht_Zentralbankgeldguthaben_in_Bargeld();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_Bar_inZ_Bankgeld_oder_umgekehrt(bool wert);

    void Slot_Bank_kauft_Wertpapiere_von();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_kauft_Wertpapiere(bool wert);

    void Slot_Bank_verkauft_Staatsanleihen_an_die_ZBank();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_verkauft_Staatsanleihen_an_ZBank(bool wert);

    void Slot_Bank_legt_Eigenkapital_ein();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_legt_Eigenkapital_ein(bool wert);

    void Slot_Bank_zahlt_Boni_an_Kunden();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_zahlt_Boni_an_Kunden(bool wert);

    void Slot_Bank_fuehrt_Clearingverfahren_durch();
    void Slot_neue_Ueberweisungsbetraege_fuer_das_Clearingverfahren();
    void Slot_Widget_Clearingverfahren_anzeigen();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_fuehrt_Clearingverfahren_durch(bool wert);


    // Finanztransaktionen der Personen
    void Slot_Kunde_zahlt_Kredit_an_die_Bank_zurueck();
    void Slot_Kunde_nimmt_Kredit_bei_der_Bank_auf();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_nimmt_Kredit_auf_oder_zahlt_zurueck(bool wert);

    void Slot_Kunde_ueberweist_Giralgeld_an_eine_andere_Bank();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_ueberweiset_Giralgeld(bool wert);

    void Slot_Kunde_gibt_anderer_Person_Bargeld();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_ueberweiset_Bargeld(bool wert);

    void Slot_Kunde_hebt_Bargeld_bei_einer_Bank_ab();
    void Slot_Kunde_zahlt_Bargeld_bei_einer_Bank_ein();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_zahlt_Bargeld_ein_oder_aus(bool wert);

    void Slot_Kunde_zahlt_Giralgeld_auf_sein_Sparkonto_ein();
    void Slot_Kunde_hebt_Geld_von_seinem_Sparkonto_ab();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_zahlt_Sparbuchgeld_ein_oder_aus(bool wert);


    // Finanztransaktionen des Staates
    void Slot_Staat_verkauft_Staatsanleihen_an_die_Bank();
    void Slot_Staat_kauft_Staatsanleihen_von_der_Bank();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Staat_kauft_oder_verkauft_Staatsanleihen(bool wert);

    void Slot_Staat_ueberweist_Giralgeld();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_Staat_ueberweist_Giralgeld(bool wert);


    // Sonstige Finanztransaktionen
    void Slot_Reset_alle_Bilanzen_to_Null();
    void Slot_Initialisiere_alle_Bilanzen();
    void Slot_Ein_Jahr_ist_vorbei();
    void Slot_Rahmen_zeichnen_fuer_die_Aktion_ein_Jahr_ist_vorbei(bool wert);


    // Presets
    void Slot_Preset_ABCD_haben_Kredite_aufgenommen();
    void Slot_Preset_Der_Staat_verschuldet_sich_und_bezahlt_Buerger();


    // Sonstige
    void Slot_Toggel_Zentralbankbilanz_sichtbar();
    void Slot_Wenn_Timer_aktiv_wird_das_hier_einmal_pro_Sekunde_ausgefuehrt();
    void Slot_Animate_last_Operation(bool wert);
    void Slot_Up();
    void Slot_Down();


    // Einleitung in Programm
    void Slot_Einleitung(int Stufe);


};

#endif // MAINWINDOW_H
