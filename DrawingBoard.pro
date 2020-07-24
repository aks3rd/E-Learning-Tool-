QT       += core gui
QT -=gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
#its define by me
#CONFIG +=console

#CONFIG -=app_bundle
#TEMPLATE =app


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += /usr/local/include/opencv4
LIBS += -L/usr/local/lib64 -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc  -lpthread -lopencv_imgcodecs


SOURCES += \
    canvas.cpp \
    drawablecomponent.cpp \
    main.cpp \
    mainwindow.cpp \
    tmcirclecomponent.cpp \
    tmellipsecomponent.cpp \
    tmfreehandcomponent.cpp \
    tmgroupcomponent.cpp \
    tmlinecomponent.cpp \
    tmpixmapcomponent.cpp \
    tmrectanglecomponent.cpp \
    tmview.cpp

HEADERS += \
    canvas.h \
    drawablecomponent.h \
    mainwindow.h \
    tmcirclecomponent.h \
    tmellipsecomponent.h \
    tmfreehandcomponent.h \
    tmgroupcomponent.h \
    tmlinecomponent.h \
    tmpixmapcomponent.h \
    tmrectanglecomponent.h \
    tmview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    cursor.qrc
