lessThan(QT_VERSION, 5) {
    error("Qt version 5+ required")
}

TEMPLATE = app
CONFIG += qt warn_on release c++11
QT += core gui widgets
QMAKE_CXXFLAGS += -O3 -funsigned-char -fno-asynchronous-unwind-tables -fno-ident
QMAKE_LFLAGS +=  -Wl,--gc-sections,--strip-all,--build-id=none

HEADERS += src/common.hpp \
           src/DrawnWidget.hpp \
           src/Board.hpp \
           src/Window.hpp
SOURCES += src/DrawnWidget.cpp \
           src/Board.cpp \
           src/Window.cpp \
           src/main.cpp
RESOURCES += images/images.qrc

MOC_DIR = build
OBJECTS_DIR = build
RCC_DIR = build
