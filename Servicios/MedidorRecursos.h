#ifndef MEDIDORRECURSOS_H
#define MEDIDORRECURSOS_H

#include <string>
#include <iostream>

using namespace std;

class MedidorRecursos {
private:
    static long long contadorIteraciones;
    static bool medicionActiva;

    // Calcular memoria de tipos básicos
    size_t calcularMemoriaString(const string& str) const;
    size_t calcularMemoriaArreglo(size_t elementos, size_t tamanoElemento) const;

public:
    MedidorRecursos();
    ~MedidorRecursos();

    // Control de medición
    static void iniciarMedicion();
    static void detenerMedicion();
    static void reiniciarContador();

    // Registro de iteraciones
    static void registrarIteracion();
    static void registrarIteraciones(int cantidad);
    static long long getContadorIteraciones();

    // Cálculo de memoria por estructura
    size_t calcularMemoriaUsuario(class Usuario* usuario) const;
    size_t calcularMemoriaCancion(class Cancion* cancion) const;
    size_t calcularMemoriaArtista(class Artista* artista) const;
    size_t calcularMemoriaAlbum(class Album* album) const;
    size_t calcularMemoriaPublicidad(class Publicidad* publicidad) const;

    size_t calcularMemoriaGestorUsuarios(class GestorUsuarios* gestor) const;
    size_t calcularMemoriaGestorCanciones(class GestorCanciones* gestor) const;
    size_t calcularMemoriaGestorArtistas(class GestorArtistas* gestor) const;
    size_t calcularMemoriaGestorAlbumes(class GestorAlbumes* gestor) const;
    size_t calcularMemoriaGestorPublicidades(class GestorPublicidades* gestor) const;

    size_t calcularMemoriaListaFavoritos(class ListaFavoritos* lista) const;
    size_t calcularMemoriaGestorSeguimiento(class GestorSeguimiento* gestor) const;
    size_t calcularMemoriaReproductor(class Reproductor* reproductor) const;

    // Calcular memoria total del sistema
    size_t calcularMemoriaTotal(
        class GestorUsuarios* gestorUsuarios,
        class GestorCanciones* gestorCanciones,
        class GestorArtistas* gestorArtistas,
        class GestorAlbumes* gestorAlbumes,
        class GestorPublicidades* gestorPublicidades,
        class Reproductor* reproductor,
        class Usuario* usuarioActual
        ) const;

    // Mostrar reporte
    void mostrarReporte(const string& funcionalidad, size_t memoriaTotal) const;
    void mostrarReporteCompleto(
        const string& funcionalidad,
        size_t memoriaTotal,
        size_t memoriaVariablesLocales = 0
        ) const;
};

#endif
