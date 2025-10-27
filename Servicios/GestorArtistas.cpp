#include "GestorArtistas.h"
#include "Servicios/MedidorRecursos.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>

GestorArtistas::GestorArtistas() {
    capacidad = 10;
    cantidadArtistas = 0;
    artistas = new Artista*[capacidad];
}

GestorArtistas::~GestorArtistas() {
    for (int i = 0; i < cantidadArtistas; i++) {
        delete artistas[i];
    }
    delete[] artistas;
}

void GestorArtistas::redimensionar() {
    capacidad *= 2;
    Artista** nuevo = new Artista*[capacidad];

    for (int i = 0; i < cantidadArtistas; i++) {
        nuevo[i] = artistas[i];
    }

    delete[] artistas;
    artistas = nuevo;
}

void GestorArtistas::dividirLinea(string linea, string* datos) {
    stringstream ss(linea);
    string temp;
    int index = 0;

    while (getline(ss, temp, '|') && index < 6) {
        datos[index++] = temp;
    }
}

bool GestorArtistas::cargarDesdeArchivo(string rutaArchivo) {
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir el archivo: " << rutaArchivo << endl;
        return false;
    }

    string linea;
    // Saltar la primera línea (encabezados)
    getline(archivo, linea);

    int cargados = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        string datos[6];
        dividirLinea(linea, datos);

        try {
            int id = stoi(datos[0]);
            string nombre = datos[1];
            int edad = stoi(datos[2]);
            string pais = datos[3];
            long seguidores = stol(datos[4]);
            int posicion = stoi(datos[5]);

            Artista* artista = new Artista(id, nombre, edad, pais, seguidores, posicion);
            agregarArtista(artista);
            cargados++;
        } catch (...) {
            cout << "[ERROR] Error al procesar artista: " << linea << endl;
        }
    }

    archivo.close();
    cout << "[OK] Artistas cargados: " << cargados << endl;
    return true;
}

Artista* GestorArtistas::buscarPorId(int id) {
    for (int i = 0; i < cantidadArtistas; i++) {
        if (artistas[i]->getIdArtista() == id) {
            return artistas[i];
        }
    }
    return nullptr;
}

void GestorArtistas::agregarArtista(Artista* artista) {
    if (cantidadArtistas >= capacidad) {
        redimensionar();
    }
    artistas[cantidadArtistas++] = artista;
}

int GestorArtistas::getCantidadArtistas() const {
    return cantidadArtistas;
}

void GestorArtistas::mostrarTodos() const {
    for (int i = 0; i < cantidadArtistas; i++) {
        cout << "\n[" << (i + 1) << "] ";
        artistas[i]->mostrarInfo();
        cout << "----------------------------------------" << endl;
    }
}

void GestorArtistas::mostrarOrdenadoPorTendencia() const {
    // Crear copia temporal para ordenar
    Artista** temp = new Artista*[cantidadArtistas];
    for (int i = 0; i < cantidadArtistas; i++) {
        MedidorRecursos::registrarIteracion();
        temp[i] = artistas[i];
    }

    // Ordenar por posición de tendencia (bubble sort)
    for (int i = 0; i < cantidadArtistas - 1; i++) {
        for (int j = 0; j < cantidadArtistas - i - 1; j++) {
            MedidorRecursos::registrarIteracion();
            if (temp[j]->getPosicionTendencia() > temp[j + 1]->getPosicionTendencia()) {
                Artista* aux = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = aux;
            }
        }
    }

    // Mostrar
    for (int i = 0; i < cantidadArtistas; i++) {
         MedidorRecursos::registrarIteracion();
        cout << "\n[" << (i + 1) << "] ";
        temp[i]->mostrarInfo();
        cout << "----------------------------------------" << endl;
    }

    delete[] temp;
}

Artista** GestorArtistas::getArtistas() const {
    return artistas;
}
