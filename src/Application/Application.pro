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
    Abstractions/IParticipantsRepository.cpp \
    Abstractions/IReceiptsRepository.cpp

HEADERS += \
    Abstractions/IEventsRepository.h \
    Abstractions/IParticipantsRepository.h \
    Abstractions/IReceiptsRepository.h \
    Application_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Domain/lib -lDomain
CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Domain/lib -lDomaind

INCLUDEPATH += $$PWD/../Domain
DEPENDPATH += $$PWD/../Domain
