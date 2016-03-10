TEMPLATE = app
TARGET = fruit_ninija

CONFIG -= app_bundle
CONFIG += qml_debug link_pkgconfig
QT += core quick gui widgets 
INCLUDEPATH += /usr/bin
MOC_DIR = .obj
OBJECTS_DIR = .obj
SOURCES +=  main.cpp 

#HEADERS +=  fruit_ninija_space.h

RESOURCES += ../qml/qml.qrc
RESOURCES += ../qml/image.qrc

