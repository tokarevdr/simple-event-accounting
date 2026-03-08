QT -= gui

TEMPLATE = lib
DEFINES += UTILS_LIBRARY

include(../../common.pri)
include(../../lib.pri)

CONFIG += c++17

SOURCES += \
    Unit.cpp

HEADERS += \
    Unit.h \
    Utils_global.h \
    Result.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
