#ifndef LISTAFAVORITOS_H
#define LISTAFAVORITOS_H

#include <string>

using namespace std;

class ListaFavoritos {
private:
    long* idsCancionesFavoritas;  // Arreglo dinámico en lugar de vector
    int cantidadCanciones;
    int capacidad;
    const int MAX_FAVORITOS = 10000;

    void redimensionar();

public:
    ListaFavoritos();
    ~ListaFavoritos();

    // Métodos principales
    bool agregarCancion(long idCancion);
    bool eliminarCancion(long idCancion);
    bool contiene(long idCancion) const;
    int getCantidadCanciones() const;
    long* getIdsCanciones() const;  // Retorna puntero al arreglo
    void limpiar();

    // Persistencia
    bool cargarDesdeArchivo(const string& rutaArchivo);
    bool guardarEnArchivo(const string& rutaArchivo) const;

    // Mostrar
    void mostrar() const;
};

#endif
