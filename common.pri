CONFIG -= debug_and_release

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

# Trying to read necessary enviroment variables
ELPRIB_IMPORT_PATH = $$(ELPRIB_PATH)

isEmpty(ELPRIB_IMPORT_PATH) {
    error("Environment variable ELPRIB_PATH is empty. Please, set it properly.")
}

ELPRIB_LIB_PATH = $$ELPRIB_IMPORT_PATH/lib
ELPRIB_INCLUDE_PATH = $$ELPRIB_IMPORT_PATH/include
ELPRIB_QML_PATH = $$ELPRIB_IMPORT_PATH/qml

message(ELPRIB_PATH = $$ELPRIB_IMPORT_PATH)

RCC_DIR = $${OUT_PWD}/rcc/
UI_DIR = $${OUT_PWD}/ui/
MOC_DIR = $${OUT_PWD}/moc/
OBJECTS_DIR = $${OUT_PWD}/obj/
