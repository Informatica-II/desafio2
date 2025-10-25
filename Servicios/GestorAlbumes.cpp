#include "GestorAlbumes.h"
#include <fstream>
#include <sstream>
#include <iostream>

GestorAlbumes::GestorAlbumes() {
    capacidad = 10;
    cantidadAlbumes = 0;
    albumes = new Album*[capacidad];
}

GestorAlbumes::~GestorAlbumes() {
    for (int i = 0; i < cantidadAlbumes; i++) {
        delete albumes[i];
    }
    delete[] albumes;
}

void GestorAlbumes::redimensionar() {
    capacidad *= 2;
    Album** nuevo = new Album*[capacidad];

    for (int i = 0; i < cantidadAlbumes; i++) {
        nuevo[i] = albumes[i];
    }

    delete[] albumes;
    albumes = nuevo;
}

void GestorAlbumes::dividirLinea(string linea, string* datos) {
    stringstream ss(linea);
    string temp;
    int index = 0;

    while (getline(ss, temp, '|') && index < 9) {
        datos[index++] = temp;
    }
}

vector<string> GestorAlbumes::dividirGeneros(const string& generos) {
    vector<string> resultado;
    stringstream ss(generos);
    string genero;

    while (getline(ss, genero, ',')) {
        resultado.push_back(genero);
    }

    return resultado;
}

bool GestorAlbumes::cargarDesdeArchivo(string rutaArchivo) {
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir el archivo: " << rutaArchivo << endl;
        return false;
    }

    string linea;
    // Saltar encabezados
    getline(archivo, linea);

    int cargados = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        string datos[9];
        dividirLinea(linea, datos);

        try {
            int idAlb = stoi(datos[0]);
            int idArt = stoi(datos[1]);
            string nombre = datos[2];
            string fecha = datos[3];
            int duracion = stoi(datos[4]);
            vector<string> generos = dividirGeneros(datos[5]);
            string sello = datos[6];
            int punt = stoi(datos[7]);
            string ruta = datos[8];

            Album* album = new Album(idAlb, idArt, nombre, fecha, duracion,
                                     generos, sello, punt, ruta);
            agregarAlbum(album);
            cargados++;
        } catch (...) {
            cout << "[ERROR] Error al procesar album: " << linea << endl;
        }
    }

    archivo.close();
    cout << "[OK] Albumes cargados: " << cargados << endl;
    return true;
}

Album* GestorAlbumes::buscarPorId(int idAlbum, int idArtista) {
    for (int i = 0; i < cantidadAlbumes; i++) {
        if (albumes[i]->getIdAlbum() == idAlbum &&
            albumes[i]->getIdArtista() == idArtista) {
            return albumes[i];
        }
    }
    return nullptr;
}

void GestorAlbumes::agregarAlbum(Album* album) {
    if (cantidadAlbumes >= capacidad) {
        redimensionar();
    }
    albumes[cantidadAlbumes++] = album;
}

int GestorAlbumes::getCantidadAlbumes() const {
    return cantidadAlbumes;
}

void GestorAlbumes::mostrarTodos() const {
    for (int i = 0; i < cantidadAlbumes; i++) {
        cout << "\n[" << (i + 1) << "] ";
        albumes[i]->mostrarInfo();
        cout << "----------------------------------------" << endl;
    }
}

void GestorAlbumes::mostrarPorArtista(int idArtista) const {
    bool encontrado = false;
    for (int i = 0; i < cantidadAlbumes; i++) {
        if (albumes[i]->getIdArtista() == idArtista) {
            if (!encontrado) {
                encontrado = true;
            }
            cout << "\n";
            albumes[i]->mostrarInfo();
            cout << "----------------------------------------" << endl;
        }
    }

    if (!encontrado) {
        cout << "No se encontraron albumes para este artista." << endl;
    }
}

Album** GestorAlbumes::getAlbumes() const {
    return albumes;
}
