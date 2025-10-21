#ifndef USUARIOS_H
#define USUARIOS_H

#include <string>
using namespace std;

class Usuarios
{
private:
    string contrasena;
public:
    string nombre;
    string tipoUsuario;
    Usuarios();
    Usuarios(const string& nombre, const string& contrasena, const string& tipo);
    bool verificarCredenciales(const string& usuario, const string& contrasena);

    // Getter solo para nombre y tipo
    string getNombre() const;
    string getTipoUsuario() const;
};

#endif // USUARIOS_H
