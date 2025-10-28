#ifndef GESTORSEGUIMIENTO_H
#define GESTORSEGUIMIENTO_H

#include <string>
#include "modelos/ListaFavoritos.h"
using namespace std;

class GestorSeguimiento {
private:
    string* usuariosSeguidos;  // Arreglo dinámico en lugar de vector
    int cantidadSeguidos;
    int capacidad;
    bool registrarSeguimiento(const std::string& nickname);

    void redimensionar();

public:
    GestorSeguimiento();
    ~GestorSeguimiento();

    // Métodos principales
    bool seguirUsuario(const std::string& nickname, ListaFavoritos* miLista, ListaFavoritos* listaDelSeguido);
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
