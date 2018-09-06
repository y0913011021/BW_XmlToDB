#-------------------------------------------------
#
# Project created by QtCreator 2018-08-31T16:20:59
#
#-------------------------------------------------

QT       += core

QT      += sql

QT       -= gui

TARGET = BW_XmlToDB
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBRARYPATH = ../lib
include ( $$LIBRARYPATH/global/global.prf )


SOURCES += main.cpp database.cpp xml_reader.cpp

HEADERS += database.h Define.h xml_reader.h
