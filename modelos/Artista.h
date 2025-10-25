#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>
#include <iostream>

using namespace std;

class Artista {
private:
    int idArtista;
    string nombre;
    int edad;
    string paisOrigen;
    long seguidores;
    int posicionTendencia;

public:
    Artista();
    Artista(int id, string nom, int ed, string pais, long seg, int pos);
    ~Artista();

    // Getters
    int getIdArtista() const;
    string getNombre() const;
    int getEdad() const;
    string getPaisOrigen() const;
    long getSeguidores() const;
    int getPosicionTendencia() const;

    // Setters
    void setSeguidores(long seg);
    void setPosicionTendencia(int pos);

    // Métodos
    void mostrarInfo() const;
    string formatearSeguidores() const;
};

#endif
