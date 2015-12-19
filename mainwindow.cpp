#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    // Bilder auf Buttons setzen.
    FEinstellungen Einstellungen;
    QString PfadZuDenIcons = Einstellungen.Pfad_zu_den_Icons();
    ui->pushButtonMaxHistoryGrenzeUp->setIcon(QIcon(PfadZuDenIcons   + "Up.png"));
    ui->pushButtonMaxHistoryGrenzeDown->setIcon(QIcon(PfadZuDenIcons + "Down.png"));
    ui->pushButtonMaxHistoryGrenzeUp->setIconSize(QSize(21,21));
    ui->pushButtonMaxHistoryGrenzeDown->setIconSize(QSize(21,21));



    // Zeitbasis
    Tausend_Milli_Sekunden_Timer = new QTimer(this);
    Tausend_Milli_Sekunden_Timer->stop();

    connect(Tausend_Milli_Sekunden_Timer,
            SIGNAL(timeout()),
            this,
            SLOT(Slot_Wenn_Timer_aktiv_wird_das_hier_einmal_pro_Sekunde_ausgefuehrt()));



    // Werte initialisieren
    ui->stackedWidget->setCurrentIndex(0);
    AktBankNummer       = 0;
    AktBankKundenNummer = 0;
    AktPersonenNr       = 0;
    AktScreenShotNr     = 0;
    AktOpGrenze         = 0;



    // eigener Viewport
    Viewport = new FViewport(this);
    Viewport->setGeometry(10,50,980,780);


    // Label für die Objektanzeige
    LabelObjektanzeige = new FMyLabel(PERSON_A, ui->stackedWidget);
    LabelObjektanzeige->setGeometry(10,10,312,35);


    Slot_Initialisiere_alle_Bilanzen();



    // Connects für die Gui
    connect(ui->checkBoxAnimateOperation,
             SIGNAL(clicked(bool)),
             this,
             SLOT(Slot_Animate_last_Operation(bool)));

    connect(ui->pushButtonMaxHistoryGrenzeDown,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Down()));

    connect(ui->pushButtonMaxHistoryGrenzeUp,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Up()));

    QObject::connect(Viewport,
            SIGNAL(IdNummer_wurde_gesendet(BILANZOBJEKTE,bool)),
            this,
            SLOT(Slot_Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE,bool)));


    // Connects für Finanztransaktionen der Zentralbank
    connect(ui->actionZentralbankbilanz_sichtbar,
            SIGNAL(triggered(bool)),
            this,
            SLOT(Slot_Toggel_Zentralbankbilanz_sichtbar()));


    // Connects für die Geschäftsbank
    connect(ui->pushButtonEigenkapitalEinlegen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Bank_legt_Eigenkapital_ein()));

    connect(ui->pushButtonKrediteBeiDerZentralbankZurueckzahlen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Bank_zahlt_Kredit_an_die_Zentralbank_zurueck()));

    connect(ui->pushButtonBargeldInZentralbankgeld,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Bank_tauscht_Bargeld_in_Zentralbankgeldguthaben()));

    connect(ui->pushButtonKrediteBeiDerZentralbankAufnehmen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Bank_nimmt_Kredit_bei_der_Zentralbank_auf()));

    connect(ui->pushButtonZentralbankgeldInBargeld,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Bank_tauscht_Zentralbankgeldguthaben_in_Bargeld()));

    connect(ui->pushButtonWertpapierAnkaufenVon,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Bank_kauft_Wertpapiere_von()));

    connect(ui->pushButtonBankVerkauftStaatsanleihenAnZBank,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Bank_verkauft_Staatsanleihen_an_die_ZBank()));


    // Connects für Finanztransaktionen der Kunden
    connect(ui->pushButtonKreditBeiDerBankZurueckzahlen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Kunde_zahlt_Kredit_an_die_Bank_zurueck()));

    connect(ui->pushButtonKreditBeiDerBankAufnehmen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Kunde_nimmt_Kredit_bei_der_Bank_auf()));

    connect(ui->pushButtonBargeldAmBankschalterAbheben,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Kunde_hebt_Bargeld_bei_einer_Bank_ab()));

    connect(ui->pushButtonBargeldAmBankschalterEinzahlen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Kunde_zahlt_Bargeld_bei_einer_Bank_ein()));

    connect(ui->pushButtonPersonGibtAndererPersonBargeld,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Kunde_gibt_anderer_Person_Bargeld()));

    connect(ui->pushButtonGiralgeldUeberweisen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Kunde_ueberweist_Giralgeld_an_eine_andere_Bank()));

    connect(ui->pushButtonSparbuchgeldEinzahlen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Kunde_zahlt_Giralgeld_auf_sein_Sparkonto_ein()));

    connect(ui->pushButtonSparbuchgeldAbheben,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Kunde_hebt_Geld_von_seinem_Sparkonto_ab()));


    // Connects für Finanztransaktionen des Staates
    connect(ui->pushButtonStaatKauftStaatsanleihen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Staat_kauft_Staatsanleihen_von_der_Bank()));

    connect(ui->pushButtonStaatVerkauftStaatsanleihen,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Staat_verkauft_Staatsanleihen_an_die_Bank()));

    connect(ui->pushButtonStaatUeberweistGiralgeld,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Staat_ueberweist_Giralgeld()));


    // Allegemeine Connects
    connect(ui->pushButtonResetAlleBilanzenToNull,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Reset_alle_Bilanzen_to_Null()));

    connect(ui->pushButtonRestart,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Initialisiere_alle_Bilanzen()));

    connect(ui->pushButtonEinJahtIstVorbei,
            SIGNAL(clicked(bool)),
            this,
            SLOT(Slot_Ein_Jahr_ist_vorbei()));

    }


