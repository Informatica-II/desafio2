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

bool GestorSeguimiento::seguirUsuario(const string& nickname, ListaFavoritos* miLista, ListaFavoritos* listaDelSeguido) {
    // Verificar si ya lo sigue (usando estaSiguiendo)
    if (estaSiguiendo(nickname)) {
        return false;
    }

    // Realizar la acción de seguir (usando el auxiliar para registrarlo)
    // El auxiliar registra el nickname y maneja la redimensión.
    registrarSeguimiento(nickname);

    //  FUSIÓN DE FAVORITOS
    if (listaDelSeguido != nullptr && miLista != nullptr) {
        // ... (Tu lógica de fusión de listas, que es la parte de negocio) ...
        long* cancionesSeguido = listaDelSeguido->getIdsCanciones();
        int cantSeguido = listaDelSeguido->getCantidadCanciones();

        for (int i = 0; i < cantSeguido; i++) {
            miLista->agregarCancion(cancionesSeguido[i]);
        }
        cout << "[OK] Se ha comenzado a seguir a " << nickname << " y se fusionaron sus favoritos." << endl;
    } else {
        cout << "[OK] Se ha comenzado a seguir a " << nickname << "." << endl;
    }

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

bool GestorSeguimiento::registrarSeguimiento(const string& nickname) {
    // 1. Verificar si ya lo sigue
    if (estaSiguiendo(nickname)) {
        return false;
    }

    // 2. Redimensionar si es necesario
    if (cantidadSeguidos >= capacidad) {
        redimensionar();
    }

    // 3. Registrar el seguimiento
    usuariosSeguidos[cantidadSeguidos] = nickname;
    cantidadSeguidos++;
    return true;
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

            registrarSeguimiento(linea);
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
