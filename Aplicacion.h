#ifndef APLICACION_H
#define APLICACION_H

#include "Servicios/GestorUsuarios.h"
#include "Servicios/GestorCanciones.h"
#include "modelos/usuarios.h"
#include "modelos/Cancion.h"

class Aplicacion {
private:
    GestorUsuarios* gestorUsuarios;
    GestorCanciones* gestorCanciones;
    Usuario* usuarioActual;

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
    string preguntaMembresia;


public:
    Aplicacion();
    ~Aplicacion();
    void ejecutar();
};

#endif
