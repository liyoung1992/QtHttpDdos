#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T10:44:39
#
#-------------------------------------------------

QT       += core gui network


#LIBS += D:\work\qt_project\curl-7.54.0-win32-mingw\lib\libcurldll.a


###LIBS += ".\..\lib\libcurl.dll"
#INCLUDEPATH+= D:\work\qt_project\curl-7.54.0-win32-mingw\include
#INCLUDEPATH+= D:\work\qt_project\curl-7.54.0-win32-mingw\include\curl



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets axcontainer

TARGET = QtHttpDdos
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        QtHttpDdos.cpp \
    QHttpThread.cpp \
    qtwebview.cpp

HEADERS  += QtHttpDdos.h \
    QHttpThread.h \
    webaxwidget.h \
    qtwebview.h

FORMS    += QtHttpDdos.ui \
    qtwebview.ui

# install
target.path = $$[QT_INSTALL_EXAMPLES]/activeqt/webbrowser
INSTALLS += target
