#include "Servicios/GestorUsuarios.h"
#include <iostream>
#include <fstream>

GestorUsuarios::GestorUsuarios() {
    capacidad = 10;
    cantidadUsuarios = 0;
    usuarios = new Usuario*[capacidad];
}

GestorUsuarios::~GestorUsuarios() {
    for (int i = 0; i < cantidadUsuarios; i++) {
        delete usuarios[i];
    }
    delete[] usuarios;
}

void GestorUsuarios::redimensionar() {
    capacidad *= 2;
    Usuario** nuevo = new Usuario*[capacidad];

    for (int i = 0; i < cantidadUsuarios; i++) {
        nuevo[i] = usuarios[i];
    }

    delete[] usuarios;
    usuarios = nuevo;
}

void GestorUsuarios::dividirLinea(string linea, string* datos) {
    int pos = 0;
    int inicio = 0;

    for (int i = 0; i < 6; i++) {
        pos = linea.find('|', inicio);
        if (pos == string::npos) {
            datos[i] = linea.substr(inicio);
        } else {
            datos[i] = linea.substr(inicio, pos - inicio);
            inicio = pos + 1;
        }
    }
}

bool GestorUsuarios::cargarDesdeArchivo(string rutaArchivo) {
    ifstream archivo(rutaArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir el archivo: " << rutaArchivo << endl;
        return false;
    }

    string linea;
    getline(archivo, linea); // Saltar encabezado

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        string datos[6];
        dividirLinea(linea, datos);

        Usuario* nuevo = new Usuario(datos[0], datos[1], datos[2], datos[3], datos[4], datos[5]);
        agregarUsuario(nuevo);
    }

    archivo.close();
    cout << "[INFO] " << cantidadUsuarios << " usuarios cargados correctamente." << endl;
    return true;
}

bool GestorUsuarios::guardarEnArchivo(string rutaArchivo) {
    ofstream archivo(rutaArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir el archivo para escritura: " << rutaArchivo << endl;
        return false;
    }

    // Escribir encabezado
    archivo << "nickname|contrasena|tipoMembresia|ciudad|pais|fechaInscripcion" << endl;

    // Escribir usuarios
    for (int i = 0; i < cantidadUsuarios; i++) {
        archivo << usuarios[i]->getNickname() << "|"
                << usuarios[i]->getContrasena() << "|"
                << usuarios[i]->getTipoMembresia() << "|"
                << usuarios[i]->getCiudad() << "|"
                << usuarios[i]->getPais() << "|"
                << usuarios[i]->getFechaInscripcion() << endl;
    }

    archivo.close();
    return true;
}

Usuario* GestorUsuarios::buscarUsuario(string nickname) {
    for (int i = 0; i < cantidadUsuarios; i++) {
        if (usuarios[i]->getNickname() == nickname) {
            return usuarios[i];
        }
    }
    return nullptr;
}

bool GestorUsuarios::existeUsuario(string nickname) {
    return buscarUsuario(nickname) != nullptr;
}

void GestorUsuarios::agregarUsuario(Usuario* usuario) {
    if (cantidadUsuarios >= capacidad) {
        redimensionar();
    }

    usuarios[cantidadUsuarios] = usuario;
    cantidadUsuarios++;
}

int GestorUsuarios::getCantidadUsuarios() const {
    return cantidadUsuarios;
}

void GestorUsuarios::mostrarTodos() const {
    cout << "\n=== USUARIOS REGISTRADOS ===" << endl;
    for (int i = 0; i < cantidadUsuarios; i++) {
        cout << (i + 1) << ". " << usuarios[i]->getNickname()
        << " (" << usuarios[i]->getTipoMembresia() << ")" << endl;
    }
    cout << "Total: " << cantidadUsuarios << " usuarios\n" << endl;
}

