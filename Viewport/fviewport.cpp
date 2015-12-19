#include "fviewport.h"

FViewport::FViewport(QWidget *parent):QGraphicsView(parent){

    // Wert initialisieren
    Zeit = 0;


    // Scene
    scene = new QGraphicsScene;
    //scene->setSceneRect(400, 0, 100, height());
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);


    // Alle Personen erzeugen und initialisieren.
    AllePersonen.append(new FGrapicsObjectPerson(0));
    AllePersonen.append(new FGrapicsObjectPerson(1));
    AllePersonen.append(new FGrapicsObjectPerson(2));
    AllePersonen.append(new FGrapicsObjectPerson(3));

    AllePersonen[0]->Set_Object_visual_marked(true);

    // Alle Personen positionieren und in die Scene einfügen.
    for(int i=0; i<4;i++){
        AllePersonen[i]->setPos(i*173, 270);
        scene->addItem(AllePersonen[i]);
        connect(AllePersonen[i],
                SIGNAL(IdNummer_von_Person_wurde_gesendet(BILANZOBJEKTE, bool)),
                this,
                SLOT(Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE, bool)));
        }



    // Staat erzeugen und initialisieren, positionieren und in die Scene einfügen.
    Staat = new FGraphicsObjectStaat;
    Staat->IdNummer = 7;
    Staat->setPos(4*173, 270);
    scene->addItem(Staat);
    connect(Staat,
            SIGNAL(IdNummer_vom_Staat_wurde_gesendet(BILANZOBJEKTE, bool)),
            this,
            SLOT(Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE, bool)));



    // Banken erzeugen und initialisieren
    FGraphicsObjectGeschaeftsBankbilanz *GeschaeftsbankbilanzA = new FGraphicsObjectGeschaeftsBankbilanz;
    FGraphicsObjectGeschaeftsBankbilanz *GeschaeftsbankbilanzB = new FGraphicsObjectGeschaeftsBankbilanz;
    GeschaeftsbankbilanzA->BankNummer = 0;
    GeschaeftsbankbilanzB->BankNummer = 1;
    AlleBanken << GeschaeftsbankbilanzA << GeschaeftsbankbilanzB;

    // Alle Bankbilanzen positionieren und in die Scene einfügen.
    for(int i=0; i<2; i++){
        AlleBanken[i]->setPos(i*450, -30);
        scene->addItem(AlleBanken[i]);
        connect(AlleBanken[i],
                SIGNAL(IdNummer_von_Geschaeftsbank_wurde_gesendet(BILANZOBJEKTE, bool)),
                this,
                SLOT(Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE, bool)));
        }



    // Zentralbank erzeugen und initialisieren, positionieren und in die Scene einfügen.
    Zentralbankbilanz = new FGraphicsObjectZentralBankBilanz;
    Zentralbankbilanz->IdNummer = 6;
    Zentralbankbilanz->setPos(130,-310);
    scene->addItem(Zentralbankbilanz);
    connect(Zentralbankbilanz,
            SIGNAL(IdNummer_von_Zentralbank_wurde_gesendet(BILANZOBJEKTE, bool)),
            this,
            SLOT(Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE, bool)));



    // Alles Anzeigen
    setRenderHint(QPainter::Antialiasing, true);
    setScene(scene);
    show();
    }


//##########################################################################################################################


void FViewport::Alles_neu_zeichnen(FAlleDaten AlleDATEN){
    AlleDaten = AlleDATEN;

    Zentralbankbilanz->Neu_zeichnen(AlleDaten);


    AlleBanken[0]->Neu_zeichnen(AlleDaten);
    AlleBanken[1]->Neu_zeichnen(AlleDaten);

    AllePersonen[0]->Neu_zeichnen(AlleDaten);
    AllePersonen[1]->Neu_zeichnen(AlleDaten);
    AllePersonen[2]->Neu_zeichnen(AlleDaten);
    AllePersonen[3]->Neu_zeichnen(AlleDaten);

    Staat->Neu_zeichnen(AlleDaten);
    }


//##########################################################################################################################


void FViewport::Set_Zentralbankbilanz_sichtbar(bool sichtbar){

    // unsichtbar
    if( !sichtbar ){
        for(int i=0; i<2; i++)  AlleBanken[i]->setPos(i*450, -50);
        Zentralbankbilanz->setVisible(false);
        }

    // Sichtbar
    if( sichtbar ){
        for(int i=0; i<2; i++)  AlleBanken[i]->setPos(i*450, -15);
        Zentralbankbilanz->setVisible(true);
        }
    }


//##########################################################################################################################


void FViewport::Objekt_mit_Id_Nummer_wurde_geklicked(BILANZOBJEKTE BilanzObjekt, bool LinksKlick){

    // Alle Objekte nicht markieren
    AllePersonen[0]->Set_Object_visual_marked(false);
    AllePersonen[1]->Set_Object_visual_marked(false);
    AllePersonen[2]->Set_Object_visual_marked(false);
    AllePersonen[3]->Set_Object_visual_marked(false);
    AlleBanken[0]->Set_Object_visual_marked(false);
    AlleBanken[1]->Set_Object_visual_marked(false);
    Zentralbankbilanz->Set_Object_visual_marked(false);
    Staat->Set_Object_visual_marked(false);


    // geklicktes Objekt markieren
    if(BilanzObjekt == PERSON_A)    AllePersonen[0]->Set_Object_visual_marked(true);
    if(BilanzObjekt == PERSON_B)    AllePersonen[1]->Set_Object_visual_marked(true);
    if(BilanzObjekt == PERSON_C)    AllePersonen[2]->Set_Object_visual_marked(true);
    if(BilanzObjekt == PERSON_D)    AllePersonen[3]->Set_Object_visual_marked(true);
    if(BilanzObjekt == BANK_A)      AlleBanken[0]->Set_Object_visual_marked(true);
    if(BilanzObjekt == BANK_B)      AlleBanken[1]->Set_Object_visual_marked(true);
    if(BilanzObjekt == ZENTRALBANK) Zentralbankbilanz->Set_Object_visual_marked(true);
    if(BilanzObjekt == DER_STAAT)   Staat->Set_Object_visual_marked(true);


    // Signal
    emit IdNummer_wurde_gesendet(BilanzObjekt, LinksKlick);
    }









