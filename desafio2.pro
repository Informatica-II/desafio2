TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Aplicacion.cpp \
        Cancion.cpp \
        GestorCanciones.cpp \
        GestorUsuarios.cpp \
        Lista.cpp \
        Reproductor.cpp \
        main.cpp \
        usuarios.cpp

HEADERS += \
    Aplicacion.h \
    Cancion.h \
    GestorCanciones.h \
    GestorUsuarios.h \
    Lista.h \
    Reproductor.h \
    usuarios.h
