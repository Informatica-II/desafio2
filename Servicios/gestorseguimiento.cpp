#include "gestorseguimiento.h"
#include <fstream>
#include <iostream>

GestorSeguimiento::GestorSeguimiento() {
    // Constructor vacío
}

GestorSeguimiento::~GestorSeguimiento() {
    // Destructor vacío
}

bool GestorSeguimiento::seguirUsuario(const string& nickname) {
    // Verificar si ya lo sigue
    if (estaSiguiendo(nickname)) {
        return false;
    }

    usuariosSeguidos.push_back(nickname);
    return true;
}

bool GestorSeguimiento::dejarDeSeguir(const string& nickname) {
    for (size_t i = 0; i < usuariosSeguidos.size(); i++) {
        if (usuariosSeguidos[i] == nickname) {
            usuariosSeguidos.erase(usuariosSeguidos.begin() + i);
            return true;
        }
    }
    return false;
}

bool GestorSeguimiento::estaSiguiendo(const string& nickname) const {
    for (size_t i = 0; i < usuariosSeguidos.size(); i++) {
        if (usuariosSeguidos[i] == nickname) {
            return true;
        }
    }
    return false;
}

int GestorSeguimiento::getCantidadSeguidos() const {
    return usuariosSeguidos.size();
}

vector<string> GestorSeguimiento::getUsuariosSeguidos() const {
    return usuariosSeguidos;
}

void GestorSeguimiento::limpiar() {
    usuariosSeguidos.clear();
}

bool GestorSeguimiento::cargarDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        return false; // Archivo no existe (primera vez)
    }

    usuariosSeguidos.clear();
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            usuariosSeguidos.push_back(linea);
        }
    }

    archivo.close();
    return true;
}

bool GestorSeguimiento::guardarEnArchivo(const string& rutaArchivo) const {
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    for (size_t i = 0; i < usuariosSeguidos.size(); i++) {
        archivo << usuariosSeguidos[i] << endl;
    }

    archivo.close();
    return true;
}

void GestorSeguimiento::mostrar() const {
    if (usuariosSeguidos.empty()) {
        cout << "No estas siguiendo a ningun usuario." << endl;
        return;
    }

    cout << "Usuarios seguidos:" << endl;
    for (size_t i = 0; i < usuariosSeguidos.size(); i++) {
        cout << "[" << (i + 1) << "] " << usuariosSeguidos[i] << endl;
    }
}
