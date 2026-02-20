QT += quick sql concurrent

include(../../common.pri)
include(../../app.pri)

CONFIG += c++17

HEADERS += \
    Utils/AsyncExecutor.h \
    ViewModels/EventsViewModel.h

SOURCES += \
        Utils/AsyncExecutor.cpp \
        ViewModels/EventsViewModel.cpp \
        main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(release, debug|release) {
    LIBS += -L$$OUT_PWD/../Domain/lib -lDomain
    LIBS += -L$$OUT_PWD/../Application/lib -lApplication
    LIBS += -L$$OUT_PWD/../Infrastructure/lib -lInfrastructure
}
CONFIG(debug, debug|release) {
    LIBS += -L$$OUT_PWD/../Domain/lib -lDomaind
    LIBS += -L$$OUT_PWD/../Application/lib -lApplicationd
    LIBS += -L$$OUT_PWD/../Infrastructure/lib -lInfrastructured
}

INCLUDEPATH += \
    $$PWD/../Domain \
    $$PWD/../Application \
    $$PWD/../Infrastructure

DEPENDPATH += \
    $$PWD/../Domain \
    $$PWD/../Application \
    $$PWD/../Infrastructure
