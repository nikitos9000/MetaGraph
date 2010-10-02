# -------------------------------------------------
# Project created by QtCreator 2010-01-13T21:15:37
# -------------------------------------------------
# QT -= gui
TARGET = FastGraph

# CONFIG += console
# CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cpp \
    DiGraph.cpp \
    DiGraphWeighted.cpp \
    Path.cpp \
    VertexSet.cpp \
    ArcSet.cpp \
    GView.cpp \
    GController.cpp \
    GModel.cpp \
    GStorage.cpp \
    WindowMain.cpp
HEADERS += DiGraph.h \
    DiGraphWeighted.h \
    Path.h \
    VertexSet.h \
    ArcSet.h \
    GController.h \
    GModel.h \
    GView.h \
    GStorage.h \
    Base.h \
    WindowMain.h \
    IDiGraph.h \
    IDiGraphWeighted.h \
    DiGraphCore.h \
    IPath.h \
    square_matrix.h \
    test.h
FORMS += WindowMain.ui
