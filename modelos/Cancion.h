#ifndef CANCION_H
#define CANCION_H

#include <string>
#include <iostream>
#include "modelos/Credito.h"

using namespace std;

class Cancion {
private:
    long idCancion;
    int idArtista;
    int idAlbum;
    int idCancionPropia;
    string nombre;
    int duracion;
    long reproducciones;
    string rutaBase;
    string rutaAudio;
    string rutaImagen;

    Credito** productores;
    int cantidadProductores;

    Credito** musicos;
    int cantidadMusicos;

    Credito** compositores;
    int cantidadCompositores;

    // Métodos auxiliares privados
    void extraerIdsDesdeIdCancion();
    void liberarCreditos();

public:
    Cancion();
    Cancion(long id, string nom, int dur, long repro, string rutaAud, string rutaImg, string creditos);
    ~Cancion();

    // Getters
    long getIdCancion() const;
    int getIdArtista() const;
    int getIdAlbum() const;
    int getIdCancionPropia() const;
    string getNombre() const;
    int getDuracion() const;
    long getReproducciones() const;
    string getRutaBase() const;
    string getRutaImagen() const;

    // Getters de créditos
    Credito** getProductores() const;
    int getCantidadProductores() const;
    Credito** getMusicos() const;
    int getCantidadMusicos() const;
    Credito** getCompositores() const;
    int getCantidadCompositores() const;

    // Setters
    void setReproducciones(long repro);
    void incrementarReproducciones();

    // Métodos
    void agregarProductor(Credito* credito);
    void agregarMusico(Credito* credito);
    void agregarCompositor(Credito* credito);
    string getRutaCompleta(bool esCalidadAlta) const;
    void mostrarInfo() const;
    void mostrarCreditos() const;
    void calcularRegaliasTotales() const;
    string formatearDuracion() const;
};

#endif
