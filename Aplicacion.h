#ifndef APLICACION_H
#define APLICACION_H

#include "Servicios/GestorUsuarios.h"
#include "Servicios/GestorCanciones.h"
#include "modelos/Usuarios.h"
#include "modelos/Cancion.h"
#include "Servicios/GestorArtistas.h"
#include "Servicios/GestorAlbumes.h"
#include "Servicios/GestorPublicidades.h"
#include "modelos/Publicidad.h"

#include <chrono>
#include <thread>

class Aplicacion {
private:
    GestorUsuarios* gestorUsuarios;
    GestorCanciones* gestorCanciones;
    GestorArtistas* gestorArtistas;
    GestorAlbumes* gestorAlbumes;
    GestorPublicidades* gestorPublicidades;
    Usuario* usuarioActual;
    string preguntaMembresia;

    void cargarDatos();
    void mostrarMenuPrincipal();
    void mostrarMenuUsuarioEstandar();
    void mostrarMenuUsuarioPremium();
    void reproduccionAleatoriaEstandar();
    void reproduccionAleatoriaPremium();
    void reproducirCancion(Cancion* cancion, bool esCalidadAlta);
    void pausarConTemporizador(int segundos);
    void reproducirConControlesPremium(Cancion** listaCanciones, int totalCanciones);
    void mostrarControlesPremium();
    bool procesarComandoReproduccion(char comando, int& indiceActual, int totalCanciones,
                                     bool& modoRepetir, bool& continuar, int* historial,
                                     int& cantidadHistorial);
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
