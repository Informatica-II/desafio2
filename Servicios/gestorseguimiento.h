#ifndef GESTORSEGUIMIENTO_H
#define GESTORSEGUIMIENTO_H

#include <vector>
#include <string>

using namespace std;

class GestorSeguimiento {
private:
    vector<string> usuariosSeguidos;

public:
    GestorSeguimiento();
    ~GestorSeguimiento();

    // Métodos principales
    bool seguirUsuario(const string& nickname);
    bool dejarDeSeguir(const string& nickname);
    bool estaSiguiendo(const string& nickname) const;
    int getCantidadSeguidos() const;
    vector<string> getUsuariosSeguidos() const;
    void limpiar();

    // Persistencia
    bool cargarDesdeArchivo(const string& rutaArchivo);
    bool guardarEnArchivo(const string& rutaArchivo) const;

    // Mostrar
    void mostrar() const;
};

#endif
