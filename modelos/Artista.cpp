#include "Artista.h"
#include <iomanip>
#include <sstream>

Artista::Artista() {
    idArtista = 0;
    nombre = "";
    edad = 0;
    paisOrigen = "";
    seguidores = 0;
    posicionTendencia = 0;
}

Artista::Artista(int id, string nom, int ed, string pais, long seg, int pos) {
    idArtista = id;
    nombre = nom;
    edad = ed;
    paisOrigen = pais;
    seguidores = seg;
    posicionTendencia = pos;
}

Artista::~Artista() {}

int Artista::getIdArtista() const {
    return idArtista;
}

string Artista::getNombre() const {
    return nombre;
}

int Artista::getEdad() const {
    return edad;
}

string Artista::getPaisOrigen() const {
    return paisOrigen;
}

long Artista::getSeguidores() const {
    return seguidores;
}

int Artista::getPosicionTendencia() const {
    return posicionTendencia;
}

void Artista::setSeguidores(long seg) {
    seguidores = seg;
}

void Artista::setPosicionTendencia(int pos) {
    posicionTendencia = pos;
}

string Artista::formatearSeguidores() const {
    if (seguidores >= 1000000) {
        double millones = seguidores / 1000000.0;
        stringstream ss;
        ss << fixed << setprecision(1) << millones << "M";
        return ss.str();
    } else if (seguidores >= 1000) {
        double miles = seguidores / 1000.0;
        stringstream ss;
        ss << fixed << setprecision(1) << miles << "K";
        return ss.str();
    }
    return to_string(seguidores);
}

void Artista::mostrarInfo() const {
    cout << "ID Artista: " << idArtista << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Edad: " << edad << " años" << endl;
    cout << "País: " << paisOrigen << endl;
    cout << "Seguidores: " << formatearSeguidores() << endl;
    cout << "Posición en tendencia: #" << posicionTendencia << endl;
}
