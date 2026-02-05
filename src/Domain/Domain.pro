QT -= gui

TEMPLATE = lib
DEFINES += DOMAIN_LIBRARY

include(../../common.pri)
include(../../lib.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entities/Event.cpp

HEADERS += \
    Domain_global.h \
    Entities/Event.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
