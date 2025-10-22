#ifndef CANCION_H
#define CANCION_H

#include <string>
#include <iostream>

using namespace std;

class Cancion {
private:
    long idCancion;
    int idArtista;
    int idAlbum;
    string nombre;
    int duracion;
    long reproducciones;
    string rutaBase;

public:
    Cancion();
    Cancion(long id, int artista, int album, string nom, int dur, long repro, string ruta);
    ~Cancion();

    // Getters
    long getIdCancion() const;
    int getIdArtista() const;
    int getIdAlbum() const;
    string getNombre() const;
    int getDuracion() const;
    long getReproducciones() const;
    string getRutaBase() const;

    // Setters
    void setReproducciones(long repro);
    void incrementarReproducciones();

    // Métodos
    string getRutaCompleta(bool esCalidadAlta) const;
    void mostrarInfo() const;
    string formatearDuracion() const;
};

#endif
