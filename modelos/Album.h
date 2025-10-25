#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Album {
private:
    int idAlbum;
    int idArtista;
    string nombre;
    string fechaLanzamiento;
    int duracionTotal;
    vector<string> generos;
    string selloDisquero;
    int puntuacion;
    string rutaPortada;

public:
    Album();
    Album(int idAlb, int idArt, string nom, string fecha, int duracion,
          vector<string> gen, string sello, int punt, string ruta);
    ~Album();

    // Getters
    int getIdAlbum() const;
    int getIdArtista() const;
    string getNombre() const;
    string getFechaLanzamiento() const;
    int getDuracionTotal() const;
    vector<string> getGeneros() const;
    string getSelloDisquero() const;
    int getPuntuacion() const;
    string getRutaPortada() const;

    // Setters
    void setPuntuacion(int punt);

    // Métodos
    void mostrarInfo() const;
    string formatearDuracion() const;
    string obtenerGenerosTexto() const;
};

#endif
