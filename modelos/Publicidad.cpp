#include "Publicidad.h"

Publicidad::Publicidad() {
    idPublicidad = 0;
    categoria = "";
    mensaje = "";
    empresa = "";
    duracion = 0;
}

Publicidad::Publicidad(int id, string cat, string msg, string emp, int dur) {
    idPublicidad = id;
    categoria = cat;
    mensaje = msg;
    empresa = emp;
    duracion = dur;
}

Publicidad::~Publicidad() {}

int Publicidad::getIdPublicidad() const {
    return idPublicidad;
}

string Publicidad::getCategoria() const {
    return categoria;
}

string Publicidad::getMensaje() const {
    return mensaje;
}

string Publicidad::getEmpresa() const {
    return empresa;
}

int Publicidad::getDuracion() const {
    return duracion;
}

int Publicidad::getPrioridad() const {
    if (categoria == "AAA") return 3;
    if (categoria == "B") return 2;
    return 1;  // Categoria C
}

void Publicidad::mostrar() const {
    cout << "\n========================================" << endl;
    cout << "         ANUNCIO PUBLICITARIO           " << endl;
    cout << "========================================" << endl;
    cout << mensaje << endl;
    cout << "----------------------------------------" << endl;
    cout << "Anunciante: " << empresa << endl;
    cout << "========================================" << endl;
}
