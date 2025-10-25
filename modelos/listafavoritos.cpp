#include "listafavoritos.h"
#include <fstream>
#include <iostream>

ListaFavoritos::ListaFavoritos() {
    // Constructor vacío, el vector se inicializa automáticamente
}

ListaFavoritos::~ListaFavoritos() {
    // Destructor vacío, el vector se destruye automáticamente
}

bool ListaFavoritos::agregarCancion(long idCancion) {
    // Verificar si ya existe
    if (contiene(idCancion)) {
        return false;
    }

    // Verificar límite
    if (idsCancionesFavoritas.size() >= MAX_FAVORITOS) {
        return false;
    }

    idsCancionesFavoritas.push_back(idCancion);
    return true;
}

bool ListaFavoritos::eliminarCancion(long idCancion) {
    for (size_t i = 0; i < idsCancionesFavoritas.size(); i++) {
        if (idsCancionesFavoritas[i] == idCancion) {
            idsCancionesFavoritas.erase(idsCancionesFavoritas.begin() + i);
            return true;
        }
    }
    return false;
}

bool ListaFavoritos::contiene(long idCancion) const {
    for (size_t i = 0; i < idsCancionesFavoritas.size(); i++) {
        if (idsCancionesFavoritas[i] == idCancion) {
            return true;
        }
    }
    return false;
}

int ListaFavoritos::getCantidadCanciones() const {
    return idsCancionesFavoritas.size();
}

vector<long> ListaFavoritos::getIdsCanciones() const {
    return idsCancionesFavoritas;
}

void ListaFavoritos::limpiar() {
    idsCancionesFavoritas.clear();
}

bool ListaFavoritos::cargarDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        return false; // Archivo no existe (primera vez)
    }

    idsCancionesFavoritas.clear();
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            try {
                long id = stol(linea);
                idsCancionesFavoritas.push_back(id);
            } catch (...) {
                // Ignorar líneas inválidas
            }
        }
    }

    archivo.close();
    return true;
}

bool ListaFavoritos::guardarEnArchivo(const string& rutaArchivo) const {
    ofstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    for (size_t i = 0; i < idsCancionesFavoritas.size(); i++) {
        archivo << idsCancionesFavoritas[i] << endl;
    }

    archivo.close();
    return true;
}

void ListaFavoritos::mostrar() const {
    if (idsCancionesFavoritas.empty()) {
        cout << "No hay canciones en favoritos." << endl;
        return;
    }

    cout << "IDs de canciones favoritas:" << endl;
    for (size_t i = 0; i < idsCancionesFavoritas.size(); i++) {
        cout << "[" << (i + 1) << "] ID: " << idsCancionesFavoritas[i] << endl;
    }
}
