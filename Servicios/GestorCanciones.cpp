#include "Servicios/GestorCanciones.h"
#include "Servicios/MedidorRecursos.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

GestorCanciones::GestorCanciones() {
    capacidad = 50;
    cantidadCanciones = 0;
    canciones = new Cancion*[capacidad];
    srand(time(0)); // Inicializar semilla aleatoria
}

GestorCanciones::~GestorCanciones() {
    for (int i = 0; i < cantidadCanciones; i++) {
        delete canciones[i];
    }
    delete[] canciones;
}

void GestorCanciones::redimensionar() {
    capacidad *= 2;
    Cancion** nuevo = new Cancion*[capacidad];

    for (int i = 0; i < cantidadCanciones; i++) {
        nuevo[i] = canciones[i];
    }

    delete[] canciones;
    canciones = nuevo;
}

void GestorCanciones::dividirLinea(string linea, string* datos) {
    int pos = 0;
    int inicio = 0;

    for (int i = 0; i < 7; i++) {
        pos = linea.find('|', inicio);
        if (pos == string::npos) {
            datos[i] = linea.substr(inicio);
        } else {
            datos[i] = linea.substr(inicio, pos - inicio);
            inicio = pos + 1;
        }
    }
}

bool GestorCanciones::cargarDesdeArchivo(string rutaArchivo) {
    ifstream archivo(rutaArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir el archivo: " << rutaArchivo << endl;
        return false;
    }

    string linea;
    getline(archivo, linea); // Saltar encabezado

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        string datos[7];
        dividirLinea(linea, datos);

        long id = atol(datos[0].c_str());
        int artista = atoi(datos[1].c_str());
        int album = atoi(datos[2].c_str());
        string nombre = datos[3];
        int duracion = atoi(datos[4].c_str());
        long reproducciones = atol(datos[5].c_str());
        string rutaBase = datos[6];

        Cancion* nueva = new Cancion(id, artista, album, nombre, duracion, reproducciones, rutaBase);
        agregarCancion(nueva);
    }

    archivo.close();
    cout << "[INFO] " << cantidadCanciones << " canciones cargadas correctamente." << endl;
    return true;
}

Cancion* GestorCanciones::buscarCancion(string nombreCancion) {
    for (int i = 0; i < cantidadCanciones; i++) {
        if (canciones[i]->getNombre() == nombreCancion) {
            cout<<"cancion encontrada."<< endl;
            return canciones[i];
        }

    }
    return nullptr;
}


Cancion* GestorCanciones::obtenerCancionAleatoria() {
    cout << "[DEBUG] Cantidad de canciones disponibles: " << cantidadCanciones << endl;
    if (cantidadCanciones == 0) return nullptr;

    int indice = rand() % cantidadCanciones;
    MedidorRecursos::registrarIteracion();
    cout << "[DEBUG] Cancion aleatoria seleccionada: " << canciones[indice]->getNombre() << endl;
    cout << "[DEBUG] Indice aleatorio: " << indice << endl;
    return canciones[indice];
}

void GestorCanciones::agregarCancion(Cancion* cancion) {
    if (cantidadCanciones >= capacidad) {
        redimensionar();
    }

    canciones[cantidadCanciones] = cancion;
    cantidadCanciones++;
}

int GestorCanciones::getCantidadCanciones() const {
    return cantidadCanciones;
}

void GestorCanciones::mostrarTodas() const {
    cout << "\n=== CATALOGO DE CANCIONES ===" << endl;
    for (int i = 0; i < cantidadCanciones; i++) {
        cout << (i + 1) << ". " << canciones[i]->getNombre()
             << " (" << canciones[i]->formatearDuracion() << ")" << "\tID: "<<canciones[i]->getIdCancion()<<endl;
    }
    cout << "Total: " << cantidadCanciones << " canciones\n" << endl;
}

Cancion* GestorCanciones::buscarPorId(long id) {
    for (int i = 0; i < cantidadCanciones; i++) {
        MedidorRecursos::registrarIteracion();
        if (canciones[i]->getIdCancion() == id) {
            return canciones[i];
        }
    }
    return nullptr;
}

