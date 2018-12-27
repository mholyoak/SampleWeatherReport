QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SampleWeatherReport
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG+=sdk_no_version_check

SOURCES += \
        main.cpp \
        weatherreportwindow.cpp \
    locationweather.cpp \
    openweathermapreporter.cpp \
    restresponse.cpp \
    curlrestrequester.cpp \
    ThirdParty/jsoncpp/dist/jsoncpp.cpp \
    weatherdetaildialog.cpp \
    addcitydialog.cpp

HEADERS += \
        weatherreportwindow.h \
    iweatherreporter.h \
    locationweather.h \
    openweathermapreporter.h \
    restresponse.h \
    irestrequester.h \
    curlrestrequester.h \
    weatherdetaildialog.h \
    addcitydialog.h

FORMS += \
        weatherreportwindow.ui \
    weatherdetaildialog.ui \
    addcitydialog.ui

#INCLUDEPATH += /usr/local/include
INCLUDEPATH += $$PWD/ThirdParty/jsoncpp/include

LIBS += -lcurl
#libs += -L/usr/local/lib -ljsoncpp
#libs += -L$$PWD/ThirdParty/jsoncpp -l jsoncpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
