QT       += core

QT       -= gui

TARGET = FileSaverService
CONFIG   += console
CONFIG   -= app_bundle


TEMPLATE = app

SOURCES += main.cc \
    soapC.cpp \
    soapFileSaverService.cpp \
    file_saver_server_impl.cc

HEADERS += \
    soapStub.h \
    soapH.h \
    soapFileSaverService.h \
    FileSaver.nsmap \
    file_saver_server_impl.h \
    SOAPServiceController.h

DEFINES += WITH_PURE_VIRTUAL


include( ../../common.pri )
