#include "mainwindow.h"
#include "ui_mainwindow.h"


//###################################################################################################################################
//#  Konstruktor  und  Destruktor:
//###################################################################################################################################


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    setMouseTracking(true);


    // MainToolBar befüllen mit:
    MultiStatePushButton = new FMultiStatePushButton(this);
    MultiStatePushButton->setIcon(QIcon(":/Bilder/Achtung.png"));
    ui->mainToolBar->addWidget(MultiStatePushButton);
    connect(MultiStatePushButton, SIGNAL(Neuer_Status_ist(int)),
                this,SLOT(Slot_Einleitung(int)));

    // Seperator
    ui->mainToolBar->addSeparator();

    // PushButtonDown
    PushButtonOperationDown = new QPushButton("");
    PushButtonOperationDown->setIcon(QIcon(":/Bilder/Down.png"));
    ui->mainToolBar->addWidget(PushButtonOperationDown);
    connect(PushButtonOperationDown, SIGNAL(clicked()),
            this, SLOT(Slot_Down()));


    // PushButtonUp
    PushButtonOperationUp = new QPushButton("");
    PushButtonOperationUp->setIcon(QIcon(":/Bilder/Up.png"));
    ui->mainToolBar->addWidget(PushButtonOperationUp);
    connect(PushButtonOperationUp, SIGNAL(clicked()),
            this, SLOT(Slot_Up()));

    // Seperator
    ui->mainToolBar->addSeparator();


    // PushButton
    PushButtonNeuesJahr = new FMyPushButton();
    PushButtonNeuesJahr->setText("Zinsen für das 0.tes Jahr");
    PushButtonNeuesJahr->setIcon(QIcon(":/Bilder/Ok.png"));
    ui->mainToolBar->addWidget(PushButtonNeuesJahr);

    connect(PushButtonNeuesJahr, SIGNAL(clicked()),
            this, SLOT(Slot_Ein_Jahr_ist_vorbei()));

    connect(PushButtonNeuesJahr, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_ein_Jahr_ist_vorbei(bool)));


    // Seperator
    ui->mainToolBar->addSeparator();

    // Restart
    PushButtonInitialisiere = new QPushButton("Restart");
    PushButtonInitialisiere->setIcon(QIcon(":/Bilder/Reset.png"));
    ui->mainToolBar->addWidget(PushButtonInitialisiere);
    connect(PushButtonInitialisiere, SIGNAL(clicked()),
            this, SLOT(Slot_Initialisiere_alle_Bilanzen()));




    // Zeitbasis
    Tausend_Milli_Sekunden_Timer = new QTimer(this);
    Tausend_Milli_Sekunden_Timer->stop();

    connect(Tausend_Milli_Sekunden_Timer, SIGNAL(timeout()),
            this, SLOT(Slot_Wenn_Timer_aktiv_wird_das_hier_einmal_pro_Sekunde_ausgefuehrt()));



    // Werte initialisieren
    ui->stackedWidget->setCurrentIndex(0);
    AktBankNummer       = 0;
    AktBankKundenNummer = 0;
    AktPersonenNr       = 0;
    AktScreenShotNr     = 0;
    AktOpGrenze         = 0;



    // eigener Viewport
    Viewport = new FViewport(ui->frameViewport);



    // Label für die stacked Widgets erstellen.
    LabelPersonen      = new FMyLabel(PERSON_A,    ui->stackedWidget->widget(0));
    LabelBanken        = new FMyLabel(BANK_X,      ui->stackedWidget->widget(1));
    LabelZentralBanken = new FMyLabel(ZENTRALBANK, ui->stackedWidget->widget(2));
    LabelStaat         = new FMyLabel(DER_STAAT,   ui->stackedWidget->widget(3));

    LabelPersonen->setGeometry(10,10,312,35);
    LabelBanken->setGeometry(10,10,312,35);
    LabelZentralBanken->setGeometry(10,10,312,35);
    LabelStaat->setGeometry(10,10,312,35);



    // Widget für das Clearingverfahren erstellen
    ClearingWidget = new FMyClearingWidget(ui->frameClearingVerfahren);



    // Push Buttons für Kundenaktionen erstellen
    PushButtonKundeNimmtKreditAuf = new FMyPushButton("aufnehmen",ui->frameAktionDesKunden);
    PushButtonKundeNimmtKreditAuf->setGeometry(10,90,110,30);

    PushButtonKundeZahltKreditZurueck = new FMyPushButton("zurückzahlen",ui->frameAktionDesKunden);
    PushButtonKundeZahltKreditZurueck->setGeometry(130,90,110,30);

    PushButtonBargeldEinzahlen = new FMyPushButton("einzahlen",ui->frameAktionDesKunden);
    PushButtonBargeldEinzahlen->setGeometry(10,190,110,30);

    PushButtonBargeldAuszahlen = new FMyPushButton("auszahlen",ui->frameAktionDesKunden);
    PushButtonBargeldAuszahlen->setGeometry(130,190,110,30);

    PushButtonSparbuchgeldEinzahlen = new FMyPushButton("einzahlen",ui->frameAktionDesKunden);
    PushButtonSparbuchgeldEinzahlen->setGeometry(10,280,110,30);

    PushButtonSparbuchgeldAuszahlen = new FMyPushButton("auszahlen",ui->frameAktionDesKunden);
    PushButtonSparbuchgeldAuszahlen->setGeometry(130,280,110,30);

    PushButtonKundeUeberweistGiralgeld = new FMyPushButton("Giralgeld",ui->frameAktionDesKunden);
    PushButtonKundeUeberweistGiralgeld->setGeometry(10,380,110,30);

    PushButtonKundeUeberweistBargeld = new FMyPushButton("Bargeld",ui->frameAktionDesKunden);
    PushButtonKundeUeberweistBargeld->setGeometry(130,380,110,30);



     // Push Buttons für Bankaktionen erstellen
    PushButtonBankNimmtZKreditAuf = new FMyPushButton("aufnehmen",ui->frameAktionDerBank);
    PushButtonBankNimmtZKreditAuf->setGeometry(10,90,110,30);

    PushButtonBankZahltZKreditZurueck = new FMyPushButton("zurückzahlen",ui->frameAktionDerBank);
    PushButtonBankZahltZKreditZurueck->setGeometry(130,90,110,30);

    PushButtonBankTauschtBargeldInZGeld = new FMyPushButton("",ui->frameAktionDerBank);
    PushButtonBankTauschtBargeldInZGeld->setGeometry(140,180,30,60);
    PushButtonBankTauschtBargeldInZGeld->setIcon(QIcon(":/Bilder/ArrowDown.png"));

    PushButtonBankTauschtZGeldInBargeld = new FMyPushButton("",ui->frameAktionDerBank);
    PushButtonBankTauschtZGeldInBargeld->setGeometry(180,180,30,60);
    PushButtonBankTauschtZGeldInBargeld->setIcon(QIcon(":/Bilder/ArrowUp.png"));

    PushButtonBankVerkauftStaatsanleihenAnZBank = new FMyPushButton("an ZBank verkaufen",ui->frameAktionDerBank);
    PushButtonBankVerkauftStaatsanleihenAnZBank->setGeometry(10,310,280,30);

    PushButtonBankLegtEigenkapitalEin = new FMyPushButton("Eigenkapital einlegen",ui->frameAktionDerBank);
    PushButtonBankLegtEigenkapitalEin->setGeometry(10,400,280,30);

    PushButtonBankKaufWertpapiereAn = new FMyPushButton("Wertpapiere kaufen von",ui->frameAktionDerBank);
    PushButtonBankKaufWertpapiereAn->setGeometry(10,440,220,30);

    PushButtonBankZahltKreditAnAndereBankZurueck = new FMyPushButton("mit ZGeld BankKredit bezahlen",ui->frameAktionDerBank);
    PushButtonBankZahltKreditAnAndereBankZurueck->setGeometry(10,480,280,30);


    // Push Button für das Clearingverfahren
    PushButtonBankFuehrtClearingverfahrenDurch = new FMyPushButton("Clearingverfahren durchführen",ui->frameClearingVerfahren);
    PushButtonBankFuehrtClearingverfahrenDurch->setGeometry(10,450,270,30);



    // Push Buttons für Staatsaktionen erstellen
    PushButtonStaatVerkauftStaatsanleihenAnDieBank = new FMyPushButton("verkaufen an",ui->frameAktionenDesStaates);
    PushButtonStaatVerkauftStaatsanleihenAnDieBank->setGeometry(10,100,110,30);

    PushButtonStaatKauftStaatsanleihenVonDerBank = new FMyPushButton("kaufen von",ui->frameAktionenDesStaates);
    PushButtonStaatKauftStaatsanleihenVonDerBank->setGeometry(140,100,110,30);

    PushButtonStaatUeberweistGiralgeldAnKunden = new FMyPushButton("von Bank A zum Kunden",ui->frameAktionenDesStaates);
    PushButtonStaatUeberweistGiralgeldAnKunden->setGeometry(10,230,210,30);


    Slot_Initialisiere_alle_Bilanzen();
    ui->radioButtonAnA->setDisabled(true);
    ui->radioButtonAnB->setChecked(true);


    // Connects für die Gui
    connect(ui->actionZentralbankbilanz_sichtbar, SIGNAL(triggered(bool)),
            this, SLOT(Slot_Toggel_Zentralbankbilanz_sichtbar()));

    connect(ui->actionLetzte_Operation_annimieren, SIGNAL(toggled(bool)),
             this, SLOT(Slot_Animate_last_Operation(bool)));

    connect(ui->actionInfo,SIGNAL(triggered()),
            this, SLOT(Slot_Zeige_InfoWidget()));

    QObject::connect(Viewport, SIGNAL(IdNummer_wurde_gesendet(BILANZOBJEKTE,bool)),
                     this, SLOT(Slot_Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE,bool)));



    // Connect Bank nimmt ZKredit auf.
    connect(PushButtonBankNimmtZKreditAuf, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Bank_nimmt_Kredit_bei_der_Zentralbank_auf()));

    connect(PushButtonBankNimmtZKreditAuf, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_nimmt_ZKredit_auf_oder_zahlt_zurueck(bool)));


    // Connect Bank zahlt ZKredit zurück.
    connect(PushButtonBankZahltZKreditZurueck, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Bank_zahlt_Kredit_an_die_Zentralbank_zurueck()));

    connect(PushButtonBankZahltZKreditZurueck, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_nimmt_ZKredit_auf_oder_zahlt_zurueck(bool)));


    //  Connect Bank zahlt Kredit an andere Bank zurueck
    connect(PushButtonBankZahltKreditAnAndereBankZurueck, SIGNAL(clicked(bool)),
            this,SLOT(Slot_Bank_bezahlt_mit_ZGeld_Kredit_an_andere_Bank_zurueck()));

    connect(PushButtonBankZahltKreditAnAndereBankZurueck, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_bezahlt_mit_ZGeld_Kredit_an_andere_Bank_zurueck(bool)));


    // Connect Bank tauscht Bargeld in Zentralbankgeldguthaben
    connect(PushButtonBankTauschtBargeldInZGeld, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Bank_tauscht_Bargeld_in_Zentralbankgeldguthaben()));

    connect(PushButtonBankTauschtBargeldInZGeld, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_Bar_inZ_Bankgeld_oder_umgekehrt(bool)));


    // Connect Bank tauscht Zentralbankgeldguthaben in Bargeld
    connect(PushButtonBankTauschtZGeldInBargeld, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Bank_tauscht_Zentralbankgeldguthaben_in_Bargeld()));

    connect(PushButtonBankTauschtZGeldInBargeld, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_Bar_inZ_Bankgeld_oder_umgekehrt(bool)));


    // Connect Bank legt Eigenkapital ein.
    connect(PushButtonBankLegtEigenkapitalEin, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Bank_legt_Eigenkapital_ein()));

    connect(PushButtonBankLegtEigenkapitalEin, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_legt_Eigenkapital_ein(bool)));


    // Connect Bank kauft Wertpapiere
    connect(PushButtonBankKaufWertpapiereAn, SIGNAL(clicked(bool)),
            this,  SLOT(Slot_Bank_kauft_Wertpapiere_von()));

    connect(PushButtonBankKaufWertpapiereAn, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_kauft_Wertpapiere(bool)));


    // Connect Bank verkauft Staatsanleihen
    connect(PushButtonBankVerkauftStaatsanleihenAnZBank, SIGNAL(clicked(bool)),
            this,  SLOT(Slot_Bank_verkauft_Staatsanleihen_an_die_ZBank()));

    connect(PushButtonBankVerkauftStaatsanleihenAnZBank, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_verkauft_Staatsanleihen_an_ZBank(bool)));



    // Connect Kunde nimmt Kredit auf.
    connect(PushButtonKundeNimmtKreditAuf, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Kunde_nimmt_Kredit_bei_der_Bank_auf()));

    connect(PushButtonKundeNimmtKreditAuf, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_nimmt_Kredit_auf_oder_zahlt_zurueck(bool)));


    // Connect Kunde zahlt Kredit zurück.
    connect(PushButtonKundeZahltKreditZurueck, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Kunde_zahlt_Kredit_an_die_Bank_zurueck()));

    connect(PushButtonKundeZahltKreditZurueck, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_nimmt_Kredit_auf_oder_zahlt_zurueck(bool)));


    // Connect Kunde zahlt Bargeld ein.
    connect(PushButtonBargeldEinzahlen, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Kunde_zahlt_Bargeld_bei_einer_Bank_ein()));

    connect(PushButtonBargeldEinzahlen, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_zahlt_Bargeld_ein_oder_aus(bool)));


    // Connect Kunde hebt Bargeld ab.
    connect(PushButtonBargeldAuszahlen, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Kunde_hebt_Bargeld_bei_einer_Bank_ab()));

    connect(PushButtonBargeldAuszahlen, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_zahlt_Bargeld_ein_oder_aus(bool)));


    // Connect Kunde zahlt Sparbuchgeld ein.
    connect(PushButtonSparbuchgeldEinzahlen, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Kunde_zahlt_Giralgeld_auf_sein_Sparkonto_ein()));

    connect(PushButtonSparbuchgeldEinzahlen,SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_zahlt_Sparbuchgeld_ein_oder_aus(bool)));


    // Connect Kunde hebt Sparbuchgeld ab.
    connect(PushButtonSparbuchgeldAuszahlen, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Kunde_hebt_Geld_von_seinem_Sparkonto_ab()));

    connect(PushButtonSparbuchgeldAuszahlen,SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_zahlt_Sparbuchgeld_ein_oder_aus(bool)));


    // Connect Kunde überweist Giralgeld
    connect(PushButtonKundeUeberweistGiralgeld, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Kunde_ueberweist_Giralgeld_an_eine_andere_Bank()));

    connect(PushButtonKundeUeberweistGiralgeld, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_ueberweiset_Giralgeld(bool)));


    // Connect Kunde überweist Bargeld
    connect(PushButtonKundeUeberweistBargeld, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Kunde_gibt_anderer_Person_Bargeld()));

    connect(PushButtonKundeUeberweistBargeld, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_ueberweiset_Bargeld(bool)));



    // Connect Staat verkauft Staatsanleihen
    connect(PushButtonStaatVerkauftStaatsanleihenAnDieBank, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Staat_verkauft_Staatsanleihen_an_die_Bank()));

    connect(PushButtonStaatVerkauftStaatsanleihenAnDieBank, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Staat_kauft_oder_verkauft_Staatsanleihen(bool)));


    // Connect Staat kauft Staatsanleihen
    connect(PushButtonStaatKauftStaatsanleihenVonDerBank, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Staat_kauft_Staatsanleihen_von_der_Bank()));

    connect(PushButtonStaatKauftStaatsanleihenVonDerBank, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Staat_kauft_oder_verkauft_Staatsanleihen(bool)));


    // Connect Staat überweist Giralgeld
    connect(PushButtonStaatUeberweistGiralgeldAnKunden, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Staat_ueberweist_Giralgeld()));

    connect(PushButtonStaatUeberweistGiralgeldAnKunden, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Staat_ueberweist_Giralgeld(bool)));



    // Connects für MainToolBar
    connect(ui->actionReset, SIGNAL(triggered(bool)),
            this, SLOT(Slot_Reset_alle_Bilanzen_to_Null()));

    connect(ui->actionInitialisiere_alle_Bilanzen, SIGNAL(triggered(bool)),
            this, SLOT(Slot_Initialisiere_alle_Bilanzen()));

    connect(ui->actionAlle_Kunden_haben_Kredite_aufgenommen, SIGNAL(triggered(bool)),
            this, SLOT(Slot_Preset_ABCD_haben_Kredite_aufgenommen()));

    connect(ui->actionDer_Staat_verschuldet_sich_und_bezahlt_Buerger, SIGNAL(triggered(bool)),
            this, SLOT(Slot_Preset_Der_Staat_verschuldet_sich_und_bezahlt_Buerger()));


    // Allegemeine Connects
    connect(ui->pushButtonTagesabschluss, SIGNAL(clicked(bool)),
            this, SLOT(Slot_Widget_Clearingverfahren_anzeigen()));

    connect(PushButtonBankFuehrtClearingverfahrenDurch, SIGNAL(clicked(bool)),
           this, SLOT(Slot_Bank_fuehrt_Clearingverfahren_durch()));

    connect(PushButtonBankFuehrtClearingverfahrenDurch, SIGNAL(DickenRahmenZeichnen(bool)),
            this, SLOT(Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_fuehrt_Clearingverfahren_durch(bool)));

    connect(PushButtonBankFuehrtClearingverfahrenDurch, SIGNAL(EnterButton()),
            this, SLOT(Slot_neue_Ueberweisungsbetraege_fuer_das_Clearingverfahren()));


    resize(QSize(1024,768));




    }


