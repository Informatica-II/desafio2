#include "Usuarios.h"
#include <iostream>
#include <fstream>

using namespace std;

Usuarios::Usuarios() {}

Usuarios::Usuarios(const string& nombre, const string& contrasena, const string& tipo)
    : nombre(nombre), contrasena(contrasena), tipoUsuario(tipo) {}

bool Usuarios::verificarCredenciales(const string& usuario, const string& contrasenaIngresada) {
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo de usuarios." << endl;
        return false;
    }

    string u, c, tipo;
    while (getline(archivo, u, ',') &&
           getline(archivo, c, ',') &&
           getline(archivo, tipo)) {

        if (u == usuario && c == contrasenaIngresada) {
            nombre = u;
            contrasena = c;
            tipoUsuario = tipo;
            return true;
        }
    }
    return false;
}

string Usuarios::getNombre() const {
    return nombre;
}

string Usuarios::getTipoUsuario() const {
    return tipoUsuario;
}
