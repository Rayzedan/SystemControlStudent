QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwin.cpp \
    adminwindow.cpp \
    authorizationwindow.cpp \
    basewindow.cpp \
    changesettings.cpp \
    courseedit.cpp \
    departedit.cpp \
    fillresult.cpp \
    main.cpp \
    mainwindow.cpp \
    questionedit.cpp \
    resultswindow.cpp \
    studentwindow.cpp \
    testforstudent.cpp \
    topicedit.cpp

HEADERS += \
    adminwin.h \
    adminwindow.h \
    authorizationwindow.h \
    basewindow.h \
    changesettings.h \
    connection.h \
    courseedit.h \
    departedit.h \
    fillresult.h \
    mainwindow.h \
    questionedit.h \
    resultswindow.h \
    studentwindow.h \
    tabwidget.h \
    testforstudent.h \
    topicedit.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    adminwin.ui \
    adminwindow.ui \
    authorizationwindow.ui \
    basewindow.ui \
    changesettings.ui \
    courseedit.ui \
    departedit.ui \
    fillresult.ui \
    mainwindow.ui \
    questionedit.ui \
    resultswindow.ui \
    studentwindow.ui \
    testforstudent.ui \
    topicedit.ui
