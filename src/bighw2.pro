QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutdialog.cpp \
    addrowdialog.cpp \
    colordelegate.cpp \
    comboboxdelegate.cpp \
    confirmcancel.cpp \
    confirmdelete.cpp \
    dateeditdelegate.cpp \
    main.cpp \
    mainwindow.cpp \
    searchdialog.cpp \
    universitymodel.cpp

HEADERS += \
    aboutdialog.h \
    addrowdialog.h \
    colordelegate.h \
    comboboxdelegate.h \
    confirmcancel.h \
    confirmdelete.h \
    dateeditdelegate.h \
    mainwindow.h \
    searchdialog.h \
    universitymodel.h

FORMS += \
    aboutdialog.ui \
    addrowdialog.ui \
    confirmcancel.ui \
    confirmdelete.ui \
    mainwindow.ui \
    searchdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