MainWindow::~MainWindow(){
    delete ui;
    }


//###################################################################################################################################
//#  GUI Slots:
//###################################################################################################################################


void MainWindow::resizeEvent(QResizeEvent *event){

    // Viewportgröße abfragen
    int w = ui->frameViewport->width();
    int h = ui->frameViewport->height();

    // Viewport skalieren
    qreal ww = (1.0*w) / (980.0);
    qreal hh = (1.0*h) / (780.0);
    QTransform Mat(ww, 0,  0,
                   0,  hh, 0,
                   0,  0,  1);
    Viewport->setTransform(Mat);
    Viewport->setGeometry(0,0,w,h);
    event->accept();
    }


//###################################################################################################################################
//#   SLOTS:
//###################################################################################################################################


void MainWindow::Slot_Zeige_InfoWidget(){
    DialogInfo *MyDialog = new DialogInfo(this);
    MyDialog->exec();
    delete MyDialog;
    }


//################################################################################################################

void MainWindow::Slot_Einleitung(int Stufe){

    QString Head = "<html>"
                   "<body bgcolor = '#BCD8E7'>";

    if(Stufe == 0){
        ui->stackedWidget->setCurrentIndex(0);
        Slot_Initialisiere_alle_Bilanzen();
        Viewport->Objekt_mit_Id_Nummer_wurde_geklicked(PERSON_A,true);
        Viewport->Alles_neu_zeichnen(AlleDaten);


        // Toolbar anschalten
        PushButtonOperationUp->setDisabled(false);
        PushButtonOperationDown->setDisabled(false);
        PushButtonNeuesJahr->setDisabled(false);
        PushButtonInitialisiere->setDisabled(false);

        // Viewport anschalten
        ui->frameViewport->setEnabled(true);
        }


    if(Stufe == 1){
        ui->stackedWidget->setCurrentIndex(6);
        Slot_Initialisiere_alle_Bilanzen();
        ui->textEditEinfuehrungInsProgramm->setHtml(
                    Head +
                    "<h2>1. Schritt: </h2>"
                    "Die Banken starten mit 500 Euro Eigenkapital.");

        // Toolbar abschalten
        PushButtonOperationUp->setDisabled(true);
        PushButtonOperationDown->setDisabled(true);
        PushButtonNeuesJahr->setDisabled(true);
        PushButtonInitialisiere->setDisabled(true);

        // Viewport abschalten
        ui->frameViewport->setEnabled(false);
        }


    if(Stufe == 2){
        ui->stackedWidget->setCurrentIndex(6);

        // A und B nehmen 3000 Euro Kredit auf
        FAktionKundeNimmtKreditAuf *op1 = new FAktionKundeNimmtKreditAuf(3000,0,0);
        FAktionKundeNimmtKreditAuf *op2 = new FAktionKundeNimmtKreditAuf(3000,0,1);
        op1->Execute_on(&AlleDaten);
        op2->Execute_on(&AlleDaten);
        StackOfOperations << op1 << op2;
        AktOpGrenze = StackOfOperations.size();



        ui->textEditEinfuehrungInsProgramm->setHtml(
                    Head +
                    "<h2>2. Schritt: </h2>"
                    "Die Kunden A und B nehmen jeweils "
                    "<br>"
                    "3000 Euro Kredit auf:"
                    "<br><br>"
                    "Auf der Aktivseite der Bankbilanz steht der Kreditvertrag."
                    "<br><br>"
                    "Auf der Passivseite schreibt die Bank dem Kunden durch einen "
                    "Buchungsvorgang das Giralgeld gut. Dieses Giralgeld hat "
                    "die Bank <b>aus dem Nichts</b> erzeugt !"
                    );
        // Gui
        Refresch_Gui_und_eventuell_Screenshot_erstellen(op2->BeschreibungDerOperation);
        }


    if(Stufe == 3){
        ui->stackedWidget->setCurrentIndex(6);
        Slot_Ein_Jahr_ist_vorbei();
        ui->textEditEinfuehrungInsProgramm->setHtml(
                    Head +
                    "<h2>3. Schritt: </h2>"
                    "Nach einem Jahr werden Zinsen fällig."
                    "<br><br>"
                    "Bei einem Kreditzins von 5% und einem Zins von 1% auf Girokonten "
                    "ergeben sich folgende Zahlungen:"
                    "<br><br>"
                    "Kunden -> Bank: 3000 * 0.05 = 150 Euro"
                    "<br>"
                    "Bank -> Kunden: 3000 * 0.01 = 30 Euro"
                    "<br><br>"
                    "Insgesamt erhält die Bank:"
                    "<br>"
                    "2 * 150 - 2 * 30 = 240 Euro Zinsen"
                    "<br><br>"
                    "<b>Fazit:</b>"
                    "<br>"
                    "Die Bank hat in einem Jahr ihr Eigenkapital von 500 auf "
                    "740 Euro erhöhen können. Das entspricht einer "
                    "<b>Eigenkapitalrendite von 48%</b>."
                    );
        }


    if(Stufe == 4){
        ui->stackedWidget->setCurrentIndex(6);
        ui->textEditEinfuehrungInsProgramm->setHtml(
                    Head +
                    "<h2>4. Schritt: </h2>"
                    "Natürlich ist der Geldkreislauf in Wahrheit komplizierter"
                    " und man muss folgende Punkte mit berücksichtigen:"
                    "<br><br>"
                    "1) Den Abfluss von Giralgeld zu anderen Banken."
                    "<br>"
                    "2) Das Abheben von Bargeld."
                    "<br>"
                    "3) Die Mindestreservevorschriften."
                    "<br>"
                    "4) Die Eigenkapitalregelungen."
                    "<br>"
                    "5) Die Refinanzierung mit Zentralbankgeld"
                    "<br><br>"
                    "Alle diese Operationen können in diesem Program simuliert"
                    " werden. Sie werden aber sehen, dass die Eigenkapitalrendite "
                    "der Bank dabei immer unverschämt hoch bleibt.");
        }

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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//----------------------------------------------------------------------------------------------------------------------------


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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//----------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_nimmt_ZKredit_auf_oder_zahlt_zurueck(bool wert){
    AlleDaten.Banken[AktBankNummer].DickerRahmenVerbindGegenZentralbank = wert;
    AlleDaten.Banken[AktBankNummer].DickerRahmenZentralbankGeldguthaben = wert;
    AlleDaten.Zentralbank.DickerRahmenForderungAnBanken[AktBankNummer]= wert;
    AlleDaten.Zentralbank.DickerRahmenZGeldGuthabenVonBanken[AktBankNummer]= wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_bezahlt_mit_ZGeld_Kredit_an_andere_Bank_zurueck(){

    int vonBankNr = AktBankNummer;
    int nachBankNr;
    if(AktBankNummer == 0 ) nachBankNr = 1;
    if(AktBankNummer == 1 ) nachBankNr = 0;
    double Betrag = ui->lineEditGeldBetragGeschaeftsbank->text().toDouble();

    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;

    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionBankZahltKreditAnAndereBankZurueck *op = new FAktionBankZahltKreditAnAndereBankZurueck(vonBankNr,
                                                                                                  nachBankNr,
                                                                                                  Betrag);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Kreditrückzahlung an ander Bank nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Kreditrückzahlung an andere Bank nicht ausgeführt.");
        return;
        }

    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//-----------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_bezahlt_mit_ZGeld_Kredit_an_andere_Bank_zurueck(bool wert){

    int vonBankNr = AktBankNummer;
    int nachBankNr;
    if(AktBankNummer == 0 ) nachBankNr = 1;
    if(AktBankNummer == 1 ) nachBankNr = 0;

    AlleDaten.Banken[vonBankNr].DickerRahmenZentralbankGeldguthaben = wert;
    AlleDaten.Banken[vonBankNr].DickerRahmenVerbindGegenAndereBank  = wert;

    AlleDaten.Banken[nachBankNr].DickerRahmenZentralbankGeldguthaben = wert;
    AlleDaten.Banken[nachBankNr].DickerRahmenKreditBeiAndererBank    = wert;

    Viewport->Alles_neu_zeichnen(AlleDaten);
    }


