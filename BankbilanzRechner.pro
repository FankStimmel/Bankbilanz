#-------------------------------------------------
#
# Project created by QtCreator 2015-11-24T14:28:31
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BankbilanzRechner
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        Bilanzen/geschaeftsbankbilanz.cpp \
        feinstellungen.cpp \
        Viewport/fgraphicsobjectzentralbankbilanz.cpp\
        Viewport/fgraphicsobjectgeschaeftsbankbilanz.cpp\
        Viewport/fgraphicsobjectperson.cpp\
        Viewport/fgraphicsobjectstaat.cpp\
        Operatoren/ffinanztransaktion.cpp\
        Operatoren/faktionkundehebtbargeldab.cpp \
        Operatoren/faktioninitialisiereallebilanzen.cpp \
        Operatoren/faktionstaatverkauftstaatsanleihen.cpp \
        Operatoren/faktionbankverkauftstaatsanleiheanzbank.cpp\
        Operatoren/faktionresetallebilanzentonull.cpp\
        Operatoren/faktioneinjahristvorbei.cpp \
        Bilanzen/fallebilanzen.cpp \
        Bilanzen/fzentralbankbilanz.cpp \
        Bilanzen/fperson.cpp \
        Bilanzen/fstaat.cpp \
        Operatoren/faktionbankkauftwertpapiere.cpp \
        Operatoren/faktionbanktauschtbargeldinzentralbankgeld.cpp \
        Operatoren/faktionkundeuebergibtbargeldan.cpp \
        Operatoren/faktionkundenimmtkreditauf.cpp \
        Operatoren/faktionbanklegteigenkapitalein.cpp \
        Operatoren/faktionkundeueberweistgiralgeldan.cpp \
        Operatoren/faktionbanknimmtkreditbeiderzbankauf.cpp \
        Operatoren/faktionbankzahltkreditbeiderzbankzurueck.cpp \
        Operatoren/faktionkundezahltkreditzurueck.cpp \
        Operatoren/faktionbanktauschtzentralbankgeldinbargeld.cpp \
        Viewport/fviewport.cpp \
        Operatoren/faktionkundezahltbargeldein.cpp \
        Operatoren/faktionstaatkauftstaatsanleihen.cpp \
        Operatoren/faktionstaatueberweistgiralgeldan.cpp \
        fmylabel.cpp \
        Operatoren/faktionkundezahltsparbuchgeldein.cpp \
        Operatoren/faktionkundehebtsparbuchgeldab.cpp \
    fmyclearingwidget.cpp \
    Operatoren/faktionclearingverfahrenausfuehren.cpp


HEADERS  += mainwindow.h \
        Bilanzen/geschaeftsbankbilanz.h \
        feinstellungen.h \
        Viewport/fgraphicsobjectzentralbankbilanz.h\
        Viewport/fgraphicsobjectgeschaeftsbankbilanz.h\
        Viewport/fgraphicsobjectperson.h\
        Viewport/fgraphicsobjectstaat.h\
        Operatoren/ffinanztransaktion.h\
        Operatoren/faktionkundehebtbargeldab.h \
        Operatoren/faktioninitialisiereallebilanzen.h \
        Operatoren/faktionstaatverkauftstaatsanleihen.h \
        Operatoren/faktionbankverkauftstaatsanleiheanzbank.h\
        Operatoren/faktionresetallebilanzentonull.h\
        Operatoren/faktioneinjahristvorbei.h \
        Bilanzen/fallebilanzen.h \
        Bilanzen/fzentralbankbilanz.h \
        Bilanzen/fperson.h \
        Bilanzen/fstaat.h \
        Operatoren/faktionbankkauftwertpapiere.h \
        Operatoren/faktionbanktauschtbargeldinzentralbankgeld.h \
        Operatoren/faktionkundeuebergibtbargeldan.h \
        Operatoren/faktionkundenimmtkreditauf.h \
        Operatoren/faktionbanklegteigenkapitalein.h \
        Operatoren/faktionkundeueberweistgiralgeldan.h \
        Operatoren/faktionbanknimmtkreditbeiderzbankauf.h \
        Operatoren/faktionbankzahltkreditbeiderzbankzurueck.h \
        Operatoren/faktionkundezahltkreditzurueck.h \
        Operatoren/faktionbanktauschtzentralbankgeldinbargeld.h \
        Viewport/fviewport.h \
        Operatoren/faktionkundezahltbargeldein.h \
        Operatoren/faktionstaatkauftstaatsanleihen.h \
        Operatoren/faktionstaatueberweistgiralgeldan.h \
        fmylabel.h \
        Operatoren/faktionkundezahltsparbuchgeldein.h \
        Operatoren/faktionkundehebtsparbuchgeldab.h \
    fmyclearingwidget.h \
    Operatoren/faktionclearingverfahrenausfuehren.h


FORMS    += mainwindow.ui \
    fmyclearingwidget.ui

RESOURCES += \
    myresources.qrc
