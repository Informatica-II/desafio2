#include "gestorseguimiento.h"
#include <fstream>
#include <iostream>

GestorSeguimiento::GestorSeguimiento() {
    capacidad = 10;
    cantidadSeguidos = 0;
    usuariosSeguidos = new string[capacidad];
}

GestorSeguimiento::~GestorSeguimiento() {
    delete[] usuariosSeguidos;
}

void GestorSeguimiento::redimensionar() {
    capacidad *= 2;
    string* nuevo = new string[capacidad];

    for (int i = 0; i < cantidadSeguidos; i++) {
        nuevo[i] = usuariosSeguidos[i];
    }

    delete[] usuariosSeguidos;
    usuariosSeguidos = nuevo;
}

bool GestorSeguimiento::seguirUsuario(const string& nickname) {
    // Verificar si ya lo sigue
    if (estaSiguiendo(nickname)) {
        return false;
    }

    // Redimensionar si es necesario
    if (cantidadSeguidos >= capacidad) {
        redimensionar();
    }

    usuariosSeguidos[cantidadSeguidos] = nickname;
    cantidadSeguidos++;
    return true;
}

bool GestorSeguimiento::dejarDeSeguir(const string& nickname) {
    for (int i = 0; i < cantidadSeguidos; i++) {
        if (usuariosSeguidos[i] == nickname) {
            // Desplazar elementos a la izquierda
            for (int j = i; j < cantidadSeguidos - 1; j++) {
                usuariosSeguidos[j] = usuariosSeguidos[j + 1];
            }
            cantidadSeguidos--;
            return true;
        }
    }
    return false;
}

bool GestorSeguimiento::estaSiguiendo(const string& nickname) const {
    for (int i = 0; i < cantidadSeguidos; i++) {
        if (usuariosSeguidos[i] == nickname) {
            return true;
        }
    }
    return false;
}

int GestorSeguimiento::getCantidadSeguidos() const {
    return cantidadSeguidos;
}

string* GestorSeguimiento::getUsuariosSeguidos() const {
    return usuariosSeguidos;
}

void GestorSeguimiento::limpiar() {
    cantidadSeguidos = 0;
}

bool GestorSeguimiento::cargarDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    cantidadSeguidos = 0;
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            seguirUsuario(linea);
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

    for (int i = 0; i < cantidadSeguidos; i++) {
        archivo << usuariosSeguidos[i] << endl;
    }

    archivo.close();
    return true;
}

void GestorSeguimiento::mostrar() const {
    if (cantidadSeguidos == 0) {
        cout << "No estas siguiendo a ningun usuario." << endl;
        return;
    }

    cout << "Usuarios seguidos:" << endl;
    for (int i = 0; i < cantidadSeguidos; i++) {
        cout << "[" << (i + 1) << "] " << usuariosSeguidos[i] << endl;
    }
}
