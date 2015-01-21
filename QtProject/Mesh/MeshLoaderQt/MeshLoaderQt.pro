#-------------------------------------------------
#
# Project created by QtCreator 2013-11-08T15:38:49
#
#-------------------------------------------------

#add opengl to QT config
QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


#usual things
TARGET = MeshLoaderQt
CONFIG   -= app_bundle
CONFIG   += console
TEMPLATE = app

#add local sources and headers

SOURCES +=  main.cpp\
            Mesh.cpp\
            NeighborMesh.cpp\
            Useful.cpp \
            laplacianmesh.cpp \
    myglwidget.cpp \
    mainwindow.cpp \
    scenegl.cpp

HEADERS +=  Mesh.h\
            NeighborMesh.h\
            Useful.h\
            Constante.h\
            Stopwatch.h \
            laplacianmesh.h \
    myglwidget.h \
    mainwindow.h \
    scenegl.h


#to include the GL and Eigen directories which are 3 directories above the current project directory
#I put the libs, Eigen, the opengl Headers in the same directory so the following instruction applies for all of them:
INCLUDEPATH += ..\..\..

#to link the dlls
LIBS += -lglut32 -lglu32 -lopengl32

OTHER_FILES +=

FORMS += \
    mainwindow.ui

RESOURCES +=