//#######################################################################################################################


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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // GUI
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//----------------------------------------------------------------------------------------------------------------------------


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

    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }

//------------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_Bar_inZ_Bankgeld_oder_umgekehrt(bool wert){
    AlleDaten.Banken[AktBankNummer].DickerRahmenZentralbankGeldguthaben = wert;
    AlleDaten.Banken[AktBankNummer].DickerRahmenBarGeldDerBank = wert;
    AlleDaten.Zentralbank.DickerRahmenBargeldumlauf = wert;
    AlleDaten.Zentralbank.DickerRahmenZGeldGuthabenVonBanken[AktBankNummer]= wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_legt_Eigenkapital_ein(){

    // Werte auslesen.
    double Betrag         = ui->lineEditGeldBetragGeschaeftsbank->text().toDouble();


    // Operationen ausführen.
    FAktionBankLegtEigenkapitalEin *op = new FAktionBankLegtEigenkapitalEin(Betrag,AktBankNummer);
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//-------------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_legt_Eigenkapital_ein(bool wert){
    AlleDaten.Banken[AktBankNummer].DickerRahmenEigenkapital = wert;
    AlleDaten.Banken[AktBankNummer].DickerRahmenBarGeldDerBank = wert;
    AlleDaten.Zentralbank.DickerRahmenBargeldumlauf = wert;
    AlleDaten.Zentralbank.DickerRahmenForderungAnBanken[2] = wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//------------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_kauft_Wertpapiere(bool wert){
    if(ui->comboBoxWertpapiereVon->currentText() == "A")
       AlleDaten.Banken[0].DickerRahmenGiroKonten[0] = wert;
    if(ui->comboBoxWertpapiereVon->currentText() == "B")
       AlleDaten.Banken[0].DickerRahmenGiroKonten[1] = wert;
    if(ui->comboBoxWertpapiereVon->currentText() == "C")
       AlleDaten.Banken[1].DickerRahmenGiroKonten[0] = wert;
    if(ui->comboBoxWertpapiereVon->currentText() == "D")
       AlleDaten.Banken[1].DickerRahmenGiroKonten[1] = wert;
    AlleDaten.Banken[AktBankNummer].DickerRahmenWertpapiere = wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//----------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_verkauft_Staatsanleihen_an_ZBank(bool wert){
    AlleDaten.Banken[AktBankNummer].DickerRahmenStaatsanleihen = wert;
    AlleDaten.Banken[AktBankNummer].DickerRahmenZentralbankGeldguthaben = wert;
    AlleDaten.Zentralbank.DickerRahmenStaatsanleihen[AktBankNummer] = wert;
    AlleDaten.Zentralbank.DickerRahmenZGeldGuthabenVonBanken[AktBankNummer] = wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
    }


