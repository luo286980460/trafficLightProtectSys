QT = core network widgets

CONFIG += c++17
# CONFIG += cmdline
# CONFIG += release
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        datatransmitter.cpp \
        main.cpp \
        mainclass.cpp \
        myhttpserver.cpp \
        mytcpclient.cpp \
        novacontroller.cpp \
        novacontrollerworker.cpp \
        qaesencryption.cpp \
        rule.cpp \
        trafficlight.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    NovaHeader.h \
    datatransmitter.h \
    mainclass.h \
    myhttpserver.h \
    mytcpclient.h \
    novacontroller.h \
    novacontrollerworker.h \
    qaesencryption.h \
    rule.h \
    trafficlight.h

win32: LIBS += -L$$PWD/libs/libhv/ -llibhv.dll

INCLUDEPATH += $$PWD/include/libhv
DEPENDPATH += $$PWD/include/libhv

unix:!macx: LIBS += -L$$PWD/libs/libhv/ -lhv

INCLUDEPATH += $$PWD/include/libhv
DEPENDPATH += $$PWD/include/libhv

win32: LIBS += -L$$PWD/libs/librdkafka/ -llibrdkafka++.dll

INCLUDEPATH += $$PWD/include/librdkafka
DEPENDPATH += $$PWD/include/librdkafka

unix:!macx: LIBS += -L$$PWD/libs/librdkafka/ -lrdkafka++

INCLUDEPATH += $$PWD/include/librdkafka
DEPENDPATH += $$PWD/include/librdkafka

unix:!macx: LIBS += -L$$PWD/libs/libNova/ -lNovaTraffic

INCLUDEPATH += $$PWD/include/libNova
DEPENDPATH += $$PWD/include/libNova