MainWindow::~MainWindow(){
    delete ui;
    }


//###################################################################################################################################
//#   SLOTS:    Finanztransaktionen  der  Geschäftsbank
//###################################################################################################################################


void MainWindow::Slot_Bank_nimmt_Kredit_bei_der_Zentralbank_auf(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragGeschaeftsbank->text().toDouble();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionBankNimmtKreditBeiDerZBankAuf *op = new FAktionBankNimmtKreditBeiDerZBankAuf(Betrag,AktBankNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Kreditaufnahme nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Kreditaufnahme bei Z-Bank nicht ausgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_zahlt_Kredit_an_die_Zentralbank_zurueck(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragGeschaeftsbank->text().toDouble();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionBankZahltKreditBeiDerZBankZurueck *op = new FAktionBankZahltKreditBeiDerZBankZurueck(Betrag,AktBankNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Kreditrückzahlung an Zentralbank nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Kreditrückzahlung an Z-Bank nicht ausgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_tauscht_Bargeld_in_Zentralbankgeldguthaben(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragGeschaeftsbank->text().toDouble();

    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionBankTauschtBargeldInZentralbankgeld *op = new FAktionBankTauschtBargeldInZentralbankgeld(Betrag,AktBankNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Umtausch von Bargeld in Zentralbankgeldguthaben nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Umtausch von Bargeld in Z-Bankgeldguthaben nicht ausgeführt.");
        return;
        }

    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // GUI
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_tauscht_Zentralbankgeldguthaben_in_Bargeld(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragGeschaeftsbank->text().toDouble();

    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionBankTauschtZentralbankgeldInBargeld *op = new FAktionBankTauschtZentralbankgeldInBargeld(Betrag,AktBankNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Umtausch von Zentralbankgeldguthaben in Bargeld nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Umtausch von Z-Geldguthaben in Bargeld nicht ausgeführt");
        return;
        }

    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_legt_Eigenkapital_ein(){

    // Werte auslesen.
    double Betrag         = ui->lineEditGeldBetragGeschaeftsbank->text().toDouble();


    // Operation ausführen.
    FAktionBankLegtEigenkapitalEin *op = new FAktionBankLegtEigenkapitalEin(Betrag,AktBankNummer);
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_kauft_Wertpapiere_von(){

    // Werte auslesen.
    float Betrag         = ui->lineEditGeldbetragStaat->text().toDouble();
    int BankKundenNummer = ui->comboBoxWertpapiereVon->currentIndex();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionBankKauftWertpapiere *op = new FAktionBankKauftWertpapiere(Betrag,AktBankNummer,BankKundenNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Ankauf von Wertpapieren nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Ankauf von Wertpapieren nicht ausgeführt");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_verkauft_Staatsanleihen_an_die_ZBank(){

    // Werte auslesen.
    float Betrag = ui->lineEditGeldBetragGeschaeftsbank->text().toDouble();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionBankVerkauftStaatsanleiheAnZBank *op = new FAktionBankVerkauftStaatsanleiheAnZBank(Betrag,AktBankNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Verkauf von Staatsanleihen nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Der Verkauf von Staatsanleihen wurde nicht ausgeführt");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################
//#   SLOTS:    Finanztransaktionen  der   Kunden
//###################################################################################################################################


void MainWindow::Slot_Kunde_zahlt_Kredit_an_die_Bank_zurueck(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionKundeZahltKreditZurueck *op = new FAktionKundeZahltKreditZurueck(Betrag,AktBankNummer,AktBankKundenNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Kreditrückzahlung nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Kreditrückzahlung nicht ausgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Kunde_nimmt_Kredit_bei_der_Bank_auf(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionKundeNimmtKreditAuf*op = new FAktionKundeNimmtKreditAuf(Betrag,AktBankNummer,AktBankKundenNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Kreditaufnahme nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Kreditaufnahme nicht ausgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Kunde_hebt_Bargeld_bei_einer_Bank_ab(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();

    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionKundeHebtBargeldAb *op = new FAktionKundeHebtBargeldAb(Betrag,AktBankNummer, AktPersonenNr);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Bargeld abheben nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Bargeldabhebung nicht ausgeführt.");
        return;
        }

    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Kunde_zahlt_Bargeld_bei_einer_Bank_ein(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionKundeZahltBargeldEin *op = new FAktionKundeZahltBargeldEin(Betrag,AktBankNummer, AktPersonenNr);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Bargeld einzahlen nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Bargeldeinzahlung nicht ausgeführt.");
        return;
        }

    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }

//###################################################################################################################################


void MainWindow::Slot_Kunde_zahlt_Giralgeld_auf_sein_Sparkonto_ein(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionKundeZahltSparbuchgeldEin *op = new FAktionKundeZahltSparbuchgeldEin(Betrag,AktBankNummer,AktBankKundenNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Einzahlung auf das Sparkonto nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: die Einzahlung auf das Sparkonto wurde nicht ausgeführt.");
        return;
        }

    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Kunde_hebt_Geld_von_seinem_Sparkonto_ab(){

    // Werte auslesen.
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionKundeHebtSparbuchgeldAb *op = new FAktionKundeHebtSparbuchgeldAb(Betrag,AktBankNummer,AktBankKundenNummer);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "abhebung vom Sparkonto nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Die Abhebung vom Sparkonto wurde nicht ausgeführt.");
        return;
        }

    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }
//###################################################################################################################################


void MainWindow::Slot_Kunde_gibt_anderer_Person_Bargeld(){

    // Werte auslesen
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();

    int AnPerson = 0;
    if(ui->radioButtonAnA->isChecked())      AnPerson = 0;
    else if(ui->radioButtonAnB->isChecked()) AnPerson = 1;
    else if(ui->radioButtonAnC->isChecked()) AnPerson = 2;
    else if(ui->radioButtonAnD->isChecked()) AnPerson = 3;
    else if(ui->radioButtonAnStaat->isChecked()){
        QMessageBox msgBox;
        msgBox.critical(0, "Bargeldübergabe an den Staat ist nicht möglich.",
                            "Es ist prinzipiell nicht möglich, dass Kunden Bargeld an den Staat geben können." );
        ui->statusBar->showMessage("Fehler: Bargeldübergabe an den Staat ist prinzipiell nicht möglich.");
        return;
        }


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionKundeUebergibtBargeldAn *op = new FAktionKundeUebergibtBargeldAn(Betrag,AktPersonenNr,AnPerson);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Bargeldübergabe nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Bargeldübergabe nicht ausgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Kunde_ueberweist_Giralgeld_an_eine_andere_Bank(){

    // Werte auslesen
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();

    int AnBankKundenNr, AnBankNr;

    // An A
    if(ui->radioButtonAnA->isChecked()){
        AnBankNr = 0;  AnBankKundenNr = 0;
        }

    // An B
    else if(ui->radioButtonAnB->isChecked()){
        AnBankNr = 0;  AnBankKundenNr = 1;
        }

    // An Staat
    else if(ui->radioButtonAnStaat->isChecked()){
        AnBankNr = 0;  AnBankKundenNr = 2;
        }

    // An C
    else if(ui->radioButtonAnC->isChecked()){
        AnBankNr = 1;  AnBankKundenNr = 0;
        }

    // An D
    else if(ui->radioButtonAnD->isChecked()){
        AnBankNr = 1;  AnBankKundenNr = 1;
        }


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionKundeUeberweistGiralgeldAn *op = new FAktionKundeUeberweistGiralgeldAn(Betrag,
                                                                                  AktBankNummer, AnBankNr,
                                                                                  AktBankKundenNummer, AnBankKundenNr);
    op->Execute_on(&AlleDatenCopie);
    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Giralgeldüberweisung nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Giralgeldüberweisung nicht ausgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################
//#   SLOTS:    Finanztransaktionen  des  Staates
//###################################################################################################################################


void MainWindow::Slot_Staat_verkauft_Staatsanleihen_an_die_Bank(){

    // Werte auslesen.
    float Betrag = ui->lineEditGeldbetragStaat->text().toDouble();
    int AnBankNr = 0;


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionStaatVerkauftStaatsanleihen *op = new FAktionStaatVerkauftStaatsanleihen(Betrag,AnBankNr);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Verkauf der Staatsanleihen nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Verkauf der Staatsanleihen nicht ausgeführt");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//##########################################################################################################


void MainWindow::Slot_Staat_kauft_Staatsanleihen_von_der_Bank(){

    // Werte auslesen.
    float Betrag = ui->lineEditGeldbetragStaat->text().toDouble();
    int AnBankNr = 0;


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionStaatKauftStaatsanleihen *op = new FAktionStaatKauftStaatsanleihen(Betrag,AnBankNr);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Kauf der Staatsanleihen nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Kauf der Staatsanleihen nicht ausgeführt");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Staat_ueberweist_Giralgeld(){
    // Werte auslesen
    double Betrag = ui->lineEditGeldBetragPersonen->text().toDouble();

    int NachBankKundenNr, NachBankNr;

    // An A
    if(ui->comboBoxStaatUeberweistGiralgeldAn->currentIndex() == 0){
        NachBankNr = 0;  NachBankKundenNr = 0;
        }

    // An B
    else if(ui->comboBoxStaatUeberweistGiralgeldAn->currentIndex() == 1){
        NachBankNr = 0;  NachBankKundenNr = 1;
        }

    // An C
    else if(ui->comboBoxStaatUeberweistGiralgeldAn->currentIndex() == 2){
        NachBankNr = 1;  NachBankKundenNr = 0;
        }

    // An D
    else if(ui->comboBoxStaatUeberweistGiralgeldAn->currentIndex() == 3){
        NachBankNr = 1;  NachBankKundenNr = 1;
        }


    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionStaatUeberweistGiralgeldAn *op = new FAktionStaatUeberweistGiralgeldAn(Betrag, NachBankNr, NachBankKundenNr);
    op->Execute_on(&AlleDatenCopie);
    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Giralgeldüberweisung nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Giralgeldüberweisung nicht ausgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################
//#   SLOTS:    SONSTIGE  FINANZTRANSAKTIONEN
//###################################################################################################################################


void MainWindow::Slot_Reset_alle_Bilanzen_to_Null(){

    // Den alten Stack löschen
    StackOfOperations.clear();       // qDeletAll ??


    // Operation ausführen.
    FAktionResetAlleBilanzenToNull *op = new FAktionResetAlleBilanzenToNull();
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = 1;


    // Gui
    ui->labelJahreszahl->setText(QString::number(AlleDaten.Jahr) + " .tes Jahr " );
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Initialisiere_alle_Bilanzen(){

    // Den alten Stack löschen       // qDeletAll ??
    StackOfOperations.clear();


    // Operation ausführen.
    FAktionInitialisiereAlleBilanzen *op = new FAktionInitialisiereAlleBilanzen();
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = 1;


    // Gui
    ui->labelJahreszahl->setText(QString::number(AlleDaten.Jahr) + " .tes Jahr ");
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Ein_Jahr_ist_vorbei(){

    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionEinJahrIstVorbei *op = new FAktionEinJahrIstVorbei();
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Abschluss des Jahres ist nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Abschluss des Jahres wurde nicht ausgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();



    // Gui
    ui->labelJahreszahl->setText(QString::number(AlleDaten.Jahr) + " .tes Jahr ");
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################
//#
//###################################################################################################################################


void MainWindow::Slot_Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE angeklicktesObjekt, bool LinksKlick){
    FEinstellungen Einstellungen;

    // GUI verändern
    if(angeklicktesObjekt == PERSON_A){
        AktBankNummer       = 0;
        AktBankKundenNummer = 0;
        AktPersonenNr       = 0;
        LabelObjektanzeige->setDaten(PERSON_A);
        ui->stackedWidget->setCurrentIndex(0);
        }

    if(angeklicktesObjekt == PERSON_B){
        AktBankNummer       = 0;
        AktBankKundenNummer = 1;
        AktPersonenNr       = 1;
        LabelObjektanzeige->setDaten(PERSON_B);
        ui->stackedWidget->setCurrentIndex(0);
        }

    if(angeklicktesObjekt == PERSON_C){
        AktBankNummer       = 1;
        AktBankKundenNummer = 0;
        AktPersonenNr       = 2;
        LabelObjektanzeige->setDaten(PERSON_C);
        ui->stackedWidget->setCurrentIndex(0);
        }

    if(angeklicktesObjekt == PERSON_D){
        AktBankNummer       = 1;
        AktBankKundenNummer = 1;
        AktPersonenNr       = 3;
        LabelObjektanzeige->setDaten(PERSON_D);
        ui->stackedWidget->setCurrentIndex(0);
        }

    if(angeklicktesObjekt == BANK_A){
        AktBankNummer = 0;
        LabelObjektanzeige->setDaten(BANK_A);
        if(LinksKlick == true)  ui->stackedWidget->setCurrentIndex(1);
        if(LinksKlick == false) ui->stackedWidget->setCurrentIndex(4);

        // Gui
        ui->labelGeschaeftsbankBilanzsumme->setText(AlleDaten.Banken[0].Get_Bilanzsumme_as_String());
        ui->labelEigenkapitalquoteGeschaeftsbank->setText(AlleDaten.Banken[0].Get_EigenKapitalQuote_as_String());
        ui->labelSparkontoZinsen->setText(QString::number(Einstellungen.SparkontoZinsen()));
        ui->labelGirokontoZinsen->setText(QString::number(Einstellungen.GirokontoZinsen()));
        ui->labelKreditZinsen->setText(QString::number(Einstellungen.KreditZinsen()));
        ui->labelEigenkapitalrendite->setText(AlleDaten.Get_Eigenkapitalrendite_Bank(0));


        // Combobox einstellen
        ui->comboBoxWertpapiereVon->clear();
        ui->comboBoxWertpapiereVon->addItem("A");
        ui->comboBoxWertpapiereVon->addItem("B");
        }

    if(angeklicktesObjekt == BANK_B){
        AktBankNummer = 1;
        LabelObjektanzeige->setDaten(BANK_B);
        if(LinksKlick == true)  ui->stackedWidget->setCurrentIndex(1);
        if(LinksKlick == false) ui->stackedWidget->setCurrentIndex(4);

        // Gui
        ui->labelGeschaeftsbankBilanzsumme->setText(AlleDaten.Banken[1].Get_Bilanzsumme_as_String());
        ui->labelEigenkapitalquoteGeschaeftsbank->setText(AlleDaten.Banken[1].Get_EigenKapitalQuote_as_String());
        ui->labelSparkontoZinsen->setText(QString::number(Einstellungen.SparkontoZinsen()));
        ui->labelGirokontoZinsen->setText(QString::number(Einstellungen.GirokontoZinsen()));
        ui->labelKreditZinsen->setText(QString::number(Einstellungen.KreditZinsen()));
        ui->labelEigenkapitalrendite->setText(AlleDaten.Get_Eigenkapitalrendite_Bank(1));

        // Combobox einstellen
        ui->comboBoxWertpapiereVon->clear();
        ui->comboBoxWertpapiereVon->addItem("C");
        ui->comboBoxWertpapiereVon->addItem("D");
        }

    if(angeklicktesObjekt == ZENTRALBANK){
        LabelObjektanzeige->setDaten(ZENTRALBANK);
        ui->stackedWidget->setCurrentIndex(2);
        }

    if(angeklicktesObjekt == DER_STAAT){
        LabelObjektanzeige->setDaten(DER_STAAT);
        ui->stackedWidget->setCurrentIndex(3);
        }

    Eventuell_ScreenShot_erstellen();
    }


//###################################################################################################################################
//#      G U I     S L O T S
//###################################################################################################################################


void MainWindow::Refresch_Gui_und_eventuell_Screenshot_erstellen(QString BeschreibungDerOperation){

    // Label Beschreibung der Operation refreschen.
    ui->statusBar->showMessage(QString::number(StackOfOperations.size()-1) + BeschreibungDerOperation);


    // Viewport refreschen.
    Viewport->Alles_neu_zeichnen(AlleDaten);


    // Bilanz Kennwerte in Gui refreschen.
    ui->labelGeschaeftsbankBilanzsumme->setText(AlleDaten.Banken[AktBankNummer].Get_Bilanzsumme_as_String());
    ui->labelEigenkapitalquoteGeschaeftsbank->setText(AlleDaten.Banken[AktBankNummer].Get_EigenKapitalQuote_as_String());


    // Eventuell Screenshot erstellen.
    Eventuell_ScreenShot_erstellen();
    }


//###################################################################################################################################


void MainWindow::Slot_Toggel_Zentralbankbilanz_sichtbar(){
    bool IstSichtbar = ui->actionZentralbankbilanz_sichtbar->isChecked();
    Viewport->Set_Zentralbankbilanz_sichtbar(IstSichtbar);
    }


//###################################################################################################################################


void MainWindow::Slot_Up(){
    if( AktOpGrenze >= StackOfOperations.size()) return;
    AktOpGrenze += 1;
    Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(AktOpGrenze, true);
    }


//###################################################################################################################################


void MainWindow::Slot_Down(){
    if( AktOpGrenze <= 0 ) return;
    AktOpGrenze -= 1;
    Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(AktOpGrenze, true);
    }


//###################################################################################################################################


void MainWindow::Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(int n, bool wert){

    /*  AllOperations mit n = 3:       0 -> Op0 = Intialisierung = z.B. Eigenkapitaleinlegen
     *                                 1 -> Op1 = Befehl1
     *                                 2 -> Op2 = Befehl2
     */


    // Historische Bilanz berechnen.
    FAlleDaten AlleDatenNeu;
    for (int i=0; i<n; i++){
        StackOfOperations[i]->Execute_on(&AlleDatenNeu);
        }


    // historische Bilanz anzeigen
    Viewport->Alles_neu_zeichnen(AlleDatenNeu);


    // Operationsbefehl anzeigen
    if(n > 0) ui->statusBar->showMessage(QString::number(n-1) + StackOfOperations[n-1]->BeschreibungDerOperation);
    else      ui->statusBar->showMessage("Leere Bilanz");

    if(wert == false) ui->statusBar->showMessage("");


    // Bilanz Kennwerte in Gui refreschen.
    ui->labelGeschaeftsbankBilanzsumme->setText(AlleDatenNeu.Banken[AktBankNummer].Get_Bilanzsumme_as_String());
    ui->labelEigenkapitalquoteGeschaeftsbank->setText(AlleDatenNeu.Banken[AktBankNummer].Get_EigenKapitalQuote_as_String());
    }


//###################################################################################################################################


void MainWindow::Slot_Animate_last_Operation(bool wert){

    // Überprüfen, ob History groß genung ist.
    if(StackOfOperations.size() < 1) {
        qDebug() << "Fehler: Der Operationsstack ist zu kurz.";
        ui->checkBoxAnimateOperation->setChecked(false);
        return;
        }


    // Statten bzw. stoppen des Timers.
    if(wert == true){

        // Down sofort ausführen.
        Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(AktOpGrenze-1,false);
        LastOp = "down";

        // Timer starten.
        Tausend_Milli_Sekunden_Timer->start(800);
        }

    if(wert == false){

        // Timer stoppen
        Tausend_Milli_Sekunden_Timer->stop();
        Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(AktOpGrenze,true);
        LastOp = "up";
        }
    }


//###################################################################################################################################


void MainWindow::Slot_Wenn_Timer_aktiv_wird_das_hier_einmal_pro_Sekunde_ausgefuehrt(){

    if(LastOp == "up"){
        Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(AktOpGrenze-1,false);
        LastOp = "down";
        return;
        }

    if(LastOp == "down"){
        Berechne_historische_Bilanz_bis_n_und_zeige_Operationsbefehl_an(AktOpGrenze,true);
        LastOp = "up";
        return;
        }
    }


//###################################################################################################################################


void MainWindow::Eventuell_ScreenShot_erstellen(){
    if(ui->actionScreenshots_aufnehmen->isChecked()){

        // Screenshot berechnen
        QPixmap Pix;
        Pix = this->grab();
        QImage AbspeicherBild = Pix.toImage();


        // Ziffer mit Vornullen erzeugen z.B.:  0023
        QString ZifferMitVornullen;
        QString Ziffer = QString::number(AktScreenShotNr++);
        if(Ziffer.size() == 1) ZifferMitVornullen = "000" + Ziffer;
        if(Ziffer.size() == 2) ZifferMitVornullen = "00" + Ziffer;
        if(Ziffer.size() == 3) ZifferMitVornullen = "0" + Ziffer;
        if(Ziffer.size() == 4) ZifferMitVornullen = Ziffer;


        // Screenshot abspeichern
        FEinstellungen Einstellungen;
        QString BildPfad = Einstellungen.Pfad_zu_Screenshots() + "Bild" + ZifferMitVornullen + ".JPG";
        QFile file(BildPfad);
        file.open(QIODevice::WriteOnly);
            AbspeicherBild.save(&file, "JPG");
        file.close();
        }
    }


//####################################################################################################################################


/*
 *  Multicore Compiler einrichten:
 *  Projekte -> Build Einstellungen -> Erstellungsschritte -> make:  -j 13
 *
 *
 *
 *  Todo:
 *  1) Fliegende Geldbeträge bei Überweisungen.
 *  2) blinkende Geldscheine bei Schöpfungen.
 *  3) Fix: Warnungen für unmögliche Aktionen
 *  4) Nach Überweisungen GUI auf Empfänger ändern.
 *
 *
 *  Fragen:
 *  1) Wie wird QE Quantitativ Easing gebucht?
 *  2) Staat verkauft Staatsanleihen an die Bank. Bank verkauft diese an die Zentralbank. Wie wird nun verzinst?
 *  3) Wie wird die Eigenkapitalquote, Mindestreservequote berechnet?
 *  4) Darf jede Bank Staatsanleihen aufnehmen?
 *
 */