//###################################################################################################################################


void MainWindow::Slot_Bank_fuehrt_Clearingverfahren_durch(){
    // Kopie der Bilanz erstellen.
    FAlleDaten AlleDatenCopie;
    AlleDatenCopie = AlleDaten;


    // Auf der Kopie überprüfen, ob die Operation zu einem Fehler führt.
    FAktionClearingVerfahrenAusfuehren *op = new FAktionClearingVerfahrenAusfuehren(ClearingWidget->AToC, ClearingWidget->AToD,
                                                                                    ClearingWidget->BToC, ClearingWidget->BToD,
                                                                                    ClearingWidget->CToA, ClearingWidget->CToB,
                                                                                    ClearingWidget->DToA, ClearingWidget->DToB);
    op->Execute_on(&AlleDatenCopie);

    if( op->Fehlerbeschreibung != "" ){
        QMessageBox msgBox;
        msgBox.critical(0, "Durchführung des Clearingverfahrens ist nicht möglich.", op->Fehlerbeschreibung );
        ui->statusBar->showMessage("Fehler: Clearingverfahren wurde nicht durchgeführt.");
        return;
        }


    // Operation ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();



    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//-----------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_neue_Ueberweisungsbetraege_fuer_das_Clearingverfahren(){
    ClearingWidget->Ueberweisungsbetraege_eintragen(AlleDaten);
    }


