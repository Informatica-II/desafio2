#include "MedidorRecursos.h"
#include "modelos/usuarios.h"
#include "modelos/Cancion.h"
#include "modelos/Artista.h"
#include "modelos/Album.h"
#include "modelos/Publicidad.h"
#include "modelos/listafavoritos.h"
#include "modelos/Reproductor.h"
#include "Servicios/GestorUsuarios.h"
#include "Servicios/GestorCanciones.h"
#include "Servicios/GestorArtistas.h"
#include "Servicios/GestorAlbumes.h"
#include "Servicios/GestorPublicidades.h"
#include "Servicios/gestorseguimiento.h"
#include <iomanip>

// Inicialización de variables estáticas
long long MedidorRecursos::contadorIteraciones = 0;
bool MedidorRecursos::medicionActiva = false;

MedidorRecursos::MedidorRecursos() {}

MedidorRecursos::~MedidorRecursos() {}

// ============================================
// CONTROL DE MEDICIÓN
// ============================================

void MedidorRecursos::iniciarMedicion() {
    medicionActiva = true;
    contadorIteraciones = 0;
}

void MedidorRecursos::detenerMedicion() {
    medicionActiva = false;
}

void MedidorRecursos::reiniciarContador() {
    contadorIteraciones = 0;
}

void MedidorRecursos::registrarIteracion() {
    if (medicionActiva) {
        contadorIteraciones++;
    }
}

void MedidorRecursos::registrarIteraciones(int cantidad) {
    if (medicionActiva) {
        contadorIteraciones += cantidad;
    }
}

long long MedidorRecursos::getContadorIteraciones() {
    return contadorIteraciones;
}

// ============================================
// CÁLCULOS AUXILIARES
// ============================================

size_t MedidorRecursos::calcularMemoriaString(const string& str) const {
    // Tamaño del objeto string + capacidad de caracteres
    return sizeof(string) + str.capacity();
}

size_t MedidorRecursos::calcularMemoriaArreglo(size_t elementos, size_t tamanoElemento) const {
    return elementos * tamanoElemento;
}

// ============================================
// MEMORIA DE OBJETOS INDIVIDUALES
// ============================================

size_t MedidorRecursos::calcularMemoriaUsuario(Usuario* usuario) const {
    if (usuario == nullptr) return 0;

    size_t total = sizeof(Usuario);

    // Strings del usuario
    total += calcularMemoriaString(usuario->getNickname());
    total += calcularMemoriaString(usuario->getContrasena());
    total += calcularMemoriaString(usuario->getTipoMembresia());
    total += calcularMemoriaString(usuario->getCiudad());
    total += calcularMemoriaString(usuario->getPais());
    total += calcularMemoriaString(usuario->getFechaInscripcion());

    // ListaFavoritos (solo si es premium)
    if (usuario->esPremium() && usuario->getListaFavoritos() != nullptr) {
        total += calcularMemoriaListaFavoritos(usuario->getListaFavoritos());
    }

    // GestorSeguimiento (solo si es premium)
    if (usuario->esPremium() && usuario->getGestorSeguimiento() != nullptr) {
        total += calcularMemoriaGestorSeguimiento(usuario->getGestorSeguimiento());
    }

    return total;
}

size_t MedidorRecursos::calcularMemoriaCancion(Cancion* cancion) const {
    if (cancion == nullptr) return 0;

    size_t total = sizeof(Cancion);
    total += calcularMemoriaString(cancion->getNombre());
    total += calcularMemoriaString(cancion->getRutaBase());

    return total;
}

size_t MedidorRecursos::calcularMemoriaArtista(Artista* artista) const {
    if (artista == nullptr) return 0;

    size_t total = sizeof(Artista);
    total += calcularMemoriaString(artista->getNombre());
    total += calcularMemoriaString(artista->getPaisOrigen());

    return total;
}

size_t MedidorRecursos::calcularMemoriaAlbum(Album* album) const {
    if (album == nullptr) return 0;

    size_t total = sizeof(Album);
    total += calcularMemoriaString(album->getNombre());
    total += calcularMemoriaString(album->getFechaLanzamiento());
    total += calcularMemoriaString(album->getSelloDisquero());
    total += calcularMemoriaString(album->getRutaPortada());

    // Arreglo de géneros
    total += calcularMemoriaArreglo(album->getCantidadGeneros(), sizeof(string));
    string* generos = album->getGeneros();
    for (int i = 0; i < album->getCantidadGeneros(); i++) {
        total += generos[i].capacity();
    }

    return total;
}

size_t MedidorRecursos::calcularMemoriaPublicidad(Publicidad* publicidad) const {
    if (publicidad == nullptr) return 0;

    size_t total = sizeof(Publicidad);
    total += calcularMemoriaString(publicidad->getCategoria());
    total += calcularMemoriaString(publicidad->getMensaje());
    total += calcularMemoriaString(publicidad->getEmpresa());

    return total;
}

// ============================================
// MEMORIA DE GESTORES
// ============================================

size_t MedidorRecursos::calcularMemoriaGestorUsuarios(GestorUsuarios* gestor) const {
    if (gestor == nullptr) return 0;

    size_t total = sizeof(GestorUsuarios);

    // Arreglo de punteros
    total += calcularMemoriaArreglo(gestor->getCantidadUsuarios(), sizeof(Usuario*));

    // Cada usuario
    Usuario** usuarios = gestor->getUsuarios();
    for (int i = 0; i < gestor->getCantidadUsuarios(); i++) {
        total += calcularMemoriaUsuario(usuarios[i]);
    }

    return total;
}

