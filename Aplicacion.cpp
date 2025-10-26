#include "Aplicacion.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

Aplicacion::Aplicacion() {
    gestorUsuarios = new GestorUsuarios();
    gestorCanciones = new GestorCanciones();
    gestorPublicidades = new GestorPublicidades();
    gestorArtistas = new GestorArtistas();
    gestorAlbumes = new GestorAlbumes();
    usuarioActual = nullptr;
    cargarDatos();
}

Aplicacion::~Aplicacion() {
    delete gestorUsuarios;
    delete gestorCanciones;
    delete gestorArtistas;
    delete gestorAlbumes;
}

void Aplicacion::ejecutar() {
    int opcion;

    do {
        mostrarMenuPrincipal();
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();                       // Limpiar el '\n' restante

        switch(opcion) {
        case 1:
            login();
            break;
        case 2:
            registrarUsuario();
            break;
        case 3:
            gestorUsuarios->mostrarTodos();
            cout << "\nPresione Enter...";
            cin.get();
            break;
        case 0:
            salir();
            break;
        default:
            cout << "\nOpcion invalida\n";
            cout << "Presione Enter...";
            cin.get();
        }

    } while(opcion != 0);
}

void Aplicacion::cargarDatos() {
    cout << "\n[SISTEMA] Cargando datos...\n" << endl;
    gestorUsuarios->cargarDesdeArchivo("data/usuarios.txt");
    gestorCanciones->cargarDesdeArchivo("data/canciones.txt");
    gestorArtistas->cargarDesdeArchivo("data/artistas.txt");
    gestorAlbumes->cargarDesdeArchivo("data/albunes.txt");
    gestorPublicidades->cargarDesdeArchivo("data/publicidad.txt");
    cout << endl;
}

void Aplicacion::mostrarMenuPrincipal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << "\n========================================" << endl;
    cout << "          U d e A T u n e s             " << endl;
    cout << "    Sistema de Streaming Musical       " << endl;
    cout << "========================================" << endl;
    cout << "\n    Vive la musica con nosotros\n" << endl;
    cout << "========================================" << endl;
    cout << "\n1. Iniciar Sesion" << endl;
    cout << "2. Registrarse" << endl;
    cout << "3. Ver usuarios registrados" << endl;
    cout << "0. Salir" << endl;
    cout << "========================================" << endl;
}

