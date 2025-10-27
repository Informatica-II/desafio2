#ifndef APLICACION_H
#define APLICACION_H

#include "Servicios/GestorUsuarios.h"
#include "Servicios/GestorCanciones.h"
#include "modelos/Usuarios.h"
#include "Servicios/GestorArtistas.h"
#include "Servicios/GestorAlbumes.h"
#include "Servicios/GestorPublicidades.h"
#include "modelos/Reproductor.h"

class Aplicacion {
private:
    GestorUsuarios* gestorUsuarios;
    GestorCanciones* gestorCanciones;
    GestorArtistas* gestorArtistas;
    GestorAlbumes* gestorAlbumes;
    GestorPublicidades* gestorPublicidades;
    Reproductor* reproductor;
    Usuario* usuarioActual;
    string preguntaMembresia;

    void cargarDatos();
    void mostrarMenuPrincipal();
    void mostrarMenuUsuarioEstandar();
    void mostrarMenuUsuarioPremium();
    void login();
    void registrarUsuario();
    void salir();
    void cerrarSesion();
    string obtenerFechaActual();



public:

    Aplicacion();
    ~Aplicacion();
    void ejecutar();

    //MÉTODOS PARA FAVORITOS:
    void agregarAFavoritos();
    void verMisFavoritos();
    void eliminarDeFavoritos();
    void reproducirMisFavoritos();

    // MÉTODOS PARA SEGUIMIENTO:
    void seguirUsuario();
    void verUsuariosSeguidos();
    void dejarDeSeguirUsuario();

};

#endif
