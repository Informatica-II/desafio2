#ifndef CREDITO_H
#define CREDITO_H

#include <string>
#include <iostream>

using namespace std;

class Credito {
private:
    string nombre;
    string apellido;
    string codigoSACC;  // 10 caracteres alfanuméricos
    string tipoCredito; // "Productor", "Musico", "Compositor"
    string getTipoCorto() const;

public:
    Credito();
    Credito(string nom, string apell, string codigo, string tipo);
    ~Credito();

    // Getters
    string getNombre() const;
    string getApellido() const;
    string getCodigoSACC() const;
    string getTipoCredito() const;
    string getNombreCompleto() const;

    // Métodos
    void mostrarInfo() const;
    double calcularRegalias(long reproducciones) const;
};

#endif
