#include "Reproductor.h"
#include "Servicios/MedidorRecursos.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Reproductor::Reproductor(GestorCanciones* gestorCanc, GestorPublicidades* gestorPub) {
    gestorCanciones = gestorCanc;
    gestorPublicidades = gestorPub;
    historialCanciones = new int[4];
    cantidadHistorial = 0;
    modoRepetir = false;
    srand(time(0));
}

Reproductor::~Reproductor() {
    delete[] historialCanciones;
}

// ============================================
// REPRODUCCIÓN SIMPLE (SIN CONTROLES)
// ============================================

void Reproductor::reproducirCancion(Cancion* cancion, bool esCalidadAlta) {
    cout << "\n REPRODUCIENDO" << endl;
    cout << "================================" << endl;
    cout << "Cancion: " << cancion->getNombre() << endl;
    cout << "Duracion: " << cancion->formatearDuracion() << endl;
    cout << "Calidad: " << (esCalidadAlta ? "320 kbps (HD)" : "128 kbps") << endl;
    cout << "================================" << endl;
    cout << "\nArchivo de audio:" << endl;
    cout << cancion->getRutaCompleta(esCalidadAlta) << endl;
    cout << "================================\n" << endl;

    cancion->incrementarReproducciones();
}

void Reproductor::reproducirCancionConInfo(Cancion* cancion, bool esCalidadAlta, int numero, int total) {
    cout << "\n--- Cancion " << numero << " de " << total << " ---" << endl;
    reproducirCancion(cancion, esCalidadAlta);
}

// ============================================
// TEMPORIZADOR CON BARRA DE PROGRESO
// ============================================

void Reproductor::pausarConTemporizador(int segundos) {
    auto inicio = steady_clock::now();
    auto duracion = seconds(segundos);
    auto fin = inicio + duracion;

    cout << "Reproduciendo: [";
    cout.flush();

    int barraTotal = 30;
    int ultimaPosicion = 0;

    while (steady_clock::now() < fin) {
        MedidorRecursos::registrarIteracion(); // Contar cada iteración del while
        auto transcurrido = duration_cast<milliseconds>(steady_clock::now() - inicio);
        double porcentaje = static_cast<double>(transcurrido.count()) / (segundos * 1000.0);
        int posicionActual = static_cast<int>(porcentaje * barraTotal);

        for (int i = ultimaPosicion; i < posicionActual && i < barraTotal; i++) {
            MedidorRecursos::registrarIteracion(); // Contar dibujado de barra
            cout << "=";
            cout.flush();
        }

        ultimaPosicion = posicionActual;
        this_thread::sleep_for(milliseconds(100));
    }

    for (int i = ultimaPosicion; i < barraTotal; i++) {
        MedidorRecursos::registrarIteracion();
        cout << "=";
    }

    cout << "] " << endl;
}

// ============================================
// REPRODUCCIÓN ESTÁNDAR (CON PUBLICIDAD)
// ============================================

void Reproductor::reproduccionAleatoriaEstandar(int totalCanciones) {
    MedidorRecursos::iniciarMedicion();
    size_t memoriaLocales = sizeof(int) * 2; // cancionesReproducidas + totalCanciones

    cout << "\n=== REPRODUCCION ALEATORIA (ESTANDAR) ===" << endl;
    cout << "Calidad: 128 kbps | Con publicidad cada 2 canciones" << endl;
    cout << "Reproduciendo " << totalCanciones << " canciones...\n" << endl;

    int cancionesReproducidas = 0;

    for (int i = 0; i < totalCanciones; i++) {
        MedidorRecursos::registrarIteracion(); // Iteración del for
        Cancion* cancion = gestorCanciones->obtenerCancionAleatoria();

        if (cancion == nullptr) {
            cout << "[ERROR] No hay canciones disponibles." << endl;
            break;
        }

        reproducirCancionConInfo(cancion, false, i + 1, totalCanciones);
        pausarConTemporizador(3);

        cancionesReproducidas++;

        // Mostrar publicidad cada 2 canciones
        if (cancionesReproducidas % 2 == 0 && i < totalCanciones - 1) {
            MedidorRecursos::registrarIteracion(); // Verificación de publicidad
            Publicidad* anuncio = gestorPublicidades->obtenerPublicidadAleatoria();
            memoriaLocales += sizeof(Publicidad*);

            if (anuncio != nullptr) {
                anuncio->mostrar();
                this_thread::sleep_for(seconds(anuncio->getDuracion()));
            }
        }

        cout << endl;
    }

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
    cout << "Total reproducido: " << cancionesReproducidas << " canciones" << endl;

    // REPORTE FINAL (debe calcularse desde Aplicacion)
    MedidorRecursos::detenerMedicion();
}



// ============================================
// CONTROLES PREMIUM
// ============================================

void Reproductor::mostrarControlesPremium() {
    cout << "\n========================================" << endl;
    cout << "        CONTROLES DE REPRODUCCION       " << endl;
    cout << "========================================" << endl;
    cout << "[N] Siguiente cancion" << endl;
    cout << "[P] Cancion anterior (hasta 4 atras)" << endl;
    cout << "[R] Repetir cancion actual (on/off)" << endl;
    cout << "[S] Salir de la reproduccion" << endl;
    cout << "========================================" << endl;
    cout << "Comando: ";
}

