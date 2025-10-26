#include "Album.h"
#include <sstream>

Album::Album() {
    idAlbum = 0;
    idArtista = 0;
    nombre = "";
    fechaLanzamiento = "";
    duracionTotal = 0;
    generos = nullptr;
    cantidadGeneros = 0;
    selloDisquero = "";
    puntuacion = 0;
    rutaPortada = "";
}

Album::Album(int idAlb, int idArt, string nom, string fecha, int duracion,
             string* gen, int cantGen, string sello, int punt, string ruta) {
    idAlbum = idAlb;
    idArtista = idArt;
    nombre = nom;
    fechaLanzamiento = fecha;
    duracionTotal = duracion;
    cantidadGeneros = cantGen;
    selloDisquero = sello;
    puntuacion = punt;
    rutaPortada = ruta;

    // Copiar arreglo de géneros
    generos = new string[cantidadGeneros];
    for (int i = 0; i < cantidadGeneros; i++) {
        generos[i] = gen[i];
    }
}

Album::~Album() {
    if (generos != nullptr) {
        delete[] generos;
    }
}

int Album::getIdAlbum() const {
    return idAlbum;
}

int Album::getIdArtista() const {
    return idArtista;
}

string Album::getNombre() const {
    return nombre;
}

string Album::getFechaLanzamiento() const {
    return fechaLanzamiento;
}

int Album::getDuracionTotal() const {
    return duracionTotal;
}

string* Album::getGeneros() const {
    return generos;
}

int Album::getCantidadGeneros() const {
    return cantidadGeneros;
}

string Album::getSelloDisquero() const {
    return selloDisquero;
}

int Album::getPuntuacion() const {
    return puntuacion;
}

string Album::getRutaPortada() const {
    return rutaPortada;
}

void Album::setPuntuacion(int punt) {
    puntuacion = punt;
}

string Album::formatearDuracion() const {
    int minutos = duracionTotal / 60;
    int segundos = duracionTotal % 60;

    stringstream ss;
    ss << minutos << "m " << segundos << "s";
    return ss.str();
}

string Album::obtenerGenerosTexto() const {
    string resultado = "";
    for (int i = 0; i < cantidadGeneros; i++) {
        resultado += generos[i];
        if (i < cantidadGeneros - 1) {
            resultado += ", ";
        }
    }
    return resultado;
}

void Album::mostrarInfo() const {
    cout << "ID Album: " << idAlbum << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Fecha de lanzamiento: " << fechaLanzamiento << endl;
    cout << "Duración total: " << formatearDuracion() << endl;
    cout << "Géneros: " << obtenerGenerosTexto() << endl;
    cout << "Sello disquero: " << selloDisquero << endl;
    cout << "Puntuación: " << puntuacion << "/10" << endl;
    cout << "Portada: " << rutaPortada << endl;
}
