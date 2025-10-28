#include "modelos/Cancion.h"
#include <sstream>
#include <iomanip>

Cancion::Cancion() {
    idCancion = 0;
    idArtista = 0;
    idAlbum = 0;
    idCancionPropia = 0;
    nombre = "";
    duracion = 0;
    reproducciones = 0;
    rutaAudio = "";
    rutaImagen = "";

    productores = new Credito*[10];
    cantidadProductores = 0;

    musicos = new Credito*[20];
    cantidadMusicos = 0;

    compositores = new Credito*[10];
    cantidadCompositores = 0;
}

Cancion::Cancion(long id, string nom, int dur, long repro, string rutaAud, string rutaImg, string creditos) {
    idCancion = id;
    nombre = nom;
    duracion = dur;
    reproducciones = repro;
    rutaAudio = rutaAud;
    rutaImagen = rutaImg;

    extraerIdsDesdeIdCancion();

    productores = new Credito*[10];
    cantidadProductores = 0;

    musicos = new Credito*[20];
    cantidadMusicos = 0;

    compositores = new Credito*[10];
    cantidadCompositores = 0;
}

Cancion::~Cancion() {
    liberarCreditos();

    delete[] productores;
    delete[] musicos;
    delete[] compositores;
}

void Cancion::extraerIdsDesdeIdCancion() {
    idArtista = idCancion / 10000;                    // Divide por 10000 = 10001
    idAlbum = (idCancion / 100) % 100;                // Obtiene dígitos 6-7
    idCancionPropia = idCancion % 100;                // Obtiene últimos 2 dígitos
}

void Cancion::liberarCreditos() {
    for (int i = 0; i < cantidadProductores; i++) {
        delete productores[i];
    }
    cantidadProductores = 0;

    for (int i = 0; i < cantidadMusicos; i++) {
        delete musicos[i];
    }
    cantidadMusicos = 0;

    for (int i = 0; i < cantidadCompositores; i++) {
        delete compositores[i];
    }
    cantidadCompositores = 0;
}

long Cancion::getIdCancion() const {
    return idCancion;
}

int Cancion::getIdArtista() const {
    return idArtista;
}

int Cancion::getIdAlbum() const {
    return idAlbum;
}

string Cancion::getNombre() const {
    return nombre;
}

int Cancion::getIdCancionPropia() const {
    return idCancionPropia;
}

int Cancion::getDuracion() const {
    return duracion;
}

long Cancion::getReproducciones() const {
    return reproducciones;
}

string Cancion::getRutaBase() const {
    return rutaBase;
}

string Cancion::getRutaImagen() const {
    return rutaImagen;
}

Credito** Cancion::getProductores() const {
    return productores;
}

int Cancion::getCantidadProductores() const {
    return cantidadProductores;
}

Credito** Cancion::getMusicos() const {
    return musicos;
}

int Cancion::getCantidadMusicos() const {
    return cantidadMusicos;
}

Credito** Cancion::getCompositores() const {
    return compositores;
}

int Cancion::getCantidadCompositores() const {
    return cantidadCompositores;
}

void Cancion::setReproducciones(long repro) {
    reproducciones = repro;
}

void Cancion::incrementarReproducciones() {
    reproducciones++;
}

void Cancion::agregarProductor(Credito* credito) {
    if (cantidadProductores < 10) {
        productores[cantidadProductores++] = credito;
    }
}

void Cancion::agregarMusico(Credito* credito) {
    if (cantidadMusicos < 20) {
        musicos[cantidadMusicos++] = credito;
    }
}

void Cancion::agregarCompositor(Credito* credito) {
    if (cantidadCompositores < 10) {
        compositores[cantidadCompositores++] = credito;
    }
}

string Cancion::getRutaCompleta(bool esCalidadAlta) const {
    string calidad = esCalidadAlta ? "_320.ogg" : "_128.ogg";
    return rutaAudio + nombre + calidad;
}

string Cancion::formatearDuracion() const {
    int minutos = duracion / 60;
    int segundos = duracion % 60;

    stringstream ss;
    ss << minutos << "m " << segundos << "s";
    return ss.str();
}

void Cancion::mostrarInfo() const {
    cout << "ID Cancion: " << idCancion << endl;
    cout << "   ID Artista: " << idArtista << endl;
    cout << "   ID Album: " << idAlbum << endl;
    cout << "   ID Cancion Propia: " << idCancionPropia << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Duracion: " << formatearDuracion() << endl;
    cout << "Reproducciones: " << reproducciones << endl;
    cout << "Ruta Audio: " << rutaAudio << endl;
    cout << "Ruta Imagen: " << rutaImagen << endl;
}

void Cancion::mostrarCreditos() const {
    cout << "\n=== CREDITOS ===" << endl;

    if (cantidadProductores > 0) {
        cout << "\nPRODUCTORES:" << endl;
        for (int i = 0; i < cantidadProductores; i++) {
            productores[i]->mostrarInfo();
        }
    }

    if (cantidadMusicos > 0) {
        cout << "\nMUSICOS:" << endl;
        for (int i = 0; i < cantidadMusicos; i++) {
            musicos[i]->mostrarInfo();
        }
    }

    if (cantidadCompositores > 0) {
        cout << "\nCOMPOSITORES:" << endl;
        for (int i = 0; i < cantidadCompositores; i++) {
            compositores[i]->mostrarInfo();
        }
    }

    cout << "================" << endl;
}

void Cancion::calcularRegaliasTotales() const {
    double totalProductores = 0.0;
    double totalMusicos = 0.0;
    double totalCompositores = 0.0;

    for (int i = 0; i < cantidadProductores; i++) {
        totalProductores += productores[i]->calcularRegalias(reproducciones);
    }

    for (int i = 0; i < cantidadMusicos; i++) {
        totalMusicos += musicos[i]->calcularRegalias(reproducciones);
    }

    for (int i = 0; i < cantidadCompositores; i++) {
        totalCompositores += compositores[i]->calcularRegalias(reproducciones);
    }

    cout << "\n=== REGALIAS TOTALES (Cancion: " << nombre << ") ===" << endl;
    cout << "Reproducciones: " << reproducciones << endl;
    cout << "\nProductores: $" << fixed << setprecision(2) << totalProductores << " COP" << endl;
    cout << "Musicos: $" << totalMusicos << " COP" << endl;
    cout << "Compositores: $" << totalCompositores << " COP" << endl;
    cout << "TOTAL: $" << (totalProductores + totalMusicos + totalCompositores) << " COP" << endl;
    cout << "========================================\n" << endl;
}
