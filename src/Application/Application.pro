QT -= gui

TEMPLATE = lib
DEFINES += APPLICATION_LIBRARY

include(../../common.pri)
include(../../lib.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Abstractions/IEventsRepository.cpp \
    CreateEvent/CreateEventRequest.cpp \
    CreateEvent/CreateEventRequestHandler.cpp \
    CreateEvent/CreateEventResponse.cpp \
    ReadEvents/ReadEventsRequest.cpp \
    ReadEvents/ReadEventsRequestHandler.cpp \
    ReadEvents/ReadEventsResponse.cpp

HEADERS += \
    Abstractions/IEventsRepository.h \
    Application_global.h \
    CreateEvent/CreateEventRequest.h \
    CreateEvent/CreateEventRequestHandler.h \
    CreateEvent/CreateEventResponse.h \
    ReadEvents/ReadEventsRequest.h \
    ReadEvents/ReadEventsRequestHandler.h \
    ReadEvents/ReadEventsResponse.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release): LIBS += -L$$ELPRIB_LIB_PATH -lmediqt
CONFIG(debug, debug|release): LIBS += -L$$ELPRIB_LIB_PATH -lmediqtd

INCLUDEPATH += $$ELPRIB_INCLUDE_PATH
DEPENDPATH += $$ELPRIB_INCLUDE_PATH

CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Domain/ -lDomain
CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Domain/ -lDomaind

INCLUDEPATH += $$PWD/../Domain
DEPENDPATH += $$PWD/../Domain
