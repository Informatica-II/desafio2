#include <iostream>
#include <string>
#include <usuarios.h>

using namespace std;

int main() {
    Usuarios user;
    string usuario, contrasena;

    cout << "--- Inicio de sesion ---" << endl;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasenia: ";
    cin >> contrasena;

    if (user.verificarCredenciales(usuario, contrasena)) {
        cout << "Inicio de sesion exitoso" << endl;
        if (user.tipoUsuario == "Premium") {
            cout << "Acceso completo a funciones premium." << endl;
        } else {
            cout << "Acceso limitado: usuario estandar." << endl;
        }
    } else {
        cout << "Usuario o contrasenia incorrectos." << endl;
    }
    cout << user.getTipoUsuario() << endl;
}
