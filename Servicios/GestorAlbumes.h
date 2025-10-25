#ifndef GESTORALBUMES_H
#define GESTORALBUMES_H

#include "modelos/Album.h"
#include <string>

using namespace std;

class GestorAlbumes {
private:
    Album** albumes;
    int cantidadAlbumes;
    int capacidad;

    void redimensionar();
    void dividirLinea(string linea, string* datos);
    vector<string> dividirGeneros(const string& generos);

public:
    GestorAlbumes();
    ~GestorAlbumes();

    bool cargarDesdeArchivo(string rutaArchivo);
    Album* buscarPorId(int idAlbum, int idArtista);
    void agregarAlbum(Album* album);
    int getCantidadAlbumes() const;
    void mostrarTodos() const;
    void mostrarPorArtista(int idArtista) const;
    Album** getAlbumes() const;
};

#endif
