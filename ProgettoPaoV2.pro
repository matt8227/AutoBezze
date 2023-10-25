QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cliente.cpp \
    data.cpp \
    handler.cpp \
    home.cpp \
    inseriscicliente.cpp \
    inseriscimanutenzione.cpp \
    inseriscimeccanico.cpp \
    ioutility.cpp \
    lineedit.cpp \
    main.cpp \
    mainwindow.cpp \
    manutenzione.cpp \
    meccanico.cpp \
    model.cpp \
    mostraclienti.cpp \
    mostramanutenzioni.cpp \
    mostrameccanici.cpp \
    persona.cpp \
    presenter.cpp \
    privato.cpp \
    rappresentante.cpp

HEADERS += \
    DeepPtr.h \
    cliente.h \
    data.h \
    handler.h \
    home.h \
    inseriscicliente.h \
    inseriscimanutenzione.h \
    inseriscimeccanico.h \
    ioutility.h \
    lineedit.h \
    mainwindow.h \
    manutenzione.h \
    meccanico.h \
    model.h \
    mostraclienti.h \
    mostramanutenzioni.h \
    mostrameccanici.h \
    persona.h \
    presenter.h \
    privato.h \
    rappresentante.h \
    vett.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
