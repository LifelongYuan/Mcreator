QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ccamera.cpp \
    file_tb.cpp \
    filter_tb.cpp \
    geommodel.cpp \
    main.cpp \
    mainmodel.cpp \
    mainwindow.cpp \
    modelview.cpp \
    multi_toolbar.cpp

HEADERS += \
    ccamera.h \
    file_tb.h \
    filter_tb.h \
    geommodel.h \
    mainmodel.h \
    mainwindow.h \
    modelview.h \
    multi_toolbar.h

LIBS += -lOpengl32 \
        -lglu32 \
        -lglut64
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
