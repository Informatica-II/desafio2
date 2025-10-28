#include "Credito.h"
#include <iomanip>

Credito::Credito() {
    nombre = "";
    apellido = "";
    codigoSACC = "";
    tipoCredito = "";
}

Credito::Credito(string nom, string apell, string codigo, string tipo) {
    nombre = nom;
    apellido = apell;
    codigoSACC = codigo;
    tipoCredito = tipo;
}

Credito::~Credito() {}

string Credito::getNombre() const {
    return nombre;
}

string Credito::getApellido() const {
    return apellido;
}

string Credito::getCodigoSACC() const {
    return codigoSACC;
}

string Credito::getTipoCredito() const {
    return tipoCredito;
}

string Credito::getTipoCorto() const {
    if (tipoCredito == "Compositor") {
        return "C";
    } else if (tipoCredito == "Productor") {
        return "P";
    } else if (tipoCredito == "Musico") {
        return "M";
    }
    return "??"; // En caso de un tipo desconocido
}

string Credito::getNombreCompleto() const {
    return nombre + " " + apellido;
}

void Credito::mostrarInfo() const {
    cout << "  - " << tipoCredito << ": " << getNombreCompleto()
    << " (SACC: " << codigoSACC << ")" << endl;
}

double Credito::calcularRegalias(long reproducciones) const {
    // Tarifas según tipo de crédito (en COP por reproducción)
    double tarifaPorReproduccion = 0.0;

    if (tipoCredito == "Compositor") {
        tarifaPorReproduccion = 0.50;  // 50 centavos por reproducción
    } else if (tipoCredito == "Productor") {
        tarifaPorReproduccion = 0.30;  // 30 centavos
    } else if (tipoCredito == "Musico") {
        tarifaPorReproduccion = 0.20;  // 20 centavos
    }

    return reproducciones * tarifaPorReproduccion;
}
