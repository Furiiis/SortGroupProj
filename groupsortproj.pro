TEMPLATE = app
CONFIG += console c++2a
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    storage.cpp \
    record.cpp \
    group.cpp \
    file_manager.cpp

HEADERS += \
    storage.hpp \
    record.hpp \
    group.hpp \
    file_manager.hpp
