TEMPLATE = app
TARGET = syberos-chess

QT += qml quick

INCLUDEPATH	+= src src/engine

HEADERS	+= src/engine/Define.h \
        src/engine/Eveluation.h \
        src/engine/HistoryHeuristic.h \
        src/engine/MoveGenerator.h \
        src/engine/NegaScout_TT_HH.h \
        src/engine/SearchEngine.h \
        src/engine/TranspositionTable.h \
        src/chessgame.h

SOURCES	+= src/main.cpp \
        src/engine/Eveluation.cpp \
        src/engine/HistoryHeuristic.cpp \
        src/engine/MoveGenerator.cpp \
        src/engine/NegaScout_TT_HH.cpp \
        src/engine/SearchEngine.cpp \
        src/engine/TranspositionTable.cpp \
        src/chessgame.cpp

MOC_DIR = .moc
OBJECTS_DIR = .obj

RESOURCES += \
    image.qrc \
    qml.qrc
DISTFILES += qml/*.qml
