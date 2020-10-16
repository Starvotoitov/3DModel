QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    doubleslider.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    modeladder.cpp \
    modelchooser.cpp \
    modelcustomizer.cpp \
    modelparameters.cpp \
    modelviewer.cpp \
    objparser.cpp \
    polygonalface.cpp \
    space3d.cpp \
    texturecoordinates.cpp \
    vertex.cpp \
    vertexnormal.cpp

HEADERS += \
    camera.h \
    doubleslider.h \
    mainwindow.h \
    model.h \
    modeladder.h \
    modelchooser.h \
    modelcustomizer.h \
    modelparameters.h \
    modelviewer.h \
    objparser.h \
    polygonalface.h \
    polygonvertex.h \
    projectiontype.h \
    space3d.h \
    texturecoordinates.h \
    vertex.h \
    vertexnormal.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
