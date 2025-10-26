#include "GestorPublicidades.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

GestorPublicidades::GestorPublicidades() {
    capacidad = 10;
    cantidadPublicidades = 0;
    publicidades = new Publicidad*[capacidad];

    for (int i = 0; i < capacidad; i++) {
        publicidades[i] = nullptr;
    }

    srand(time(0));
}

GestorPublicidades::~GestorPublicidades() {
    for (int i = 0; i < cantidadPublicidades; i++) {
        delete publicidades[i];
    }
    delete[] publicidades;
}

GestorPublicidades::GestorPublicidades(const GestorPublicidades& otro) :
    cantidadPublicidades(otro.cantidadPublicidades),
    capacidad(otro.capacidad)
{
    // 1. Asignar nueva memoria para el arreglo de punteros.
    publicidades = new Publicidad*[capacidad];

    // 2. Copiar los punteros (ambos objetos comparten las instancias de Publicidad,
    //    lo cual es aceptable si no se espera que la copia las modifique o elimine).
    for (int i = 0; i < cantidadPublicidades; i++) {
        publicidades[i] = otro.publicidades[i];
    }

    // 3. Inicializar los espacios restantes a nullptr.
    for (int i = cantidadPublicidades; i < capacidad; i++) {
        publicidades[i] = nullptr;
    }
}

GestorPublicidades& GestorPublicidades::operator=(const GestorPublicidades& otro) {
    if (this != &otro) { // Evitar la auto-asignación (g1 = g1)
        // 1. Liberar la memoria antigua (¡CRUCIAL!)
        // Llama al destructor de tu objeto.
        for (int i = 0; i < cantidadPublicidades; i++) {
            delete publicidades[i];
        }
        delete[] publicidades;

        // 2. Copiar los valores
        cantidadPublicidades = otro.cantidadPublicidades;
        capacidad = otro.capacidad;

        // 3. Crear y llenar el nuevo arreglo (similar al constructor de copia)
        publicidades = new Publicidad*[capacidad];
        for (int i = 0; i < cantidadPublicidades; i++) {
            publicidades[i] = otro.publicidades[i];
        }
        for (int i = cantidadPublicidades; i < capacidad; i++) {
            publicidades[i] = nullptr;
        }
    }
    return *this;
}

void GestorPublicidades::redimensionar() {
    // 1. Inicializar la variable local con el valor actual de 'capacidad'.
    int oldCapacidad = capacidad;

    // 2. Duplicar la capacidad (ahora oldCapacidad tiene el valor antiguo).
    capacidad *= 2;

    // 3. Crear el nuevo arreglo.
    Publicidad** nuevo = new Publicidad*[capacidad];

    // 4. Copiar los punteros existentes.
    for (int i = 0; i < cantidadPublicidades; i++) {
        nuevo[i] = publicidades[i];
    }

    // 5. INICIALIZAR LOS NUEVOS ESPACIOS A nullptr (Usando oldCapacidad como inicio).
    // Esto es CRUCIAL para evitar el SIGSEGV cuando el arreglo se itera parcialmente lleno.
    for (int i = oldCapacidad; i < capacidad; i++) {
        nuevo[i] = nullptr;
    }

    // 6. Limpiar y reasignar.
    delete[] publicidades;
    publicidades = nuevo;
}

void GestorPublicidades::dividirLinea(string linea, string* datos) {
    stringstream ss(linea);
    string temp;
    int index = 0;

    while (getline(ss, temp, '|') && index < 5) {
        datos[index++] = temp;
    }
}

bool GestorPublicidades::cargarDesdeArchivo(string rutaArchivo) {
    ifstream archivo(rutaArchivo.c_str());

    if (!archivo.is_open()) {
        cout << "[ERROR] No se pudo abrir: " << rutaArchivo << endl;
        return false;
    }

    string linea;
    getline(archivo, linea);  // Saltar encabezados

    int cargados = 0;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        string datos[5];
        dividirLinea(linea, datos);

        try {
            int id = stoi(datos[0]);
            string categoria = datos[1];
            string mensaje = datos[2];
            string empresa = datos[3];
            int duracion = stoi(datos[4]);

            Publicidad* pub = new Publicidad(id, categoria, mensaje, empresa, duracion);
            agregarPublicidad(pub);
            cargados++;
        } catch (...) {
            cout << "[ERROR] Error al procesar publicidad: " << linea << endl;
        }
    }

    archivo.close();
    cout << "[OK] Publicidades cargadas: " << cargados << endl;
    return true;
}

Publicidad* GestorPublicidades::obtenerPublicidadAleatoria() {
    if (cantidadPublicidades == 0) {
        return nullptr;
    }

    // Calcular suma total de prioridades
    int sumaPrioridades = 0;
    for (int i = 0; i < cantidadPublicidades; i++) {
        sumaPrioridades += publicidades[i]->getPrioridad();
    }

    // Generar número aleatorio entre 1 y sumaPrioridades
    int aleatorio = (rand() % sumaPrioridades) + 1;

    // Seleccionar publicidad según peso
    int acumulado = 0;
    for (int i = 0; i < cantidadPublicidades; i++) {
        acumulado += publicidades[i]->getPrioridad();
        if (aleatorio <= acumulado) {
            return publicidades[i];
        }
    }

    return publicidades[0];  // Fallback
}

void GestorPublicidades::agregarPublicidad(Publicidad* pub) {
    if (cantidadPublicidades >= capacidad) {
        redimensionar();
    }
    publicidades[cantidadPublicidades++] = pub;
}

int GestorPublicidades::getCantidadPublicidades() const {
   return cantidadPublicidades;

}
