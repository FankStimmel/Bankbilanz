#include "dialoginfo.h"
#include "ui_dialoginfo.h"

DialogInfo::DialogInfo(QWidget *parent) : QDialog(parent), ui(new Ui::DialogInfo){
    ui->setupUi(this);
    ui->textEdit->setHtml(
        "<b>Gebrüder Rothschild, London 1863:</b><br>"
        "Die Wenigen, die das System verstehen, werden dermaßen"
        " an seinen Profiten interessiert oder so abhängig von "
        "seinen Vorzügen sein, daß aus ihren Reihen niemals eine"
        " Opposition hervorgehen wird. Die große Masse der Leute"
        " aber, geistig unfähig zu begreifen, wird seine Last ohne"
        " Murren tragen, vielleicht sogar ohne je Verdacht zu "
        "schöpfen, dass das System ihnen feindlich ist."
        "<br>"
        "<br>"
        "<b>Mayer Amschel Rothschild (1744 – 1812):</b><br>"
        "Gib mir die Kontrolle über das Geld einer Nation und es"
        " interessiert mich nicht, wer dessen Gesetze macht."
        "<br>"
        "<br>"
        "<b>Henry Ford (1863 – 1947):</b><br>"
        "Eigentlich ist es gut, dass die Menschen der Nation "
        "unser Banken- und Geldsystem nicht verstehen. Würden"
        " sie es nämlich, so hätten wir eine Revolution noch"
        " vor morgen früh."
        "<br>"
        "<br>"
        "<b>Bertolt Brecht:</b><br>"
        "Bankraub ist eine Initiative von Dilettanten. Wahre Profis gründen eine Bank."
        "<br>"
        "<br>"
        "<b>Theodore Roosevelt: (1858 – 1919), 26. Präsident der USA</b><br>"
        "Eine große Industrienation wird von ihrem Kreditsystem kontrolliert. Unser"
        " Kreditsystem liegt konzentriert in den Händen einiger Weniger. Wir sind zu"
        " einer der schlecht regiertesten, eine der am meist kontrollierten und"
        " dominierten Regierung der Welt geworden. Nicht länger eine Regierung der"
        " freien Meinung, nicht länger eine Regierung der Überzeugung und Wahlen der"
        " Mehrheit, sondern eine Regierung der Meinung und Zwang einer kleinen"
        " Gruppe dominierender Menschen."
        );
    }


DialogInfo::~DialogInfo(){
    delete ui;
    }