//-----------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Bank_fuehrt_Clearingverfahren_durch(bool wert){
    FAktionClearingVerfahrenAusfuehren op;
    op.Set_Dicke_Rahmen(&AlleDaten,wert);
    Viewport->Alles_neu_zeichnen(AlleDaten);
    }


//-----------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Widget_Clearingverfahren_anzeigen(){
    ui->stackedWidget->setCurrentIndex(5);
    ClearingWidget->Ueberweisungsbetraege_eintragen(AlleDaten);
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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//-------------------------------------------------------------------------------------------------------------------------------


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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }

//------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_nimmt_Kredit_auf_oder_zahlt_zurueck(bool wert){
    AlleDaten.Banken[AktBankNummer].DickerRahmenGiroKonten[AktBankKundenNummer] = wert;
    AlleDaten.Banken[AktBankNummer].DickerRahmenHypotheken[AktBankKundenNummer] = wert;
    AlleDaten.Kunden[AktPersonenNr].DickerRahmenSchulden = wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
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

    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//------------------------------------------------------------------------------------------------------------------------------


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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//------------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_zahlt_Bargeld_ein_oder_aus(bool wert){
    AlleDaten.Banken[AktBankNummer].DickerRahmenGiroKonten[AktBankKundenNummer] = wert;
    AlleDaten.Banken[AktBankNummer].DickerRahmenBarGeldDerBank = wert;
    AlleDaten.Kunden[AktPersonenNr].DickerRahmenBarGeld = wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//--------------------------------------------------------------------------------------------------------------------------------


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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//---------------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_zahlt_Sparbuchgeld_ein_oder_aus(bool wert){
    AlleDaten.Banken[AktBankNummer].DickerRahmenGiroKonten[AktBankKundenNummer] = wert;
    AlleDaten.Banken[AktBankNummer].DickerRahmenSparbuchKonten[AktBankKundenNummer] = wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//-------------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_ueberweiset_Bargeld(bool wert){
    if(ui->radioButtonAnA->isChecked())
        AlleDaten.Kunden[0].DickerRahmenBarGeld = wert;
    if(ui->radioButtonAnB->isChecked())
        AlleDaten.Kunden[1].DickerRahmenBarGeld = wert;
    if(ui->radioButtonAnC->isChecked())
        AlleDaten.Kunden[2].DickerRahmenBarGeld = wert;
    if(ui->radioButtonAnD->isChecked())
        AlleDaten.Kunden[3].DickerRahmenBarGeld = wert;
    AlleDaten.Kunden[AktPersonenNr].DickerRahmenBarGeld = wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
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


