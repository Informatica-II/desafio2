#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include <iostream>

using namespace std;

class Usuario {
protected:
    string nickname;
    string contrasena;        // <- NUEVO
    string tipoMembresia;
    string ciudad;
    string pais;
    string fechaInscripcion;

public:
    Usuario();
    Usuario(string nick, string pass, string tipo, string city, string country, string fecha);
    ~Usuario();

    // Getters
    string getNickname() const;
    string getContrasena() const;  // <- NUEVO
    string getTipoMembresia() const;
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;

    // Setters
    void setNickname(string nick);
    void setContrasena(string pass);  // <- NUEVO
    void setTipoMembresia(string tipo);
    void setCiudad(string city);
    void setPais(string country);
    void setFechaInscripcion(string fecha);

    // Métodos
    bool esPremium() const;
    bool validarContrasena(string pass) const;  // <- NUEVO
    void mostrarInfo() const;
};

#endif
