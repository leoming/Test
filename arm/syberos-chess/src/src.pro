TEMPLATE = app
TARGET = chess
CONFIG -= app_bundle
CONFIG += qml_debug link_pkgconfig
PKGCONFIG += syberos-application syberos-application-cache
QT += qml quick gui widgets

INCLUDEPATH	+= . engine

HEADERS	+= engine/Define.h \
        engine/Eveluation.h \
        engine/HistoryHeuristic.h \
        engine/MoveGenerator.h \
        engine/NegaScout_TT_HH.h \
        engine/SearchEngine.h \
        engine/TranspositionTable.h \
        chessgame.h \
        chessspace.h

SOURCES	+= main.cpp \
        engine/Eveluation.cpp \
        engine/HistoryHeuristic.cpp \
        engine/MoveGenerator.cpp \
        engine/NegaScout_TT_HH.cpp \
        engine/SearchEngine.cpp \
        engine/TranspositionTable.cpp \
        chessgame.cpp \
        chessspace.cpp

MOC_DIR = .moc
OBJECTS_DIR = .obj

RESOURCES += \
    ../image.qrc \
    ../qml.qrc


target.path = /usr/apps/syberos-chess/bin
INSTALLS += target
