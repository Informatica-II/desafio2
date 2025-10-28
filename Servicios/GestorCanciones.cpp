#include "Servicios/GestorCanciones.h"
#include "Servicios/MedidorRecursos.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>

GestorCanciones::GestorCanciones() {
    capacidad = 50;
    cantidadCanciones = 0;
    canciones = new Cancion*[capacidad];
    srand(time(0)); // Inicializar semilla aleatoria
}

GestorCanciones::~GestorCanciones() {
    for (int i = 0; i < cantidadCanciones; i++) {
        delete canciones[i];
    }
    delete[] canciones;
}

void GestorCanciones::redimensionar() {
    capacidad *= 2;
    Cancion** nuevo = new Cancion*[capacidad];

    for (int i = 0; i < cantidadCanciones; i++) {
        nuevo[i] = canciones[i];
    }

    delete[] canciones;
    canciones = nuevo;
}

void GestorCanciones::dividirLinea(string linea, string* datos) {
    int pos = 0;
    int inicio = 0;

    for (int i = 0; i < 7; i++) {
        pos = linea.find('|', inicio);
        if (pos == string::npos) {
            datos[i] = linea.substr(inicio);
        } else {
            datos[i] = linea.substr(inicio, pos - inicio);
            inicio = pos + 1;
        }
    }
}

bool GestorCanciones::cargarDesdeArchivo(string rutaArchivo) {
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir: " << rutaArchivo << endl;
        return false;
    }

    string linea;
    getline(archivo, linea); // Saltar encabezados

    int cargados = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        string datos[7];

        // Leer campos básicos
        for (int i = 0; i < 6; i++) {
            getline(ss, datos[i], '|');
        }
        getline(ss, datos[6]);

        try {
            long id = stol(datos[0]);
            string nombre = datos[1];
            int duracion = stoi(datos[2]);
            long reproducciones = stol(datos[3]);
            string rutaAudio = datos[4];
            string rutaImagen = datos[5];
            string creditos = datos[6];

            Cancion* cancion = new Cancion(id, nombre, duracion, reproducciones, rutaAudio, rutaImagen, creditos);

            // Parsear créditos
            parsearCreditos(cancion, creditos);

            agregarCancion(cancion);
            cargados++;

        } catch (...) {
            cout << "[ERROR] Error al procesar cancion: " << linea << endl;
        }
    }

    archivo.close();
    cout << "[OK] Canciones cargadas: " << cargados << endl;
    return true;
}
void GestorCanciones::parsearCreditos(Cancion* cancion, const string& creditosStr) {
    // Formato: P:Nombre,Apellido,Codigo|M:Nombre,Apellido,Codigo|C:Nombre,Apellido,Codigo

    stringstream ss(creditosStr);
    string categoriaStr;

    while (getline(ss, categoriaStr, '|')) {
        if (categoriaStr.empty()) continue;

        // Obtener tipo de crédito
        char tipoChar = categoriaStr[0];
        string tipo;
        if (tipoChar == 'P') tipo = "Productor";
        else if (tipoChar == 'M') tipo = "Musico";
        else if (tipoChar == 'C') tipo = "Compositor";
        else continue;

        // Saltar "P:" o "M:" o "C:"
        string creditosDeCategoria = categoriaStr.substr(2);

        // Separar múltiples créditos de la misma categoría
        stringstream ss2(creditosDeCategoria);
        string creditoIndividual;

        while (getline(ss2, creditoIndividual, ';')) {
            // Dividir por comas: Nombre,Apellido,Codigo
            stringstream ss3(creditoIndividual);
            string nombre, apellido, codigo;

            getline(ss3, nombre, ',');
            getline(ss3, apellido, ',');
            getline(ss3, codigo, ',');

            Credito* credito = new Credito(nombre, apellido, codigo, tipo);

            if (tipo == "Productor") {
                cancion->agregarProductor(credito);
            } else if (tipo == "Musico") {
                cancion->agregarMusico(credito);
            } else if (tipo == "Compositor") {
                cancion->agregarCompositor(credito);
            }
        }
    }
}
Cancion* GestorCanciones::buscarCancion(string nombreCancion) {
    for (int i = 0; i < cantidadCanciones; i++) {
        if (canciones[i]->getNombre() == nombreCancion) {
            cout<<"cancion encontrada."<< endl;
            return canciones[i];
        }

    }
    return nullptr;
}


Cancion* GestorCanciones::obtenerCancionAleatoria() {
    cout << "[DEBUG] Cantidad de canciones disponibles: " << cantidadCanciones << endl;
    if (cantidadCanciones == 0) return nullptr;

    int indice = rand() % cantidadCanciones;
    MedidorRecursos::registrarIteracion();
    cout << "[DEBUG] Cancion aleatoria seleccionada: " << canciones[indice]->getNombre() << endl;
    cout << "[DEBUG] Indice aleatorio: " << indice << endl;
    return canciones[indice];
}

void GestorCanciones::agregarCancion(Cancion* cancion) {
    if (cantidadCanciones >= capacidad) {
        redimensionar();
    }

    canciones[cantidadCanciones] = cancion;
    cantidadCanciones++;
}

int GestorCanciones::getCantidadCanciones() const {
    return cantidadCanciones;
}

void GestorCanciones::mostrarTodas() const {
    cout << "\n=== CATALOGO DE CANCIONES ===" << endl;
    for (int i = 0; i < cantidadCanciones; i++) {
        cout << (i + 1) << ". " << canciones[i]->getNombre()
             << " (" << canciones[i]->formatearDuracion() << ")" << "\tID: "<<canciones[i]->getIdCancion()<<endl;
    }
    cout << "Total: " << cantidadCanciones << " canciones\n" << endl;
}

Cancion* GestorCanciones::buscarPorId(long id) {
    for (int i = 0; i < cantidadCanciones; i++) {
        MedidorRecursos::registrarIteracion();
        if (canciones[i]->getIdCancion() == id) {
            return canciones[i];
        }
    }
    return nullptr;
}

