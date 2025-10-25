#ifndef GESTORARTISTAS_H
#define GESTORARTISTAS_H

#include "modelos/Artista.h"
#include <string>

using namespace std;

class GestorArtistas {
private:
    Artista** artistas;
    int cantidadArtistas;
    int capacidad;

    void redimensionar();
    void dividirLinea(string linea, string* datos);

public:
    GestorArtistas();
    ~GestorArtistas();

    bool cargarDesdeArchivo(string rutaArchivo);
    Artista* buscarPorId(int id);
    void agregarArtista(Artista* artista);
    int getCantidadArtistas() const;
    void mostrarTodos() const;
    void mostrarOrdenadoPorTendencia() const;
    Artista** getArtistas() const;
};

#endif
