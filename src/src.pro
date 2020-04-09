#-------------------------------------------------
#
# Project created by QtCreator 2020-04-09T12:20:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MinecraftLauncher
TEMPLATE = app

CONFIG(debug, debug|release):CONFIGURATION=debug
CONFIG(release, debug|release):CONFIGURATION=release

build_pass:CONFIG(debug, debug|release) {
    TARGET = $$join(TARGET,,,_debug)
}

OBJECTS_DIR         = ../build/obj/$${CONFIGURATION}
MOC_DIR             = ../build/$${CONFIGURATION}
RCC_DIR             = ../build/rcc
UI_DIR              = ../build/ui
DESTDIR             = ../bin

CONFIG += c++11
QMAKE_CXXFLAGS += "-std=c++11"

win32|win64{
    RC_FILE=  index.rc
    OTHER_FILES+= index.rc
    DISTFILES += index.rc
}

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    global.cpp

HEADERS += \
        mainwindow.h \
    global.h

FORMS += \
        mainwindow.ui

TRANSLATIONS = lang/ru_RU.ts

exists(./gitversion.pri):include(./gitversion.pri)

RESOURCES += \
    resources.qrc
