#ifndef GESTORSEGUIMIENTO_H
#define GESTORSEGUIMIENTO_H

#include <string>

using namespace std;

class GestorSeguimiento {
private:
    string* usuariosSeguidos;  // Arreglo dinámico en lugar de vector
    int cantidadSeguidos;
    int capacidad;

    void redimensionar();

public:
    GestorSeguimiento();
    ~GestorSeguimiento();

    // Métodos principales
    bool seguirUsuario(const string& nickname);
    bool dejarDeSeguir(const string& nickname);
    bool estaSiguiendo(const string& nickname) const;
    int getCantidadSeguidos() const;
    string* getUsuariosSeguidos() const;  // Retorna puntero al arreglo
    void limpiar();

    // Persistencia
    bool cargarDesdeArchivo(const string& rutaArchivo);
    bool guardarEnArchivo(const string& rutaArchivo) const;

    // Mostrar
    void mostrar() const;
};

#endif
