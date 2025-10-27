#ifndef REPRODUCTOR_H
#define REPRODUCTOR_H

#include "Cancion.h"
#include "Publicidad.h"
#include "Servicios/GestorCanciones.h"
#include "Servicios/GestorPublicidades.h"
#include <chrono>
#include <thread>
#include <string>

using namespace std;
using namespace std::chrono;

class Reproductor {
private:
    GestorCanciones* gestorCanciones;
    GestorPublicidades* gestorPublicidades;

    // Control de reproducción Premium
    int* historialCanciones;
    int cantidadHistorial;
    bool modoRepetir;

    // Métodos privados auxiliares
    void pausarConTemporizador(int segundos);
    void mostrarControlesPremium();
    bool procesarComandoReproduccion(char comando, int& indiceActual, int totalCanciones,
                                     bool& continuar);
    void reproducirCancionConInfo(Cancion* cancion, bool esCalidadAlta, int numero, int total);

public:
    Reproductor(GestorCanciones* gestorCanc, GestorPublicidades* gestorPub);
    ~Reproductor();

    // Reproducción estándar (con publicidad)
    void reproduccionAleatoriaEstandar(int totalCanciones = 10);

    // Reproducción Premium (con controles)
    void reproduccionAleatoriaPremium(int totalCanciones = 15);
    void reproducirListaConControles(Cancion** listaCanciones, int totalCanciones);

    // Reproducción simple (sin controles)
    void reproducirCancion(Cancion* cancion, bool esCalidadAlta);
};

#endif