void Aplicacion::mostrarMenuUsuarioEstandar() {
    int opcion;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "\n========================================" << endl;
        cout << "          U d e A T u n e s             " << endl;
        cout << "        USUARIO ESTANDAR (GRATIS)       " << endl;
        cout << "========================================" << endl;
        cout << "\nBienvenido: " << usuarioActual->getNickname() << endl;
        cout << "Ciudad: " << usuarioActual->getCiudad() << ", " << usuarioActual->getPais() << endl;
        cout << "Calidad de audio: 128 kbps" << endl;
        cout << "========================================" << endl;

        cout << "\n--- REPRODUCCION ---" << endl;
        cout << "1. Reproduccion aleatoria" << endl;
        cout << "   (Con publicidad cada 2 canciones)" << endl;

        cout << "\n--- BUSQUEDA ---" << endl;
        cout << "2. Buscar cancion por ID" << endl;
        cout << "3. Ver todos los artistas" << endl;
        cout << "4. Ver todos los albumes" << endl;
        cout << "5. Ver todas las canciones" << endl;

        cout << "\n--- MI CUENTA ---" << endl;
        cout << "6. Ver mi informacion" << endl;
        cout << "7. Hazte Premium! ($19,900/mes)" << endl;

        cout << "\n8. Cerrar sesion" << endl;
        cout << "0. Salir de la aplicacion" << endl;
        cout << "========================================" << endl;

        cout << "\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
        case 1:
            cout << "\n[INFO] Reproduccion aleatoria..." << endl;
            reproduccionAleatoriaEstandar();
            cout << "Presione Enter...";
            cin.get();
            break;
        case 2:
        {
            string idInput;
            cout << "\n=== BUSCAR CANCION POR ID ===" << endl;
            cout << "Ingrese el ID de la cancion: ";
            getline(cin, idInput);

            long idCancion;
            try {
                idCancion = stol(idInput);
            } catch (...) {
                cout << "\n[ERROR] ID invalido. Debe ser un numero." << endl;
                cout << "Presione Enter...";
                cin.get();
                break;
            }

            Cancion* cancion = gestorCanciones->buscarPorId(idCancion);

            if (cancion != nullptr) {
                cout << "\n=== CANCION ENCONTRADA ===" << endl;
                cancion->mostrarInfo();

                cout << "\n¿Que desea hacer?" << endl;
                cout << "1. Reproducir" << endl;
                cout << "0. Volver al menu" << endl;
                cout << "Opcion: ";

                int subOpcion;
                cin >> subOpcion;
                cin.ignore();

                if (subOpcion == 1) {
                    reproducirCancion(cancion, true);
                }
             else {
                cout << "\n[ERROR] No se encontro ninguna cancion con ese ID." << endl;
            }
        }
            cout << "\nPresione Enter...";
            cin.get();
        }
        case 3:
            cout << "\n=== LISTA DE ARTISTAS ===" << endl;
            cout << "Total de artistas: " << gestorArtistas->getCantidadArtistas() << endl;
            cout << "========================================" << endl;
            gestorArtistas->mostrarOrdenadoPorTendencia();
            cout << "\nPresione Enter...";
            cin.get();
            break;
        case 4:
            cout << "\n=== LISTA DE ALBUMES ===" << endl;
            cout << "Total de albumes: " << gestorAlbumes->getCantidadAlbumes() << endl;
            cout << "========================================" << endl;
            gestorAlbumes->mostrarTodos();
            cout << "\nPresione Enter...";
            cin.get();
            break;
        case 5:
            cout << "\n=== TODAS LAS CANCIONES ===" << endl;
            cout << "Total de canciones: " << gestorCanciones->getCantidadCanciones() << endl;
            cout << "========================================" << endl;
            gestorCanciones->mostrarTodas();
            cout << "\nPresione Enter...";
            cin.get();
            break;
        case 6:
            usuarioActual->mostrarInfo();
            cout << "Presione Enter...";
            cin.get();
            break;
        case 7:
            cout << "\n========================================" << endl;
            cout << "        ¡HAZTE PREMIUM HOY!             " << endl;
            cout << "========================================" << endl;
            cout << "\nBeneficios Premium:" << endl;
            cout << "Sin anuncios publicitarios" << endl;
            cout << "Calidad de audio HD (320 kbps)" << endl;
            cout << "Lista de favoritos (hasta 10,000 canciones)" << endl;
            cout << "Seguir listas de otros usuarios premium" << endl;
            cout << "Controles avanzados de reproduccion" << endl;
            cout << "\nPrecio: $19,900 COP/mes" << endl;
            cout << "¿Deseas subscribirte?"<< endl;
            cout << "\n 1. Si.\n 2. No."<< endl;
            cin >> preguntaMembresia;
            if (preguntaMembresia == "1"){
                usuarioActual->setTipoMembresia("premium" );
                cout << usuarioActual->getTipoMembresia()<<endl;
                gestorUsuarios->guardarEnArchivo("data/usuarios.txt");
                cout << "Disfrute de su Membresia, el cobro sera automatico a su tarjeta de credito"<< endl;
                cout << "Cierre sesión para actualizar membresia" << endl;
                cin.get();
            }

            cout << "Presione Enter...";
            cin.get();
            break;
        case 8:
            cerrarSesion();
            return;
        case 0:
            salir();
            exit(0);
            break;
        default:
            cout << "\n[ERROR] Opcion invalida." << endl;
            cout << "Presione Enter...";
            cin.get();
        }

    } while(opcion != 8 && opcion != 0);
}