bool Reproductor::procesarComandoReproduccion(char comando, int& indiceActual, int totalCanciones,
                                              bool& continuar) {
    if (isdigit(static_cast<unsigned char>(comando))) {
        cout << "\n[ERROR] No se permiten numeros. Use N, P, R o S." << endl;
        return false;
    }

    comando = toupper(static_cast<unsigned char>(comando));

    switch(comando) {
    case 'N':
        if (indiceActual < totalCanciones - 1) {
            if (!modoRepetir && cantidadHistorial < 4) {
                for (int i = cantidadHistorial; i > 0; i--) {
                    historialCanciones[i] = historialCanciones[i - 1];
                }
                historialCanciones[0] = indiceActual;
                cantidadHistorial++;
            }
            indiceActual++;
            cout << "\n Siguiente cancion...\n" << endl;
            return true;
        } else {
            cout << "\n[INFO] Ya estas en la ultima cancion." << endl;
            return false;
        }

    case 'P':
        if (cantidadHistorial > 0) {
            indiceActual = historialCanciones[0];

            for (int i = 0; i < cantidadHistorial - 1; i++) {
                historialCanciones[i] = historialCanciones[i + 1];
            }
            cantidadHistorial--;

            cout << "\n️Cancion anterior...\n" << endl;
            return true;
        } else {
            cout << "\n[INFO] No hay canciones anteriores (maximo 4 hacia atras)." << endl;
            return false;
        }
    case 'R':
        modoRepetir = !modoRepetir;
        if (modoRepetir) {
            cout << "\n Modo repetir ACTIVADO - Esta cancion se repetira indefinidamente." << endl;
        } else {
            cout << "\n Modo repetir DESACTIVADO - Reproduccion normal." << endl;
        }
        return false;

    case 'S':
        cout << "\n️ Deteniendo reproduccion..." << endl;
        continuar = false;
        return false;

    default:
        cout << "\n[ERROR] Comando invalido. Use N, P, R o S." << endl;
        return false;
    }
}

// ============================================
// REPRODUCCIÓN PREMIUM (CON CONTROLES)
// ============================================

void Reproductor::reproduccionAleatoriaPremium(int totalCanciones) {
    cout << "\n=== REPRODUCCION ALEATORIA (PREMIUM) ===" << endl;
    cout << "Calidad: 320 kbps HD | Sin publicidad " << endl;
    cout << "Controles avanzados disponibles" << endl;

    Cancion** listaCanciones = new Cancion*[totalCanciones];

    for (int i = 0; i < totalCanciones; i++) {
        listaCanciones[i] = gestorCanciones->obtenerCancionAleatoria();
        if (listaCanciones[i] == nullptr) {
            cout << "[ERROR] No hay suficientes canciones disponibles." << endl;
            delete[] listaCanciones;
            return;
        }
    }

    reproducirListaConControles(listaCanciones, totalCanciones);

    delete[] listaCanciones;

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
}

void Reproductor::reproducirListaConControles(Cancion** listaCanciones, int totalCanciones) {
    int indiceActual = 0;
    modoRepetir = false;
    bool continuar = true;
    cantidadHistorial = 0;

    cout << "\n🎵 Reproduccion iniciada con controles Premium" << endl;
    cout << "Total de canciones: " << totalCanciones << endl;

    while (continuar && indiceActual < totalCanciones) {
        cout << "\n========================================" << endl;
        cout << "Cancion " << (indiceActual + 1) << " de " << totalCanciones << endl;
        if (modoRepetir) {
            cout << " MODO REPETIR ACTIVADO" << endl;
        }
        cout << "========================================" << endl;

        reproducirCancion(listaCanciones[indiceActual], true);
        pausarConTemporizador(3);

        // Validación de comando
        bool comandoValido = false;
        bool cambiarCancion = false;

        while (!comandoValido && continuar) {
            mostrarControlesPremium();

            string entrada;
            getline(cin, entrada);

            if (entrada.length() != 1) {
                cout << "\n[ERROR] Ingrese solo UNA letra (N, P, R o S)." << endl;
                continue;
            }

            char comando = entrada[0];

            if (isdigit(static_cast<unsigned char>(comando))) {
                cout << "\n[ERROR] No se permiten numeros. Use N, P, R o S." << endl;
                continue;
            }

            comando = toupper(static_cast<unsigned char>(comando));

            if (comando != 'N' && comando != 'P' && comando != 'R' && comando != 'S') {
                cout << "\n[ERROR] Comando invalido. Use N, P, R o S." << endl;
                continue;
            }

            comandoValido = true;
            cambiarCancion = procesarComandoReproduccion(comando, indiceActual, totalCanciones, continuar);
        }

        // Lógica de avance/repetición
        if (modoRepetir && !cambiarCancion && continuar) {
            continue;
        }


    if (!continuar && indiceActual >= totalCanciones - 1) {
        cout << "\n Reproduccion finalizada." << endl;
    }
}
}
