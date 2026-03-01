QT -= gui

TEMPLATE = lib
DEFINES += UTILS_LIBRARY

include(../../common.pri)
include(../../lib.pri)

CONFIG += c++17

SOURCES += \
    AsyncExecutor.cpp \
    Result.cpp

HEADERS += \
    AsyncExecutor.h \
    Utils_global.h \
    Result.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