void Aplicacion::mostrarMenuUsuarioPremium() {
    int opcion;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "\n========================================" << endl;
        cout << "          U d e A T u n e s             " << endl;
        cout << "           USUARIO PREMIUM          " << endl;
        cout << "========================================" << endl;
        cout << "\nBienvenido: " << usuarioActual->getNickname() << endl;
        cout << "Ciudad: " << usuarioActual->getCiudad() << ", " << usuarioActual->getPais() << endl;
        cout << "Calidad de audio: 320 kbps (HD)" << endl;
        cout << "========================================" << endl;

        cout << "\n--- REPRODUCCION ---" << endl;
        cout << "1. Reproduccion aleatoria" << endl;
        cout << "   (Sin anuncios, controles avanzados)" << endl;

        cout << "\n--- MIS FAVORITOS ---" << endl;
        cout << "2. Ver mi lista de favoritos" << endl;
        cout << "3. Agregar cancion a favoritos" << endl;
        cout << "4. Eliminar cancion de favoritos" << endl;
        cout << "5. Seguir lista de otro usuario" << endl;
        cout << "6. Reproducir mis favoritos" << endl;

        cout << "\n--- BUSQUEDA ---" << endl;
        cout << "7. Buscar cancion por ID" << endl;
        cout << "8. Ver todos los artistas" << endl;
        cout << "9. Ver todos los albumes" << endl;
        cout << "10. Ver todas las canciones" << endl;

        cout << "\n--- MI CUENTA ---" << endl;
        cout << "11. Ver mi informacion" << endl;

        cout << "\n12. Cerrar sesion" << endl;
        cout << "0. Salir de la aplicacion" << endl;
        cout << "========================================" << endl;

        cout << "\nOpcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
        case 1:
            cout <<"Reproduccion Aleatoria..."<<endl;
            reproduccionAleatoriaPremium();

            break;

        case 2:
            cout << "TUS FAVORITOS"<<endl;
            verMisFavoritos();

            break;

        case 3:
            cout << "AGREGAR CANCION A FAVORITOS"<<endl;
            agregarAFavoritos();

            break;

        case 4:
            cout<<"ELIMINAR CANCION DE FAVORITOS"<<endl;
            eliminarDeFavoritos();

            break;

        case 5:
            cout<<"SEGUIR A OTRO USUARIO"<<endl;
            seguirUsuario();

            break;

        case 6:
            cout<<"REPRODUCIR MIS FAVORITOS"<<endl;
            reproducirMisFavoritos();

            break;

        case 7:
        {
            string idInput;
            cout << "\n=== BUSCAR CANCION POR ID ===" << endl;
            cout << "Ingrese el ID de la cancion: ";
            getline(cin, idInput);

            long idCancion;
            try {
                idCancion = stol(idInput);
            } catch (...) {
                cout << "\n[ERROR] ID invalido. Debe ser un numero." << endl;
                cout << "Presione Enter...";
                cin.get();
                break;
            }

            Cancion* cancion = gestorCanciones->buscarPorId(idCancion);

            if (cancion != nullptr) {
                cout << "\n=== CANCION ENCONTRADA ===" << endl;
                cancion->mostrarInfo();

                cout << "\n¿Que desea hacer?" << endl;
                cout << "1. Reproducir" << endl;
                cout << "2. Agregar a favoritos" << endl;
                cout << "0. Volver al menu" << endl;
                cout << "Opcion: ";

                int subOpcion;
                cin >> subOpcion;
                cin.ignore();

                if (subOpcion == 1) {
                    reproducirCancion(cancion, true);
                } else if (subOpcion == 2) {
                    if (usuarioActual->getListaFavoritos()->agregarCancion(idCancion)) {
                        string rutaFavoritos = "data/favoritos_" + usuarioActual->getNickname() + ".txt";
                        usuarioActual->getListaFavoritos()->guardarEnArchivo(rutaFavoritos);
                        cout << "\n[EXITO] Cancion agregada a favoritos!" << endl;
                    } else {
                        cout << "\n[ERROR] La cancion ya esta en favoritos." << endl;
                    }
                }
            } else {
                cout << "\n[ERROR] No se encontro ninguna cancion con ese ID." << endl;
            }

            cout << "\nPresione Enter...";
            cin.get();
        }
        break;

        case 8:
            cout << "\n=== LISTA DE ARTISTAS ===" << endl;
            cout << "Total de artistas: " << gestorArtistas->getCantidadArtistas() << endl;
            cout << "========================================" << endl;
            gestorArtistas->mostrarOrdenadoPorTendencia();
            cout << "\nPresione Enter...";
            cin.get();
            break;

        case 9:
            cout << "\n=== LISTA DE ALBUMES ===" << endl;
            cout << "Total de albumes: " << gestorAlbumes->getCantidadAlbumes() << endl;
            cout << "========================================" << endl;
            gestorAlbumes->mostrarTodos();
            cout << "\nPresione Enter...";
            cin.get();
            break;

        case 10:
            cout << "\n=== TODAS LAS CANCIONES ===" << endl;
            cout << "Total de canciones: " << gestorCanciones->getCantidadCanciones() << endl;
            cout << "========================================" << endl;
            gestorCanciones->mostrarTodas();
            cout << "\nPresione Enter...";
            cin.get();
            break;

        case 11:
            usuarioActual->mostrarInfo();
            cout << "Presione Enter...";
            cin.get();
            break;

        case 12:
            cerrarSesion();
            return;
        case 0:
            salir();
            exit(0);
            break;
        default:
            cout << "\n[ERROR] Opcion invalida." << endl;
            cout << "Presione Enter...";
            cin.get();
        }

    } while(opcion != 12 && opcion != 0);
}

