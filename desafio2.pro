TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Aplicacion.cpp \
    Servicios/GestorAlbumes.cpp \
    Servicios/GestorArtistas.cpp \
        Servicios/GestorCanciones.cpp \
    Servicios/GestorSeguimiento.cpp \
        Servicios/GestorUsuarios.cpp \
        main.cpp \
    modelos/Album.cpp \
    modelos/Artista.cpp \
        modelos/Cancion.cpp \
        modelos/Lista.cpp \
    modelos/ListaFavoritos.cpp \
        modelos/Reproductor.cpp \
    modelos/Usuarios.cpp


HEADERS += \
    Aplicacion.h \
    Servicios/GestorAlbumes.h \
    Servicios/GestorArtistas.h \
    Servicios/GestorCanciones.h \
    Servicios/GestorSeguimiento.h \
    Servicios/GestorUsuarios.h \
    modelos/Album.h \
    modelos/Artista.h \
    modelos/Cancion.h \
    modelos/Lista.h \
    modelos/ListaFavoritos.h \
    modelos/Reproductor.h \
    modelos/Usuarios.h

