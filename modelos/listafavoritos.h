#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <vector>
#include <string>
#include "Cancion.h"

using namespace std;

class ListaFavoritos {
private:
    vector<long> idsCancionesFavoritas;  // Solo guardamos los IDs
    const int MAX_FAVORITOS = 10000;

public:
    ListaFavoritos();
    ~ListaFavoritos();

    // Métodos principales
    bool agregarCancion(long idCancion);
    bool eliminarCancion(long idCancion);
    bool contiene(long idCancion) const;
    int getCantidadCanciones() const;
    vector<long> getIdsCanciones() const;
    void limpiar();

    // Persistencia
    bool cargarDesdeArchivo(const string& rutaArchivo);
    bool guardarEnArchivo(const string& rutaArchivo) const;

    // Mostrar
    void mostrar() const;
};

#endif
