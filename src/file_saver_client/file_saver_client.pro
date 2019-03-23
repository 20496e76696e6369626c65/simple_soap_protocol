QT       += core gui widgets


TARGET = FileSaverClient
TEMPLATE = app


SOURCES +=\
           soapC.cpp \
           soapFileSaverProxy.cpp \
           main.cc \
           soap_client_widget.cc

HEADERS  += \
            soapStub.h \
            soapH.h \
            soapFileSaverProxy.h \
            FileSaver.nsmap \
            soap_client_widget.h

include( ../../common.pri )