//-----------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Kunde_ueberweiset_Giralgeld(bool wert){
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

    // Op erstellen
    int Betrag = 9999; // irgendetwas
    FAktionKundeUeberweistGiralgeldAn op(Betrag,AktBankNummer, AnBankNr,
                                               AktBankKundenNummer, AnBankKundenNr);
    op.DickenRahmen_zeichnen(&AlleDaten,wert);
    Viewport->Alles_neu_zeichnen(AlleDaten);
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


    // Operationen ausführen.
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = StackOfOperations.size();


    // Gui
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//-----------------------------------------------------------------------------------------------------------------------------


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


//-------------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Staat_kauft_oder_verkauft_Staatsanleihen(bool wert){
    AlleDaten.Banken[0].DickerRahmenStaatsanleihen = wert;
    AlleDaten.Banken[0].DickerRahmenStaatsGiroKonto = wert;
    AlleDaten.Staat.DickerRahmenSchuldenAnBanken = wert;
    Viewport->Alles_neu_zeichnen(AlleDaten);
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


//-------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_Staat_ueberweist_Giralgeld(bool wert){
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

    int Betrag = 9999; // egal
    FAktionStaatUeberweistGiralgeldAn op(Betrag, NachBankNr, NachBankKundenNr);
    op.Dicke_Rahmen_zeichnen(&AlleDaten, wert);
    Viewport->Alles_neu_zeichnen(AlleDaten);
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
    PushButtonNeuesJahr->setText("Zinsen für das " + QString::number(AlleDaten.Jahr) + ".tes Jahr");
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
    PushButtonNeuesJahr->setText("Zinsen für das " + QString::number(AlleDaten.Jahr) + ".tes Jahr");
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//###################################################################################################################################


