#ifndef GESTORUSUARIOS_H
#define GESTORUSUARIOS_H

#include "modelos/usuarios.h"
#include <string>

using namespace std;

class GestorUsuarios {
private:
    Usuario** usuarios;
    int cantidadUsuarios;
    int capacidad;

    void redimensionar();
    void dividirLinea(string linea, string* datos);

public:
    GestorUsuarios();
    ~GestorUsuarios();

    bool cargarDesdeArchivo(string rutaArchivo);
    bool guardarEnArchivo(string rutaArchivo);  // <- NUEVO
    Usuario* buscarUsuario(string nickname);
    bool existeUsuario(string nickname);  // <- NUEVO
    void agregarUsuario(Usuario* usuario);
    int getCantidadUsuarios() const;
    void mostrarTodos() const;
};

#endif
