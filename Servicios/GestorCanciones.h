#ifndef GESTORCANCIONES_H
#define GESTORCANCIONES_H

#include "modelos/Cancion.h"
#include <string>

using namespace std;

class GestorCanciones {
private:
    Cancion** canciones;
    int cantidadCanciones;
    int capacidad;

    void redimensionar();
    void dividirLinea(string linea, string* datos);

public:
    GestorCanciones();
    ~GestorCanciones();

    bool cargarDesdeArchivo(string rutaArchivo);
    Cancion* buscarCancion(long idCancion);
    Cancion* obtenerCancionAleatoria();
    void agregarCancion(Cancion* cancion);
    int getCantidadCanciones() const;
    void mostrarTodas() const;
};

#endif
