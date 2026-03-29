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
    Abstractions/IConsumersRepository.cpp \
    Abstractions/IEventUsersRepository.cpp \
    Abstractions/IEventsInfoRepository.cpp \
    Abstractions/IReceiptItemsInfoRepository.cpp \
    Abstractions/IReceiptsInfoRepository.cpp \
    Abstractions/IUsersRepository.cpp

HEADERS += \
    Abstractions/IConsumersRepository.h \
    Abstractions/IEventUsersRepository.h \
    Abstractions/IEventsInfoRepository.h \
    Abstractions/IReceiptItemsInfoRepository.h \
    Abstractions/IReceiptsInfoRepository.h \
    Abstractions/IUsersRepository.h \
    Application_global.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release) {
    LIBS += -L$$OUT_PWD/../Domain/lib -lDomain
    LIBS += -L$$OUT_PWD/../Utils/lib -lUtils
}

CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../Domain/lib -lDomaind
    LIBS += -L$$OUT_PWD/../Utils/lib -lUtilsd
}

INCLUDEPATH += \
    $$PWD/../Domain \
    $$PWD/../Utils

DEPENDPATH += \
    $$PWD/../Domain \
    $$PWD/../Utils
