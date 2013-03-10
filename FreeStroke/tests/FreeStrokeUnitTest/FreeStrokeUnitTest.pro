#-------------------------------------------------
#
# Project created by QtCreator 2013-01-07T15:23:25
#
#-------------------------------------------------


include(../../project/FreeStroke.pri)

DEFINES += UNITTEST \
        QT_CREATOR_ENV

unix:!mac:QMAKE_CXXFLAGS += -std=gnu++0x

DESTDIR = ./

QT       += qt3support
QT       += xml
#QT       -= gui

TARGET = FreeStrokeUnitTest
CONFIG   += console
CONFIG   -= app_bundle

OBJECTS_DIR = ./build/
MOC_DIR = ./build/
UI_DIR = ./build/

TEMPLATE = app

SOURCES +=  sources/mainTest.cpp \
            sources/test.cpp \
            sources/keytest.cpp \
            sources/daolayertest.cpp \
            sources/gesturetest.cpp \
            sources/rawjointstatetest.cpp \
            sources/vector3test.cpp \
            sources/inputgesturetest.cpp \
            sources/gesturefeaturestest.cpp \
            sources/historyrecordtest.cpp \
            sources/allfeaturestest.cpp \
            sources/segmentertest.cpp \
            sources/skeletondatatest.cpp \
            sources/lraconvergedtest.cpp \
            sources/lrasigmoidtest.cpp \
            sources/logisticregressionalgorithmtest.cpp \
            sources/recognizertest.cpp \
            sources/xmltest.cpp \
            sources/xmlconfigtest.cpp \
            sources/controllertest.cpp \
            sources/networkfulltest.cpp \
            sources/networkclienttest.cpp \
            sources/networkservertest.cpp \
            sources/networkloggertest.cpp \
            sources/executionmgrtest.cpp \
            sources/utilstest.cpp \
            sources/commandtest.cpp \
            sources/recordtest.cpp \
            ../../tools/FakeServer/KControllerCopy/kutils.cpp \
            ../../tools/FakeServer/KControllerCopy/logger.cpp \
            ../../tools/FakeServer/KControllerCopy/kinect.cpp
#            ../../tools/FakeServer/KControllerCopy/serverutils.cpp \
#            ../../tools/FakeServer/KControllerCopy/tcpserver.cpp \
#            ../../tools/FakeServer/KControllerCopy/udpserver.cpp \
#            ../../tools/FakeServer/KControllerCopy/abstractkserver.cpp \
#            ../../tools/FakeServer/sources/fakeserver.cpp

HEADERS +=  includes/test.h \
            includes/keytest.h \
            includes/daolayertest.h \
            includes/gesturetest.h \
            includes/rawjointstatetest.h \
            includes/vector3test.h \
            includes/inputgesturetest.h \
            includes/gesturefeaturestest.h \
            includes/historyrecordtest.h \
            includes/allfeaturestest.h \
            includes/lraconvergedtest.h \
            includes/lrasigmoidtest.h \
            includes/skeletondatatest.h \
            includes/segmentertest.h \
            includes/logisticregressionalgorithmtest.h \
            includes/recognizertest.h \
            includes/xmltest.h \
            includes/xmlconfigtest.h \
            includes/controllertest.h \
            includes/networkfulltest.h \
            includes/networkclienttest.h \
            includes/networkservertest.h \
            includes/networkloggertest.h \
            includes/executionmgrtest.h \
            includes/utilstest.h \
            includes/commandtest.h \
            includes/recordtest.h \
            ../../tools/FakeServer/KControllerCopy/kutils.h \
            ../../tools/FakeServer/KControllerCopy/logger.h \
            ../../tools/FakeServer/KControllerCopy/kinect.h
#            ../../tools/FakeServer/KControllerCopy/serverutils.h \
#            ../../tools/FakeServer/KControllerCopy/tcpserver.h \
#            ../../tools/FakeServer/KControllerCopy/udpserver.h \
#            ../../tools/FakeServer/KControllerCopy/abstractkserver.h \
#            ../../tools/FakeServer/includes/fakeserver.h

!win32 {
    LIBS += -lcppunit
}

win32 {
    INCLUDEPATH += libs/cppunit/include \
                    ../../project/win32

    LIBS += ./libs/cppunit/lib/libcppunit-1-12-1.dll
}
