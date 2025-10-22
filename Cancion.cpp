#include "Cancion.h"
#include <sstream>
#include <iomanip>

Cancion::Cancion() {
    idCancion = 0;
    idArtista = 0;
    idAlbum = 0;
    nombre = "";
    duracion = 0;
    reproducciones = 0;
    rutaBase = "";
}

Cancion::Cancion(long id, int artista, int album, string nom, int dur, long repro, string ruta) {
    idCancion = id;
    idArtista = artista;
    idAlbum = album;
    nombre = nom;
    duracion = dur;
    reproducciones = repro;
    rutaBase = ruta;
}

Cancion::~Cancion() {
}

long Cancion::getIdCancion() const {
    return idCancion;
}

int Cancion::getIdArtista() const {
    return idArtista;
}

int Cancion::getIdAlbum() const {
    return idAlbum;
}

string Cancion::getNombre() const {
    return nombre;
}

int Cancion::getDuracion() const {
    return duracion;
}

long Cancion::getReproducciones() const {
    return reproducciones;
}

string Cancion::getRutaBase() const {
    return rutaBase;
}

void Cancion::setReproducciones(long repro) {
    reproducciones = repro;
}

void Cancion::incrementarReproducciones() {
    reproducciones++;
}

string Cancion::getRutaCompleta(bool esCalidadAlta) const {
    string nombreArchivo = nombre;

    // Convertir nombre a minúsculas y reemplazar espacios por _
    for (int i = 0; i < nombreArchivo.length(); i++) {
        if (nombreArchivo[i] == ' ') {
            nombreArchivo[i] = '_';
        } else if (nombreArchivo[i] >= 'A' && nombreArchivo[i] <= 'Z') {
            nombreArchivo[i] = nombreArchivo[i] + 32; // Convertir a minúscula
        }
    }

    string calidad = esCalidadAlta ? "320" : "128";
    return rutaBase + nombreArchivo + "_" + calidad + ".ogg";
}

string Cancion::formatearDuracion() const {
    int minutos = duracion / 60;
    int segundos = duracion % 60;

    stringstream ss;
    ss << minutos << ":" << setfill('0') << setw(2) << segundos;
    return ss.str();
}

void Cancion::mostrarInfo() const {
    cout << "\n=== INFORMACION DE LA CANCION ===" << endl;
    cout << "ID: " << idCancion << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Duracion: " << formatearDuracion() << endl;
    cout << "Reproducciones: " << reproducciones << endl;
    cout << "================================\n" << endl;
}
