#-------------------------------------------------
#
# Project created by QtCreator 2017-04-21T12:34:06
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DnfLogin
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
        widget.cpp \
    clickablelabel.cpp \
    regeditdialog.cpp \
    forgetdialog.cpp \
    aes_cbc.cpp \
    httpaesrequest.cpp \
    util.cpp \
    repasswddialog.cpp \
    checkqlineedit.cpp

HEADERS  += widget.h \
    clickablelabel.h \
    regeditdialog.h \
    forgetdialog.h \
    aes_cbc.h \
    httpaesrequest.h \
    util.h \
    repasswddialog.h \
    checkqlineedit.h

FORMS    += widget.ui \
    regeditdialog.ui \
    forgetdialog.ui \
    repasswddialog.ui
RC_FILE = DnfLogin.rc

DISTFILES += \
    manifest.xml
