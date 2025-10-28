TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Aplicacion.cpp \
    Servicios/GestorAlbumes.cpp \
    Servicios/GestorArtistas.cpp \
        Servicios/GestorCanciones.cpp \
    Servicios/GestorPublicidades.cpp \
    Servicios/GestorSeguimiento.cpp \
        Servicios/GestorUsuarios.cpp \
    Servicios/MedidorRecursos.cpp \
        main.cpp \
    modelos/Album.cpp \
    modelos/Artista.cpp \
        modelos/Cancion.cpp \
    modelos/Credito.cpp \
    modelos/ListaFavoritos.cpp \
    modelos/Publicidad.cpp \
        modelos/Reproductor.cpp \
    modelos/Usuarios.cpp


HEADERS += \
    Aplicacion.h \
    Servicios/GestorAlbumes.h \
    Servicios/GestorArtistas.h \
    Servicios/GestorCanciones.h \
    Servicios/GestorPublicidades.h \
    Servicios/GestorSeguimiento.h \
    Servicios/GestorUsuarios.h \
    Servicios/MedidorRecursos.h \
    modelos/Album.h \
    modelos/Artista.h \
    modelos/Cancion.h \
    modelos/Credito.h \
    modelos/ListaFavoritos.h \
    modelos/Publicidad.h \
    modelos/Reproductor.h \
    modelos/Usuarios.h

