#-------------------------------------------------
#
# Project generated by QtCreator for SyberOS.
#
#-------------------------------------------------

QML_IMPORT_PATH = $$[QT_INSTALL_QML]

RESOURCES += qml.qrc \
             image.qrc


CONFIG += link_pkgconfig

PKGCONFIG += syberos-application syberos-application-cache

# This is needed for using syberos-application and syberos-qt module
INCLUDEPATH += $$[QT_INSTALL_HEADERS]/../syberos_application \
                           $$[QT_INSTALL_HEADERS]/../framework \
                    src \
                    src/engine

QT += gui qml quick

TARGET = chess

#Please Do not modify these macros, otherwise your app will not installed correctly and will not run at all.
APP_DIR = /data/apps
APP_DATA = /data/data
INS_DIR = $$APP_DIR/com.syberos.chess
DATA_DIR = $$APP_DATA/com.syberos.chess

DEFINES += SOP_ID=\\\"com.syberos.chess\\\"
DEFINES += APP_DIR_ENVVAR=\\\"APPDIR_REGULAR\\\"
# Currently home screen sets the environment variable, so when run from
# elsewhere, use this work-around instead.
DEFINES += APP_DIR=\\\"$$APP_DIR\\\"

# The .cpp file which was generated for your project.
SOURCES += src/main.cpp \
           src/chess_Workspace.cpp \
           src/engine/Eveluation.cpp \
           src/engine/HistoryHeuristic.cpp \
           src/engine/MoveGenerator.cpp \
           src/engine/NegaScout_TT_HH.cpp \
           src/engine/SearchEngine.cpp \
           src/engine/TranspositionTable.cpp \
           src/chessgame.cpp
HEADERS += src/chess_Workspace.h \
        src/engine/Define.h \
        src/engine/Eveluation.h \
        src/engine/HistoryHeuristic.h \
        src/engine/MoveGenerator.h \
        src/engine/NegaScout_TT_HH.h \
        src/engine/SearchEngine.h \
        src/engine/TranspositionTable.h \
        src/chessgame.h

# Installation path
target.path = $$INS_DIR/bin

res.files = res
res.path = $$INS_DIR/

meta.files = META-INF
meta.path = $$INS_DIR/

syber.files = sopconfig.xml
syber.path = $$INS_DIR/

audio.files = audio/audio_move_chess.ogg
audio.path = $$INS_DIR/audio

INSTALLS += target res meta syber audio

QML_FILES = qml/*.qml

OTHER_FILES += $$QML_FILES *.qm
               
