#-------------------------------------------------
#
# Project created by QtCreator 2017-07-26T17:43:33
#
#-------------------------------------------------

QT       += core gui
QT       += sql
# QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Restaurant
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    loginwindow.cpp \
    signupwindow.cpp \
    menuwindow.cpp \
    menudelegate.cpp \
    choosetablewindow.cpp

HEADERS  += mainwindow.h \
    loginwindow.h \
    account.h \
    signupwindow.h \
    menu.h \
    menuwindow.h \
    menudelegate.h \
    tables.h \
    choosetablewindow.h \
    values.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    signupwindow.ui \
    menuwindow.ui \
    choosetablewindow.ui

DISTFILES += \
    readme.txt \
    menu.txt

RESOURCES += \
    images.qrc \
    restaurant.qrc