void MainWindow::Slot_Preset_ABCD_haben_Kredite_aufgenommen(){

    // Den alten Stack löschen       // qDeletAll ??
    StackOfOperations.clear();


    // Operation ausführen.
    FAktionPresetABCDhabenKrediteAufgenommen *op = new FAktionPresetABCDhabenKrediteAufgenommen();
    op->Execute_on(&AlleDaten);
    StackOfOperations << op;
    AktOpGrenze = 1;


    // Gui
    PushButtonNeuesJahr->setText("Zinsen für das " + QString::number(AlleDaten.Jahr) + ".tes Jahr");
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }

//###################################################################################################################################


void MainWindow::Slot_Preset_Der_Staat_verschuldet_sich_und_bezahlt_Buerger(){

    // Initialisierung
    Slot_Initialisiere_alle_Bilanzen();


    // Der Staat verkauft 6000 Staatsanleihen an Bank 0.
    FAktionStaatVerkauftStaatsanleihen *op1 = new FAktionStaatVerkauftStaatsanleihen(6000,0);
    op1->Execute_on(&AlleDaten);
    StackOfOperations << op1;


    // Der Staat überweist 1000 Euro an die Bürger.
    for (int NachBankNr=0; NachBankNr<2; NachBankNr++){
        for(int NachBankKundenNr=0; NachBankKundenNr<2; NachBankKundenNr++){
            FAktionStaatUeberweistGiralgeldAn *op2;
            op2 = new FAktionStaatUeberweistGiralgeldAn(1000, NachBankNr, NachBankKundenNr);
            op2->Execute_on(&AlleDaten);
            StackOfOperations << op2;
            }
        }


    // Gui
    AktOpGrenze = StackOfOperations.size();
    Refresch_Gui_und_eventuell_Screenshot_erstellen(") Preset: Der Staat verschuldet sich und zahlt an die Bürger.");
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
    PushButtonNeuesJahr->setText("Zinsen für das " + QString::number(AlleDaten.Jahr) + ".tes Jahr");
    Refresch_Gui_und_eventuell_Screenshot_erstellen(op->BeschreibungDerOperation);
    }


//-----------------------------------------------------------------------------------------------------------------------------


