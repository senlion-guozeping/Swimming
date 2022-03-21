QT       += core gui
QT       += datavisualization
QT       += sql
QT       += websockets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/Algorithm/kmeans.cpp \
    src/Algorithm/statistics.cpp \
    src/Common/basictool.cpp \
    src/Common/message.cpp \
    src/Common/modulemanager.cpp \
    src/Common/window.cpp \
    src/DB/BaseDB.cpp \
    src/Excel/player.cpp \
    src/Settings/BaseSetting.cpp \
    src/Settings/TableSetting.cpp \
    src/Settings/WindowSetting.cpp \
    src/UI/Help.cpp \
    src/UI/filtermodel.cpp \
    src/UI/filtervalue.cpp \
    src/UI/newdata.cpp \
    src/UI/tablemanger.cpp \
    src/UI/tablemodel.cpp

HEADERS += \
    mainwindow.h \
    src/Algorithm/kmeans.h \
    src/Algorithm/statistics.h \
    src/Common/basictool.h \
    src/Common/log.h \
    src/Common/message.h \
    src/Common/modulemanager.h \
    src/Common/window.h \
    src/DB/BaseDB.h \
    src/Excel/player.h \
    src/Setting/base.h \
    src/Settings/BaseSetting.h \
    src/Settings/TableSetting.h \
    src/Settings/WindowSetting.h \
    src/UI/Help.h \
    src/UI/filtermodel.h \
    src/UI/filtervalue.h \
    src/UI/newdata.h \
    src/UI/tablemanger.h \
    src/UI/tablemodel.h

FORMS += \
    mainwindow.ui \
    src/UI/Help.ui \
    src/UI/filtermodel.ui \
    src/UI/filtervalue.ui \
    src/UI/newdata.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

include(./QXlsx/QXlsx.pri)
