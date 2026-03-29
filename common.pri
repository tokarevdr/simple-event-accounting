CONFIG -= debug_and_release

CONFIG(debug, debug|release) {
    BUILD_FLAG = debug
    LIB_SUFFIX = d
} else {
    BUILD_FLAG = release
}

RCC_DIR = $${OUT_PWD}/rcc/
UI_DIR = $${OUT_PWD}/ui/
MOC_DIR = $${OUT_PWD}/moc/
OBJECTS_DIR = $${OUT_PWD}/obj/
