#-------------------------------------------------
#
# Project created by QtCreator 2012-10-10T10:24:23
#
#-------------------------------------------------

QT          += core gui opengl network xml

TARGET      = FreeStroke
TEMPLATE    = app
QMAKE += -j3

DESTDIR = ./

HEADERS     +=  ../../includes/application.h \
                ../../includes/common/controller.h \
                ../../includes/common/math.h \
                ../../includes/common/gesture.h \
                ../../includes/common/skeletondata.h \
                ../../includes/common/vector3.h \
                ../../includes/daolayer/command.h \
                ../../includes/ui/commandchooser/commandchooser.h \
                ../../includes/daolayer/commandtype.h \
                ../../includes/daolayer/daolayer.h \
                ../../includes/daolayer/historyrecord.h \
                ../../includes/daolayer/record.h \
                ../../includes/daolayer/sqlite3.h \
                ../../includes/gestures/segmenter.h \
                ../../includes/gestures/executionmanager.h \
                ../../includes/gestures/data/inputgesture.h \
                ../../includes/gestures/data/rawjointstate.h \
                ../../includes/gestures/algorithm/logisticregressionalgorithm.h \
                ../../includes/gestures/features/gesturefeature.h \
                ../../includes/gestures/features/gesturefeatures.h \
                ../../includes/gestures/features/neutralfeature.h \
                ../../includes/gestures/features/allfeatures.h \
                ../../includes/mainwindow.h \
                ../../includes/network/aes.h \
                ../../includes/network/communication.h \
                ../../includes/network/diffiehellman.h \
                ../../includes/network/tcpclient.h \
                ../../includes/network/udpclient.h \
                ../../includes/common/utils.h \
                ../../includes/ui/executionview.h \
                ../../includes/ui/listview.h \
                ../../includes/ui/parametersview.h \
                ../../includes/ui/bottombar/bottombar.h \
                ../../includes/ui/bottombar/bottombarseparator.h \
                ../../includes/ui/cell/cell.h \
                ../../includes/ui/cell/cellcontroller.h \
                ../../includes/ui/dialog/dialog.h \
                ../../includes/ui/dialog/dialogbutton.h \
                ../../includes/ui/element/element.h \
                ../../includes/ui/element/button/buttonelement.h \
                ../../includes/ui/element/button/menubuttonelement.h \
                ../../includes/ui/element/button/playbuttonelement.h \
                ../../includes/ui/element/combobox/combobox.h \
                ../../includes/ui/element/keylistener/keyconverter.h \
                ../../includes/ui/element/keylistener/keylistener.h \
                ../../includes/ui/element/label/label.h \
                ../../includes/ui/element/switcher/switcher.h \
                ../../includes/ui/element/textfield/textfield.h \
                ../../includes/ui/gestureparams/gestureparams.h \
                ../../includes/ui/glview/glview.h \
                ../../includes/ui/glview/openglview.h \
                ../../includes/ui/scrollbar/scrollbar.h \
                ../../includes/ui/list/list.h \
                ../../includes/ui/notification/notification.h \
                ../../includes/ui/notification/notifications.h \
                ../../includes/ui/stepper/stepper.h \
                ../../includes/ui/stepper/steppercontroller.h \
                ../../includes/ui/stepper/stepsnewgesture.h \
                ../../includes/ui/stepper/steppernewgesture.h \
                ../../includes/ui/topbar/topbar.h \
                ../../includes/ui/stepper/stepstutorial.h \
                ../../includes/ui/video/videocomponent.h \
                ../../includes/ui/maincontainer/maincontainer.h \
                ../../includes/ui/gesturelistview/gesturelistview.h \
                ../../includes/xml/xml.h \
                ../../includes/xml/xmlconf.h