void Aplicacion::login() {
    string nickname, contrasena;

    cout << "\n=== INICIAR SESION ===" << endl;
    cout << "Nickname: ";
    getline(cin, nickname);
    cout << "Contrasena: ";
    getline(cin, contrasena);

    Usuario* usuario = gestorUsuarios->buscarUsuario(nickname);

    if (usuario != nullptr) {
        if (usuario->validarContrasena(contrasena)) {
            usuarioActual = usuario;

            // CARGAR FAVORITOS Y SEGUIDOS (solo para premium)
            if (usuarioActual->esPremium()) {
                string rutaFavoritos = "data/favoritos_" + nickname + ".txt";
                string rutaSeguidos = "data/seguidos_" + nickname + ".txt";

                usuarioActual->getListaFavoritos()->cargarDesdeArchivo(rutaFavoritos);
                usuarioActual->getGestorSeguimiento()->cargarDesdeArchivo(rutaSeguidos);
            }
            cout << "\nLogin exitoso!" << endl;
            cout << "Redirigiendo..." << endl;

// Pequeña pausa
#ifdef _WIN32
            system("timeout /t 1 >nul");
#else
            system("sleep 1");
#endif

            // Redirigir según tipo de usuario
            if (usuarioActual->esPremium()) {
                mostrarMenuUsuarioPremium();
            } else {
                mostrarMenuUsuarioEstandar();
            }
        } else {
            cout << "\n[ERROR] Contrasena incorrecta." << endl;
            cout << "Presione Enter...";
            cin.get();
        }
    } else {
        cout << "\n[ERROR] Usuario no encontrado." << endl;
        cout << "Presione Enter...";
        cin.get();
    }
}

