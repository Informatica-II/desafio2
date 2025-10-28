#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
#include <iostream>
#include "modelos/listafavoritos.h"
#include "Servicios/gestorseguimiento.h"


using namespace std;

class Usuario {

private:
    ListaFavoritos* listaFavoritos;
    GestorSeguimiento* gestorSeguimiento;

protected:
    string nickname;
    string contrasena;
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
    string getContrasena() const;
    string getTipoMembresia() const;
    string getCiudad() const;
    string getPais() const;
    string getFechaInscripcion() const;
    ListaFavoritos* getListaFavoritos();
    GestorSeguimiento* getGestorSeguimiento();

    // Setters
    void setNickname(string nick);
    void setContrasena(string pass);
    void setTipoMembresia(string tipo);
    void setCiudad(string city);
    void setPais(string country);
    void setFechaInscripcion(string fecha);
    void setListaFavoritos(ListaFavoritos* lista);

    // Métodos
    bool esPremium() const;
    bool validarContrasena(string pass) const;
    void mostrarInfo() const;
};

#endif
