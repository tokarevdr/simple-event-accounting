QT -= gui
QT += sql

TEMPLATE = lib
DEFINES += INFRASTRUCTURE_LIBRARY

include(../../common.pri)
include(../../lib.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Repositories/SqliteEventsRepository.cpp

HEADERS += \
    Infrastructure_global.h \
    Repositories/SqliteEventsRepository.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release) {
    LIBS += -L$$OUT_PWD/../Domain/lib -lDomain
    LIBS += -L$$OUT_PWD/../Application/lib -lApplication
    LIBS += -L$$OUT_PWD/../Utils/lib -lUtils
}

CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../Domain/lib -lDomaind
    LIBS += -L$$OUT_PWD/../Application/lib -lApplicationd
    LIBS += -L$$OUT_PWD/../Utils/lib -lUtilsd
}

INCLUDEPATH += \
    $$PWD/../Domain \
    $$PWD/../Application \
    $$PWD/../Utils

DEPENDPATH += \
    $$PWD/../Domain \
    $$PWD/../Application \
    $$PWD/../Utils
