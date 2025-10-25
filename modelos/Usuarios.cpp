#include "modelos/Usuarios.h"
#include <iostream>

using namespace std;

Usuario::Usuario() {
    nickname = "";
    contrasena = "";
    tipoMembresia = "estandar";
    ciudad = "";
    pais = "";
    fechaInscripcion = "";

    listaFavoritos = nullptr;
    gestorSeguimiento = nullptr;
}

Usuario::Usuario(string nick, string pass, string tipo, string city, string country, string fecha) {
    nickname = nick;
    contrasena = pass;
    tipoMembresia = tipo;
    ciudad = city;
    pais = country;
    fechaInscripcion = fecha;

    //SOLO SI ES PREMIUM TIENE FAVORITOS
   if (tipoMembresia == "premium") {
    listaFavoritos = new ListaFavoritos();
    gestorSeguimiento = new GestorSeguimiento();
      } else {
    listaFavoritos = nullptr;
    gestorSeguimiento = nullptr;
      }
}

Usuario::~Usuario() {

    //Destructor de memoria
    if (listaFavoritos != nullptr) {
        delete listaFavoritos;
        listaFavoritos = nullptr;
    }

    if (gestorSeguimiento != nullptr) {
        delete gestorSeguimiento;
        gestorSeguimiento = nullptr;
    }
}

// Getters
string Usuario::getNickname() const {
    return nickname;
}

string Usuario::getContrasena() const {
    return contrasena;
}

string Usuario::getTipoMembresia() const {
    return tipoMembresia;
}

string Usuario::getCiudad() const {
    return ciudad;
}

string Usuario::getPais() const {
    return pais;
}

string Usuario::getFechaInscripcion() const {
    return fechaInscripcion;
}

ListaFavoritos* Usuario::getListaFavoritos() {
    return listaFavoritos;
}

GestorSeguimiento* Usuario::getGestorSeguimiento() {
    return gestorSeguimiento;
}
// Setters
void Usuario::setNickname(string nick) {
    nickname = nick;
}

void Usuario::setContrasena(string pass) {
    contrasena = pass;
}

void Usuario::setTipoMembresia(string tipo) {
    tipoMembresia = tipo;
}

void Usuario::setCiudad(string city) {
    ciudad = city;
}

void Usuario::setPais(string country) {
    pais = country;
}

void Usuario::setFechaInscripcion(string fecha) {
    fechaInscripcion = fecha;
}

// Métodos
bool Usuario::esPremium() const {
    return tipoMembresia == "premium";
}

bool Usuario::validarContrasena(string pass) const {
    return contrasena == pass;
}

void Usuario::mostrarInfo() const {
    cout << "\n=== INFORMACION DEL USUARIO ===" << endl;
    cout << "Nickname: " << nickname << endl;
    cout << "Membresia: " << tipoMembresia << endl;
    cout << "Ubicacion: " << ciudad << ", " << pais << endl;
    cout << "Fecha inscripcion: " << fechaInscripcion << endl;
    cout << "================================\n" << endl;
}

