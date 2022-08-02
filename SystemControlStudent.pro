QT       += core gui sql
QT       += printsupport
QT       += core5compat
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addusers.cpp \
    adminwin.cpp \
    authorizationwindow.cpp \
    chaptersettings.cpp \
    database.cpp \
    fillresult.cpp \
    main.cpp \
    mainwindow.cpp \
    settingsquestion.cpp \
    studentwindow.cpp \
    testforstudent.cpp

HEADERS += \
    addusers.h \
    adminwin.h \
    authorizationwindow.h \
    chaptersettings.h \
    database.h \
    fillresult.h \
    mainwindow.h \
    settingsquestion.h \
    studentwindow.h \
    tabwidget.h \
    testforstudent.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    addusers.ui \
    adminwin.ui \
    authorizationwindow.ui \
    chaptersettings.ui \
    fillresult.ui \
    mainwindow.ui \
    settingsquestion.ui \
    studentwindow.ui \
    testforstudent.ui

RESOURCES += \
    resourses.qrc

DISTFILES += \
    resourses/L.png \
    resourses/R.png \
    resourses/icons8-expand-arrow-50.png
