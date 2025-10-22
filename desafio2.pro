TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Aplicacion.cpp \
        Servicios/GestorCanciones.cpp \
        Servicios/GestorUsuarios.cpp \
        main.cpp \
        modelos/Cancion.cpp \
        modelos/Lista.cpp \
        modelos/Reproductor.cpp \
        modelos/usuarios.cpp \
      

HEADERS += \
    Aplicacion.h \
    Servicios/GestorCanciones.h \
    Servicios/GestorUsuarios.h \
    modelos/Cancion.h \
    modelos/Lista.h \
    modelos/Reproductor.h \
    modelos/usuarios.h \
   
