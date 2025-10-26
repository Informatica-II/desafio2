#ifndef GESTORPUBLICIDADES_H
#define GESTORPUBLICIDADES_H

#include "modelos/Publicidad.h"
#include <string>

using namespace std;

class GestorPublicidades {
private:
    Publicidad** publicidades;
    int cantidadPublicidades;
    int capacidad;
    GestorPublicidades(const GestorPublicidades& otro);
    GestorPublicidades& operator=(const GestorPublicidades& otro);

    void redimensionar();
    void dividirLinea(string linea, string* datos);

public:
    GestorPublicidades();
    ~GestorPublicidades();

    bool cargarDesdeArchivo(string rutaArchivo);
    Publicidad* obtenerPublicidadAleatoria();  // Con ponderación por prioridad
    void agregarPublicidad(Publicidad* pub);
    int getCantidadPublicidades() const;
};

#endif
