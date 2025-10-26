#include "listafavoritos.h"
#include <fstream>
#include <iostream>

ListaFavoritos::ListaFavoritos() {
    capacidad = 10;
    cantidadCanciones = 0;
    idsCancionesFavoritas = new long[capacidad];
}

ListaFavoritos::~ListaFavoritos() {
    delete[] idsCancionesFavoritas;
}

void ListaFavoritos::redimensionar() {
    capacidad *= 2;
    long* nuevo = new long[capacidad];

    for (int i = 0; i < cantidadCanciones; i++) {
        nuevo[i] = idsCancionesFavoritas[i];
    }

    delete[] idsCancionesFavoritas;
    idsCancionesFavoritas = nuevo;
}

bool ListaFavoritos::agregarCancion(long idCancion) {
    // Verificar si ya existe
    if (contiene(idCancion)) {
        return false;
    }

    // Verificar límite
    if (cantidadCanciones >= MAX_FAVORITOS) {
        return false;
    }

    // Redimensionar si es necesario
    if (cantidadCanciones >= capacidad) {
        redimensionar();
    }

    idsCancionesFavoritas[cantidadCanciones] = idCancion;
    cantidadCanciones++;
    return true;
}

bool ListaFavoritos::eliminarCancion(long idCancion) {
    for (int i = 0; i < cantidadCanciones; i++) {
        if (idsCancionesFavoritas[i] == idCancion) {
            // Desplazar elementos a la izquierda
            for (int j = i; j < cantidadCanciones - 1; j++) {
                idsCancionesFavoritas[j] = idsCancionesFavoritas[j + 1];
            }
            cantidadCanciones--;
            return true;
        }
    }
    return false;
}

bool ListaFavoritos::contiene(long idCancion) const {
    for (int i = 0; i < cantidadCanciones; i++) {
        if (idsCancionesFavoritas[i] == idCancion) {
            return true;
        }
    }
    return false;
}

int ListaFavoritos::getCantidadCanciones() const {
    return cantidadCanciones;
}

long* ListaFavoritos::getIdsCanciones() const {
    return idsCancionesFavoritas;
}

void ListaFavoritos::limpiar() {
    cantidadCanciones = 0;
}

bool ListaFavoritos::cargarDesdeArchivo(const string& rutaArchivo) {
    ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        return false;
    }

    cantidadCanciones = 0;
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            try {
                long id = stol(linea);
                agregarCancion(id);
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

    for (int i = 0; i < cantidadCanciones; i++) {
        archivo << idsCancionesFavoritas[i] << endl;
    }

    archivo.close();
    return true;
}

void ListaFavoritos::mostrar() const {
    if (cantidadCanciones == 0) {
        cout << "No hay canciones en favoritos." << endl;
        return;
    }

    cout << "IDs de canciones favoritas:" << endl;
    for (int i = 0; i < cantidadCanciones; i++) {
        cout << "[" << (i + 1) << "] ID: " << idsCancionesFavoritas[i] << endl;
    }
}
