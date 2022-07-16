QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminwin.cpp \
    authorizationwindow.cpp \
    database.cpp \
    fillresult.cpp \
    main.cpp \
    mainwindow.cpp \
    studentwindow.cpp \
    testforstudent.cpp

HEADERS += \
    adminwin.h \
    authorizationwindow.h \
    database.h \
    fillresult.h \
    mainwindow.h \
    studentwindow.h \
    tabwidget.h \
    testforstudent.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    adminwin.ui \
    authorizationwindow.ui \
    fillresult.ui \
    mainwindow.ui \
    studentwindow.ui \
    testforstudent.ui
