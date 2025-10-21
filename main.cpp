#include <iostream>
#include <fstream>
#include <string>
#include <usuarios.h>

using namespace std;

string tipoUsuario;

bool verificarCredenciales(const string& usuario, const string& contrasena) {
    ifstream archivo("usuarios.txt");
    string u, c, tipo;
    int contador = 0;

    while (!archivo.eof()) {
        getline(archivo, u, ',');     // Usuario
        getline(archivo, c, ',');     // Contraseña
        getline(archivo, tipo);       // Tipo de usuario
        contador++;

        if (u == usuario && c == contrasena) {
            tipoUsuario = tipo;
            cout << "Tipo de usuario: " << tipo << endl;
            cout << "Iteraciones realizadas: " << contador << endl;
            return true;
        }
    }

    cout << "Iteraciones realizadas: " << contador << endl;
    return false;
}

int main() {
    string usuario, contrasena;

    cout << "--- Inicio de sesion ---" << endl;
    cout << "Usuario: ";
    cin >> usuario;
    cout << "Contrasenia: ";
    cin >> contrasena;

    if (verificarCredenciales(usuario, contrasena)) {
        cout << "Inicio de sesion exitoso" << endl;
        if (tipoUsuario == "premium") {
            cout << "Acceso completo a funciones premium." << endl;
        } else {
            cout << "Acceso limitado: usuario estandar." << endl;
        }
    } else {
        cout << "Usuario o contrasenia incorrectos." << endl;
    }
}
