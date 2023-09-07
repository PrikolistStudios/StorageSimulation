QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Building.cpp \
    Identificator.cpp \
    Manager.cpp \
    Price.cpp \
    Product.cpp \
    Query.cpp \
    Timer.cpp \
    Wrapper.cpp \
    main.cpp \
    productsparameters.cpp \
    simresultdialogue.cpp \
    simulationparameters.cpp \
    simwindow.cpp

HEADERS += \
    Building.h \
    Identificator.h \
    MTime.h \
    Manager.h \
    Price.h \
    Product.h \
    Query.h \
    Wrapper.h \
    productsparameters.h \
    simresultdialogue.h \
    simulationparameters.h \
    simwindow.h

FORMS += \
    productsparameters.ui \
    simresultdialogue.ui \
    simulationparameters.ui \
    simwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
