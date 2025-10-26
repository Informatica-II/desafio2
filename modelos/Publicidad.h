#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

#include <string>
#include <iostream>

using namespace std;

class Publicidad {
private:
    int idPublicidad;
    string categoria;      // AAA, B o C
    string mensaje;
    string empresa;
    int duracion;          // en segundos

public:
    Publicidad();
    Publicidad(int id, string cat, string msg, string emp, int dur);
    ~Publicidad();

    // Getters
    int getIdPublicidad() const;
    string getCategoria() const;
    string getMensaje() const;
    string getEmpresa() const;
    int getDuracion() const;

    // Métodos
    int getPrioridad() const;  // Retorna 1, 2 o 3
    void mostrar() const;
};

#endif
