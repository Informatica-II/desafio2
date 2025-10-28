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
    void parsearCreditos(Cancion* cancion, const string& creditosStr);

public:
    GestorCanciones();
    ~GestorCanciones();
    Cancion* buscarPorId(long id);

    bool cargarDesdeArchivo(string rutaArchivo);
    Cancion* buscarCancion(string nombreCancion);
    Cancion* obtenerCancionAleatoria();
    void agregarCancion(Cancion* cancion);
    int getCantidadCanciones() const;
    void mostrarTodas() const;
};

#endif