void MainWindow::Slot_Rahmen_zeichnen_fuer_die_Aktion_ein_Jahr_ist_vorbei(bool wert){
    FAktionEinJahrIstVorbei op;
    op.Set_Dicke_Rahmen(&AlleDaten,wert);
    Viewport->Alles_neu_zeichnen(AlleDaten);
    }





//###################################################################################################################################
//#
//###################################################################################################################################


void MainWindow::Slot_Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE angeklicktesObjekt, bool LinksKlick){
    FEinstellungen Einstellungen;

    ui->radioButtonAnA->setEnabled(true);
    ui->radioButtonAnB->setEnabled(true);
    ui->radioButtonAnC->setEnabled(true);
    ui->radioButtonAnD->setEnabled(true);

    // GUI verändern
    switch(angeklicktesObjekt){

    case PERSON_A:
        AktBankNummer       = 0;
        AktBankKundenNummer = 0;
        AktPersonenNr       = 0;
        LabelPersonen->setDaten(PERSON_A);
        ui->radioButtonAnA->setDisabled(true);
        ui->radioButtonAnB->setChecked(true);
        ui->stackedWidget->setCurrentIndex(0);
        break;


    case PERSON_B:
        AktBankNummer       = 0;
        AktBankKundenNummer = 1;
        AktPersonenNr       = 1;
        LabelPersonen->setDaten(PERSON_B);
        ui->radioButtonAnB->setDisabled(true);
        ui->radioButtonAnA->setChecked(true);
        ui->stackedWidget->setCurrentIndex(0);
        break;


    case PERSON_C:
        AktBankNummer       = 1;
        AktBankKundenNummer = 0;
        AktPersonenNr       = 2;
        LabelPersonen->setDaten(PERSON_C);
        ui->radioButtonAnC->setDisabled(true);
        ui->radioButtonAnD->setChecked(true);
        ui->stackedWidget->setCurrentIndex(0);
        break;


    case PERSON_D:
        AktBankNummer       = 1;
        AktBankKundenNummer = 1;
        AktPersonenNr       = 3;
        LabelPersonen->setDaten(PERSON_D);
        ui->radioButtonAnD->setDisabled(true);
        ui->radioButtonAnC->setChecked(true);
        ui->stackedWidget->setCurrentIndex(0);
        break;


    case BANK_X:
        AktBankNummer = 0;
        LabelBanken->setDaten(BANK_X);
        if(LinksKlick == true)  ui->stackedWidget->setCurrentIndex(1);
        if(LinksKlick == false) ui->stackedWidget->setCurrentIndex(4);

        // Gui
        ui->labelGeschaeftsbankBilanzsumme->setText(AlleDaten.Banken[0].Get_Bilanzsumme_as_String());
        ui->labelEigenkapitalquoteGeschaeftsbank->setText(AlleDaten.Banken[0].Get_EigenKapitalQuote_as_String());
        ui->labelSparkontoZinsen->setText(QString::number(100.0*Einstellungen.SparkontoZinsen()) + " %");
        ui->labelGirokontoZinsen->setText(QString::number(100.0*Einstellungen.GirokontoZinsen()) + " %");
        ui->labelKreditZinsen->setText(QString::number(100.0*Einstellungen.KreditZinsen()) + " %");
        ui->labelEigenkapitalrendite->setText(AlleDaten.Get_Eigenkapitalrendite_Bank(0));

        // Combobox einstellen
        ui->comboBoxWertpapiereVon->clear();
        ui->comboBoxWertpapiereVon->addItem("A");
        ui->comboBoxWertpapiereVon->addItem("B");
        break;


    case BANK_Y:
        AktBankNummer = 1;
        LabelBanken->setDaten(BANK_Y);
        if(LinksKlick == true)  ui->stackedWidget->setCurrentIndex(1);
        if(LinksKlick == false) ui->stackedWidget->setCurrentIndex(4);

        // Gui
        ui->labelGeschaeftsbankBilanzsumme->setText(AlleDaten.Banken[1].Get_Bilanzsumme_as_String());
        ui->labelEigenkapitalquoteGeschaeftsbank->setText(AlleDaten.Banken[1].Get_EigenKapitalQuote_as_String());
        ui->labelSparkontoZinsen->setText(QString::number(100.0*Einstellungen.SparkontoZinsen()) + " %");
        ui->labelGirokontoZinsen->setText(QString::number(100.0*Einstellungen.GirokontoZinsen()) + " %");
        ui->labelKreditZinsen->setText(QString::number(100.0*Einstellungen.KreditZinsen()) + " %");
        ui->labelEigenkapitalrendite->setText(AlleDaten.Get_Eigenkapitalrendite_Bank(1));

        // Combobox einstellen
        ui->comboBoxWertpapiereVon->clear();
        ui->comboBoxWertpapiereVon->addItem("C");
        ui->comboBoxWertpapiereVon->addItem("D");
        break;


    case ZENTRALBANK:
        ui->stackedWidget->setCurrentIndex(2);
        break;


    case DER_STAAT:
        ui->stackedWidget->setCurrentIndex(3);
        break;


    default:
        qDebug() << "Fehler bei der Auswahl";
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
        ui->actionLetzte_Operation_annimieren->setChecked(false);
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
 *  5) Wie funktioniert die Bankgründung?
 *
 */






