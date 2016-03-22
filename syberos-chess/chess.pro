TEMPLATE	= app
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

INCLUDEPATH	+= engine wrapper

HEADERS	+= engine/AlphaBetaEngine.h \
	engine/AlphaBeta_TTEngine.h \
	engine/Alphabeta_HH.h \
	engine/AspirationSearch.h \
	engine/Define.h \
	engine/Eveluation.h \
	engine/FAlphaBetaEngine.h \
	engine/HistoryHeuristic.h \
	engine/IDAlphabetaEngine.h \
	engine/MTD_fEngine.h \
	engine/MoveGenerator.h \
	engine/NegaMaxEngine.h \
	engine/NegaScout_TT_HH.h \
	engine/PVS_Engine.h \
	engine/SearchEngine.h \
	engine/TranspositionTable.h \
	wrapper/progress.h \
        wrapper/chessgame.h \
        main_form.h \
        configform.h

SOURCES	+= main.cpp \
        main_form.cpp \
        configform.cpp \
	engine/AlphaBetaEngine.cpp \
	engine/AlphaBeta_TTEngine.cpp \
	engine/Alphabeta_HH.cpp \
	engine/AspirationSearch.cpp \
	engine/Eveluation.cpp \
	engine/FAlphaBetaEngine.cpp \
	engine/HistoryHeuristic.cpp \
	engine/IDAlphabetaEngine.cpp \
	engine/MTD_fEngine.cpp \
	engine/MoveGenerator.cpp \
	engine/NegaMaxEngine.cpp \
	engine/NegaScout_TT_HH.cpp \
	engine/PVS_Engine.cpp \
	engine/SearchEngine.cpp \
	engine/TranspositionTable.cpp \
	wrapper/chessgame.cpp

#The following line was changed from FORMS to FORMS3 by qt3to4
#FORMS = main_form.ui \
#	configform.ui

unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

RESOURCES += \
    image.qrc