void Aplicacion::registrarUsuario() {
    string nickname, contrasena, ciudad, pais;
    int tipoMembresia;

    cout << "\n=== REGISTRO DE NUEVO USUARIO ===" << endl;

    cout << "Ingrese nickname: ";
    getline(cin, nickname);

    if (gestorUsuarios->existeUsuario(nickname)) {
        cout << "\n[ERROR] El nickname ya existe. Intente con otro." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    if (nickname.empty()) {
        cout << "\n[ERROR] El nickname no puede estar vacio." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "Ingrese contrasena: ";
    getline(cin, contrasena);

    if (contrasena.empty()) {
        cout << "\n[ERROR] La contrasena no puede estar vacia." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "\nTipo de membresia:" << endl;
    cout << "1. Estandar (Gratis - 128 kbps con publicidad)" << endl;
    cout << "2. Premium ($19,900/mes - 320 kbps sin publicidad)" << endl;
    cout << "Opcion: ";
    cin >> tipoMembresia;
    cin.ignore();

    string tipo = (tipoMembresia == 2) ? "premium" : "estandar";

    cout << "Ingrese ciudad: ";
    getline(cin, ciudad);

    cout << "Ingrese pais: ";
    getline(cin, pais);

    string fechaActual = obtenerFechaActual();

    Usuario* nuevoUsuario = new Usuario(nickname, contrasena, tipo, ciudad, pais, fechaActual);
    gestorUsuarios->agregarUsuario(nuevoUsuario);

    if (gestorUsuarios->guardarEnArchivo("data/usuarios.txt")) {
        cout << "\n¡Usuario registrado exitosamente!" << endl;
        cout << "\nDatos del usuario:" << endl;
        nuevoUsuario->mostrarInfo();
    } else {
        cout << "\n[ERROR] No se pudo guardar el usuario." << endl;
    }

    cout << "Presione Enter...";
    cin.get();
}

void Aplicacion::cerrarSesion() {
    cout << "\n[SISTEMA] Cerrando sesion..." << endl;
    cout << "Hasta pronto, " << usuarioActual->getNickname() << "!" << endl;
    usuarioActual = nullptr;

#ifdef _WIN32
    system("timeout /t 1 >nul");
#else
    system("sleep 1");
#endif
}

string Aplicacion::obtenerFechaActual() {
    time_t ahora = time(0);
    tm* tiempoLocal = localtime(&ahora);

    stringstream ss;
    ss << (tiempoLocal->tm_year + 1900) << "-"
       << setfill('0') << setw(2) << (tiempoLocal->tm_mon + 1) << "-"
       << setfill('0') << setw(2) << tiempoLocal->tm_mday;

    return ss.str();
}

void Aplicacion::salir() {
    cout << "\n[SISTEMA] Guardando datos..." << endl;
    gestorUsuarios->guardarEnArchivo("data/usuarios.txt");
    cout << "¡Gracias por usar UdeATunes!" << endl;
    cout << "Vive la musica con nosotros.\n" << endl;
}

void Aplicacion::reproducirCancion(Cancion* cancion, bool esCalidadAlta) {
    cout << "\n REPRODUCIENDO " << endl;
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

void Aplicacion::reproduccionAleatoriaEstandar() {
    cout << "\n=== REPRODUCCION ALEATORIA (ESTANDAR) ===" << endl;
    cout << "Calidad: 128 kbps | Con publicidad cada 2 canciones" << endl;
    cout << "Reproduciendo 10 canciones...\n" << endl;

    int cancionesReproducidas = 0;
    int totalCanciones = 10;

    for (int i = 0; i < totalCanciones; i++) {
        Cancion* cancion = gestorCanciones->obtenerCancionAleatoria();

        if (cancion == nullptr) {
            cout << "[ERROR] No hay canciones disponibles." << endl;
            break;
        }

        cout << "\n--- Cancion " << (i + 1) << " de " << totalCanciones << " ---" << endl;
        reproducirCancion(cancion, false); // Calidad estándar
        // Usar temporizador con chrono (3 segundos)
        pausarConTemporizador(3);


        cancionesReproducidas++;

        // Mostrar publicidad cada 2 canciones
        if (cancionesReproducidas % 2 == 0 && i < totalCanciones - 1) {
            Publicidad* anuncio = gestorPublicidades->obtenerPublicidadAleatoria();

            if (anuncio != nullptr) {
                anuncio->mostrar();

                // Pausar según duración del anuncio
                this_thread::sleep_for(seconds(anuncio->getDuracion()));
            }
        }


        cout << endl;
    }

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
    cout << "Total reproducido: " << cancionesReproducidas << " canciones" << endl;
    cout << "\nPresione Enter...";
    cin.get();
}

// METODOS PREMIUM:
void Aplicacion::reproduccionAleatoriaPremium() {
    cout << "\n=== REPRODUCCION ALEATORIA (PREMIUM) ===" << endl;
    cout << " Calidad: 320 kbps HD | Sin publicidad " << endl;
    cout << " Controles avanzados disponibles" << endl;

    int totalCanciones = 5;
    Cancion** listaCanciones = new Cancion*[totalCanciones];

    // Obtener canciones aleatorias
    for (int i = 0; i < totalCanciones; i++) {
        listaCanciones[i] = gestorCanciones->obtenerCancionAleatoria();
        if (listaCanciones[i] == nullptr) {
            cout << "[ERROR] No hay suficientes canciones disponibles." << endl;
            delete[] listaCanciones;
            cout << "\nPresione Enter...";
            cin.get();
            return;
        }
    }

    // Reproducir con controles premium
    reproducirConControlesPremium(listaCanciones, totalCanciones);

    delete[] listaCanciones;

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
    cout << "\nPresione Enter...";
    cin.get();
}

void Aplicacion::agregarAFavoritos() {
    string idInput;

    cout << "\n=== AGREGAR CANCION A FAVORITOS ===" << endl;
    cout << "Ingrese el ID de la cancion: ";
    getline(cin, idInput);

    long idCancion;
    try {
        idCancion = stol(idInput);
    } catch (...) {
        cout << "\n[ERROR] ID invalido. Debe ser un numero." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    Cancion* cancion = gestorCanciones->buscarPorId(idCancion);

    if (cancion == nullptr) {
        cout << "\n[ERROR] No se encontro ninguna cancion con el ID: " << idCancion << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "\n=== CANCION ENCONTRADA ===" << endl;
    cout << "ID Cancion: " << cancion->getIdCancion() << endl;
    cout << "Nombre: " << cancion->getNombre() << endl;
    cout << "Duracion: " << cancion->formatearDuracion() << endl;
    cout << "Reproducciones: " << cancion->getReproducciones() << endl;
    cout << "========================================" << endl;

    cout << "\n¿Que desea hacer?" << endl;
    cout << "1. Agregar a favoritos" << endl;
    cout << "2. Reproducir esta cancion" << endl;
    cout << "0. Cancelar" << endl;
    cout << "Opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore();

    switch(opcion) {
    case 1:
        if (usuarioActual->getListaFavoritos()->agregarCancion(idCancion)) {
            string rutaFavoritos = "data/favoritos_" + usuarioActual->getNickname() + ".txt";

            if (usuarioActual->getListaFavoritos()->guardarEnArchivo(rutaFavoritos)) {
                cout << "\n[EXITO] ¡Cancion agregada a favoritos!" << endl;
                cout << "Total: " << usuarioActual->getListaFavoritos()->getCantidadCanciones()
                     << " / 10,000" << endl;
            } else {
                cout << "\n[ERROR] No se pudo guardar en el archivo." << endl;
            }
        } else {
            cout << "\n[ERROR] La cancion ya esta en favoritos o alcanzaste el limite (10,000)." << endl;
        }
        break;

    case 2:
        reproducirCancion(cancion, true);
        break;

    case 0:
        cout << "\nOperacion cancelada." << endl;
        break;

    default:
        cout << "\n[ERROR] Opcion invalida." << endl;
    }

    cout << "\nPresione Enter...";
    cin.get();
}

void Aplicacion::verMisFavoritos() {
    cout << "\n=== MI LISTA DE FAVORITOS ===" << endl;

    ListaFavoritos* favoritos = usuarioActual->getListaFavoritos();

    if (favoritos->getCantidadCanciones() == 0) {
        cout << "No tienes canciones en favoritos aun." << endl;
    } else {
        cout << "Total: " << favoritos->getCantidadCanciones() << " / 10,000\n" << endl;

        long* ids = favoritos->getIdsCanciones();
        int cantidad = favoritos->getCantidadCanciones();

        for (int i = 0; i < cantidad; i++) {
            Cancion* cancion = gestorCanciones->buscarPorId(ids[i]);

            if (cancion != nullptr) {
                cout << "----------------------------------------" << endl;
                cout << "[" << (i + 1) << "] ";
                cancion->mostrarInfo();
            }
        }
        cout << "----------------------------------------" << endl;
    }

    cout << "\nPresione Enter...";
    cin.get();
}
void Aplicacion::eliminarDeFavoritos() {
    string idInput;

    cout << "\n=== ELIMINAR CANCION DE FAVORITOS ===" << endl;

    ListaFavoritos* favoritos = usuarioActual->getListaFavoritos();

    if (favoritos->getCantidadCanciones() == 0) {
        cout << "No tienes canciones en favoritos." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "Tus canciones favoritas:\n" << endl;
    long* ids = favoritos->getIdsCanciones();
    int cantidad = favoritos->getCantidadCanciones();

    for (int i = 0; i < cantidad; i++) {
        Cancion* c = gestorCanciones->buscarPorId(ids[i]);
        if (c != nullptr) {
            cout << "[" << (i + 1) << "] ID: " << ids[i]
                 << " - " << c->getNombre() << endl;
        }
    }

    cout << "\nIngrese el ID de la cancion a eliminar: ";
    getline(cin, idInput);

    long idCancion;
    try {
        idCancion = stol(idInput);
    } catch (...) {
        cout << "\n[ERROR] ID invalido." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    if (favoritos->eliminarCancion(idCancion)) {
        string rutaFavoritos = "data/favoritos_" + usuarioActual->getNickname() + ".txt";
        favoritos->guardarEnArchivo(rutaFavoritos);
        cout << "\n[EXITO] Cancion eliminada de favoritos." << endl;
    } else {
        cout << "\n[ERROR] No se encontro esa cancion en tus favoritos." << endl;
    }

    cout << "Presione Enter...";
    cin.get();
}

void Aplicacion::seguirUsuario() {
    string nicknameASeguir;

    cout << "\n=== SEGUIR LISTA DE OTRO USUARIO ===" << endl;
    cout << "Ingrese el nickname del usuario: ";
    getline(cin, nicknameASeguir);

    if (nicknameASeguir == usuarioActual->getNickname()) {
        cout << "\n[ERROR] No puedes seguirte a ti mismo." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    Usuario* usuarioSeguir = gestorUsuarios->buscarUsuario(nicknameASeguir);

    if (usuarioSeguir == nullptr) {
        cout << "\n[ERROR] El usuario no existe." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    if (!usuarioSeguir->esPremium()) {
        cout << "\n[ERROR] Solo puedes seguir usuarios Premium." << endl;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    GestorSeguimiento* gestor = usuarioActual->getGestorSeguimiento();

    if (gestor->seguirUsuario(nicknameASeguir)) {
        string rutaSeguidos = "data/seguidos_" + usuarioActual->getNickname() + ".txt";
        gestor->guardarEnArchivo(rutaSeguidos);
        cout << "\n[EXITO] Ahora sigues a " << nicknameASeguir << endl;
    } else {
        cout << "\n[ERROR] Ya sigues a este usuario." << endl;
    }

    cout << "Presione Enter...";
    cin.get();
}

void Aplicacion::reproducirMisFavoritos() {
    cout << "\n=== REPRODUCIR FAVORITOS ===" << endl;

    // Crear arreglo dinámico para todas las canciones
    int capacidadTotal = 10000;
    Cancion** todasCanciones = new Cancion*[capacidadTotal];
    int totalCanciones = 0;

    // Mis favoritos
    long* misFavoritos = usuarioActual->getListaFavoritos()->getIdsCanciones();
    int cantMisFavoritos = usuarioActual->getListaFavoritos()->getCantidadCanciones();

    for (int i = 0; i < cantMisFavoritos; i++) {
        Cancion* c = gestorCanciones->buscarPorId(misFavoritos[i]);
        if (c != nullptr && totalCanciones < capacidadTotal) {
            todasCanciones[totalCanciones++] = c;
        }
    }

    // Favoritos de usuarios seguidos
    string* seguidos = usuarioActual->getGestorSeguimiento()->getUsuariosSeguidos();
    int cantSeguidos = usuarioActual->getGestorSeguimiento()->getCantidadSeguidos();

    for (int i = 0; i < cantSeguidos; i++) {
        Usuario* usuarioSeguido = gestorUsuarios->buscarUsuario(seguidos[i]);
        if (usuarioSeguido != nullptr && usuarioSeguido->esPremium()) {
            long* favoritosSeguido = usuarioSeguido->getListaFavoritos()->getIdsCanciones();
            int cantFavoritosSeguido = usuarioSeguido->getListaFavoritos()->getCantidadCanciones();

            for (int j = 0; j < cantFavoritosSeguido; j++) {
                Cancion* c = gestorCanciones->buscarPorId(favoritosSeguido[j]);
                if (c != nullptr && totalCanciones < capacidadTotal) {
                    todasCanciones[totalCanciones++] = c;
                }
            }
        }
    }

    if (totalCanciones == 0) {
        cout << "No hay canciones para reproducir." << endl;
        delete[] todasCanciones;
        cout << "Presione Enter...";
        cin.get();
        return;
    }

    cout << "Total de canciones: " << totalCanciones << endl;
    cout << "\nModo de reproduccion:" << endl;
    cout << "1. Orden original" << endl;
    cout << "2. Aleatorio" << endl;
    cout << "Opcion: ";

    int modo;
    cin >> modo;
    cin.ignore();

    // Mezclar si es aleatorio (Fisher-Yates)
    if (modo == 2) {
        srand(time(0));
        for (int i = totalCanciones - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Cancion* temp = todasCanciones[i];
            todasCanciones[i] = todasCanciones[j];
            todasCanciones[j] = temp;
        }
        cout << "\n Reproduccion aleatoria\n" << endl;
    } else {
        cout << "\n Reproduccion en orden\n" << endl;
    }

    // Reproducir con controles premium
    reproducirConControlesPremium(todasCanciones, totalCanciones);

    delete[] todasCanciones;

    cout << "\n=== REPRODUCCION FINALIZADA ===" << endl;
    cout << "Presione Enter...";
    cin.get();
}

void Aplicacion::pausarConTemporizador(int segundos) {
    auto inicio = steady_clock::now();
    auto duracion = seconds(segundos);
    auto fin = inicio + duracion;

    cout << "Reproduciendo: [";

    int barraTotal = 30;  // 30 caracteres de barra
    int ultimaPosicion = 0;

    while (steady_clock::now() < fin) {
        auto transcurrido = duration_cast<milliseconds>(steady_clock::now() - inicio);
        double porcentaje = static_cast<double>(transcurrido.count()) / (segundos * 1000.0);
        int posicionActual = static_cast<int>(porcentaje * barraTotal);

        // Dibujar barra de progreso
        for (int i = ultimaPosicion; i < posicionActual && i < barraTotal; i++) {
            cout << "=";

        }

        ultimaPosicion = posicionActual;

        // Pequeña pausa
        this_thread::sleep_for(milliseconds(100));
    }

    // Completar la barra
    for (int i = ultimaPosicion; i < barraTotal; i++) {
        cout << "=";
    }

    cout << "] " << endl;
}

void Aplicacion::mostrarControlesPremium() {
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

bool Aplicacion::procesarComandoReproduccion(char comando, int& indiceActual, int totalCanciones,
                                             bool& modoRepetir, bool& continuar, int* historial,
                                             int& cantidadHistorial) {
    switch(comando) {
    case 'N':
    case 'n':
        // Siguiente canción
        if (indiceActual < totalCanciones - 1) {
            // Guardar en historial (solo si no está en modo repetir)
            if (!modoRepetir && cantidadHistorial < 4) {
                // Desplazar historial hacia la derecha
                for (int i = cantidadHistorial; i > 0; i--) {
                    historial[i] = historial[i - 1];
                }
                historial[0] = indiceActual;
                cantidadHistorial++;
            }

            indiceActual++;
            cout << "\n Siguiente cancion...\n" << endl;
            return true;  // Continuar con nueva canción
        } else {
            cout << "\n[INFO] Ya estas en la ultima cancion." << endl;
            return false;  // Seguir reproduciendo la actual
        }

    case 'P':
    case 'p':
        // Canción anterior
        if (cantidadHistorial > 0) {
            indiceActual = historial[0];

            // Eliminar del historial
            for (int i = 0; i < cantidadHistorial - 1; i++) {
                historial[i] = historial[i + 1];
            }
            cantidadHistorial--;

            cout << "\n Cancion anterior...\n" << endl;
            return true;  // Continuar con canción anterior
        } else {
            cout << "\n[INFO] No hay canciones anteriores (maximo 4 hacia atras)." << endl;
            return false;
        }

    case 'R':
    case 'r':
        // Modo repetir
        modoRepetir = !modoRepetir;
        if (modoRepetir) {
            cout << "\n Modo repetir ACTIVADO - Esta cancion se repetira indefinidamente." << endl;
        } else {
            cout << "\n Modo repetir DESACTIVADO - Reproduccion normal." << endl;
        }
        return false;  // Seguir con la canción actual

    case 'S':
    case 's':
        // Salir
        cout << "\n️ Deteniendo reproduccion..." << endl;
        continuar = false;
        return false;

    default:
        cout << "\n[ERROR] Comando invalido. Use N, P, R o S." << endl;
        return false;
    }
}

void Aplicacion::reproducirConControlesPremium(Cancion** listaCanciones, int totalCanciones) {
    int indiceActual = 0;
    bool modoRepetir = false;
    bool continuar = true;

    // Historial de canciones (máximo 4)
    int* historial = new int[4];
    int cantidadHistorial = 0;

    cout << "\n Reproduccion iniciada con controles Premium" << endl;
    cout << "Total de canciones: " << totalCanciones << endl;

    while (continuar && indiceActual < totalCanciones) {
        // Mostrar información de la canción actual
        cout << "\n========================================" << endl;
        cout << "Cancion " << (indiceActual + 1) << " de " << totalCanciones << endl;
        if (modoRepetir) {
            cout << " MODO REPETIR ACTIVADO" << endl;
        }
        cout << "========================================" << endl;

        reproducirCancion(listaCanciones[indiceActual], true);

        // Simular reproducción con temporizador
        auto inicio = steady_clock::now();
        auto duracion = seconds(3);
        auto fin = inicio + duracion;

        bool comandoIngresado = false;
        bool cambiarCancion = false;

        cout << "\nReproduciendo";
        cout.flush();

        // Reproducción con posibilidad de interrupción
        while (steady_clock::now() < fin && continuar) {
            // Calcular progreso
            auto transcurrido = duration_cast<milliseconds>(steady_clock::now() - inicio);
            double porcentaje = static_cast<double>(transcurrido.count()) / 3000.0;

            // Mostrar puntos de progreso
            if (porcentaje >= 0.33 && porcentaje < 0.34 && !comandoIngresado) {
                cout << ".";
                cout.flush();
            } else if (porcentaje >= 0.66 && porcentaje < 0.67 && !comandoIngresado) {
                cout << ".";
                cout.flush();
            }

            // Pequeña pausa
            this_thread::sleep_for(milliseconds(100));
        }

        if (!comandoIngresado) {
            cout << ". " << endl;
        }

        // Si está en modo repetir, repetir automáticamente
        if (modoRepetir) {
            cout << "\n Repitiendo cancion..." << endl;
            mostrarControlesPremium();

            char comando;
            cin >> comando;
            cin.ignore();

            cambiarCancion = procesarComandoReproduccion(comando, indiceActual, totalCanciones,
                                                         modoRepetir, continuar, historial,
                                                         cantidadHistorial);

            if (!cambiarCancion && continuar && !modoRepetir) {
                // Si desactivó repetir, avanzar a siguiente
                if (indiceActual < totalCanciones - 1) {
                    if (cantidadHistorial < 4) {
                        for (int i = cantidadHistorial; i > 0; i--) {
                            historial[i] = historial[i - 1];
                        }
                        historial[0] = indiceActual;
                        cantidadHistorial++;
                    }
                    indiceActual++;
                } else {
                    continuar = false;
                }
            }
        } else {
            // Modo normal: mostrar controles después de cada canción
            mostrarControlesPremium();

            char comando;
            cin >> comando;
            cin.ignore();

            cambiarCancion = procesarComandoReproduccion(comando, indiceActual, totalCanciones,
                                                         modoRepetir, continuar, historial,
                                                         cantidadHistorial);

            // Si no cambió de canción y no está en modo repetir, avanzar automáticamente
            if (!cambiarCancion && continuar && !modoRepetir) {
                if (indiceActual < totalCanciones - 1) {
                    if (cantidadHistorial < 4) {
                        for (int i = cantidadHistorial; i > 0; i--) {
                            historial[i] = historial[i - 1];
                        }
                        historial[0] = indiceActual;
                        cantidadHistorial++;
                    }
                    indiceActual++;
                } else {
                    continuar = false;
                }
            }
        }
    }

    delete[] historial;

    if (indiceActual >= totalCanciones && continuar) {
        cout << "\n Has llegado al final de la lista de reproduccion." << endl;
    }
}