size_t MedidorRecursos::calcularMemoriaGestorCanciones(GestorCanciones* gestor) const {
    if (gestor == nullptr) return 0;

    size_t total = sizeof(GestorCanciones);
    total += calcularMemoriaArreglo(gestor->getCantidadCanciones(), sizeof(Cancion*));

    // Cada canción (asumiendo que hay un método para obtener el arreglo)
    for (int i = 0; i < gestor->getCantidadCanciones(); i++) {
        // Aproximación: cada canción ocupa memoria similar
        total += sizeof(Cancion) + 200; // Aproximado para strings
    }

    return total;
}

size_t MedidorRecursos::calcularMemoriaGestorArtistas(GestorArtistas* gestor) const {
    if (gestor == nullptr) return 0;

    size_t total = sizeof(GestorArtistas);
    total += calcularMemoriaArreglo(gestor->getCantidadArtistas(), sizeof(Artista*));
    total += gestor->getCantidadArtistas() * (sizeof(Artista) + 150);

    return total;
}

size_t MedidorRecursos::calcularMemoriaGestorAlbumes(GestorAlbumes* gestor) const {
    if (gestor == nullptr) return 0;

    size_t total = sizeof(GestorAlbumes);
    total += calcularMemoriaArreglo(gestor->getCantidadAlbumes(), sizeof(Album*));
    total += gestor->getCantidadAlbumes() * (sizeof(Album) + 300);

    return total;
}

size_t MedidorRecursos::calcularMemoriaGestorPublicidades(GestorPublicidades* gestor) const {
    if (gestor == nullptr) return 0;

    size_t total = sizeof(GestorPublicidades);
    total += calcularMemoriaArreglo(gestor->getCantidadPublicidades(), sizeof(Publicidad*));
    total += gestor->getCantidadPublicidades() * (sizeof(Publicidad) + 250);

    return total;
}

// ============================================
// MEMORIA DE COMPONENTES AUXILIARES
// ============================================

size_t MedidorRecursos::calcularMemoriaListaFavoritos(ListaFavoritos* lista) const {
    if (lista == nullptr) return 0;

    size_t total = sizeof(ListaFavoritos);
    total += calcularMemoriaArreglo(lista->getCantidadCanciones(), sizeof(long));

    return total;
}

size_t MedidorRecursos::calcularMemoriaGestorSeguimiento(GestorSeguimiento* gestor) const {
    if (gestor == nullptr) return 0;

    size_t total = sizeof(GestorSeguimiento);
    total += calcularMemoriaArreglo(gestor->getCantidadSeguidos(), sizeof(string));
    total += gestor->getCantidadSeguidos() * 50; // Aproximado para cada nickname

    return total;
}

size_t MedidorRecursos::calcularMemoriaReproductor(Reproductor* reproductor) const {
    if (reproductor == nullptr) return 0;

    size_t total = sizeof(Reproductor);
    total += sizeof(int) * 4; // Historial (máximo 4 canciones)

    return total;
}

// ============================================
// MEMORIA TOTAL DEL SISTEMA
// ============================================

size_t MedidorRecursos::calcularMemoriaTotal(
    GestorUsuarios* gestorUsuarios,
    GestorCanciones* gestorCanciones,
    GestorArtistas* gestorArtistas,
    GestorAlbumes* gestorAlbumes,
    GestorPublicidades* gestorPublicidades,
    Reproductor* reproductor,
    Usuario* usuarioActual
    ) const {
    size_t total = 0;

    total += calcularMemoriaGestorUsuarios(gestorUsuarios);
    total += calcularMemoriaGestorCanciones(gestorCanciones);
    total += calcularMemoriaGestorArtistas(gestorArtistas);
    total += calcularMemoriaGestorAlbumes(gestorAlbumes);
    total += calcularMemoriaGestorPublicidades(gestorPublicidades);
    total += calcularMemoriaReproductor(reproductor);

    // Usuario actual (si está logueado)
    if (usuarioActual != nullptr) {
        total += sizeof(Usuario*); // El puntero en sí
    }

    return total;
}

// ============================================
// REPORTES
// ============================================

void MedidorRecursos::mostrarReporte(const string& funcionalidad, size_t memoriaTotal) const {
    cout << "\n========================================" << endl;
    cout << "    MEDICION DE RECURSOS - " << funcionalidad << endl;
    cout << "========================================" << endl;
    cout << "Iteraciones totales: " << contadorIteraciones << endl;
    cout << "Memoria consumida: " << fixed << setprecision(2)
         << (memoriaTotal / 1024.0) << " KB (" << memoriaTotal << " bytes)" << endl;
    cout << "========================================\n" << endl;
}

void MedidorRecursos::mostrarReporteCompleto(
    const string& funcionalidad,
    size_t memoriaTotal,
    size_t memoriaVariablesLocales
    ) const {
    size_t memoriaFinal = memoriaTotal + memoriaVariablesLocales;

    cout << "\n========================================" << endl;
    cout << "    MEDICION DE RECURSOS - " << funcionalidad << endl;
    cout << "========================================" << endl;
    cout << "Iteraciones totales: " << contadorIteraciones << endl;
    cout << "\nDesglose de memoria:" << endl;
    cout << "  - Estructuras del sistema: " << fixed << setprecision(2)
         << (memoriaTotal / 1024.0) << " KB" << endl;

    if (memoriaVariablesLocales > 0) {
        cout << "  - Variables locales/parametros: " << fixed << setprecision(2)
        << (memoriaVariablesLocales / 1024.0) << " KB" << endl;
    }

    cout << "\nMemoria total consumida: " << fixed << setprecision(2)
         << (memoriaFinal / 1024.0) << " KB (" << memoriaFinal << " bytes)" << endl;
    cout << "========================================\n" << endl;
}