SOURCES     +=  ../../sources/application.cpp \
                ../../sources/common/controller.cpp \
                ../../sources/common/math.cpp \
                ../../sources/common/gesture.cpp \
                ../../sources/common/skeletondata.cpp \
                ../../sources/common/vector3.cpp \
                ../../sources/daolayer/command.cpp \
                ../../sources/ui/commandchooser/commandchooser.cpp \
                ../../sources/daolayer/daolayer.cpp \
                ../../sources/daolayer/historyrecord.cpp \
                ../../sources/daolayer/record.cpp \
                ../../sources/gestures/segmenter.cpp \
                ../../sources/gestures/executionmanager.cpp \
                ../../sources/gestures/data/inputgesture.cpp \
                ../../sources/gestures/data/rawjointstate.cpp \
                ../../sources/gestures/algorithm/logisticregressionalgorithm.cpp \
                ../../sources/gestures/features/gesturefeatures.cpp \
                ../../sources/gestures/features/neutralfeature.cpp \
                ../../sources/gestures/features/allfeatures.cpp \
                ../../sources/main.cpp \
                ../../sources/mainwindow.cpp \
                ../../sources/network/aes.cpp \
                ../../sources/network/communication.cpp \
                ../../sources/network/diffiehellman.cpp \
                ../../sources/network/udpclient.cpp \
                ../../sources/network/tcpclient.cpp \
                ../../sources/common/utils.cpp \
                ../../sources/ui/executionview.cpp \
                ../../sources/ui/listview.cpp \
                ../../sources/ui/parametersview.cpp \
                ../../sources/ui/bottombar/bottombar.cpp \
                ../../sources/ui/bottombar/bottombarseparator.cpp \
                ../../sources/ui/cell/cell.cpp \
                ../../sources/ui/cell/cellcontroller.cpp \
                ../../sources/ui/dialog/dialog.cpp \
                ../../sources/ui/dialog/dialogbutton.cpp \
                ../../sources/ui/element/element.cpp \
                ../../sources/ui/element/button/buttonelement.cpp \
                ../../sources/ui/element/button/menubuttonelement.cpp \
                ../../sources/ui/element/button/playbuttonelement.cpp \
                ../../sources/ui/element/combobox/combobox.cpp \
                ../../sources/ui/element/keylistener/keylistener.cpp \
                ../../sources/ui/element/label/label.cpp \
                ../../sources/ui/element/switcher/switcher.cpp \
                ../../sources/ui/element/textfield/textfield.cpp \
                ../../sources/ui/gestureparams/gestureparams.cpp \
                ../../sources/ui/glview/glview.cpp \
                ../../sources/ui/glview/openglview.cpp \
                ../../sources/ui/list/list.cpp \
                ../../sources/ui/notification/notification.cpp \
                ../../sources/ui/notification/notifications.cpp \
                ../../sources/ui/scrollbar/scrollbar.cpp \
                ../../sources/ui/stepper/stepper.cpp \
                ../../sources/ui/stepper/steppercontroller.cpp \
                ../../sources/ui/stepper/stepsnewgesture.cpp \
                ../../sources/ui/stepper/steppernewgesture.cpp \
                ../../sources/ui/topbar/topbar.cpp \
                ../../sources/ui/stepper/stepstutorial.cpp \
                ../../sources/ui/video/videocomponent.cpp \
                ../../sources/ui/maincontainer/maincontainer.cpp \
                ../../sources/ui/gesturelistview/gesturelistview.cpp \
                ../../sources/xml/xml.cpp \
                ../../sources/xml/xmlconf.cpp

TRANSLATIONS = tr_en.ts tr_fr.ts

RESOURCES += ../../resources/resources.qrc

mac {
    OBJECTS_DIR = ../buildOSX/
    MOC_DIR = ../buildOSX/
    UI_DIR = ../buildOSX/

    HEADERS               += ../../includes/others/mac/mac.h
    OBJECTIVE_SOURCES     += ../../sources/others/mac/mac.mm
    LIBS                  += -framework AppKit \
                             -framework IOKit \
                             -framework CoreServices \
                             -framework Carbon \
                             /usr/lib/libsqlite3.0.dylib
}

unix:!mac {
    OBJECTS_DIR = ../buildUnix/
    MOC_DIR = ../buildUnix/
    UI_DIR = ../buildUnix/

    HEADERS               += ../../includes/others/linux/linux.h
    SOURCES               += ../../sources/others/linux/linux.cpp
    LIBS += -L/usr/local/lib/ \
            -lGLU \
            -lX11 \
            -lsqlite3
}

win32 {

    QMAKE_LFLAGS += -static-libstdc++
    OBJECTS_DIR = ../buildWin32/
    MOC_DIR = ../buildWin32/
    UI_DIR = ../buildWin32/


    HEADERS               += ../../includes/others/windows/windows.h
    SOURCES               += ../../sources/others/windows/windows.cpp

    LIBS += ../../libs/sqlite3.lib
}
