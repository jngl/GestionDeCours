#-------------------------------------------------
#
# Project created by QtCreator 2014-10-28T12:38:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GestionDeCours
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
    View/mainwindow.cpp \
    Model/ProjectTree/project.cpp \
    Model/ProjectTree/projectsroot.cpp \
    Model/TableModel/model.cpp \
    Model/modelcalendrier.cpp \
    Model/TableModel/modelforeignkey.cpp \
    Model/TableModel/modelmetadata.cpp \
    Model/TableModel/modelrow.cpp \
    Model/ProjectTree/tree.cpp \
    Model/ProjectTree/item.cpp \
    Model/factory.cpp \
    View/delegate.cpp \
    View/foreignkeyeditor.cpp

HEADERS  += \
    View/mainwindow.h \
    Model/ProjectTree/project.h \
    Model/ProjectTree/projectsroot.h \
    Model/TableModel/model.h \
    Model/modelcalendrier.h \
    Model/TableModel/modelforeignkey.h \
    Model/TableModel/modelmetadata.h \
    ModelTableModel//modelrow.h \
    Model/ProjectTree/tree.h \
    Model/ProjectTree/item.h \
    Model/TableModel/modelrow.h \
    Model/factory.h \
    View/delegate.h \
    View/foreignkeyeditor.h

FORMS += \
    View/mainwindow.ui
