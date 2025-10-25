#ifndef APLICACION_H
#define APLICACION_H

#include "Servicios/GestorUsuarios.h"
#include "Servicios/GestorCanciones.h"
#include "modelos/Usuarios.h"
#include "modelos/Cancion.h"
#include "Servicios/GestorArtistas.h"
#include "Servicios/GestorAlbumes.h"


class Aplicacion {
private:
    GestorUsuarios* gestorUsuarios;
    GestorCanciones* gestorCanciones;
    GestorArtistas* gestorArtistas;
    GestorAlbumes* gestorAlbumes;
    Usuario* usuarioActual;
    string preguntaMembresia;

    void cargarDatos();
    void mostrarMenuPrincipal();
    void mostrarMenuUsuarioEstandar();
    void mostrarMenuUsuarioPremium();
    void reproduccionAleatoriaEstandar();
    void reproduccionAleatoriaPremium();
    void reproducirCancion(Cancion* cancion, bool esCalidadAlta);
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
